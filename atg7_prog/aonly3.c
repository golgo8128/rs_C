#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"
static int last,lasts; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int aonly3_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-aonly3") == 0){
    last = atoi(argv[n + 1]);
    lasts = atoi(argv[n + 2]);
    return 3; /* �p�����[�^���R�� */
  }
  else return 0;
}
void aonly3_head(char *line){
}
/* �G���g������ */
void aonly3_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i,s,l,space,ss,ll,spaces;  
  valid_cds[0]=0;
  for(i = 1;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    if(cds[i].complement == 0 && cds[i].cds_start != 0 && cds[i-1].complement ==0 && cds[i-1].cds_end !=0){
      /* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�n) */
      s = cds[i].cds_start;
      l = cds[i-1].cds_end;
      space = s-l;
      if(space > lasts) valid_cds[i] = 0;
      if(space < last) valid_cds[i] = 0;
    }/* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�I) */
    if(cds[i].complement == 1 &&  cds[i].cds_start != 0 && cds[i-1].cds_end != 0 && cds[i-1].complement ==1){
      /* �R�[�h�̈悪��d���̔��Α��ɂ��� */
      ss = cds[i].cds_start;
      ll = cds[i-1].cds_end;
      spaces = ss-ll;
      if(spaces > lasts)valid_cds[i-1] = 0;
      if(spaces < last)valid_cds[i-1] = 0;
    }
    if(cds[i].complement==0 && cds[i-1].complement==1){
      valid_cds[i]=0;
      valid_cds[i-1]=0;
    }
  }
} /* �R�[�h�̈�̐������������J��Ԃ�(�I) */
/* �ŏI���� */
void aonly3_fin(){
  printf("Finished!!\n");
}
/* �w���v */
void aonly3_help(){
  printf("-aonly3\t -ijou -inai douitu houkou \n");
}




