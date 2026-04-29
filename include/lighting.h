#ifndef LIGHTING_H
#define LIGHTING_H

#include "math3d.h"

typedef struct {
    vec3_t direction;
    float intensity;
} light_t;

float compute_lighting(vec3_t edge_dir, const light_t* lights, int num_lights);

#endif
