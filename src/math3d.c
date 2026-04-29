#include <math.h>
#include "math3d.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Global matrices
mat4_t world_matrix;
mat4_t view_matrix;
mat4_t projection_matrix;

// Constructor
vec3_t vec3_new(float x, float y, float z) {
    vec3_t v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

// Vector operations
vec3_t vec3_add(vec3_t a, vec3_t b) {
    return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3_t vec3_scale(vec3_t v, float s) {
    return vec3_new(v.x * s, v.y * s, v.z * s);
}

vec3_t vec3_sub(vec3_t a, vec3_t b) {
    return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

float vec3_dot(vec3_t a, vec3_t b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3_t vec3_cross(vec3_t a, vec3_t b) {
    return vec3_new(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float vec3_length(vec3_t v) {
    return sqrtf(vec3_dot(v, v));
}

vec3_t vec3_normalize(vec3_t v) {
    float len = vec3_length(v);
    if (len > 0.0f) return vec3_scale(v, 1.0f / len);
    return v;
}

vec3_t vec3_normalize_fast(vec3_t v) {
    float x = vec3_dot(v, v);
    if (x == 0.0f) return v;

    union { float f; int i; } conv = { .f = x };
    conv.i = 0x5f3759df - (conv.i >> 1);
    float y = conv.f;
    y = y * (1.5f - (x * 0.5f * y * y));

    return vec3_scale(v, y);
}

// Cartesian <-> Spherical
vec3_t cartesian_to_spherical(vec3_t v) {
    float r = vec3_length(v);
    float theta = atan2f(v.y, v.x);
    if (theta < 0) theta += 2 * M_PI;
    float phi = (r > 0.0f) ? acosf(v.z / r) : 0.0f;
    return vec3_new(r, theta, phi);
}

vec3_t spherical_to_cartesian(vec3_t v) {
    float r = v.r, theta = v.theta, phi = v.phi;
    float sin_phi = sinf(phi);
    return vec3_new(
        r * cosf(theta) * sin_phi,
        r * sinf(theta) * sin_phi,
        r * cosf(phi)
    );
}

// SLERP
vec3_t vec3_slerp(vec3_t a, vec3_t b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    float dot = vec3_dot(a, b);
    dot = fmaxf(-1.0f, fminf(1.0f, dot));

    float theta = acosf(dot) * t;
    vec3_t relative = vec3_normalize(vec3_sub(b, vec3_scale(a, dot)));

    return vec3_add(
        vec3_scale(a, cosf(theta)),
        vec3_scale(relative, sinf(theta))
    );
}

// Matrix operations
mat4_t mat4_identity() {
    mat4_t m = {0};
    for (int i = 0; i < 4; i++) m.m[i][i] = 1.0f;
    return m;
}

mat4_t mat4_translate(float tx, float ty, float tz) {
    mat4_t m = mat4_identity();
    m.m[0][3] = tx;
    m.m[1][3] = ty;
    m.m[2][3] = tz;
    return m;
}

mat4_t mat4_scale(float sx, float sy, float sz) {
    mat4_t m = mat4_identity();
    m.m[0][0] = sx;
    m.m[1][1] = sy;
    m.m[2][2] = sz;
    return m;
}

mat4_t mat4_rotate_x(float angle_rad) {
    float c = cosf(angle_rad), s = sinf(angle_rad);
    mat4_t m = mat4_identity();
    m.m[1][1] = c;  m.m[1][2] = -s;
    m.m[2][1] = s;  m.m[2][2] = c;
    return m;
}

mat4_t mat4_rotate_y(float angle_rad) {
    float c = cosf(angle_rad), s = sinf(angle_rad);
    mat4_t m = mat4_identity();
    m.m[0][0] = c;  m.m[0][2] = s;
    m.m[2][0] = -s; m.m[2][2] = c;
    return m;
}

mat4_t mat4_rotate_z(float angle_rad) {
    float c = cosf(angle_rad), s = sinf(angle_rad);
    mat4_t m = mat4_identity();
    m.m[0][0] = c;  m.m[0][1] = -s;
    m.m[1][0] = s;  m.m[1][1] = c;
    return m;
}

mat4_t mat4_rotate_xyz(float x, float y, float z) {
    return mat4_multiply(
        mat4_multiply(mat4_rotate_x(x), mat4_rotate_y(y)),
        mat4_rotate_z(z)
    );
}

mat4_t mat4_multiply(mat4_t a, mat4_t b) {
    mat4_t r = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                r.m[i][j] += a.m[i][k] * b.m[k][j];
    return r;
}

vec3_t mat4_mul_vec3(mat4_t m, vec3_t v) {
    float x = m.m[0][0]*v.x + m.m[0][1]*v.y + m.m[0][2]*v.z + m.m[0][3];
    float y = m.m[1][0]*v.x + m.m[1][1]*v.y + m.m[1][2]*v.z + m.m[1][3];
    float z = m.m[2][0]*v.x + m.m[2][1]*v.y + m.m[2][2]*v.z + m.m[2][3];
    float w = m.m[3][0]*v.x + m.m[3][1]*v.y + m.m[3][2]*v.z + m.m[3][3];

    if (w != 0.0f) {
        x /= w; y /= w; z /= w;
    }

    return vec3_new(x, y, z);
}

mat4_t mat4_frustum_asymmetric(float l, float r, float b, float t, float n, float f) {
    mat4_t m = {0};
    m.m[0][0] = 2 * n / (r - l);
    m.m[1][1] = 2 * n / (t - b);
    m.m[0][2] = (r + l) / (r - l);
    m.m[1][2] = (t + b) / (t - b);
    m.m[2][2] = -(f + n) / (f - n);
    m.m[2][3] = -2 * f * n / (f - n);
    m.m[3][2] = -1.0f;
    return m;
}
