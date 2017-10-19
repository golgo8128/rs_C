#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"
static int last; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int aonly_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-aonly") == 0){
    last = atoi(argv[n + 1]);
    return 2; /* �p�����[�^���Q�� */
  }
  else return 0;
}
void aonly_head(char *line){
}
/* �G���g������ */
void aonly_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i,s,l,space,ss,ll,spaces;  
  valid_cds[0]=0;
  for(i = 1;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    if(cds[i].complement == 0 && cds[i].cds_start != 0 && cds[i-1].complement ==0 && cds[i-1].cds_end !=0){
      /* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�n) */
      s = cds[i].cds_start;
      l = cds[i-1].cds_end;
      space = s-l;
      if(space < last) valid_cds[i] = 0;
    }/* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�I) */
    if(cds[i].complement == 1 &&  cds[i].cds_start != 0 && cds[i-1].cds_end != 0 && cds[i-1].complement ==1){
      /* �R�[�h�̈悪��d���̔��Α��ɂ��� */
      ss = cds[i].cds_start;
      ll = cds[i-1].cds_end;
      spaces = ss-ll;
      if(spaces < last)valid_cds[i-1] = 0;
    }
    if(cds[i].complement==0 && cds[i-1].complement==1){
      valid_cds[i]=0;
      valid_cds[i-1]=0;
    }
  }
} /* �R�[�h�̈�̐������������J��Ԃ�(�I) */
/* �ŏI���� */
void aonly_fin(){
  printf("Finished!!\n");
}
/* �w���v */
void aonly_help(){
  printf("-aonly\t Only accepts if two same oriented codons are separated by ");
  printf("specified bases or farther\n");
}




