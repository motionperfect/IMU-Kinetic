#ifndef _6DOF_MATH_H
#define _6DOF_MATH_H

#include "arm_math.h"

/*
** Math functions
*/
int8_t ucSignOf (const float32_t fValue);
float32_t fMeanOfArray (uint16_t usLength, const float32_t *const pfArray);
float32_t fVectorNorm (uint16_t usLength, const float32_t *const pfVector);
void vCrossProductBetweenVectorOfThree (const float32_t *const pfFirst,
                                        const float32_t *const pfSecond,
                                        float32_t *const pfOutput);
#define ABS(X)  X < 0 ? -X : X

#endif /* !_6DOF_MATH_H */
