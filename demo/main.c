#include "canvas.h"
#include "math3d.h"
#include "renderer.h"
#include "lighting.h"
#include "animation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 512
#define HEIGHT 512

int main() {
    canvas_t* canvas = canvas_create(WIDTH, HEIGHT);

    // === Task 1: Radial lines ===
    float cx = WIDTH / 2.0f;
    float cy = HEIGHT / 2.0f;
    float radius = WIDTH * 0.45f;

    for (int deg = 0; deg < 360; deg += 15) {
        float rad = deg * M_PI / 180.0f;
        float x = cx + radius * cosf(rad);
        float y = cy + radius * sinf(rad);
        draw_line_f(canvas, cx, cy, x, y, 1.5f);
    }

    canvas_save_pgm(canvas, "clock.pgm");
    
    canvas_clear(canvas);

    // === Camera/Projection Setup ===
    view_matrix = mat4_translate(0, 0, -6);
    projection_matrix = mat4_frustum_asymmetric(-1, 1, -1, 1, 1.0f, 100.0f);

    // === Task 2: Rotating Cube (Wireframe) ===
    mesh_t cube = generate_cube();
    for (int frame = 0; frame < 60; frame++) {
        float base_angle = frame *3.0f * M_PI / 180.0f;

        // Different speeds per axis
        float angle_x = base_angle * 0.7f;
        float angle_y = base_angle * 1.0f;
        float angle_z = base_angle * 1.3f;

        // Compose rotation around X, Y, Z
        world_matrix = mat4_rotate_xyz(angle_x, angle_y, angle_z);

        wireframe(canvas, cube);

        char filename[100];
        sprintf(filename, "cube_frame_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
        canvas_clear(canvas);
    }
    free_mesh(&cube);

    // === Task 3/4: Soccer Ball with Lighting/Animation ===
    mesh_t ball = generate_soccer_ball();

    light_t lights[] = {
        { .direction = vec3_normalize((vec3_t){1, -1, -1}), .intensity = 0.8f },
        { .direction = vec3_normalize((vec3_t){-1, -1, -1}), .intensity = 0.5f }
    };

    // Bezier control points
    vec3_t p0 = {0, 0, 0};
    vec3_t p1 = {2, 2, 0};
    vec3_t p2 = {-2, -2, 0};
    vec3_t p3 = {0, 0, 0};

    for (int frame = 0; frame <= 100; frame++) {
        float t = frame / 100.0f;

        vec3_t anim_pos = bezier(p0, p1, p2, p3, t);
        float base_angle = t * 2 * M_PI; // Full rotation over the animation

        float angle_x = base_angle * 0.5f;
        float angle_y = base_angle * 1.0f;
        float angle_z = base_angle * 1.2f;

        mat4_t translate = mat4_translate(anim_pos.x, anim_pos.y, anim_pos.z);
        mat4_t rotate = mat4_rotate_xyz(angle_x, angle_y, angle_z);

        // Combine translation and rotation
        world_matrix = mat4_multiply(translate, rotate);

        wireframe_lit(canvas, ball, lights, 2);

        char filename[100];
        sprintf(filename, "ball_frame_%03d.pgm", frame);
        canvas_save_pgm(canvas, filename);
        canvas_clear(canvas);
    }
    free_mesh(&ball);


    canvas_destroy(canvas);
    return 0;
}
