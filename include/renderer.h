#ifndef RENDERER_H
#define RENDERER_H

#include "canvas.h"
#include "math3d.h"
#include "lighting.h"

extern mat4_t world_matrix;
extern mat4_t view_matrix;
extern mat4_t projection_matrix;

// Edge connecting two vertex indices
typedef struct {
    int a, b;
} edge_t;

// Mesh containing vertices and edges
typedef struct {
    vec3_t *vertices;
    int vertex_count;
    int (*edges)[2];
    int edge_count;
} mesh_t;

vec3_t vertex(vec3_t local);
int clip_to_circular_viewport(int x, int y);

void wireframe(canvas_t* canvas, mesh_t mesh);
void wireframe_lit(canvas_t* canvas, mesh_t mesh, const light_t* lights, int num_lights);

mesh_t generate_cube();
mesh_t generate_soccer_ball();
void free_mesh(mesh_t* mesh);

#endif