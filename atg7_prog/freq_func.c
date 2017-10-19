
/* $B#A#T#G#C4^NL$NIQEY$r!sI=<($9$k(B */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "global_st.h"
#include "atg_func.h"

#define A 0
#define C 1
#define G 2
#define T 3

static char type[5] = {"ACGT"};


static int ctr[4];  /* $B%?%s%Q%/<A$4$H$N#OCM(B */
static int E[4];    /* $B@8J*$4$H$N#ECM(B */


int freq_par(int argc, char *argv[], int n)
{
  int i;

  if(strcmp(argv[n],"-freq") == 0){
    


    /* $BBg0hJQ?t$N=i4|2=(B */
    for( i = 0; i < 4; i++ ){
      ctr[i] = 0;
      E[i] = 0;
    }

    return 1;    /* $B;H$&%Q%i%a!<%?$N?t(B */
  }

  else return 0;
}
  
void freq_head(char *line){


   int i, fl = 0;

   if( strncmp("BASE COUNT", line, 10) == 0 ){
/*     printf("%s",line); */
     for( i = 10; line[i] != '\0' && fl < 4; i++ ){
      if( isdigit(line[i]) != 0 ){         /* $B?tCM$@$C$?$i(B */
/*	printf("test:%s\n", line[i]); */
	E[fl] = atoi(&line[i]);
	fl++;
	for( ; isalpha(line[i]) == 0 && line[i] != '\0'; i++ ){
	  /* alphabet $B$,$/$k$^$G(B i $B$r(B incliment $B$9$k(B*/ 
	}
      }
    }
/*     printf("E[A]: %d  E[C]: %d  E[G]: %d  E[T]: %d\n", 
	    E[A],  E[C],  E[G],  E[T]); */
   }
}

void freq_ent(struct gparam *entry_info, char seqn[], int max,
	      struct cds_info cds[], int ncds)
{

/* 
   cds[].cds_start  $BK]Lu3+;ONN0h(B(complement$B$N$H$-$OK]Lu=*N;(B)
   cds[].cds_end    $BK]Lu=*N;NN0h(B(complement$B$N$H$-$OK]Lu3+;O(B)
   cds[].complement 0 = $BK]Lu$,DL>o$N8~$-(B 1 = $BK]Lu$,5U8~$-(B
   entry            LOCUS$BL>(B
*/



  int i, j, cdslen, num=0;
  double chi,e_a,e_t,e_c,e_g;

/*  printf("this is test again\n"); */


  for(i = 0; i < ncds; i++){

    /* $B=i4|2=(B */
    for( j = 0; j < 4; j++ ){
      ctr[j] = 0;
    }

    cdslen = cds[i].cds_end - cds[i].cds_start + 1;  /* $B0dEA;R$N1v4p?t(B */
    printf("[%s]:%d",cds[i].product,num ++);    

    /* normal */
    if(cds[i].complement == 0 && 
       cds[i].cds_start != 0 && cds[i].cds_end != 0){   

      for( j = 0; j < cdslen; j++ ){
	if( seqn[ cds[i].cds_start + j ] == 'a' ) ctr[A]++;
	if( seqn[ cds[i].cds_start + j ] == 't' ) ctr[T]++;
	if( seqn[ cds[i].cds_start + j ] == 'c' ) ctr[C]++;      
	if( seqn[ cds[i].cds_start + j ] == 'g' ) ctr[G]++;      
      }/* for */

    }/* if normal */
    
    /* complement */
    else if(cds[i].complement == 1 && 
	    cds[i].cds_start != 0 && cds[i].cds_end != 0){  

      for( j = 0; j < cdslen; j++ ){
	if( seqn[ cds[i].cds_start + j ] == 'a' ) ctr[T]++;
	if( seqn[ cds[i].cds_start + j ] == 't' ) ctr[A]++;
	if( seqn[ cds[i].cds_start + j ] == 'c' ) ctr[G]++;      
	if( seqn[ cds[i].cds_start + j ] == 'g' ) ctr[C]++;      
      }/* for */

    }/* else if complement */

    else { /* printf("???\n"); */ cdslen = 0;}

/*    printf("\t A:%lf%% T:%lf%% C:%lf%% G:%lf%%  [%s] \n",
	   1.0 * ctr_a/cdslen * 100, 1.0 * ctr_t/cdslen * 100,
	   1.0 * ctr_c/cdslen*100, 1.0 * ctr_g/cdslen * 100, 
	   entry_info->source );
*/

    e_a = 1.0 * cdslen * E[A] / (E[A] + E[T] + E[C] + E[G]);
    e_t = 1.0 * cdslen * E[T] / (E[A] + E[T] + E[C] + E[G]);
    e_c = 1.0 * cdslen * E[C] / (E[A] + E[T] + E[C] + E[G]);
    e_g = 1.0 * cdslen * E[G] / (E[A] + E[T] + E[C] + E[G]);

    chi = 1.0 * (ctr[A] - e_a)*(ctr[A] - e_a) / e_a +
          1.0 * (ctr[T] - e_t)*(ctr[T] - e_t) / e_t +
          1.0 * (ctr[C] - e_c)*(ctr[C] - e_c) / e_c +
          1.0 * (ctr[G] - e_g)*(ctr[G] - e_g) / e_g;

    printf("@ A:%.2lf%% @ T:%.2lf%% @ C:%.2lf%% @ G:%.2lf%% @ %lf @ [%s] \n",
	   1.0 * ctr[A]/cdslen * 100, 1.0 * ctr[T]/cdslen * 100,
	   1.0 * ctr[C]/cdslen * 100, 1.0 * ctr[G]/cdslen * 100, 
	   chi_prob(4-1,chi), entry_info->source );
/*
    printf("AO:%d / AE:%.2lf ",ctr[A], e_a);
    printf("TO:%d / TE:%.2lf ",ctr[T], e_t);
    printf("CO:%d / CE:%.2lf ",ctr[C], e_c);
    printf("GO:%d / GE:%.2lf ",ctr[G], e_g);
    putchar('\n');
*/
  }/*   for(i = 0; i < ncds; i++)   */

}

/* $B7k2L$NI=<((B */
void freq_fin()
{
  int i;
/*
  for( i = 0; i < 4; i++ ){
    printf("E[%c] %d\n", type[i], E[i]);
  }

  printf("Analyses of base contents of gene finished.\n");
*/
}

void freq_help()
{

  printf("-freq Analyses of base contents of genes\n");

}
