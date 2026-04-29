#include "canvas.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

canvas_t* canvas_create(int width, int height) {
    canvas_t* c = malloc(sizeof(canvas_t));
    c->width = width;
    c->height = height;

    c->pixels = malloc(height * sizeof(float*));
    for (int i = 0; i < height; i++) {
        c->pixels[i] = calloc(width, sizeof(float));
    }

    return c;
}

void canvas_destroy(canvas_t* canvas) {
    for (int i = 0; i < canvas->height; i++) {
        free(canvas->pixels[i]);
    }
    free(canvas->pixels);
    free(canvas);
}

void set_pixel_f(canvas_t* c, float x, float y, float intensity) {
    int x0 = (int)floorf(x);
    int y0 = (int)floorf(y);
    float dx = x - x0;
    float dy = y - y0;

    for (int dy_offset = 0; dy_offset <= 1; dy_offset++) {
        for (int dx_offset = 0; dx_offset <= 1; dx_offset++) {
            int xi = x0 + dx_offset;
            int yi = y0 + dy_offset;
            if (xi >= 0 && xi < c->width && yi >= 0 && yi < c->height) {
                float weight = (1.0f - fabsf(dx_offset - dx)) * (1.0f - fabsf(dy_offset - dy));
                c->pixels[yi][xi] += intensity * weight;
                if (c->pixels[yi][xi] > 1.0f) c->pixels[yi][xi] = 1.0f;
            }
        }
    }
}

void draw_line_f(canvas_t* c, float x0, float y0, float x1, float y1, float thickness) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float len = hypotf(dx, dy);
    int steps = (int)(len * 2);

    for (int i = 0; i <= steps; i++) {
        float t = (float)i / steps;
        float x = x0 + t * dx;
        float y = y0 + t * dy;

        for (float ox = -thickness / 2; ox <= thickness / 2; ox += 0.5f) {
            for (float oy = -thickness / 2; oy <= thickness / 2; oy += 0.5f) {
                set_pixel_f(c, x + ox, y + oy, 1.0f);
            }
        }
    }
}

void canvas_clear(canvas_t* canvas) {
    for (int y = 0; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            canvas->pixels[y][x] = 0.0f;
        }
    }
}

void canvas_save_pgm(canvas_t* canvas, const char* filename) {
    FILE* f = fopen(filename, "w");
    fprintf(f, "P2\n%d %d\n255\n", canvas->width, canvas->height);
    for (int y = 0; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            int value = (int)(canvas->pixels[y][x] * 255.0f);
            fprintf(f, "%d ", value);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

