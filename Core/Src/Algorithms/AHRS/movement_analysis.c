#include "Algorithms/AHRS/6dof.h"
#include <math.h>

static ThreeDegreeOfFreedom_t xRotation = {
    0, 0, 0
};

static void
prvTurnAroundAxe (const float32_t fY, const float32_t fX, float32_t *const pfRotation)
{
  const float32_t fArcTangent = atan2f (fY, fX) * 180 / PI;

  *pfRotation *= 0.98 + fArcTangent * 0.02;
}

static void
prvAngleAroundAxe (const float32_t fAxe, float32_t *const pfRotation)
{
  *pfRotation += (fAxe / GYROSCOPE_SENSITIVITY) * SAMPLE_PERIOD;
}

static void prvComplementaryFilter (const SensorsData_t *const pxSensorsData,
                                    float32_t *const pfPitch,
                                    float32_t *const pfRoll,
                                    float32_t *const pfYaw)
{
  /* Integrate the gyroscope data -> int(angularSpeed) = angle */
  // Angle around the X-axis
  prvAngleAroundAxe (pxSensorsData->gyroscope.x, pfPitch);

  // Angle around the Y-axis
  prvAngleAroundAxe (pxSensorsData->gyroscope.y, pfRoll);

  // Angle around the Z-axis
  prvAngleAroundAxe (pxSensorsData->gyroscope.z, pfYaw);

  /**
   * Compensate for drift with accelerometer data if !bullshit
   * Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
   */
  const float32_t fForceMagnitudeApproximation =
      fabsf (pxSensorsData->accelerometer.x) +
      fabsf (pxSensorsData->accelerometer.y) +
      fabsf (pxSensorsData->accelerometer.z);

  if (fForceMagnitudeApproximation > G * G_COEF_MIN
      && fForceMagnitudeApproximation < G * G_COEF_MAX)
    {
      /* Turning around the X axis results in a vector on the Y-axis */
      prvTurnAroundAxe (pxSensorsData->accelerometer.y, pxSensorsData->accelerometer.z, pfPitch);

      /* Turning around the Y axis results in a vector on the X-axis */
      prvTurnAroundAxe (pxSensorsData->accelerometer.x, pxSensorsData->accelerometer.z, pfRoll);

      /* Turning around the Z axis results in a vector on the Z-axis (not really) */
      /*const float32_t fAccelerometerYaw =
          atanf (pxSensorsData->accelerometer.z / sqrtf (
              powf (pxSensorsData->accelerometer.x, 2) +
              powf (pxSensorsData->accelerometer.z, 2)
          )) * 180 / PI;*/
      prvTurnAroundAxe (pxSensorsData->accelerometer.z / sqrtf (
          powf (pxSensorsData->accelerometer.x, 2) +
          powf (pxSensorsData->accelerometer.z, 2)
      ), 1, pfYaw);
    }
}

/**
 * @brief Compute global orientation with a new entry
 *
 * @param pxSensorsData New entry
 */
JointState_t eMovementAnalysis (SensorsData_t *const pxSensorsData,
                                const Joint_t eJoint)
{
  prvComplementaryFilter (pxSensorsData,
                          &xRotation.pitch,
                          &xRotation.roll,
                          &xRotation.yaw);

  JointState_t eRollState = eCheckJointAngle (xRotation.roll, eJoint);
  JointState_t ePitchState = eCheckJointAngle (xRotation.pitch, eJoint);
  JointState_t eYawState = eCheckJointAngle (xRotation.yaw, eJoint);

  uint16_t usRotationState = ePitchState + eRollState + eYawState;

  return usRotationState > WARNING ? RISK : usRotationState;
}
