#include "Algorithms/AHRS/angle_table.h"

/**
 * @brief Global table of accepted amplitude
 *
 */
float32_t ANGLES_TABLE[] = {
    30,   /* ELBOW_EXTENSION */
    10,   /* ELBOW_FLEXION */
    20,   /* SHOULDER */
    35,   /* TMP */
};

jointures_state check_jointure_angle (float32_t angle, jointures jointure)
{
  if (angle < 0)
    {
      angle *= -1;
    }

  if (angle * 0.9 <= ANGLES_TABLE[jointure])
    {
      return ACCEPTABLE;
    }
  else if (angle <= ANGLES_TABLE[jointure])
    {
      return WARNING;
    }
  return RISK;
}
