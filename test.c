#include <stdio.h>
#include <stdint.h>

#include "toml_parse.h"

int main() {

    FILE *p_file = fopen( "script.toml" , "r" );
    puts(get_name(p_file));

    return 0;
}