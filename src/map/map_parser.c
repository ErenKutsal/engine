//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#include "../../include/map/map_parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/renderer.h"

Map* parse_map(char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    Map* map;
    char* tileset_filename;
    int tileset_cols;
    int tileset_rows;
    int tile_size;
    int map_width = 0;
    int map_height = 0;

    char line[MAX_LINE_LENGTH];
    char* delimeter = " \n";
    int line_count = 1;
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("line %d: %s\n", line_count, line);
        char* token = strtok(line, delimeter);
        int token_count = 1;
        while (token != NULL)
        {
            if (line_count == 2)
            {
                if (token_count == 3) tileset_filename = strdup(token);
            } else if (line_count == 3)
            {
                if (token_count == 3) tileset_cols = atoi(token);
            } else if (line_count == 4)
            {
                if (token_count == 3) tileset_rows = atoi(token);
            } else if (line_count == 5)
            {
                if (token_count == 3) tile_size = atoi(token);
            } else if (line_count == 8)
            {
                if (token_count == 3) map_width = atoi(token);
            } else if (line_count == 9)
            {
                if (token_count == 3)
                {
                    map_height = atoi(token);

                    Tileset* p_tileset = (Tileset*)malloc(sizeof(Tileset));
                    if (!p_tileset) {
                        perror("Failed to allocate memory for tileset");
                        fclose(file);
                        return NULL;
                    }

                    // Fill the dynamically allocated Tileset
                    p_tileset->filename = tileset_filename; // Point to the copied filename
                    p_tileset->cols = tileset_cols;
                    p_tileset->rows = tileset_rows;
                    p_tileset->tile_size = tile_size;
                    p_tileset->texture = renderer_load_texture(tileset_filename);

                    map = map_create(map_width, map_height, p_tileset);
                    map->tileset = p_tileset;
                    printf("map created.\n");
                }
            }

            if (line_count >= 11 && line_count <= 11 + map_height - 1)
            {
                int x = token_count - 1;
                int y = line_count - 11;
                Tile tile = (Tile) {atoi(token), tile_size, true};
                map_set_tile(map, tile, x, y);
                printf("tile set. x: %d, y: %d, index: %d\n", x, y, atoi(token));
            }
            token = strtok(NULL, delimeter);
            token_count++;
        }
        line_count++;
    }
    fclose(file);
    return map;
}


