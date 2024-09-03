#ifndef __CONFIG_H__
#define __CONFIG_H__

#define WIDTH 1280
#define HEIGHT 720
#define TILE_SIZE 16
#define CHUNK_SIZE (TILE_SIZE*16)
#define COLS (WIDTH/TILE_SIZE)
#define ROWS (HEIGHT/TILE_SIZE)

#define DEBUG_TEXT(str, x, font_size, color) DrawText(str, x, y, font_size, WHITE); y+=font_size

#endif // __CONFIG_H__
