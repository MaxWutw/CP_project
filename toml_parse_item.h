#pragma once 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
	int32_t id;
	char name[50];
	char picture_file_name[50];
} Item;

//get all items in toml, put them into *items
//please remember to open MAX_ITEMS array for items
//no need to free/malloc anything
//see toml_parse_item.c for test code
int32_t get_items(FILE *pFile, Item *items, int32_t *items_count);