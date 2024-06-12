#pragma once 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "backpack.h"

#define START 1

/* 
 *    範例：
 *        [1]   
 *        title = "出生"
 *        text = "選擇出生，幫她選個家庭"
 *        item = "#33"
 *        option = { 2 , 3 , 4 }
 *        #註解
 *        
 *        #數字我取名叫key
 */

//------------------------------------------------------------------
/* const char *get_name( FILE *p_file )
 * 
 *  介紹:
 *      拿 toml 的 name , 函式直接回傳
 * 
 *  輸入:
 *      file 的 pointer
 *
 *  回傳:
 *      toml的名稱 （唯讀的字串）
 *      NULL       (p_file 是空指標)     
 * 
 */ 
const char *get_name( FILE *p_file );

//------------------------------------------------------------------
/* int32_t get_title( FILE *p_file , int32_t key , char **title )
 *
 *  介紹: 
 *      拿 指定 key 裡的 title , 會存在*title
 * 
 *  注意: 
 *      free is your own business!!!
 * 
 *  輸入:
 *      1 . file 的 pointer
 *      2 . 要找的title所在的key
 *      3 . 一個空的 ＆char* (我會幫你allocate)
 * 
 *  回傳:
 *      0 : 拿到title
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到title
 *      3 : 其他
 */ 
int32_t get_title( FILE *p_file , int32_t key , char **title );

//------------------------------------------------------------------
/* int32_t get_text( FILE *p_file , int32_t key , char **text )
 *
 *  介紹: 
 *      拿 指定 key 裡的 text , 會存在*text
 * 
 *  注意: 
 *      free is your own business!!!
 * 
 *  輸入:
 *      1 . file 的 pointer
 *      2 . 要找的text所在的key
 *      3 . 一個空的 ＆char* (我會幫你allocate)
 *
 *  回傳:
 *      0 : 拿到text
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到text
 *      3 : 其他
 */ 
int32_t get_text( FILE *p_file , int32_t key , char **text );

//------------------------------------------------------------------
/* get_option( FILE *p_file , int32_t key , int32_t option[3] )
 *
 *  介紹: 
 *      拿 指定 key 裡的 option , 存在option[3]裡
 * 
 *  輸入:
 *      1 . file 的 pointer
 *      2 . 要找的option所在的key
 *      3 . 一個大小為3的int32_t陣列 (用來存opiton)
 *
 *
 *  回傳:
 *      0 : 拿到option
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到option
 *      3 : 其他
 */ 
int32_t get_option( FILE *p_file , int32_t key , int32_t option[3] );

//------------------------------------------------------------------
/* get_add_inventory( FILE *p_file , int32_t key , sBackPack *backpack , Item *items)
 *
 *  介紹: 
 *      拿 指定 key 裡的 option , 存在option[3]裡
 * 
 *  輸入:
 *      1 . file 的 pointer
 *      2 . 要找的option所在的key
 *      3 . 玩家背包的指標
 * 		4 . 劇本中的items[MAX_ITEMS]
 *
 *
 *  回傳:
 *      0 : 找到指定物品，成功放入背包
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到player.inventory.add
 *      3 : 其他
 */ 
int32_t get_add_inventory( FILE *p_file , int32_t key , sBackPack *backpack , Item *items);
