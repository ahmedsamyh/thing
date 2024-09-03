#ifndef _MATH_H_
#define _MATH_H_

#include <raymath.h>
#include <commonlib.h>

#ifndef PI
#   define PI (3.14159265359f)
#endif
#ifndef TWO_PI
#   define TWO_PI (PI*2.f)
#endif

float deg2rad(float deg);
float rad2deg(float rad);
float randomf(float from, float to);
uint8 randomu8(uint8 from, uint8 to);

float map(float value, float from_min, float from_max, float to_min, float to_max);

// Raylib
Vector2 vector2_from_radians(float rad);
Vector2 vector2_from_degrees(float deg);
float vector2_radians(Vector2 v);
float vector2_degrees(Vector2 v);

#endif /* _MATH_H_ */
