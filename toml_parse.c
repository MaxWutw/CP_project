#include "toml_parse.h"

void __delet_enter( char *s ) {

    if( !s ) return;
    if( s[ strlen(s) - 1 ] == '\n' ) {
        s[ strlen(s) - 1 ] = '\0';
    }
    return;
}

char* __int_to_key_format( int32_t key ) {

    int32_t n = (int32_t)log10(key) + 1;
    char *s = calloc( n+3 , sizeof(char) );
    sprintf( s , "[%d]" , key );

    return s;
}

/*
*  回傳:
*      0 : 讀到key
*     -1 : 找不到key
*/ 

int32_t __find_key( FILE *p_file , int32_t key ) {

    char buffer[132] = {0};
    char *s_key = __int_to_key_format(key);

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , s_key ) != NULL ) {
            return 0;
        }
    }
    return -1;
}

int32_t get_text( FILE *p_file , int32_t key , char **text ) {

    char buffer[256];
    char tmp[256];

    __find_key( p_file , key );

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "text" ) != NULL ) {
            break;
        }
    }
    
    strcpy( tmp , strchr( buffer , '\"') );
    *text = calloc( strlen(tmp) + 1 , sizeof(char) );
    strcpy( *text , tmp );

    return 0;
}

