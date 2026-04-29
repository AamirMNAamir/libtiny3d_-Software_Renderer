#ifndef MATH3D_H
#define MATH3D_H

#include <math.h>

// 3D Vector structure (Cartesian + spherical)
typedef struct {
    union {
        struct { float x, y, z; };
        struct { float r, theta, phi; }; // radius, azimuth, polar angle
    };
} vec3_t;

// 4x4 Matrix structure
typedef struct {
    float m[4][4];
} mat4_t;

// Vector operations
vec3_t vec3_new(float x, float y, float z);   
vec3_t mat4_mul_vec3(mat4_t m, vec3_t v);     
vec3_t vec3_add(vec3_t a, vec3_t b);
vec3_t vec3_scale(vec3_t v, float s);
vec3_t vec3_sub(vec3_t a, vec3_t b);
float vec3_dot(vec3_t a, vec3_t b);
vec3_t vec3_cross(vec3_t a, vec3_t b);
float vec3_length(vec3_t v);
vec3_t vec3_normalize(vec3_t v);
vec3_t vec3_normalize_fast(vec3_t v);

// Cartesian <-> Spherical conversions
vec3_t cartesian_to_spherical(vec3_t v);
vec3_t spherical_to_cartesian(vec3_t v);

// SLERP interpolation between two unit vectors a and b
vec3_t vec3_slerp(vec3_t a, vec3_t b, float t);

// Matrix operations
mat4_t mat4_identity();
mat4_t mat4_translate(float tx, float ty, float tz);
mat4_t mat4_scale(float sx, float sy, float sz);
mat4_t mat4_rotate_x(float angle_rad);
mat4_t mat4_rotate_y(float angle_rad);
mat4_t mat4_rotate_z(float angle_rad);

// Compose rotations: rotate X then Y then Z
mat4_t mat4_rotate_xyz(float angle_x, float angle_y, float angle_z);

// Matrix multiplication
mat4_t mat4_multiply(mat4_t a, mat4_t b);

// Multiply matrix * vec3 (with w=1), returns transformed vec3
vec3_t mat4_transform_vec3(mat4_t m, vec3_t v);  

// Asymmetric frustum projection matrix
mat4_t mat4_frustum_asymmetric(float left, float right, float bottom, float top, float near, float far);

// Global matrices
extern mat4_t world_matrix;
extern mat4_t view_matrix;
extern mat4_t projection_matrix;

#endif
