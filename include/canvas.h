#ifndef CANVAS_H
#define CANVAS_H

typedef struct {
    int width, height; //width and height of the canvas
    float** pixels; // 2D array: pixels[y][x] in range [0.0, 1.0]
} canvas_t;

canvas_t* canvas_create(int width, int height);

void canvas_destroy(canvas_t* canvas);

void set_pixel_f(canvas_t* canvas, float x, float y, float intensity); 
void draw_line_f(canvas_t* canvas, float x0, float y0, float x1, float y1, float thickness);

void canvas_clear(canvas_t* canvas);
void canvas_save_pgm(canvas_t* canvas, const char* filename);

#endif
