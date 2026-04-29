#include "renderer.h"
#include "math3d.h"
#include "lighting.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hardcoded OBJ data as multiline string
static const char *soccer_obj_data =
"v 0.0 0.0 1.021\n"
"v 0.4035482 0.0 0.9378643\n"
"v -0.2274644 0.3333333 0.9378643\n"
"v -0.1471226 -0.375774 0.9378643\n"
"v 0.579632 0.3333333 0.7715933\n"
"v 0.5058321 -0.375774 0.8033483\n"
"v -0.6020514 0.2908927 0.7715933\n"
"v -0.05138057 0.6666667 0.7715933\n"
"v 0.1654988 -0.6080151 0.8033483\n"
"v -0.5217096 -0.4182147 0.7715933\n"
"v 0.8579998 0.2908927 0.4708062\n"
"v 0.3521676 0.6666667 0.6884578\n"
"v 0.7841999 -0.4182147 0.5025612\n"
"v -0.657475 0.5979962 0.5025612\n"
"v -0.749174 -0.08488134 0.6884578\n"
"v -0.3171418 0.8302373 0.5025612\n"
"v 0.1035333 -0.8826969 0.5025612\n"
"v -0.5836751 -0.6928964 0.4708062\n"
"v 0.8025761 0.5979962 0.2017741\n"
"v 0.9602837 -0.08488134 0.3362902\n"
"v 0.4899547 0.8302373 0.3362902\n"
"v 0.7222343 -0.6928964 0.2017741\n"
"v -0.8600213 0.5293258 0.1503935\n"
"v -0.9517203 -0.1535518 0.3362902\n"
"v -0.1793548 0.993808 0.1503935\n"
"v 0.381901 -0.9251375 0.2017741\n"
"v -0.2710537 -0.9251375 0.3362902\n"
"v -0.8494363 -0.5293258 0.2017741\n"
"v 0.8494363 0.5293258 -0.2017741\n"
"v 1.007144 -0.1535518 -0.06725804\n"
"v 0.2241935 0.993808 0.06725804\n"
"v 0.8600213 -0.5293258 -0.1503935\n"
"v -0.7222343 0.6928964 -0.2017741\n"
"v -1.007144 0.1535518 0.06725804\n"
"v -0.381901 0.9251375 -0.2017741\n"
"v 0.1793548 -0.993808 -0.1503935\n"
"v -0.2241935 -0.993808 -0.06725804\n"
"v -0.8025761 -0.5979962 -0.2017741\n"
"v 0.5836751 0.6928964 -0.4708062\n"
"v 0.9517203 0.1535518 -0.3362902\n"
"v 0.2710537 0.9251375 -0.3362902\n"
"v 0.657475 -0.5979962 -0.5025612\n"
"v -0.7841999 0.4182147 -0.5025612\n"
"v -0.9602837 0.08488134 -0.3362902\n"
"v -0.1035333 0.8826969 -0.5025612\n"
"v 0.3171418 -0.8302373 -0.5025612\n"
"v -0.4899547 -0.8302373 -0.3362902\n"
"v -0.8579998 -0.2908927 -0.4708062\n"
"v 0.5217096 0.4182147 -0.7715933\n"
"v 0.749174 0.08488134 -0.6884578\n"
"v 0.6020514 -0.2908927 -0.7715933\n"
"v -0.5058321 0.375774 -0.8033483\n"
"v -0.1654988 0.6080151 -0.8033483\n"
"v 0.05138057 -0.6666667 -0.7715933\n"
"v -0.3521676 -0.6666667 -0.6884578\n"
"v -0.579632 -0.3333333 -0.7715933\n"
"v 0.1471226 0.375774 -0.9378643\n"
"v 0.2274644 -0.3333333 -0.9378643\n"
"v -0.4035482 0.0 -0.9378643\n"
"v 0.0 0.0 -1.021\n"
"f 1 4 9 6 2\n"
"f 3 8 16 14 7\n"
"f 5 11 19 21 12\n"
"f 10 15 24 28 18\n"
"f 13 22 32 30 20\n"
"f 17 27 37 36 26\n"
"f 23 33 43 44 34\n"
"f 25 31 41 45 35\n"
"f 29 40 50 49 39\n"
"f 38 48 56 55 47\n"
"f 42 46 54 58 51\n"
"f 52 53 57 60 59\n"
"f 1 2 5 12 8 3\n"
"f 1 3 7 15 10 4\n"
"f 2 6 13 20 11 5\n"
"f 4 10 18 27 17 9\n"
"f 6 9 17 26 22 13\n"
"f 7 14 23 34 24 15\n"
"f 8 12 21 31 25 16\n"
"f 11 20 30 40 29 19\n"
"f 14 16 25 35 33 23\n"
"f 18 28 38 47 37 27\n"
"f 19 29 39 41 31 21\n"
"f 22 26 36 46 42 32\n"
"f 24 34 44 48 38 28\n"
"f 30 32 42 51 50 40\n"
"f 33 35 45 53 52 43\n"
"f 36 37 47 55 54 46\n"
"f 39 49 57 53 45 41\n"
"f 43 52 59 56 48 44\n"
"f 49 50 51 58 60 57\n"
"f 54 55 56 59 60 58\n";

