#include "arm_math.h"

/**
 * @brief Get the sign of a value
 *        This function can be Inline but don't know how to adapt it to arm
 *
 * @param fValue Value to check
 * @return int8_t Get -1 if negative number, 0 if null or 1 if positive number
 */
int8_t ucSignOf (const float32_t fValue)
{
  return fValue < 0 ? -1 : fValue > 0;
}

/**
 * @brief Compute mean value of a float32_t array
 *
 * @param usLength Array length
 * @param pfArray Array
 * @return float32_t The mean value
 */
float32_t fMeanOfArray (uint16_t usLength, const float32_t *const pfArray)
{
  float32_t fSum = 0.0;

  for (uint16_t usIndex = 0; usIndex < usLength; usIndex += 1)
    {
      fSum += pfArray[usIndex];
    }
  return fSum / (float32_t)usLength;
}

/**
 * @brief Compute vector norm
 *
 * @param usLength Vector length
 * @param pfVector Vector
 * @return float32_t The norm value
 */
float32_t fVectorNorm (uint16_t usLength, const float32_t *const pfVector)
{
  float32_t fSum = 0.0;
  float32_t fNorm;

  for (uint16_t usIndex = 0; usIndex < usLength; usIndex += 1)
    {
      fSum += pfVector[usIndex] * pfVector[usIndex];
    }
  arm_sqrt_f32 (fSum, &fNorm);
  return fNorm;
}

/**
 * @brief Compute cross product between a vector a and a vector b
 *        x = a.y * b.z - a.z * b.y
 *        y = a.z * b.x - a.x * b.z
 *        z = a.x * b.y - a.y * b.x
 *
 * @param pfFirst First Vector
 * @param pfSecond Second Vector
 * @param pfOutput Output Vector
 */
void vCrossProductBetweenVectorOfThree (const float32_t *const pfFirst,
                                        const float32_t *const pfSecond,
                                        float32_t *const pfOutput)
{
  pfOutput[0] = pfFirst[1] * pfSecond[2] - pfFirst[2] * pfSecond[1];
  pfOutput[1] = pfFirst[2] * pfSecond[0] - pfFirst[0] * pfSecond[2];
  pfOutput[2] = pfFirst[0] * pfSecond[1] - pfFirst[1] * pfSecond[0];
}
