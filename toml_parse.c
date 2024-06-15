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

    fseek( p_file , 0 , SEEK_SET );

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , s_key ) != NULL ) {
            if(s_key != NULL) free(s_key);
            return 0;
        }
    }
    if(s_key != NULL) free(s_key);
    return -1;
}

const char *get_name( FILE *p_file ) {

    if( !p_file ) return NULL;
    
    char buffer[256] = {0};
    char *p = NULL;

    while( fgets( buffer , sizeof(buffer) , p_file ) ) {
        if( ( p = strstr( buffer , "name" ) ) != NULL ) {
            break;
        }
    }

    __delet_all_enter( p );
    p = strchr( p , '\"' ) + 1;
    if( p[ strlen(p) - 1 ] == '\"' ) {
        p[ strlen(p) - 1 ] = '\0';
    }

    return (const char*)p;
}

int32_t get_title( FILE *p_file , int32_t key , char **title ) {

    if( !p_file || !title ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "title" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '\"') + 1 ); //加1移除第一個雙引號
            __delet_all_enter(tmp);
            //可再更好
            *title = malloc( 500 );
            //刪除後面雙引號
            char *p = strchr( tmp , '"');
            *p = '\0';

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

    char buffer[1024];
    char tmp[1024];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "text" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '\"') + 1 );
            __delet_all_enter(tmp);
            //刪除後面雙引號
            char *p = strchr( tmp , '"');
            *p = '\0';
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
            sscanf( tmp , "{ %d , %d , %d }", &option[0] , &option[1] , &option[2] );
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int32_t get_add_inventory( FILE *p_file , int32_t key , sBackPack *backpack , Item *items){

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];
    int32_t add_flag = 0;

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "player.inventory.add" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '=') );
            int32_t item_id=0;
            sscanf( tmp , "=%d", &item_id);
            printf("obtain item %d, name: %s\n", item_id, items[item_id-1].name);
            AddItemToBackpack(backpack, &items[item_id-1]);
            add_flag = 1;
            continue;
            //return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            if(add_flag) return 0;
            else return 2;
        }
    }
    return 3;
}

int32_t get_npc_showup( FILE *p_file , int32_t key , Npc *npcs, SDL_Renderer *renderer, SDL_DisplayMode *DM){

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "npc" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '=') );
            int32_t npc_id=0;
            sscanf( tmp , "=%d", &npc_id);
            printf("npc%d", npc_id);
            fflush(stdin);
            
            if( npc_id == 1 ) {
                renderCharacter2(renderer, DM, "img/bad-man.png" , (DM -> w)/1.8 , (DM -> h)/8 , 250 , 400 );
            } else if( npc_id == 1 ) {
                renderCharacter2(renderer, DM, "img/bad-man.png" , (DM -> w)/1.8 , (DM -> h)/8 , 250 , 400 );
            } else if(npc_id == 1 ) {
                renderCharacter2(renderer, DM, "img/bad-man.png" , (DM -> w)/1.8 , (DM -> h)/8 , 250 , 400 );
            }
            
            //printf("NPC %d show up, name: %s\n", npc_id, npcs[npc_id-1].name);
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    
    return 3;
}

int32_t get_player_stat( FILE *p_file , int32_t key , int32_t *return_val){

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "player.stat" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '=') );
            sscanf( tmp , "=%d", return_val);
            // renderCharacter(renderer, DM, "img/street_fighter.png");
            //printf("NPC %d show up, name: %s\n", npc_id, npcs[npc_id-1].name);
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int32_t get_player_mood( FILE *p_file , int32_t key , char *picture_name , int32_t *return_val){

    if( !p_file ) return -1;

    char buffer[256];
    // char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "mood" ) != NULL ) {
            if (sscanf(buffer, " mood = { \"%[^\"]\" , %d }", picture_name, return_val) == 2) {
                return 0;
            }
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int32_t check_key_format( FILE *p_file , int32_t key ) {
    
    if( !p_file ) return -1;

    char buffer[256];

    if( __find_key( p_file , key ) == -1 ) return -2;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "option" ) != NULL ) {
            return 1;
        }
        if( strstr( buffer , "to" ) != NULL ) {
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return -3;
        }
    }
    return -3;

}

int32_t get_to( FILE *p_file , int32_t key , int32_t to[3] ) {

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return 1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "to" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '{') );
            sscanf( tmp , "{ %d:%d , -1:%d }", &to[0] , &to[1] , &to[2] );
            return 0;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return 2;
        }
    }
    return 3;
}

int8_t getBackground(FILE *pFile, int32_t key, char *backgroundPath){
    if(pFile == NULL) return FALSE;

    char buffer[256];
    if( __find_key(pFile, key) == -1 ){
        return FALSE;
    }

    while(!feof(pFile)){
        fgets(buffer, sizeof(buffer), pFile);
        if( strstr(buffer, "background") != NULL ){
            if(sscanf(buffer, "background=\"%[^\"]\"", backgroundPath) == 1){
                return TRUE;
            }
        }
    }

    return FALSE;
}

int32_t get_npc( FILE *p_file , int32_t key ){

    if( !p_file ) return -1;

    char buffer[256];
    char tmp[256];

    if( __find_key( p_file , key ) == -1 ) return -1;

    while( !feof(p_file) ) {

        fgets( buffer , sizeof(buffer) , p_file );
        if( strstr( buffer , "npc" ) != NULL ) {
            strcpy( tmp , strchr( buffer , '=') );
            int32_t npc_id=0;
            sscanf( tmp , "=%d", &npc_id);
            return npc_id;
        }
        if( strchr( buffer , '[' ) != NULL ) {
            return -1;
        }
    }
    
    return -1;
}