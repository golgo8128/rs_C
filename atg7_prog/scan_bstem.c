#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global_st.h"
#include "atg_func.h"

#define DEBUG_LEVEL 3

static int pos1, pos2;
static int range;
static int broken;
static int counter[4];
static int flag;
static int broken_seq1[4][20];
static int broken_seq2[4][20];
static int length_of_stem[4][20];

int scan_bstem_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-scan_bstem") == 0){
    pos1 = atoi(argv[n + 1]);
    pos2 = atoi(argv[n + 2]);
    range = atoi(argv[n + 3]);
    broken = atoi(argv[n + 4]);
    return 5;
  }
  else return 0;
}

void scan_bstem_head(char *line){

}


extern int comp_match(char c1, char c2);


void reverse(char *seq){ /*$BG[Ns$r5U=g$K$9$k(B*/
  int i;
  int length;

  static char cseq[1000];

  length=strlen(seq);
  strncpy(cseq, seq, length);

  for(i=0;i<length;i++){
     seq[i]=cseq[length-i-1];
  }
}


/* seq1,seq2$B$NG[Ns$r(Bp_seq1, p_seq2$B$K%3%T!<$7!"=i$a$N(Bp1_i, p1_j$BJ8;z$r(B
   $B@Z$j<h$C$FH?E>$5$;$k!#>eN.G[Ns$N2r@O$N=`Hw$H$7$FM-8z(B */
void cut_p1(char *seq1,char *seq2,char *p_seq1,char *p_seq2,int p1_i,int p1_j)
{
  strncpy(p_seq1, seq1, range*2+1);
  strncpy(p_seq2, seq2, range*2+1);

  p_seq1[p1_i]='\0';
  p_seq2[p1_j]='\0';
  
  reverse(p_seq1);
  reverse(p_seq2);

  p_seq1[p1_i]='\0';
  p_seq2[p1_j]='\0';
}

/* seq1, seq2$B$NG[Ns$N(Bp2_i, p2_j$B0J9_$r(Bp_seq1, p_seq2$B$K%3%T!<$9$k!#(B
   $B2<N.G[Ns$N2r@O$KM-8z(B */
void cut_p2(char *seq1,char *seq2,char *p_seq1,char *p_seq2,int p2_i,int p2_j)
{
  strncpy(p_seq1, &seq1[p2_i], range*2+1-p2_i);
  p_seq1[range*2+1-p2_i]='\0';
  strncpy(p_seq2, &seq2[p2_j], range*2+1-p2_j);
  p_seq2[range*2+1-p2_j]='\0';
}

int search_next_stem(char *p_seq1,char *p_seq2,int flag)
/* flag $B$O@ZCGItJ,$N0LCV$HD9$5$r5-O?$9$k>l=j$r<($9!#(B0$B$J$i5-O?$7$J$$!#(B */
{
  int i,j,k;
  
  int max_n=0;
  int p,p1,p2;
  int seq1_len,seq2_len;
  k=0;

  seq1_len=strlen(p_seq1);
  seq2_len=strlen(p_seq2);

  /* broken$B$NHO0OFb$G:G$bBP9g$9$k2U=j$rFCDj$9$k!#(B*/ 
  max_n = 0;
  for(i=0;i<=broken;i++){
    for(j=0;j<=broken;j++){
      k = 0;
      while(comp_match(p_seq1[i+k],p_seq2[j+k])==1 && 
	    i+k<seq1_len && j+k<seq2_len) {
	k++;
      } /* i,j$B$+$i$NO"B3BP9g?t$r%+%&%s%H(B */
      if(k > max_n){	
	max_n = k;
	p1 = i;
	p2 = j;
	if(flag > 0){ /* flag$B$,(B0$B$G$J$1$l$P0LCV(B($BAjBP(B)$B$H%9%F%`$ND9$5$r5-O?(B */
	  broken_seq1[flag - 1][counter[flag - 1]] = i;
	  broken_seq2[flag - 1][counter[flag - 1]] = j;
	  length_of_stem[flag - 1][counter[flag - 1]] = k;
	} /* flag$B$O5-O?$N<oN`!#?F4X?t$G;XDj!#(B */
      }
    }
  }
  if(max_n >= 4){ /* 4$B1v4p0J>eBP9f$7$?$i!"$^$@?-$P$7$F$$$/!#(B */
    p_seq1 = &p_seq1[max_n+p1];
    p_seq2 = &p_seq2[max_n+p2];
    if(flag > 0)counter[flag-1]++; /* $B%9%F%`?t%+%&%s%H%"%C%W(B */
    max_n=search_next_stem(p_seq1,p_seq2,flag) + max_n;
  }
  else max_n = 0;
  return max_n;
}

