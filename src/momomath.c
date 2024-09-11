#include <momomath.h>
#include <stdlib.h>

float deg2rad(float deg){
  return (deg / 360.f)*TWO_PI;
}

float rad2deg(float rad){
 return (rad / TWO_PI)*360.f;
}

float randomf(float from, float to) {
  float rn = (float)rand() / (float)RAND_MAX;
  return from + (rn * (to - from));
}

int randomi(int from, int to) {
  float rn = (float)rand() / (float)RAND_MAX;
  return from + (rn * (to - from));
}

uint8 randomu8(uint8 from, uint8 to) {
    float rn = ((float)rand() / (float)RAND_MAX);
    return (uint8)(from + (rn * (to - from)));
}

float map(float value, float from_min, float from_max, float to_min, float to_max) {
  return to_min + ((to_max - to_min) / (from_max - from_min)) * (value - from_min);
}

// Raylib
Vector2 vector2_from_radians(float rad) {
    Vector2 result = {
        .x = cosf(rad),
        .y = sinf(rad),
    };
    return result;
}

Vector2 vector2_from_degrees(float deg) {
    Vector2 result = {
        .x = cosf(DEG2RAD * deg),
        .y = sinf(DEG2RAD * deg),
    };
    return result;
}

float vector2_radians(Vector2 v) {
    return atan2f(v.y, v.x);
}

float vector2_degrees(Vector2 v) {
    return RAD2DEG*vector2_radians(v);
}

