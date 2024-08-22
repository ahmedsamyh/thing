#include <common.h>

Vector2 vec3_to_vec2(Vector3 v3) {
    return CLITERAL(Vector2) { v3.x, v3.y + v3.z };
}
