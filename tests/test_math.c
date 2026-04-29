#include <stdio.h>
#include "math3d.h"

int main() {
    // Create a vector using direct member initialization
    vec3_t v = { .x = 1.0f, .y = 0.0f, .z = 0.0f };

    // Rotate 90 degrees (pi/2 radians) around Z axis
    float angle = 3.14159265f / 2.0f;
    mat4_t rot_z = mat4_rotate_z(angle);

    vec3_t rotated = mat4_mul_vec3(rot_z, v);

    printf("Original vector: (%.3f, %.3f, %.3f)\n", v.x, v.y, v.z);
    printf("Rotated vector:  (%.3f, %.3f, %.3f)\n", rotated.x, rotated.y, rotated.z);

    // SLERP interpolation between two unit vectors a and b
    vec3_t a = vec3_normalize((vec3_t){ .x = 1.0f, .y = 0.0f, .z = 0.0f });
    vec3_t b = vec3_normalize((vec3_t){ .x = 0.0f, .y = 1.0f, .z = 0.0f });

    printf("\nSLERP between (1,0,0) and (0,1,0):\n");
    for (float t = 0; t <= 1.01f; t += 0.25f) {
        vec3_t s = vec3_slerp(a, b, t);
        printf(" t=%.2f -> (%.3f, %.3f, %.3f)\n", t, s.x, s.y, s.z);
    }

    return 0;
}
