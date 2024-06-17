#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INVENTORY_SIZE 256
#define MAX_NAME_SIZE 512

//this is a player structure
typedef struct {
	int32_t status_val;
	char *player_name;
	int32_t (*set_player_name)(char *name);
	char *(*get_player_name)();
	int32_t (*set_player_status)(int32_t val);
	int32_t (*get_player_status)();

	//inventory is an array of item ids, id can only be uint 
	int32_t *inventory;
	int32_t (*obtain_item)(int32_t id);
	int32_t (*check_item)(int32_t id);
	int32_t (*delete_item)(int32_t id);
} Player;


//setup a new player
Player init_player();

//set player's name
//return 0 : success
//return 1 : failed
int32_t set_player_name(char *name);


//get player's name
//return the player's name
//return NULL if name is NULL
char *get_player_name();

//set status to val
//return 0 : success
int32_t set_player_status(int32_t val);


//get status val
//return the status val
int32_t get_player_status();


//add an item into player's inventory
//return 0 : success
//return 1 : the item already exist
//return -1: the inventory is full
int32_t obtain_item(int32_t id);


//check an item whether exist in player's inventory or not
//return 0 : no item found
//return 1 : yes item found
int32_t check_item(int32_t id);


//delete a item from player's inventory
//return 0 : delete success
//return 1: no item found
int32_t delete_item(int32_t id);


//-----------------------------------------------------------------

// //this is a npc structure
// typedef struct Npc Npc;
// struct Npc{
// 	int32_t id;
// 	int32_t status_val;
// 	int32_t (*set_npc_status)(Npc *npc, int32_t val);
// 	int32_t (*add_npc_status)(Npc *npc, int32_t val);
// 	int32_t (*get_npc_status)(Npc *npc);
// };


// //setup a new npc
// Npc init_npc();


// //given npc, val
// //set npc's status to val
// //return 0 : success
// int32_t set_npc_status(Npc *npc, int32_t val);



// //given npc, val
// //add npc's status with val
// //return 0: success
// int32_t add_npc_status(Npc *npc, int32_t val);


// //given npc
// //return the npc's status val
// int32_t get_npc_status(Npc *npc);