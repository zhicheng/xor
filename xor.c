#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *tmalloc(size_t size)
{
	void *ret;
	if ((ret = malloc(size)) == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(1);
	}
	return ret;
}

int
main(int argc, char *argv[])
{
	int i, j;
	char ch;
	size_t n;
	FILE *fp1;
	FILE *fp2;
	char *key;
	char *buffer1;
	char *buffer2;
	size_t keylen = 0;

	if (argc != 4) {
		fprintf(stderr, "Usage %s key infile outfile\n", argv[0]);
		return 1;
	}

	key = strdup(argv[1]);
	keylen = strlen(key);

	buffer1 = tmalloc(keylen);
	buffer2 = tmalloc(keylen);

	if (strcmp(argv[2], argv[3]) == 0) {
		fprintf(stderr, "infile == outfile\n");
		return 1;
	}


	if ((fp1 = fopen(argv[2], "rb")) == NULL) {
		fprintf(stderr, "file %s open fail\n", argv[1]);
		return 1;
	}

	if ((fp2 = fopen(argv[3], "wb")) == NULL) {
		fprintf(stderr, "file %s open fail\n", argv[3]);
		return 1;
	}

	while ((n = fread(buffer1, 1, keylen, fp1)) > 0) {
		for (i = 0; i < n; i++)
			buffer2[i] = buffer1[i] ^ key[keylen - i % keylen - 1];
		fwrite(buffer2, 1, n, fp2);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
