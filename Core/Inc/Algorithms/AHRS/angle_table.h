#ifndef _ANGLE_TABLE_H
#define _ANGLE_TABLE_H

#include "arm_math.h"

/**
 * @brief List of jointures
 *
 */
enum {
  ELBOW_EXTENSION = 0,
  ELBOW_FLEXION,
  SHOULDER,
  WRIST,
  NECK,
  BACK
} typedef Joint_t;

/**
 * @brief List of jointure states
 *
 */
enum {
  ACCEPTABLE = 0,
  WARNING,
  RISK
} typedef JointState_t;

/**
 * @brief Global table of accepted amplitude
 *
 */
extern const float32_t pfCriticalAnglesTable[];

JointState_t eCheckJointAngle (float32_t fAngle, Joint_t eJoint);

#endif /* !_ANGLE_TABLE_H */
