#include <stdio.h>
#include <stdlib.h>

int ascii_ok(char c){

  if(32 <= c && c<= 126){ return 1; }
  if(c == 9 || c == 10){ return 1; }
  else { return 0; }

}

void main(int argc, char *argv[]){

  FILE *fp;
  char *input_file;
  char c, prev_c;


  input_file = argv[1];


  if(argc != 2){
    fprintf(stderr, "Parameter error.\n");
    exit(1); 
  }

  if((fp = fopen(input_file, "r")) == NULL){
    fprintf(stderr, "File \"%s\" does not exist.\n", input_file);
    exit(1);
  }

  prev_c = 0;
  while(1){

    fread(&c, sizeof(char), 1, fp );

    if(feof(fp)){
      if(prev_c == 13){
	putchar('\n');
      } 
      break;
    }

    if(ascii_ok(c)){
      if(prev_c == 13 && c != 10){
	putchar('\n');
      }
      putchar(c);
    }
    prev_c = c;
  }

  close(fp);
  
}
