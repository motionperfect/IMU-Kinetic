#include "Algorithms/AHRS/angle_table.h"

/**
 * @brief Global table of accepted amplitude
 *
 */
const float32_t pfCriticalAnglesTable[] = {
    30,   /* ELBOW_EXTENSION */
    10,   /* ELBOW_FLEXION */
    20,   /* SHOULDER */
    35,   /* TMP */
};

JointState_t eCheckJointAngle (float32_t fAngle, Joint_t eJoint)
{
  JointState_t eJointState = RISK;

  fAngle = fabsf (fAngle);
  if (fAngle * 0.9 <= pfCriticalAnglesTable[eJoint])
    {
      eJointState = ACCEPTABLE;
    }
  else if (fAngle <= pfCriticalAnglesTable[eJoint])
    {
      eJointState = WARNING;
    }
  return eJointState;
}
