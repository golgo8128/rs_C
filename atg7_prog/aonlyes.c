#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"

static int ijou,inai; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int aonlyes_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-aonlyes") == 0){
    ijou = atoi(argv[n + 1]);
    inai = atoi(argv[n + 2]);
    return 3; /* �p�����[�^���R�� */
  }
  else return 0;
}
void aonlyes_head(char *line){
}
/* �G���g������ */
void aonlyes_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i,j,dist;
  valid_cds[0]=0;
  for(i = 1;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    
    if(cds[i].complement == 0 && cds[i-1].complement ==0){
      dist = cds[i].cds_start - cds[i-1].cds_end;
      if(dist >= ijou && dist <= inai)valid_cds[i] = 0;
    }
    
    else if(cds[i].complement == 1 && cds[i-1].complement ==1){
      /* �R�[�h�̈悪��d���̔��Α��ɂ��� */
      dist = cds[i].cds_start - cds[i-1].cds_end;
      if(dist >= ijou && dist <= inai)valid_cds[i-1] = 0;
    }
  } /* �R�[�h�̈�̐������������J��Ԃ�(�I) */
}

  /* �ŏI���� */
void aonlyes_fin(){

}
/* �w���v */
void aonlyes_help(){
  printf("-aonlyes\t eliminates -ijou -inai douitu houkou \n");
}




