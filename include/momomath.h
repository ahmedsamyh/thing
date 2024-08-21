#ifndef _MATH_H_
#define _MATH_H_

#include <raymath.h>

#ifndef PI
#   define PI (3.14159265359f)
#endif
#define TWO_PI (PI*2.f)

float deg2rad(float deg);
float rad2deg(float rad);
float randomf(float from, float to);

float map(float value, float from_min, float from_max, float to_min, float to_max);

// Raylib
Vector2 vector2_from_degrees(float deg);

#endif /* _MATH_H_ */
