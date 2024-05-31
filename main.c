#include <stdio.h>
#include <stdint.h>

#include "toml_parse.h"

void print_choose( FILE *p_file , int32_t option[3] ) {

    char *title = NULL;

    if( option[0] != 0 ) {
        get_title( p_file , option[0] , &title );
        printf("1.%s\n", title );
    }
    if( option[1] != 0 ) {
        get_title( p_file , option[1] , &title );
        printf("2.%s\n", title );
    }
    if( option[2] != 0 ) {
        get_title( p_file , option[2] , &title );
        printf("3.%s\n", title );
    }

    return;
}

void get_choose( int32_t *key , int32_t option[3]) {
    printf("你的選擇： ");
    scanf("%d", key);
    *key = option[*key-1];

    return;
}


int main() {

    // system("clear");

    // FILE *p_script_file = fopen( "script.toml" , "r" );

    // if( p_script_file == NULL ) {
    //     printf("File open error\n");
    //     return 0;
    // }

    // int32_t key = 0;
    // char *text = NULL;
    // int32_t option[3] = {0};

    // get_text( p_script_file , START , &text );
    // puts(text);
    // get_option( p_script_file , START , option );
    // print_choose( p_script_file , option );
    // get_choose( &key , option );

    // while(1) {

    //     free(text);
    //     option[0] = 0;
    //     option[1] = 0;
    //     option[2] = 0;

    //     system("clear");
    //     get_text( p_script_file , key , &text );
    //     puts(text);
    //     get_option( p_script_file , key , option );

    //     if( option[0] == 0 && 
    //         option[1] == 0 &&
    //         option[2] == 0    ) 
    //     {
    //         break;
    //     }

    //     print_choose( p_script_file , option );
    //     get_choose( &key , option );
    // }    

    // char str1[100];
    // char *str2 = "hello";

    // str1 = "hello";
    // // str2[0] = 'c';
    // puts(str1);

    return 0;
}