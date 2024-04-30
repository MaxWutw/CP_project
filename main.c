#include <stdio.h>
#include <stdint.h>

#include "toml_parse.h"

#define START 6

int main() {

    FILE *p_script_file = fopen( "script.toml" , "r" );

    if( p_script_file == NULL ) {
        printf("File open error\n");
        return 0;
    }

    char *text = NULL;

    get_text( p_script_file , 6 , &text );
    puts(text);
    printf("%lu", sizeof(text));

    fclose( p_script_file );


    return 0;
}