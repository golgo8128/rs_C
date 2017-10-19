#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"

static int ijou,inai; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int aonly4_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-aonly4") == 0){
    ijou = atoi(argv[n + 1]);
    inai = atoi(argv[n + 2]);
    return 3; /* �p�����[�^���R�� */
  }
  else return 0;
}
void aonly4_head(char *line){
}
/* �G���g������ */
void aonly4_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i,j,dist;


  for(i = 0;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    
    if(cds[i].complement == 0 && i > 0){
      dist = cds[i].cds_start - cds[i-1].cds_end;
      if(dist < ijou || dist > inai)valid_cds[i] = 0;
    }
    
    else if(cds[i].complement == 1 && i < ncds - 1){
      /* �R�[�h�̈悪��d���̔��Α��ɂ��� */
      dist = cds[i+1].cds_start - cds[i].cds_end;
      if(dist < ijou || dist > inai)valid_cds[i] = 0;
    }
  } /* �R�[�h�̈�̐������������J��Ԃ�(�I) */

}

  /* �ŏI���� */
void aonly4_fin(){

}
/* �w���v */
void aonly4_help(){
  printf("-aonly4\t Accepts only sequences whose start codons are separated by specified bases from the previous gene(State min and max)\n");
}