/* $B>eN.B&$NBP9g7k2L$rI=<(!)(B start$B$O?F4X?t$G;}$C$F$$$kBP9g3+;O0LCV!#(B
   b1, b2$B$O(Bbroken$B>pJs!#(Bb1$B$,(Bseq$B$KBP1~$9$k!#(Bstem length$B$O%0%m!<%P%k$r;HMQ$9$k!#(B
   n$B$OG[Ns$N<oN`$r;XDj$9$k%U%i%C%0!#(B */
void print_seq_up(char *seq,int start,int b1[4][20],int b2[4][20],int n){
  int i,j;

/* 5'$BKvC<$^$GLa$k(B */
  for(i=0;i<counter[n];i++){
    start=start-b1[n][i]-length_of_stem[n][i];
  }

  for(i = counter[n] - 1;i >= 0; i--){

    /* $BBP9gItJ,$OBgJ8;z$GI=<((B */
    for(j=start;j<start+length_of_stem[n][i];j++){
      putchar(toupper(seq[j]));
    }

    /* $BBP9g$7$F$$$J$$ItJ,$NI=<((B */
    for(j=start+length_of_stem[n][i];
	j<start+length_of_stem[n][i]+b1[n][i];j++){
	putchar(seq[j]);
      }
    
    /* $B$b$&0lK\$NG[Ns$HHf$Y$FG[Ns$,C;$$>l9g$O%.%c%C%W$GKd$a$k!#(B */
    if(b1[n][i]<b2[n][i]){
      for(j=0;j<b2[n][i]-b1[n][i];j++)putchar('-');
    }

    /* $B<!$NBP9g0LCV$X(B */
    start=start+length_of_stem[n][i]+b1[n][i];

  }
}

/* $B2<N.B&$NBP9g7k2L$rI=<(!)(B start$B$O?F4X?t$G;}$C$F$$$kBP9g3+;O0LCV!#(B
   b1, b2$B$O(Bbroken$B>pJs!#(Bb1$B$,(Bseq$B$KBP1~$9$k!#(Bstem length$B$O%0%m!<%P%k$r;HMQ$9$k!#(B
   n$B$OG[Ns$N<oN`$r;XDj$9$k%U%i%C%0!#(B */
void print_seq_down(char *seq,int start,int b1[4][20],int b2[4][20],int n){
  int i,j;

  for(i=0;i<counter[n];i++){
    /* $BHsBP9gItJ,$rI=<((B */
    for(j = start;j < start + b1[n][i];j ++)putchar(seq[j]);

    /* $B$b$&0lK\$NG[Ns$h$jC;$$>l9g$O%.%c%C%W$rF~$l$k(B */
    if(b1[n][i]<b2[n][i]){
      for(j = 0;j < b2[n][i] - b1[n][i];j ++)putchar('-');
    }

    /* $BBP9gItJ,$OBgJ8;z$GI=<((B */
    for(j=start+b1[n][i];j<start+length_of_stem[n][i]+b1[n][i];j++){
      putchar(toupper(seq[j]));
    }

    /* $B<!$N(B($BHs(B)$BBP9gItJ,$X(B */
    start=start+length_of_stem[n][i]+b1[n][i];

  }
}


