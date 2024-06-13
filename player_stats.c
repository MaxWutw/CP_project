#include "player_stats.h"

static int32_t player_status = 0;
static int32_t player_inventory[MAX_INVENTORY_SIZE] = {0};
static char player_name[MAX_NAME_SIZE] = {0};

Player init_player(){
	player_status = 0;
	memset(player_inventory,-1,sizeof(int32_t)*MAX_INVENTORY_SIZE);
	memset(player_name,0,sizeof(char)*MAX_NAME_SIZE);
	Player player = {player_status,player_name,set_player_name,get_player_name,set_player_status,get_player_status,player_inventory,obtain_item,check_item,delete_item};
	return player;
}

//set player's name
//return 0 : success
//return 1 : failed
int32_t set_player_name(char *name){
	strncpy(player_name,name,strlen(name));
	return 0;
}

//get player's name
//return the player's name
//return NULL if name is NULL
char *get_player_name(){
	return player_name;
}

int32_t set_player_status(int32_t val){
	player_status = val;
	return 0;
}
int32_t get_player_status(){
	return player_status;
}

int32_t obtain_item(int32_t id){
	for(int32_t i=0; i<MAX_INVENTORY_SIZE; i++){
		if(player_inventory[i] == id) return 1;
		if(player_inventory[i] == -1) {
			player_inventory[i] = id;
			return 0;
		}
	}
	return -1;
}

int32_t check_item(int32_t id){
	for(int32_t i=0; i<MAX_INVENTORY_SIZE; i++){
		if(player_inventory[i] == id) return 1;
	}
	return 0;
}

int32_t delete_item(int32_t id){
	for(int32_t i=0; i<MAX_INVENTORY_SIZE; i++){
		if(player_inventory[i] == id){
			player_inventory[i] = -1;
			return 0;
		}
	}
	return 1;
}

// Npc init_npc(){
// 	Npc npc = {0, set_npc_status, add_npc_status, get_npc_status};
// 	return npc;
// }


// int32_t set_npc_status(Npc *npc, int32_t val){
// 	npc->status_val = val;
// 	return 0;
// }


// int32_t add_npc_status(Npc *npc, int32_t val){
// 	npc->status_val += val;
// 	return 0;
// }


// int32_t get_npc_status(Npc *npc){
// 	return npc->status_val;
// }