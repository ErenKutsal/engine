//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#include "../../include/map/map_parser.h"
#include "../../include/renderer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool starts_with(const char* str, const char* prefix)
{
    return strncmp(str, prefix, strlen(prefix)) == 0;
}
void trim_newline(char* str)
{
    char* nl = strchr(str, '\n');
    if (nl) *nl = '\0';
}

int parse_map(const char* filename, Map* map)
{
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Failed to open map file");
        return 0;
    }

    char line[128];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (starts_with(line, "tileset"))
        {
            parse_tileset_data(f, map);
        }
        else if (starts_with(line, "map"))
        {
            parse_map_attr(f, map);
        }
        else if (starts_with(line, "tile_attributes"))
        {
            parse_tile_attributes(f, map);
        }
        else if (starts_with(line, "entities"))
        {
            parse_entities(f, map);
        }
    }

    fclose(f);
    return 1;
}

static void parse_tileset_data(FILE* f, Map* map)
{
    map->tileset = malloc(sizeof(Tileset));

    char line[LINE_MAX_SIZE];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (strchr(line, ']')) break;

        if (starts_with(line, "tileset_path"))
        {
            extract_str(line, "tileset_path =", map->tileset->filename, 64);
            map->tileset->texture = renderer_load_texture(map->tileset->filename);
        }
        else if (starts_with(line, "columns"))
        {
            map->tileset->cols = extract_int(line, "columns =");
        }
        else if (starts_with(line, "rows"))
        {
            map->tileset->rows = extract_int(line, "rows =");
        }
    }
}

static void parse_map_attr(FILE* f, Map* map)
{
    char line[LINE_MAX_SIZE];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (strchr(line, ']')) break;

        if (starts_with(line, "tile_width"))
        {
            map->tile_width = extract_int(line, "tile_width =");
        }
        else if (starts_with(line, "tile_height"))
        {
            map->tile_height = extract_int(line, "tile_height =");
        }
        else if (starts_with(line, "map_width"))
        {
            map->map_width = extract_int(line, "map_width =");
        }
        else if (starts_with(line, "map_height"))
        {
            map->map_height = extract_int(line, "map_height =");
        }
        else if (starts_with(line, "map_data"))
        {
            parse_map_data(f, map);
        }
    }
}

static void parse_map_data(FILE* f, Map* map)
{
    int size = map->map_width * map->map_height;
    map->map_data = malloc(sizeof(int) * size);
    int count = 0;

    char line[4096];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (strchr(line, '}')) break;

        char* token = strtok(line, ",");
        while (token && count < size)
        {
            map->map_data[count++] = extract_int(token, "");
            token = strtok(NULL, ",");
        }
    }
}

static void parse_tile_attributes(FILE* f, Map* map)
{
    map->tile_attributes = malloc(sizeof(TileAttribute) * TILE_ATTRIBUTES_MAX);
    map->tile_attr_count = 0;

    char line[LINE_MAX_SIZE];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (strchr(line, ']')) break;
        if (strchr(line, '{'))
        {
            TileAttribute attr = {0};
            attr.is_passable = true;
            while (fgets(line, sizeof(line), f))
            {
                if (strchr(line, '}')) break;
                if (starts_with(line, "index"))
                {
                    attr.index = extract_int(line, "index =");
                }
                else if (starts_with(line, "passable"))
                {
                    attr.is_passable = extract_bool(line, "passable =");
                }
            }
        map->tile_attributes[map->tile_attr_count++] = attr;
        }
    }
}

static void parse_entities(FILE* f, Map* map)
{
    map->entity_datas = malloc(sizeof(EntityData) * ENTITY_DATAS_MAX);
    map->entity_data_count = 0;

    char line[LINE_MAX_SIZE];
    while (fgets(line, sizeof(line), f))
    {
        trim_newline(line);
        if (strchr(line, ']')) break;
        if (strchr(line, '{'))
        {
            EntityData edata = {0};
            while (fgets(line, sizeof(line), f))
            {
                if (strchr(line, '}')) break;

                if (starts_with(line, "type"))
                {
                    extract_str(line, "type =", edata.type, 32);
                }
                else if (starts_with(line, "x"))
                {
                    edata.x = extract_int(line, "x =");
                }
                else if (starts_with(line, "y"))
                {
                    edata.y = extract_int(line, "y =");
                }
            }
            map->entity_datas[map->entity_data_count++] = edata;
        }
    }
}

static int extract_int(const char* line, const char* prefix)
{
    char* pos = strstr(line, prefix);
    if (!pos) return -1;

    pos += strlen(prefix);
    while (isspace((unsigned char) *pos)) pos++;

    char* endptr;
    const long value = strtol(pos, &endptr, 10);
    if (pos == endptr)
    {
        printf("Error extracting index\n");
        return -1;
    }

    return (int) value;
}

static bool extract_bool(const char* line, const char* prefix)
{
    char* pos = strstr(line, prefix);
    if (!pos) return false;

    pos += strlen(prefix);
    while (isspace((unsigned char) *pos)) pos++;

    if (strncmp(pos, "true", 4) == 0)
    {
        return true;
    }
    if (strncmp(pos, "false", 5) == 0)
    {
        return false;
    }
    return true;
}

static void extract_str(const char* line, const char* prefix, char* out, int max_len)
{
    char* pos = strstr(line, prefix);
    if (!pos) return;

    pos += strlen(prefix);
    while (isspace((unsigned char) *pos)) pos++;

    size_t i = 0;
    while (*pos && !isspace((unsigned char) *pos) && i < max_len - 1)
    {
        out[i++] = *pos++;
    }

    out[i] = '\0';
}





/*
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
                if (atoi(token) == 3 || atoi(token) == 2)
                {
                    tile.is_passable = false;
                }
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
*/



