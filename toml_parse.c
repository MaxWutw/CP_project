#include "toml_parse.h"

void __delet_enter( char *s ) {

    if( !s ) return;
    if( s[ strlen(s) - 1 ] == '\n' ) {
        s[ strlen(s) - 1 ] = '\0';
    }
    return;
}

void __delet_all_enter( char *s ) {

    for( int32_t i=0 ; s[i] != '\0' ; i++ ) {
        if( s[i] == '\n' ) {
            s[i] = '\0';
        }
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

int32_t get_title( FILE *p_file , int32_t key , char **title ) {

    if( !p_file || !title ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "title" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '\"') );
            __delet_all_enter(tmp);
            //可再更好
            *title = malloc( 500 );
            strcpy( *title , tmp );
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int32_t get_text( FILE *p_file , int32_t key , char **text ) {

    if( !p_file || !text ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "text" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '\"') );
            __delet_all_enter(tmp);
            //可再更好
            *text = malloc( 1000 );
            strcpy( *text , tmp );
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int32_t get_option( FILE *p_file , int32_t key , int32_t option[3] ) {

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "option" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '{') );
            __delet_all_enter(tmp);

            strcpy( *text , tmp );
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}



