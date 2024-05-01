all:
	-gcc main.c toml_parse.c -o main
	-gcc test.c toml_parse.c -o test

clean:
	rm test