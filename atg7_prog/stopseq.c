
/* $B=*;O%3%I%s$N$^$o$j$NG[Ns$rI=<($9$k(B */

int karyu_enki;   /* $BI=<($9$k2<N.$N1v4p?t(B */

int stopseq_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n],"-stopseq") == 0){
    karyu_enki = atoi(argv[n + 1]);
    return 2;    /* $B;H$&%Q%i%a!<%?$N?t(B */
  }
  else return 0;
}


stopseq_head(char *line){

}

stopseq_ent(char *entry, char seqn[], int max, 
	    struct cds_info cds[], int ncds)
{
  int n,s;
/* 
   cds[].cds_start  $BK]Lu3+;ONN0h(B(complement$B$N$H$-$OK]Lu=*N;(B)
   cds[].cds_end    $BK]Lu=*N;NN0h(B(complement$B$N$H$-$OK]Lu3+;O(B)
   cds[].complement 0 = $BK]Lu$,DL>o$N8~$-(B 1 = $BK]Lu$,5U8~$-(B
*/

  for(n = 0;n < ncds;n ++){
    if(cds[n].complement == 0 && cds[n].cds_end != 0){
      for(s = cds[n].cds_end - 2; s <= cds[n].cds_end + karyu_enki; s++)
	if(s <= max)putchar(seqn[s - 1]);
      putchar('\n');
    }
  }
}
    

stopseq_fin(){
  
  printf("$BK]Lu=*N;NN0h$N=hM}$,L5;v=*N;$7$^$7$?!#(B\n");

}

stopseq_help(){

  printf("-stopseq $BK]Lu=*N;NN0h$NG[Ns$NI=<((B($B1v4p?t$r;XDj(B)\n");

}



