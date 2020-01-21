#ifndef _6_DOF_H
#define _6_DOF_H

#include "Algorithms/AHRS/angle_table.h"

// Frequency of the sensor (Hz)
#define SENSOR_FREQ                 (208)

// Timestamp between two packets (s)
#define SAMPLE_PERIOD               (1 / (float32_t)SENSOR_FREQ)

// Accelerometer sensitivity of the 6dof sensor
#define ACCELEROMETER_SENSITIVITY   (1.0)

// Gyroscope sensitivity of the 6dof sensor
#define GYROSCOPE_SENSITIVITY       (1.0)

// Gravitational constant at 16Bit
#define G                           (1.6384)

// Gravitational coefficient for the minimum boundary
#define G_COEF_MIN                  (0.5)

// Gravitational coefficient for the maximum boundary
#define G_COEF_MAX                  (2.0)

// Gyroscope coefficient for the complementary filter
#define GYR_COEF                    (0.98)

// Accelerometer coefficient for the complementary filter
#define ACC_COEF                    (1 - GYR_COEF)

/**
 * @brief Three degrees of freedom (3DOF), refers to tracking of rotational
 * motion only: pitch, yaw, and roll.
 */
typedef struct {
  float32_t pitch;    /**< Current X orientation of the 6dof (deg). */
  float32_t roll;        /**< Current Y orientation of the 6dof (deg). */
  float32_t yaw;        /**< Current Z orientation of the 6dof (deg). */
} ThreeDegreeOfFreedom_t;

/**
 * @brief Instance structure for the floating-point 6dof structure.
 */
typedef struct {
  uint16_t id;        /**< ID of the sensor. */
  struct {
    float32_t x; // X (g) of the 6dof
    float32_t y; // Y (g) of the 6dof
    float32_t z; // Z (g) of the 6dof
  } accelerometer;
  struct {
    float32_t x; // X (deg/s) of the 6dof
    float32_t y; // Y (deg/s) of the 6dof
    float32_t z; // Z (deg/s) of the 6dof
  } gyroscope;
} SensorsData_t;

/**
 * Algorithm functions
 */
JointState_t
eMovementAnalysis (SensorsData_t *pxSensorsData, Joint_t eJoint);
void vSixDegreeOfFreedomDump (SensorsData_t *pxSensorsData);

#endif /* !_6_DOF_H */
