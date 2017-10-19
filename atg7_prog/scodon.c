#include <stdio.h>
#include "global_st.h"

/* $B%Q%i%a!<%?$N8!::$r$9$k4X?t(B */
int scodon_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-scodon") == 0){ /* $B%Q%i%a!<%?$O(B "-scodon" */
    return 1; /* $B%Q%i%a!<%?$N?t(B = 1 */
  }
  else return 0; /* "-scodon"$B$G$O$J$+$C$?(B */
}


void scodon_head(char *line){

}

/* $B3F%(%s%H%j$KBP$9$k=hM}(B */
void scodon_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i;
  
  printf("%s",entry_info->entry_line); /* $B%(%s%H%j$N(BLOCUS$B$N9T$rI=<((B */

  for(i = 0;i < ncds;i ++){ /* $B%(%s%H%j$NCf$K4^$^$l$k(BCDS$B$N?t$@$1<B9T(B */

    if(cds[i].complement == 0 && cds[i].cds_start != 0){
      /* $B%3!<%INN0h$,(BDNA$BFs=E:?$NH?BPB&$G$J$/!"K]Lu3+;ONN0h$,L@3N(B */

      putchar(seqn[ cds[i].cds_start     - 1 ]); /* $B3+;O%3%I%s$N#1J8;zL\(B */
      putchar(seqn[ cds[i].cds_start + 1 - 1 ]); /* $B3+;O%3%I%s$N#2J8;zL\(B */
      putchar(seqn[ cds[i].cds_start + 2 - 1 ]); /* $B3+;O%3%I%s$N#3J8;zL\(B */
      putchar('\n'); /* $B2~9T(B */
    }
  }
}

/* $B:G=*=hM}(B */
void scodon_fin(){

  printf("Finished!!\n");

}

/* $B%X%k%W(B */
void scodon_help(){

  printf("-scodon\t Displays start codon\n");

}
