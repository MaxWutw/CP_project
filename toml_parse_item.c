#include "toml_parse_item.h"

int32_t get_items(FILE *pFile, Item *items, int32_t *items_count){
    if(pFile==NULL)return -1;

    char line[256];
	int in_items_section = 0;
	*items_count = 0;

	while (fgets(line, sizeof(line), pFile)) {
		if (strstr(line, "[item]")) {
			in_items_section = 1;
			continue;
		}

		if (in_items_section) {
			if (line[0] == '[') {
				break; // End of [item] section
			}

			int id;
			char name[50];
			char picture_file_name[50];

			if (sscanf(line, " {%d , \"%[^\"]\", \"%[^\"]\"},", &id, name, picture_file_name) == 3) {
				items[*items_count].id = id;
				strcpy(items[*items_count].name, name);
				strcpy(items[*items_count].picture_file_name, picture_file_name);
				(*items_count)++;
			}
		}
	}
}

/* test code

int main() {
	Item items[MAX_ITEMS];
	int num_items = 0;
	FILE *file = fopen("debug.toml", "r");
	read_items(file, items, &num_items);

	for (int i = 0; i < num_items; i++) {
		printf("Item %d: id=%d, name=%s, picture_file_name=%s\n", 
			   i, items[i].id, items[i].name, items[i].picture_file_name);
	}

	fclose(file);
	return 0;
}

*/