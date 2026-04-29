// animation.c
#include "math3d.h"
#include "animation.h"


// p0 to p3: control points
vec3_t bezier(vec3_t p0, vec3_t p1, vec3_t p2, vec3_t p3, float t) {
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    vec3_t result = vec3_scale(p0, uuu);                         // (1 - t)^3 * p0
    result = vec3_add(result, vec3_scale(p1, 3 * uu * t));       // + 3(1-t)^2 * t * p1
    result = vec3_add(result, vec3_scale(p2, 3 * u * tt));       // + 3(1-t) * t^2 * p2
    result = vec3_add(result, vec3_scale(p3, ttt));              // + t^3 * p3

    return result;
}
