#include "lighting.h"
#include "math3d.h"

float compute_lighting(vec3_t edge_dir, const light_t* lights, int num_lights) {
    float total = 0.0f;
    vec3_t norm_edge_dir = vec3_normalize(edge_dir);

    for (int i = 0; i < num_lights; ++i) {
        vec3_t norm_light_dir = vec3_normalize(lights[i].direction);
        float dot_val = vec3_dot(norm_edge_dir, norm_light_dir);
        if (dot_val > 0.0f) {
            total += dot_val * lights[i].intensity;
        }
    }

    return (total > 1.0f) ? 1.0f : total;
}
