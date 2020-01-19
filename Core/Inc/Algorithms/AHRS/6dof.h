#ifndef _6_DOF_H
#define _6_DOF_H

#include "Algorithms/AHRS/angle_table.h"

// Frequence of the sensor (Hz)
#define SENSOR_FREQ 208
// Timestamp between two packets (s)
#define SAMPLE_PERIOD 1 / (float32_t)SENSOR_FREQ
// Accelerometer sensitivity of the 6dof sensor
#define ACCELEROMETER_SENSITIVITY 1.0
// Gyroscope sensitivity of the 6dof sensor
#define GYROSCOPE_SENSITIVITY 1.0
// Gravitational constant at 16Bit
#define G 1.6384
// Gravitational coefficient for the minimum boundary
#define G_COEF_MIN 0.5
// Gravitational coefficient for the maximum boundary
#define G_COEF_MAX 2.0
// Gyroscope coefficient for the complementary filter
#define GYR_COEF 0.98
// Accelerometer coefficient for the complementary filter
#define ACC_COEF 1 - GYR_COEF

/**
 * @brief 6dof orientation.
 */
typedef struct {
  float32_t pitch;    /**< Current X orientation of the 6dof (deg). */
  float32_t roll;        /**< Current Y orientation of the 6dof (deg). */
  float32_t yaw;        /**< Current Z orientation of the 6dof (deg). */
} arm_6dof_orientation_f32;

/**
 * @brief Instance structure for the floating-point 6dof structure.
 */
typedef struct {
  uint16_t id;        /**< ID of the sensor. */
  float32_t acc_x;    /**< Accelerometer X (g) of the 6dof. */
  float32_t acc_y;    /**< Accelerometer Y (g) of the 6dof. */
  float32_t acc_z;    /**< Accelerometer Z (g) of the 6dof. */
  float32_t gyr_x;    /**< Gyroscope X (deg/s) of the 6dof. */
  float32_t gyr_y;    /**< Gyroscope Y (deg/s) of the 6dof. */
  float32_t gyr_z;    /**< Gyroscope Z (deg/s) of the 6dof. */
} arm_6dof_instance_f32;

/*
** Algoritm functions
*/

jointures_state
movement_analysis (arm_6dof_instance_f32 *dof_data, jointures jointure);
void arm_6dof_dump_f32 (arm_6dof_instance_f32 *S);

#endif /* !_6_DOF_H */
