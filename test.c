#include <stdio.h>
#include <stdint.h>

#include "toml_parse.h"

int main() {

    char str1[] = "{19, 20, 21}";
    char str2[] = "{ 19 , 20 , 21 }";

    int32_t option1[3];
    int32_t option2[3];

    sscanf( str1 , "{ %d , %d , %d }", &option1[0], &option1[1], &option1[2]);
    sscanf( str2 , "{ %d , %d , %d }", &option2[0], &option2[1], &option2[2]);

    for( int32_t i=0 ; i<3 ; i++ ) {
        printf("1:%d 2:%d\n", option1[i], option2[i]);
    }


    return 0;
}