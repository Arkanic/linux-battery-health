#include <stdio.h>
#include <stdlib.h>

// read file to malloc'd string of right length
char *readfile(char *filename) {
	FILE *f = fopen(filename, "rb");
	if(!f) return 0;

	fseek(f, 0, SEEK_END);
	long length = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *buffer = malloc(sizeof(char) * length);
	if(!buffer) return 0;

	fread(buffer, 1, length, f);
	fclose(f);

	return buffer;
}

long readmes(char *filename) {
        char *raw = readfile(filename);
        if(!raw) {
                fprintf(stderr, "failed to read measurement at %s\n", filename);
                return 1;
        }

        long result = atol(raw);
        free(raw);

        return result;
}
