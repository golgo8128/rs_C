/*                                                        */
/* ****************************************************** */
/* $@%K%e!<%i%k%M%C%H%o!<%/$r;H$C$F#4?'LdBj$r2r$/%W%m%0%i%`(J */
/* ****************************************************** */
/*                                                        */
/* $@#1#9#9#6G/(J $@IpF#8&(J $@?7?M8&=$2q(J                           */
/*                                                        */
/* $@$3$N%W%m%0%i%`$O(J gcc $@$r;H$C$F%3%s%Q%$%k$9$k$3$H(J        */

#define VERSION "March 29, 1996"

#include <stdio.h>


void main(){

#define N_CTRY 7 /* $@9q$N?t(J 0 $@$+$i(J (N_CTRY - 1) $@$^$G(J */

/* $@3F%K%e!<%m%s$K4X$9$k>pJs(J */

  int  U[N_CTRY][4]; /* $@H/2P$9$k$+H]$+$r7hDj$9$k>pJs(J */
  int dU[N_CTRY][4]; /* $@F0:n<0$+$iF@$i$l$k>pJs(J  U$@$KB-$5$l$k(J */
  int  V[N_CTRY][4]; /* 0 = $@H/2P$7$F$$$J$$(J   1 = $@H/2P$7$F$$$k(J */


/* $@9q$,@\$7$F$$$k$+H]$+$K4X$9$k>pJs(J */

  int D[N_CTRY][N_CTRY] = {
    { 0, 1, 1, 0, 1, 0, 0 },
    { 1, 0, 1, 1, 0, 0, 0 },
    { 1, 1, 0, 1, 1, 0, 0 },
    { 0, 1, 1, 0, 1, 1, 0 },
    { 1, 0, 1, 1, 0, 1, 1 },
    { 0, 0, 0, 1, 1, 0, 1 },
    { 0, 0, 0, 0, 1, 1, 0 }
  }; /* 0 = $@@\$7$F$$$J$$(J  1 = $@@\$7$F$$$k(J */
     /* $@F1$89qF1;N$O@\$7$F$$$J$$$b$N$H$_$J$9(J */

  int seed; /* $@Mp?t%7!<%I$N(J No. */

  int x,y,m,n,i,j,counter,fin_flag,dummy; /* $@B>L\E*JQ?t(J */

/* $@Mp?t%7!<%I$N@_Dj(J */

  printf("Input random number seed:");
  scanf("%d", &seed);
  for( n = 0 ; n < seed ; n ++)dummy = rand();


/* U$@$NCM$N=i4|2=(J */

  initialize(U); /* U$@$NCM$r%i%s%@%`$K@_Dj$9$k(J */
  calc_V(U,V);   /* U$@$NCM$h$j(JV$@$N>pJs(J($@H/2P$9$k$+H]$+(J)$@$r7hDj(J */
  display_N(U);
  display_N(V);

/* $@%a%$%s%k!<%W(J */
  counter = 0;
  while(1){
    counter ++;
    printf("trial %d\n",counter);
    fin_flag = calc_dU(dU,V,D); /* V,D($@9qF1;N$,@\$7$F$$$k>pJs(J)$@$h$j(J
				   dU$@$r7W;;$9$k(J */
    calc_U(U,dU);     /* $@F0:n<0$h$j(JU$@$N<!$N>uBV$r7hDj$9$k(J */
    calc_V(U,V);     /* U$@$NCM$h$j(JV$@$N>pJs(J($@H/2P$9$k$+H]$+(J)$@$r7hDj(J */
    if(fin_flag)break; /* dU$@$,<}B+$7$?$i=*N;(J */
    display_N(V);
    putchar('\n');
  }

/* $@7k2L$r=PNO$7!"=*N;(J */
  printf("Final Result:\n");
  display_N(V);

}


/* U$@$NCM$N=i4|2=(J $@%i%s%@%`$K@_Dj$9$k(J */
initialize(int U[N_CTRY][4])
{
  int x,i;

  for(x = 0;x < N_CTRY;x ++)
    for(i = 0;i < 4;i ++)U[x][i] = rand() % 100 - 100/2;
}

/* V$@$NCM(J($@H/2P$7$F$$$k$+H]$+(J)$@$r(JU$@$N>pJs$h$j7hDj$9$k(J */
calc_V(int U[N_CTRY][4], int V[N_CTRY][4])
{
  int x,i;

  for(x = 0;x < N_CTRY;x ++){
    for(i = 0;i < 4;i ++){
      if(U[x][i] >= 0)V[x][i] = 1;
      else V[x][i] = 0;
    }
  }
}

/* U$@$NCM$r3F%K%e!<%m%s$NF0:n<0$h$j7W;;$9$k(J */
int calc_U(int U[N_CTRY][4],int dU[N_CTRY][4])
{
  int x,i;
  for(x = 0;x < N_CTRY;x ++)
    for(i = 0;i < 4;i ++)
      U[x][i] += dU[x][i];
}



