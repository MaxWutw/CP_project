#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_INVENTORY_SIZE 256

typedef struct {
	int32_t status_val;
	int32_t (*set_status)(int32_t val);
	int32_t (*get_status)();

	//inventory is an array of item ids, id can only be uint 
	int32_t *inventory;
	int32_t (*obtain_item)(int32_t id);
	int32_t (*check_item)(int32_t id);
	int32_t (*delete_item)(int32_t id);
} Player;


//setup a new player
Player init_player();


//set status to val
//return 0 : success
int32_t set_status(int32_t val);


//get status val
//return the status val
int32_t get_status();


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