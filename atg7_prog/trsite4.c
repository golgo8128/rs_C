#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_st.h"
static int upto; /* �㗬������܂ŕ\�����邩���w�� */
static int down; /* ����������܂ŕ\�����邩���w�� */
static int last; /* ��`�q�ƈ�`�q��������ȏ㗣��Ă��邩���w�� */
/* �p�����[�^���� */
int trsite4_par(int argc, char *argv[], int n)
{
  if(strcmp(argv[n], "-trsite4") == 0){
    upto = atoi(argv[n + 1]); 
    /* �Q�Ԗڂ̃p�����[�^���㗬�ŕ\�����鉖��Ƃ��� */
    down = atoi(argv[n + 2]);
    /* �R�Ԗڂ̃p�����[�^�������ŕ\�����鉖��Ƃ��� */
    last = atoi(argv[n + 3]);
    /* �S�Ԗڂ̃p�����[�^�������ŕ\�����鉖��Ƃ��� */
    return 4; /* �p�����[�^���S�� */
  }
  else return 0;
}
void trsite4_head(char *line){
}
/* �G���g������ */
void trsite4_ent(struct gparam *entry_info, char seqn[], int max,
              struct cds_info cds[], int ncds){
  int i, j, begin, end, k, dobe, doen, begins, ends, js, ks, dobes, doens,s,l,space,ll,ss,spaces;
  printf("%s", entry_info->entry_line); 

  for(i = 1;i < ncds;i ++){ /* �R�[�h�̈�̐������������J��Ԃ�(�n) */
    if(cds[i].complement == 0 && cds[i].cds_start != 0 && cds[i-1].complement ==0 && cds[i-1].cds_end !=0){
      /* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�n) */
      s = cds[i].cds_start;
      l = cds[i-1].cds_end;
      space = s-l;
      printf("-> %d\n", space);
      if(space >= last){
	begin = cds[i].cds_start - upto; /* �㗬�̕\���J�n�n�_ */
	end = cds[i].cds_start + 2;      /* �J�n�R�h���̍Ō�̉��� */
	printf("%d",i);
	for(j = begin;j <= end;j ++){ /* ������㗬����J�n�R�h���܂ŕ\�� */
	  if(j >= 1 && j <= max)putchar(seqn[j-1]);
	  else putchar(' '); /* �f�[�^���Ȃ��Ƃ��́A�󔒂�\�� */
	}
	putchar('\n');
	dobe = cds[i].cds_start + 1; /* �����̕\���J�n�n�_ */
	doen = cds[i].cds_start + down; /* �����̕\���ŏI�n�_ */
	for(k = dobe; k <= doen; k++){ /* ����������̎n�߂���I���܂ŕ\�� */
	  if(k >= 1 && k<= max)putchar(seqn[k+1]);
	  else putchar(' ');
	}
	putchar('\n');
      } /* �R�[�h�̈悪��d���̔��Α��łȂ��A�|��J�n�̈悪���m(�I) */
    }
    if(cds[i].complement == 1 &&  cds[i].cds_start != 0 && cds[i-1].cds_end != 0 && cds[i-1].complement ==1){
      /* �R�[�h�̈悪��d���̔��Α��ɂ��� */
      ss = cds[i].cds_start;
      ll = cds[i-1].cds_end;
      spaces = ss-ll;
      printf("<- %d\n",spaces);
      if(spaces >= last){
	begins = cds[i-1].cds_end + upto; /*���⍽�ł����㗬�|��J�n�n�_*/
	ends = cds[i-1].cds_end - 2;      /* ���⍽�ł����J�n�R�h���̍Ō�̉��� */
	printf("%d",i-1);
	for(js = begins;js >= ends;js --){ /* ������㗬����J�n�R�h���܂ŕ\�� */
	  if(js >= 1 && js <= max){
	    if(seqn[js-1]=='a')	putchar('t');
	    if(seqn[js-1]=='t')	putchar('a');
	    if(seqn[js-1]=='c')	putchar('g');
	    if(seqn[js-1]=='g')	putchar('c');
	  }
	  else putchar(' '); /* �f�[�^���Ȃ��Ƃ��́A�󔒂�\�� */
	}
	putchar('\n');
	dobes = cds[i-1].cds_end -3 ; /* ���⍽�ł��������̕\���J�n�n�_ */
	doens = cds[i-1].cds_end - down -2; /* ���⍽�ł��������̕\���ŏI�n�_ */
	for(ks = dobes; ks >= doens; ks--){/*����������̎n�߂���I���܂ŕ\��*/
	  if(ks >= 1 && ks<= max){
	    if(seqn[ks-1]=='a')	putchar('t');
	    if(seqn[ks-1]=='t')	putchar('a');
	    if(seqn[ks-1]=='c')	putchar('g');
	    if(seqn[ks-1]=='g')	putchar('c');	
	  }
	  else putchar(' ');
	}
	putchar('\n');
      }
    }
  } /* �R�[�h�̈�̐������������J��Ԃ�(�I) */
}
/* �ŏI���� */
void trsite4_fin(){
  printf("Finished!!\n");
}
/* �w���v */
void trsite4_help(){
  printf("-trsite4\t Displays sequences around translation initiation sites\n");
}