/* V($@H/2P>uBV(J),D($@9q$,@\$7$F$$$k>uBV(J)$@$h$jF0:n<0(JdU$@$r7W;;$9$k(J */
int calc_dU(int dU[N_CTRY][4], int V[N_CTRY][4], int D[N_CTRY][N_CTRY])
{
  int x,i,dU_temp,fin,fin_flag;

  fin_flag = 1; /* 1 $@$N$^$^$J$i<}B+(J */
  for(x = 0;x < N_CTRY;x ++)
    for(i = 0;i < 4;i ++){
/*      printf("In country %2d whose color is %d\n",x,i); */
      dU_temp = calc_each_dU(x,i,V,D,&fin);
      if(fin != 0)fin_flag = 0; /* $@<}B+>r7o(J */
/*       printf("Country %2d Color %d:dU = %d\n\n",x,i,dU_temp); */
      dU[x][i] = dU_temp;
    }
  return(fin_flag);
}

/* $@9qHV9f(Jx $@?'HV9f(Ji $@$K4X$9$k%K%e!<%m%s$NF0:n<0$r7W;;$9$k(J */
/* *fin$@$K$O3F%K%e!<%m%s$N<}B+<0(J($@<}B+$J$i(J0)$@$,F~$k(J */
int calc_each_dU(int x,int i,int V[N_CTRY][4],int D[N_CTRY][N_CTRY],
		 int *fin)
{
#define A 5
#define B 5
#define C 5
#define C1 5
#define C2 5

  int j,y;
  int m,n;
  int result;

  int vA,vB,vC,vC1,vC2;
  
  vA = 0; /* $@<+J,$,H/?'$7$F$$$k?'$N?t(J */
  for(j = 0;j < 4;j ++)vA += V[x][j];
  vA = vA - 1; /* $@#1?'$r0z$/(J */

  vB = 0;
  for(y = 0;y < N_CTRY;y ++){
    if(y != x){
      m = 0; /* y $@$N9q$N2s$j$K$"$k9q$N?t(J */
      for(n = 0;n < N_CTRY;n ++)m += D[y][n];
      vB += D[x][y] * V[y][i] * m;
/*
      if(D[x][y] && V[y][i]){
	printf("Country %d and %d is close to each other\n",x,y);
	printf("Country %d has %d countries around\n",y,m);
	for(n = 0;n < N_CTRY;n ++)printf("%d ",D[x][n]);
	printf("\nvB is now %d\n",vB);
      }
*/
    }
  }

/* $@%R%k%/%i%$%_%s%0%?!<%`(J */
  vC = 0;
  for(j = 0;j < 4;j ++)
    vC += V[x][j]; /* $@?'$,#1?'$G$bEI$i$l$F$$$k$+$NH=Dj(J */
/*  printf("Country %d is colored by %d colours\n",x,vC); */

  vC1 = 0; /* x $@$,@\$7$F$$$kNN0h$N?t(J */
  for(n = 0;n < N_CTRY;n ++)vC1 += D[x][n];

  m = 0; /* x $@$,@\$7$F$$$kNN0h$,@\$7$F$$$kNN0h$N9g7W(J */
  for(y = 0;y < N_CTRY;y ++)
    for(n = 0;n < N_CTRY;n ++)m += D[x][y] * D[y][n];
  vC2 = m / vC1; /* $@J?6Q$r$H$k(J */
/*
  printf("vA:%d vB:%d vC:%d vC1:%d vC2:%4lf\n",vA,vB,vC,vC1,1.0*m/vC1);
*/

  result = -1 * A * vA 
              - B * vB
              + C * h(vC) * (C1 * vC1 + C2 * vC2); /* $@F0:n<0(J */

  *fin =   -1 * A * vA
              - B * vB * V[x][i]
              + C * h(vC) * (C1 * vC1 + C2 * vC2); /* $@<}B+>r7o(J */

  return(result);
}

/* x$@$,(J0$@$N$H$-$N$_(J1$@$rJV$7!"$=$l0J30$N;~$O(J0$@$rJV$9(J */
int h(int x){
  if(x == 0)return 1;
  else return 0;
}


/* $@A4$F(J0$@$J$i(J1$@$rJV$9(J $@DL>o$O3F%K%e!<%m%s$NF0:n<0$rF~NO$H$9$k(J */
all_zero_N(int N[N_CTRY][4])
{
  int x,i;
  for(x = 0;x < N_CTRY;x ++)
    for(i = 0;i < 4;i ++)
      if(N[x][i] != 0)return 0;
  return 1;
}


/* $@3F%K%e!<%m%s$NCM$rI=<($9$k(J */
display_N(int N[N_CTRY][4])
{
  int x,i;
  for(x = 0; x < N_CTRY;x ++){
    for(i = 0;i < 4;i ++)printf("%3d ",N[x][i]);
    putchar('\n');
  }
}

