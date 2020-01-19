#include "Algorithms/AHRS/6dof.h"
#include <math.h>

arm_6dof_orientation_f32 ORIENTATION = {
    0, 0, 0
};

void
complementary_filter (arm_6dof_instance_f32 *dof_data, float32_t *pitch, float32_t *roll, float32_t *yaw)
{
  /* Integrate the gyroscope data -> int(angularSpeed) = angle */
  *pitch += (dof_data->gyr_x / GYROSCOPE_SENSITIVITY)
            * SAMPLE_PERIOD; // Angle around the X-axis
  *roll += (dof_data->gyr_y / GYROSCOPE_SENSITIVITY)
           * SAMPLE_PERIOD; // Angle around the Y-axis
  *yaw += (dof_data->gyr_z / GYROSCOPE_SENSITIVITY)
          * SAMPLE_PERIOD; // Angle around the Z-axis

  /*
  ** Compensate for drift with accelerometer data if !bullshit
  ** Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
  */
  float32_t force_magnitude_approx =
      fabsf (dof_data->acc_x) + fabsf (dof_data->acc_y)
      + fabsf (dof_data->acc_z);
  if (force_magnitude_approx > G * G_COEF_MIN
      && force_magnitude_approx < G * G_COEF_MAX)
    {
      /* Turning around the X axis results in a vector on the Y-axis */
      float32_t pitchAcc = atan2f (dof_data->acc_y, dof_data->acc_z) * 180 / PI;
      *pitch = *pitch * 0.98 + pitchAcc * 0.02;

      /* Turning around the Y axis results in a vector on the X-axis */
      float32_t rollAcc = atan2f (dof_data->acc_x, dof_data->acc_z) * 180 / PI;
      *roll = *roll * 0.98 + rollAcc * 0.02;

      /* Turning around the Z axis results in a vector on the Z-axis (not really) */
      float32_t yawAcc = atanf (dof_data->acc_z / sqrtf (
          dof_data->acc_x * dof_data->acc_x
          + dof_data->acc_z * dof_data->acc_z)) * 180 / PI;
      *yaw = *yaw * 0.98 + yawAcc * 0.02;
    }
}

/**
 * @brief Compute global orientation with a new entry
 *
 * @param dof_data New entry
 */
jointures_state
movement_analysis (arm_6dof_instance_f32 *dof_data, jointures jointure)
{
  complementary_filter (dof_data, &ORIENTATION.pitch, &ORIENTATION.roll, &ORIENTATION.yaw);
  jointures_state s_pitch = check_jointure_angle (ORIENTATION.pitch, jointure);
  jointures_state s_roll = check_jointure_angle (ORIENTATION.roll, jointure);
  jointures_state s_yaw = check_jointure_angle (ORIENTATION.yaw, jointure);
  uint16_t state_value = s_pitch + s_roll + s_yaw;

  return state_value >= RISK ? RISK : state_value;
}
