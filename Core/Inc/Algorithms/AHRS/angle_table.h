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
} typedef jointures;

/**
 * @brief List of jointure states
 *
 */
enum {
  ACCEPTABLE = 0,
  WARNING,
  RISK
} typedef jointures_state;

/**
 * @brief Global table of accepted amplitude
 *
 */
extern float32_t ANGLES_TABLE[];

jointures_state check_jointure_angle (float32_t angle, jointures jointure);

#endif /* !_ANGLE_TABLE_H */