void scan_bstem_ent(struct gparam *entry_info, char seqn[], int max,
		 struct cds_info cds[], int ncds){
  int i,j,k;

  char *compseqn;
  static char seq1[1000],seq2[1000];
  static char cseq2[1000];
  static char p1_seq1[1000],p1_seq2[1000];
  static char p2_seq1[1000],p2_seq2[1000];

  int max_n=0;
  int base;
  int max_n_i=0;
  int max_n_j=0;
  int total_n=0;
  int max_base=0;
  int max_base_i=0;
  int max_base_j=0;
  int pos_i[2];
  int pos_j[2];
  int p1_i,p1_j,p2_i,p2_j;
  int complement_flag;
  int a1, a2;

  for(i=0;i<4;i++)counter[i]=0;
  
  compseqn = compseqget(seqn, max);
  
  if(pos1 > pos2){ /* In case of complement */
    complement_flag = 1;
    pos1 = max - pos1 + 1; /* $B0lHV:G=i$NE:;z$,(B1$B$@$H$$$&2>Dj(B */
    pos2 = max - pos2 + 1; /* $B$G0LCV$r(Bcomplement$B$KJd@5(B */
    strncpy(seq1, &compseqn[pos1-1-range], range*2+1);
    seq1[ range*2 + 1 ] = '\0';
    strncpy(seq2, &compseqn[pos2-1-range], range*2+1);
    seq2[ range*2 + 1 ] = '\0';
  }
  else{
    complement_flag = 0;
    strncpy(seq1, &seqn[pos1-1-range], range*2+1);
    seq1[ range*2 + 1 ] = '\0';
    strncpy(seq2, &seqn[pos2-1-range], range*2+1);
    seq2[ range*2 +1]='\0';
  }

  strncpy(cseq2, seq2, range*2+1);
  reverse(cseq2);
  /* $B$3$l$G(Bseq1$B$H(Bcseq2$B$K2r@OBP>]$NG[Ns$,F~$k(B */
  
  flag=0;
  k=0;

  /* range$B$NHO0OFb$N1v4p$NBP9g$r8+$F$$$/(B */
  for(i=0;i<range*2+1;i++){
    for(j=0;j<range*2+1;j++){
      k = 0;
      while(comp_match(seq1[i+k],cseq2[j+k]) == 1 
	    && i + k < range*2 && j + k < range*2)
	k++;
      /* seq1[i],seq2[j]$B$+$i$NO"B3BP9g$r?t$($k(B */

      if(k>max_base){   /* $BO"B3:GBgBP9g?t$H0LCV$r5-O?(B */
	max_base=k;
	max_base_i=i;
	max_base_j=j;
      }

      if(k>=4){ /* 4$B1v4p0J>eBP9g$7$F$$$l$P$=$3$+$i1v4p$NBP9g$rC5$9(B */
	p1_i=i;   /* 5'$BB&BP9gKvC<(B...$B$G$$$$$N$+!)(B */
	p1_j=j;   /* cut_p1, cut_p2$B$N5!G=$N$A$,$$$h$jLdBj$J$7$H;W$o$l$k(B */
	
	p2_i=i+k; /* 3'$BB&BP9gKvC<$N(B1$B1v4p30(B */
	p2_j=j+k;
	
       /* seq1, cseq2$B$N:G=i$N(Bp1_i, p1_j$BJ8;z$r@Z$j<h$C$FH?E>$5$;$F(B
          p1_seq1,p1_seq2$B$KF~$l$k(B */
	cut_p1(seq1,cseq2,p1_seq1,p1_seq2,p1_i,p1_j);
	total_n = search_next_stem(p1_seq1,p1_seq2,flag) + k;

	/* seq1, cseq2$B$N(Bp2_i,p2_j$B0J9_$NG[Ns$r(Bp2_seq1,p2_seq2$B$KF~$l$k(B */
	cut_p2(seq1,cseq2,p2_seq1,p2_seq2,p2_i,p2_j);
	total_n = search_next_stem(p2_seq1,p2_seq2,flag) + total_n;

	if(total_n > max_n){ /* $B9g7WBP9g?t$N:GBgCM$N5-O?(B */
	  max_n=total_n;
	  max_n_i=i;
	  max_n_j=j;
	  base=k; /* $BCf?4%9%F%`$NBP9g?t(B */
	}
      }
    }
  }


/* $BBP9g2U=j$NFCDj(B:flag$B$rN)$F$F5-O?$7$F$$$/(B */

/* $B9g7WBP9g?t:GBg$N$H$3$m$N>eN.$NBP9g$rD4$Y$k(B flag = 1 */
  cut_p1(seq1,cseq2,p1_seq1,p1_seq2,max_n_i,max_n_j);
  total_n = search_next_stem(p1_seq1,p1_seq2,1);

/* $B9g7WBP9g?t:GBg$N$H$3$m$N2<N.$NBP9g$rD4$Y$k(B flag = 2 */
  cut_p2(seq1,cseq2,p2_seq1,p2_seq2,max_n_i+base,max_n_j+base);
  total_n = search_next_stem(p2_seq1,p2_seq2,2);

/* $B:GBgO"B3BP9g$N$H$3$m$N>eN.$NBP9g$rD4$Y$k(B flag = 3 */
  cut_p1(seq1,cseq2,p1_seq1,p1_seq2,max_base_i,max_base_j);
  total_n = search_next_stem(p1_seq1,p1_seq2,3);

/* $B:GBgO"B3BP9g$N$H$3$m$N2<N.$NBP9g$rD4$Y$k(B flag = 4 */
  cut_p2(seq1,cseq2,p2_seq1,p2_seq2,max_base_i+max_base,max_base_j+max_base);
  total_n = search_next_stem(p2_seq1,p2_seq2,4);


/* $B9g7WBP9g?t:GBg$NG[Ns$N7k2LI=<((B */
/*
  printf("***** **************************** *****\n");
  printf("***** Result of total-max matching *****\n");
  printf("***** **************************** *****\n");
*/
/* $B>eN.B&BP9gI=<((B */
/*
  printf("Sequence:\n");
  print_seq_up(seq1,max_n_i,broken_seq1,broken_seq2,0);
*/
/* $BBP9g$NCf?4%9%F%`$rI=<((B */
/*
  for(i=max_n_i;i<max_n_i+base;i++){
    putchar(toupper(seq1[i]));
  }
*/
/* $B2<N.B&BP9gI=<((B */
/*
  print_seq_down(seq1,max_n_i+base,broken_seq1,broken_seq2,1);
  printf("\n");
*/
/* ($BAjJdB&$NG[Ns$bF1MM(B) */
/*
  print_seq_up(cseq2,max_n_j,broken_seq2,broken_seq1,0);
  for(i=max_n_j;i<max_n_j+base;i++){
    putchar(toupper(cseq2[i]));
  }
  print_seq_down(cseq2,max_n_j+base,broken_seq2,broken_seq1,1);
  printf("\n\n");

  printf("Total matching...%d\n\n", max_n);
*/
#if DEBUG_LEVEL >= 4
  printf("Main stem position:\n");
  a1 = pos1 - range + max_n_i;
  a2 = pos2 + range - max_n_j;
  if(complement_flag){
    a1 = max - a1 + 1;
    a2 = max - a2 + 1;
  }
  printf("   Absolute: (%d %d)\n", a1, a2);
  printf("   From range terminal: (%d %d)\n", max_n_i, max_n_j);
#endif
#if DEBUG_LEVEL >= 5
  printf("\nBroken information upstream:\n");
  for(i = counter[0] - 1;i >= 0;i --){
    printf("seq1(%d): Stem:%d Broken:%d   ",
	   i, length_of_stem[0][i], broken_seq1[0][i]);
    printf("seq2(%d): Stem:%d Broken:%d\n",
	   i, length_of_stem[0][i], broken_seq2[0][i]);
  }
  printf("\nBroken information downstream:\n");
  for(i = 0;i < counter[1];i ++){
    printf("seq1(%d): Broken:%d Stem:%d   ",
	   i,broken_seq1[1][i], length_of_stem[1][i]);
    printf("seq2(%d): Broken:%d Stem:%d\n",
	   i,broken_seq2[1][i], length_of_stem[1][i]);
  }
#endif
  pos_i[0]=max_n_i;
  pos_j[0]=max_n_j;
  for(i=0;i<counter[0];i++){
    pos_i[0] = pos_i[0] - broken_seq1[0][i] - length_of_stem[0][i];
    pos_j[0] = pos_j[0] - broken_seq2[0][i] - length_of_stem[0][i];
  }

/* pos1,pos2$B$+$i$NAjBP0LCV$N7W;;(B */
  pos_i[0] =  pos_i[0] - range;
  pos_j[0] = -pos_j[0] + range;
/*
  printf("Stem position:\n");
  a1 = pos1 + pos_i[0];
  a2 = pos2 + pos_j[0];
  if(complement_flag){
    a1 = max - a1 + 1;
    a2 = max - a2 + 1;
  }
  
  printf("   Absolute: (%d %d)\n", a1, a2);
  printf("   From user indicated: (%d %d)\n", pos_i[0], pos_j[0]);

  putchar('\n');
*/

/* $B:GBgO"B3BP9g$N7k2LI=<((B */
/*
  printf("** ************************* ***********\n");
  printf("** Result of max consecutive matching ** \n");
  printf("** ************************* ***********\n");
  printf("Sequence:\n");
*/

  a1 = pos1 - range + max_base_i;
  a2 = pos2 + range - max_base_j;
  if(complement_flag){
    a1 = max - a1 + 1;
    a2 = max - a2 + 1;
  }


  printf("&\n");
/*  printf("Main stem position:\n"); */
/*  printf("   Absolute: (%d %d)\n",a1, a2); */
/*  printf("   From range terminal: (%d %d)\n", max_base_i, max_base_j); */
  printf("%d & %d & %d &\n", 
	 max_base_i - range,
	 range - max_base_j,
	 max_base);

/* $B>eN.B&BP9gI=<((B */
  print_seq_up(seq1,max_base_i,broken_seq1,broken_seq2,2);

/* $BBP9g$NCf?4%9%F%`$rI=<((B */
  for(i=max_base_i;i<max_base_i+max_base;i++){
    putchar(toupper(seq1[i]));
  }
/* $B2<N.B&BP9gI=<((B */
  print_seq_down(seq1,max_base_i+max_base,broken_seq1,broken_seq2,3);
  printf("\\\\\n& & & &\n");



/* ($BAjJdB&$NG[Ns$bF1MM(B) */
  print_seq_up(cseq2,max_base_j,broken_seq2,broken_seq1,2);
  for(i=max_base_j;i<max_base_j+max_base;i++){
    putchar(toupper(cseq2[i]));
  }
  print_seq_down(cseq2,max_base_j+max_base,broken_seq2,broken_seq1,3);
  printf("\\\\\n\n");
/*
  printf("Max consecutive matching...%d\n\n", max_base);
*/
#if DEBUG_LEVEL >= 5
  printf("\nBroken information upstream:\n");
  for(i = counter[2] - 1;i >= 0;i --){
    printf("seq1(%d): Stem:%d Broken:%d   ",
	   i, length_of_stem[2][i], broken_seq1[2][i]);
    printf("seq2(%d): Stem:%d Broken:%d\n",
	   i, length_of_stem[2][i], broken_seq2[2][i]);
  }
  printf("\nBroken information downstream:\n");
  for(i = 0;i < counter[3];i ++){
    printf("seq1(%d): Broken:%d Stem:%d   ",
	   i,broken_seq1[3][i], length_of_stem[3][i]);
    printf("seq2(%d): Broken:%d Stem:%d\n",
	   i,broken_seq2[3][i], length_of_stem[3][i]);
  }
#endif
  pos_i[1]=max_base_i;
  pos_j[1]=max_base_j;
  for(i=0;i<counter[2];i++){
    pos_i[1]=pos_i[1]-broken_seq1[2][i]-length_of_stem[2][i];
    pos_j[1]=pos_j[1]-broken_seq2[2][i]-length_of_stem[2][i];
  }

/* pos1,pos2$B$+$i$NAjBP0LCV$N7W;;(B */
  pos_i[1] =  pos_i[1] - range;
  pos_j[1] = -pos_j[1] + range;

  a1 = pos1 + pos_i[1];
  a2 = pos2 + pos_j[1];
  if(complement_flag){
    a1 = max - a1 + 1;
    a2 = max - a2 + 1;
  }
/*
  printf("Stem position:\n");
  printf("   Absolute: (%d %d)\n", a1, a2);
  printf("   From user indicated: (%d %d)\n", pos_i[1], pos_j[1]);

  putchar('\n');
*/
  free(compseqn);
}

void scan_bstem_fin(){

}

void scan_bstem_help(){

  printf("-scan_bstem Searches broken for stem. State 4 numbers: Position 1, 2, range, number of broken bases\n");

}





