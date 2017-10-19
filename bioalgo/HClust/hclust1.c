#define N_DATA 4 /* �f�[�^�� */
#define DIM 21

/* �N���X�^�[��� */
struct CLUSTER {
  int n; /* �f�[�^�� */
  int gene[N_DATA]; /* �ێ����Ă���f�[�^�ԍ��̏W�� */
}; 

/* �v���g�^�C�v�錾 */
double  corr_single(double a[], double b[], int n);
double  corr_clust(struct CLUSTER& a, struct CLUSTER& b,
                   double d[N_DATA][N_DATA]);
void merge(struct CLUSTER& a, struct CLUSTER& b, struct CLUSTER& merged);

/* n�����f�[�^a, b�̑��֌W�����v�Z���� */
double corr_single(double a[], double b[], int n){
  int i;
  double d = 0.0;
  double mean_a, mean_b;
  double var_a, var_b;
  double corr;
  
  for(mean_a = 0, i = 0;i < n;i ++)mean_a += a[i] / n;
  for(mean_b = 0, i = 0;i < n;i ++)mean_b += b[i] / n;
  for(var_a = 0, i = 0;i < n;i ++)
    var_a += (a[i] - mean_a)*(a[i] - mean_a) / n;
  for(var_b = 0, i = 0;i < n;i ++)
    var_b += (b[i] - mean_b)*(b[i] - mean_b) / n;
  for(corr = 0, i = 0;i < n;i ++)
    corr += (a[i] - mean_a) / sqrt(var_a)
      * (b[i] - mean_b) / sqrt(var_b) / n;

  return corr;
}

/* �N���X�^�[a, b�̗v�f�Ԃ̑��ւ��v�Z���� */
double corr_clust(struct CLUSTER& a, struct CLUSTER& b,
                  double d[N_DATA][N_DATA]){
  int i, k;
  double max;
  
  max = d[ a.gene[0] ][ b.gene[0] ];
  for (i = 0; i < a.n; i ++){
      for (k = 0; k < b.n; k ++){
          if (max < d[ a.gene[i] ][ b.gene[k] ])
              max = d[ a.gene[i] ][ b.gene[k] ];
        }
    }
  return max;
}

/* �N���X�^�[a, b�𓝍����A���ʂ��N���X�^�[new�ɓ���� */
void merge(struct CLUSTER& a, struct CLUSTER& b, struct CLUSTER& merged){
  int i, n;
  
  n = 0;
  for (i = 0; i < a.n; i ++)
      merged.gene[ n++ ] = a.gene[i];
  for (i=0; i < b.n; i++)
      merged.gene[ n++ ] = b.gene[i];
  merged.n = n;
}

/* ������dim�̃f�[�^�Qdata���K�w�I�N���X�^�����O
   �f�[�^��N_DATA�̓O���[�o���ϐ��Ƃ��ė^������ */
void h_cluster(double data[N_DATA][DIM]){
  int i, j, n;
  double d[N_DATA][N_DATA];   /* �f�[�^�Ԃ̑��֍s�� */
  double corr, corr_max;      /* �f�[�^�Ԃ̑��� */
  int c1, c2;
  
  static struct CLUSTER cl[N_DATA]; /* �N���X�^�[��� */
  static struct CLUSTER w;     /* ���[�N�p */
  
  /* �N���X�^�[���̏����� */
  for (i=0; i < N_DATA; i++){
      cl[i].n = 1;
      cl[i].gene[0] = i;
    }
  
  /* ���֍s��̍쐬 */
  for (i = 0; i < N_DATA; i++)
      for (j = 0; j < N_DATA; j++)
        d[i][j] = corr_single(data[i], data[j], DIM);
  
  /* �K�w�I�N���X�^�����O */
  n = N_DATA - 1;
  while (n > 0){
    corr_max = -1.0;
    for (i = 0; i < n; i ++){
        for (j = i + 1; j <= n; j ++){
              corr = corr_clust(cl[i], cl[j], d);
            if (corr > corr_max){ 
                corr_max = corr;
                c1 = i, c2 = j;
              }	    
          }
      }

    printf("[ Merge %d ] Merging the following two clusters:\n",
           N_DATA - n - 1);
    printf("(1) Cluster containing data #");
    for(i = 0;i < cl[ c1 ].n;i ++){
      printf("%d", cl[ c1 ].gene[i]);
      if(i < cl[ c1 ].n - 1)putchar(',');
    }
    printf("\n(2) Cluster containing data #");
    for(i = 0;i < cl[ c2 ].n;i ++){
      printf("%d", cl[ c2 ].gene[i]);
      if(i < cl[ c2 ].n - 1)putchar(',');
    }
    printf("\nDistance between these two clusters = %lf\n\n", corr_max);
    
    merge(cl[ c1 ], cl[ c2 ], w); /* �N���X�^�[�𓝍� */
    cl[ c1 ] = w; /* �N���X�^�[c2��c1�֓������Ċi�[ */	  
    cl[ c2 ] = cl[n]; /* �N���X�^�[c2��j�����A��Ԍ��̃N���X�^�[�����Ɋi�[ */
    n--; /* �N���X�^�[���P���炷 */
  }
}