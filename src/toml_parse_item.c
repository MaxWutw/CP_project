#include <stdio.h>
#include "toml_parse_item.h"

int32_t get_items(FILE *pFile, Item *items, int32_t *items_count){
    if(pFile == NULL) return -1;
	fseek(pFile, 0, SEEK_SET);
    char line[256];
    int in_items_section = 0;
    *items_count = 0;
    while (fgets(line, sizeof(line), pFile) != NULL) {
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

    return 1; 
}

int32_t get_npcs(FILE *pFile, Npc *npcs, int32_t *npcs_count){
    if(pFile == NULL) return -1;
	fseek(pFile, 0, SEEK_SET);
    char line[256];
    int in_npcs_section = 0;
    *npcs_count = 0;
    while (fgets(line, sizeof(line), pFile)) {
        if (strstr(line, "[npc]")) {
            in_npcs_section = 1;
            continue;
        }

        if (in_npcs_section) {
            if (line[0] == '[') {
                break; // End of [npc] section
            }

            int id;
            char name[50];
            char picture_file_name[50];
            char status_name_placeholder[50];
            int32_t status_val;
            
            if (sscanf(line, " {%d , \"%[^\"]\", \"%[^\"]\", %49[^,], %d}", &id, name, picture_file_name, status_name_placeholder, &status_val) == 5) {
                npcs[*npcs_count].id = id;
                strcpy(npcs[*npcs_count].name, name);
                strcpy(npcs[*npcs_count].picture_file_name, picture_file_name);
                if (strcmp(status_name_placeholder, "NULL") == 0) {
                    npcs[*npcs_count].status_name[0] = '\0'; // 空字串表示NULL
                } else {
                    strcpy(npcs[*npcs_count].status_name, status_name_placeholder);
                }
                npcs[*npcs_count].status_val = status_val;
                (*npcs_count)++;
            }
        }
    }

    return 1; 
}

int32_t get_player_attribute(FILE *pFile, char* stat_name, int32_t *stat_val) {
    if (pFile == NULL) return -1;

    char line[256];
    int in_player_section = 0;

    while (fgets(line, sizeof(line), pFile)) {
        if (strstr(line, "[player]")) {
            in_player_section = 1;
            continue;
        }

        if (in_player_section) {
            if (line[0] == '[') {
                break; // End of [player] section
            }

            char name[50];
            int val;

            // Check for stat.name
            if (sscanf(line, " stat.name=\"%[^\"]\"", name) == 1) {
                strcpy(stat_name, name);
            }

            // Check for stat value
            if (sscanf(line, " stat=%d", &val) == 1) {
                *stat_val = val;
            }
        }
    }

    return 1; 
}

/* test code

int main() { //for items
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

int main() { //for npcs
    FILE *file = fopen("npcs.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    Npc npcs[100];
    int32_t npcs_count;

    if (get_npcs(file, npcs, &npcs_count) == 1) {
        for (int i = 0; i < npcs_count; i++) {
            printf("ID: %d, Name: %s, Picture: %s, Status: %s, Status Value: %d\n", 
                npcs[i].id, 
                npcs[i].name, 
                npcs[i].picture_file_name, 
                npcs[i].status_name[0] == '\0' ? "NULL" : npcs[i].status_name, 
                npcs[i].status_val);
        }
    } else {
        printf("Failed to read NPCs.\n");
    }

    fclose(file);
    return 0;
}
*/