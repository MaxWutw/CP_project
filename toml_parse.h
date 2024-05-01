#pragma once 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define START 6

/* 
 *    範例：
 *        [6]   
 *        title = "出生"
 *        text = "選擇出生，幫她選個家庭"
 *        option = { 7 , 8 , 9 }
 *        #註解
 *        
 *        #數字我取名叫key
 */
//------------------------------------------------------------------
/*
 *  回傳:
 *      0 : 拿到title
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到title
 *      3 : 其他
 */ 
int32_t get_title( FILE *p_file , int32_t key , char **title );

/*
 *  回傳:
 *      0 : 拿到text
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到text
 *      3 : 其他
 */ 
int32_t get_text( FILE *p_file , int32_t key , char **text );


/*
 *  回傳:
 *      0 : 拿到option
 *     -1 : 輸入空指標
 *      1 : 找不到[key]
 *      2 : 在[key]裡找不到option
 *      3 : 其他
 */ 
int32_t get_option( FILE *p_file , int32_t key , int32_t option[3] );

