//
// Created by Ahmet Eren Kutsal on 16.07.2025.
//

#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "map.h"

#define LINE_MAX_SIZE 256

int parse_map(const char* filename, Map* map);
bool starts_with(const char* str, const char* prefix);
void trim_newline(char* str);

static void parse_tileset_data(FILE* f, Map* map);
static void parse_map_attr(FILE* f, Map* map);
static void parse_map_data(FILE* f, Map* map);
static void parse_tile_attributes(FILE* f, Map* map);
static void parse_entities(FILE* f, Map* map);

static int extract_int(const char* line, const char* prefix);
static bool extract_bool(const char* line, const char* prefix);
static void extract_str(const char* line, const char* prefix, char* out, int max_len);

#endif //MAP_PARSER_H
