#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
#include "atg_func.h"
static int last; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int trsite6_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-trsite6") == 0){
    last = atoi(argv[n + 1]);
    return 2; 
  }/* �R�[�h�̈�̐������������J��Ԃ�(�I) */
  else return 0;
}
void trsite6_head(char *line){
}
/* �G���g������ */
void trsite6_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i,s,l,space,ll,ss,spaces;
  printf("%s", entry_info->entry_line); 
  for(i = 1;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    if(cds[i].complement == 0 && cds[i].cds_start != 0 && cds[i-1].complement !=0 && cds[i-1].cds_end !=0){
/*�R�[�h�̈�̈�����E�A������������������Ă���̈�Ȃ��*/
      s = cds[i].cds_start;
      l = cds[i-1].cds_end;
      space = s-l;
      if(space <= last){
	valid_cds[i] = 0;
	valid_cds[i-1] = 0;
      } 
    }
    if(cds[i].complement == 0 &&  cds[i].cds_start != 0 && cds[i-1].cds_end != 0 && cds[i-1].complement ==0){
/* �R�[�h�̈悪�E�����Ȃ�� */
      valid_cds[i] = 0;
    }
    if(cds[i].complement == 1 &&  cds[i].cds_start != 0 && cds[i-1].cds_end != 0 && cds[i-1].complement ==1){
/* �R�[�h�̈悪�������Ȃ�� */
      valid_cds[i-1] = 0;
    }
  }
}
/* �ŏI���� */
void trsite6_fin(){
  printf("Finished!!\n");
}
/* �w���v */
void trsite6_help(){
  printf("-trsite6\t Accepts sequences only if two CDSs are ");
  printf("opposite oriented and separated by specified bases or ");
  printf("farther\n");
}




