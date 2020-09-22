/*
 * mhkiff_uncompress1_2.c
 *
 *  Created on: 2020/09/22
 *      Author: rsaito
 */


#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>

int read_uncompress_kiffchunk(
		char *filename,
		int seekpos,
		int compressed_size,
		int uncompressed_size){

	FILE *fp;
	unsigned char *uncompressbuf; // static char unc[10000000]; ??
	unsigned char *compressedbuf;

	if((fp = fopen(filename, "r")) == NULL){
		return(-1);
	}

	uncompressbuf = (unsigned char *)malloc(uncompressed_size * sizeof(unsigned char));
	compressedbuf = (unsigned char *)malloc(compressed_size * sizeof(unsigned char));

	/* uncompress(origbuf, &origsize, compbuf, compsize); */
	// https://refspecs.linuxbase.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/zlib-uncompress-1.html

	free(compressedbuf);
	// free(uncompressbuf);

	return(0);

}



int main(){

	int ret_val;

	ret_val = read_uncompress_kiffchunk(
			"/Users/rsaito/Desktop/TMPArea/C_114STD_1.kiff",
			19853425, 1453424, 2574004
	);

	printf("Hello, world!\n");
	printf("%d\n", ret_val);


}
