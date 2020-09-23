/*
 * mhkiff_uncompress1_2.c
 *
 *  Created on: 2020/09/22
 *      Author: rsaito
 */

/* On Mac,
 * gcc -c mhkiff_uncompress1_4.c
 * gcc -L/usr/lib mhkiff_uncompress1_4.o -o mhkiff_uncompress1_4 -lz
 */

#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

void read_uncompress_kiffchunk(char *, int *, int *, int *, int *);

void read_uncompress_kiffchunk(
		char *filename,
		int *seekpos,
		int *compressed_size,
		int *uncompressed_size,
		int *res_status){

	FILE *fp;
	unsigned char *uncompressbuf; // static char unc[10000000]; ??
	unsigned char *compressedbuf;
	int uncompress_res;

	if((fp = fopen(filename, "r")) == NULL){
		*res_status = -1001;
		return;
	}

	if(fseek(fp, *seekpos, SEEK_SET) != 0){
		*res_status = -1002;
		return;
	}

	uncompressbuf = (unsigned char *)malloc(*uncompressed_size * sizeof(unsigned char));
	compressedbuf = (unsigned char *)malloc(*compressed_size * sizeof(unsigned char));

	if(fread(compressedbuf, sizeof(char), *compressed_size, fp) < 0){
		*res_status = -1003;
		return;
	}

	uncompress_res = uncompress(
			uncompressbuf, uncompressed_size,
			compressedbuf, *compressed_size);
	// https://refspecs.linuxbase.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/zlib-uncompress-1.html

	printf("Z_OK: %d, Z_BUF_ERROR: %d, Z_MEM_ERROR: %d, Z_DATA_ERROR: %d\n",
			Z_OK, Z_BUF_ERROR, Z_MEM_ERROR, Z_DATA_ERROR);
	printf("Uncompress result: %d\n", uncompress_res);

	free(compressedbuf);
	// free(uncompressbuf);

	*res_status = 0;

}


int main(){

	int ret_val;
	int seek_pos          = 19853425;
	int compressed_size   = 1453424;
	int uncompressed_size = 2574004;

	read_uncompress_kiffchunk(
			"/Users/rsaito/Desktop/TMPArea/C_114STD_1.kiff",
			&seek_pos, &compressed_size, &uncompressed_size, &ret_val);

	printf("Hello, world!\n");
	printf("%d\n", ret_val);

}

