/****************************************************************************/
/* atg$B8e$N%9%H%C%W%3%I%s$rD4$Y$k(B                                            */
/*                                                                          */
/*                                                    $B@=:n<T(B $B:4!9LZ=(OB(B     */
/*                                                    $B@=:nF|(B $BJ?@.(B8$BG/(B7$B7n(B26$BF|(B */
/****************************************************************************/

int imput_sp;
int kazusp[2][256];
double count_sp[2][4][256];
char *sp[4]={"taa","tag","tga","TOT"};


int stop_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-stop")==0){
    imput_sp=atoi(argv[n+1]);
    return 2;
  }
  else return 0;
}


stop_ent(char *entry, char *seqn, int max, int cds[], int ncds)
{
  int i, j, type, n=0;
  int first=0;

  if(ncds>0){

    /** $B3+;O%3%I%s(B **/
    if(strncmp(&seqn[cds[n]-1],"atg",3)==0){
      for(i=1;i<=imput_sp && cds[n]-1+i<max;i++){
	kazusp[0][i]++;
	for(type=0;type<3;type++){
	  if(strncmp(&seqn[cds[n]-1+2+i],sp[type],3)==0){ 
	    count_sp[0][type][i]++;
	    count_sp[0][  3 ][i]++;
	    /*if(i<=12) printf("%s\n",entry);*/
	  }
	}
      }
    }
    

    /** $B:G=i$N(BATG($BHs3+;O%3%I%s(B) **/
    if(strncmp(&seqn[cds[0]-1],"atg",3)==0){
      for(j=0;j<cds[0]-3 && first==0;j++){
	if(strncmp(&seqn[j],"atg",3)==0){
	  first++;
	  for(i=1;i<=imput_sp && j+i<cds[0]-1;i++){
	    kazusp[1][i]++;
	    for(type=0;type<3;type++){
	      if(strncmp(&seqn[j+2+i],sp[type],3)==0){
		count_sp[1][type][i]++;
		count_sp[1][  3 ][i]++;
	      }
	    }
	  }
	}
      }
    }
    
  }
}

stop_fin()
{
  int i, j, type, sw1, sw2;

  goto xg;

  for(sw1=0;sw1<2;sw1++){/*1*/
    printf("%d",(int)kazusp[sw1][1]);
    for(i=1;i<=imput_sp;i+=12){/*2*/
      for(sw2=0;sw2<2;sw2++){/*3*/
	for(type=0;type<5;type++){/*4*/
	  if(type==4){/*5*/
	    printf("\n ALL|");
	    for(j=0;j<12 && i+j<=imput_sp;j++){/*6*/
	      if(sw2==0) printf("%6d",(int)kazusp[sw1][i+j]);
	      else printf("%6.1lf",(double)kazusp[sw1][i+j]*100/kazusp[sw1][i+j]);
	      /*6*/}
	    /*5*/}
	  
	  else{/*7*/
	    printf("\n %s|",sp[type]);
	    for(j=0;j<12 && i+j<=imput_sp;j++){/*8*/
	      if(sw2==0) printf("%6d",(int)count_sp[sw1][type][i+j]);
	      else printf("%6.2lf",(double)count_sp[sw1][type][i+j]*100/kazusp[sw1][i+j]);
	      /*8*/}
	    /*7*/}
	  /*4*/}
	printf("\n");
	/*3*/}
      /*2*/}
    printf("\n");
    /*1*/}



/*************************** xgraph_data ****************************/
  xg: ;

  for(i=1;i<=imput_sp;i++){
    if(count_sp[1][3][i]>0){
      printf("%6d %.2lf\n",i,(double)count_sp[1][3][i]*100/kazusp[1][i]);
    }
  }
  printf("\n");
  

/********************************************************************/

}


stop_help()
{
  printf("-stop\t atg$B8e$N=*;_%3%I%s$rD4$Y$k(B \n");
  printf("         $B%3%I%s?t$r;XDj$7$F2<$5$$(B \n");
}  

