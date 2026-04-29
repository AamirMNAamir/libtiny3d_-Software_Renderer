#include <stdio.h>
#include "math3d.h"
#include "renderer.h"

#define WIDTH 512
#define HEIGHT 512

int main() {
    // Setup matrices for testing
    world_matrix = mat4_identity();
    view_matrix = mat4_translate(0, 0, -5);
    projection_matrix = mat4_frustum_asymmetric(-1, 1, -1, 1, 1.0f, 100.0f);

    // Test vertices (a few sample points)
    vec3_t test_points[] = {
        { .x = 0, .y = 0, .z = 0 },
        { .x = 1, .y = 1, .z = 0 },
        { .x = -1, .y = -1, .z = 0 },
        { .x = 0, .y = 0, .z = 1 },
        { .x = 10, .y = 0, .z = 0 }
    };


    int num_points = sizeof(test_points) / sizeof(test_points[0]);

    printf("Testing vertex() transformations:\n");
    for (int i = 0; i < num_points; i++) {
        vec3_t screen_pos = vertex(test_points[i]);
        printf("Local: (%.2f, %.2f, %.2f) => Screen: (%.2f, %.2f), Depth: %.2f\n",
               test_points[i].x, test_points[i].y, test_points[i].z,
               screen_pos.x, screen_pos.y, screen_pos.z);
    }

    printf("\nTesting clip_to_circular_viewport():\n");
    int test_coords[][2] = {
        {256, 256},      // center - inside
        {0, 0},          // top-left corner - outside
        {512, 512},      // bottom-right corner - outside
        {256 + 200, 256},// near edge - inside
        {256 + 230, 256} // outside radius - outside
    };

    for (int i = 0; i < 5; i++) {
        int x = test_coords[i][0];
        int y = test_coords[i][1];
        int inside = clip_to_circular_viewport(x, y);
        printf("Point (%d, %d) is %s the circular viewport.\n", x, y, inside ? "inside" : "outside");
    }

    return 0;
}
