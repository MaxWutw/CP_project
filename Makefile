all:
	-gcc main.c toml_parse.c -o main

clean:
	rm test