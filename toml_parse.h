#pragma once 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

char* __int_to_key_format( int32_t key );