// === Parse a line starting with "v " to extract vertex coordinates
static void parse_vertex_line(const char *line, vec3_t *vertex) {
    sscanf(line, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
}

// === Parse a face line "f ..." and extract vertex indices
static int parse_face_indices(const char *line, int *indices, int max_indices) {
    int count = 0;
    const char *p = line + 2; // skip 'f '
    char *token;
    char buf[256];
    strncpy(buf, p, sizeof(buf));
    buf[sizeof(buf)-1] = 0;
    token = strtok(buf, " ");
    while (token && count < max_indices) {
        sscanf(token, "%d", &indices[count++]);
        token = strtok(NULL, " ");
    }
    return count;
}

// === Soccer ball mesh generation from embedded string data ===
mesh_t generate_soccer_ball() {
    float scale = 2.0f;  // Scale factor to increase or decrease size

    vec3_t *vertices = malloc(1000 * sizeof(vec3_t));
    int (*edges)[2] = malloc(2000 * sizeof(int[2]));
    int vertex_count = 0;
    int edge_count = 0;

    char line[256];
    const char *data_ptr = soccer_obj_data;
    while (*data_ptr) {
        // read one line into line[]
        int i = 0;
        while (*data_ptr && *data_ptr != '\n' && i < (int)(sizeof(line) - 1)) {
            line[i++] = *data_ptr++;
        }
        if (*data_ptr == '\n') data_ptr++;
        line[i] = 0;

        if (line[0] == 'v' && line[1] == ' ') {
            // parse vertex
            vec3_t v;
            parse_vertex_line(line, &v);

            // apply scaling here
            v.x *= scale;
            v.y *= scale;
            v.z *= scale;

            vertices[vertex_count++] = v;
        }
        else if (line[0] == 'f') {
            int indices[10], count = parse_face_indices(line, indices, 10);
            for (int i = 0; i < count; i++) {
                int a = indices[i] - 1;
                int b = indices[(i + 1) % count] - 1;
                // check duplicate edge
                int duplicate = 0;
                for (int e = 0; e < edge_count; e++) {
                    if ((edges[e][0] == a && edges[e][1] == b) ||
                        (edges[e][0] == b && edges[e][1] == a)) {
                        duplicate = 1;
                        break;
                    }
                }
                if (!duplicate) {
                    edges[edge_count][0] = a;
                    edges[edge_count][1] = b;
                    edge_count++;
                }
            }
        }
    }

    mesh_t m;
    m.vertex_count = vertex_count;
    m.vertices = malloc(vertex_count * sizeof(vec3_t));
    memcpy(m.vertices, vertices, vertex_count * sizeof(vec3_t));
    free(vertices);

    m.edge_count = edge_count;
    m.edges = malloc(edge_count * sizeof(int[2]));
    memcpy(m.edges, edges, edge_count * sizeof(int[2]));
    free(edges);

    return m;
}

// === Simple cube (for testing) ===
mesh_t generate_cube() {
    vec3_t cube_vertices[] = {
        {-1, -1, -1}, {1, -1, -1}, {1,  1, -1}, {-1,  1, -1},
        {-1, -1,  1}, {1, -1,  1}, {1,  1,  1}, {-1,  1,  1}
    };

    int cube_edges[12][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0},
        {4, 5}, {5, 6}, {6, 7}, {7, 4},
        {0, 4}, {1, 5}, {2, 6}, {3, 7}
    };

    mesh_t m;
    m.vertex_count = 8;
    m.vertices = malloc(8 * sizeof(vec3_t));
    memcpy(m.vertices, cube_vertices, 8 * sizeof(vec3_t));

    m.edge_count = 12;
    m.edges = malloc(12 * sizeof(int[2]));
    memcpy(m.edges, cube_edges, 12 * sizeof(int[2]));

    return m;
}

// === Free a mesh ===
void free_mesh(mesh_t *m) {
    free(m->vertices);
    free(m->edges);
}

// === Project 3D vertex to 2D screen ===
static vec3_t project(vec3_t v) {
    vec3_t world = mat4_mul_vec3(world_matrix, v);
    vec3_t view  = mat4_mul_vec3(view_matrix, world);
    vec3_t proj  = mat4_mul_vec3(projection_matrix, view);

    float x = (proj.x + 1.0f) * 0.5f * 512;
    float y = (1.0f - proj.y) * 0.5f * 512;
    return (vec3_t){x, y, proj.z};
}

// === Draw wireframe ===
void wireframe(canvas_t *canvas, mesh_t m) {
    for (int i = 0; i < m.edge_count; i++) {
        vec3_t p1 = project(m.vertices[m.edges[i][0]]);
        vec3_t p2 = project(m.vertices[m.edges[i][1]]);
        draw_line_f(canvas, p1.x, p1.y, p2.x, p2.y, 1.0f);
    }
}

// === Draw wireframe with lighting ===
void wireframe_lit(canvas_t *canvas, mesh_t m, const light_t *lights, int num_lights) {
    for (int i = 0; i < m.edge_count; i++) {
        vec3_t v1 = m.vertices[m.edges[i][0]];
        vec3_t v2 = m.vertices[m.edges[i][1]];

        vec3_t edge = {
            v2.x - v1.x,
            v2.y - v1.y,
            v2.z - v1.z
        };
        vec3_t normal = vec3_normalize(edge);
        float intensity = compute_lighting(normal, lights, num_lights);

        vec3_t p1 = project(v1);
        vec3_t p2 = project(v2);
        draw_line_f(canvas, p1.x, p1.y, p2.x, p2.y, intensity);
    }
}
