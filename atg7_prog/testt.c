/* $BK]Lu3+;ONN0h$N>eN.#n1v4p$rI=<((B */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"

int lenoseq;

int testt_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n],"-testt") == 0){
    lenoseq = atoi(argv[n + 1]);
    return 2;    /* $B;H$&%Q%i%a!<%?$N?t(B */
  }
  else return 0;
}
  

void testt_head(char *line){

}

void testt_ent(char *entry, char seqn[], int max, struct cds_info cds[], int ncds)
{

/* 
   cds[].cds_start  $BK]Lu3+;ONN0h(B(complement$B$N$H$-$OK]Lu=*N;(B)
   cds[].cds_end    $BK]Lu=*N;NN0h(B(complement$B$N$H$-$OK]Lu3+;O(B)
   cds[].complement 0 = $BK]Lu$,DL>o$N8~$-(B 1 = $BK]Lu$,5U8~$-(B
   entry            LOCUS$BL>(B
*/

  int i, j, begin, minus;
  int num = 0;

  if(ncds == 0 || cds[0].cds_start == 1)return;
  printf("%s",entry);
  printf("Number of cds:%d\n",ncds);
  for(i = 0; i < ncds; i++){

    if(cds[i].complement == 0 && cds[i].cds_start != 0){   /* normal */
      begin = cds[i].cds_start - lenoseq -1;

      if( begin < 0 )   begin = 0;
      else{ }
      

      for( j = begin; j < cds[i].cds_start + 2 + 10; j++ ){
	printf("%c",seqn[j]);
	if(j == cds[i].cds_start - 2 || j == cds[i].cds_start + 1)
	  putchar(' ');
      }
      printf("%4d:[%s:%s]",num ++, cds[i].product,cds[i].gene);
      printf("\n");
      
    }
    
    else if(cds[i].complement == 1 && cds[i].cds_end != 0){  /* complement */
      begin = cds[i].cds_end + lenoseq -1;

      if( begin > max )  begin = max;
      else{ }


      for( j = begin; j > cds[i].cds_end -4 - 10; j-- ){
	printf("%c", cmpl(seqn[j]));
	if(j == cds[i].cds_end || j == cds[i].cds_end - 3)
	  putchar(' ');
      }
      printf("%4d:[%s:%s]",num ++, cds[i].product,cds[i].gene);
      printf("\n");
    }

    else printf("???\n");

  }/*   for(i = 0; i < ncds; i++)   */

}

/* $B7k2L$NI=<((B */
void testt_fin()
{
  
  printf("Finished.\n");

}

void testt_help()
{

  printf("-testt\t Displays nucleotides around start codon(state 1 number)\n");

}

