#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
  int64_t **m;
  int64_t length0;
  int64_t length1;
} C_matrix ;

void computeAndPrint (C_matrix * m1, C_matrix * m2, C_matrix * m3, int64_t v1);
void initMatrix (C_matrix * m, int64_t initValue);
void matrixMultiplication (C_matrix * m1, C_matrix * m2, C_matrix * m3);
int64_t totalSum (C_matrix * m);

C_matrix * newArray (int64_t dim0, int64_t dim1){
  C_matrix *m = (C_matrix *) malloc(sizeof(C_matrix));

  m->length0 = dim0;
  m->length1 = dim1;

  m->m = (int64_t **) malloc(sizeof(int64_t *) * dim0);
  for (int64_t c=0 ; c < dim0; c++){
    m->m[c] = (int64_t *) malloc(sizeof(int64_t) * dim1);
  }

  return m;
}

void main ( ){

  // Allocate the matrices
  C_matrix *m1, *m2, *m3;
  int64_t dim;
  dim = 300;
  m1 = newArray(dim, dim);
  assert(m1 != NULL);
  m2 = newArray(dim, dim);
  assert(m2 != NULL);
  m3 = newArray(dim, dim);
  assert(m3 != NULL);

  // Compute
  computeAndPrint(m1, m2, m3, 0);

  return;
}

void computeAndPrint (C_matrix * m1, C_matrix * m2, C_matrix * m3, int64_t v1){

  // Initialize the matrices
  initMatrix(m1, v1) ;
  initMatrix(m2, v1) ;

  // Multiple the matrices
  matrixMultiplication(m1, m2, m3) ;

  // Compute the total sum
  int64_t t = totalSum(m1) ;
  printf("%lld\n", t);
  t = totalSum(m2);
  printf("%lld\n", t);
  t = totalSum(m3);
  printf("%lld\n", t);

  return ;
}

void initMatrix (C_matrix * m, int64_t initValue){
  for (int64_t index1 = 0; index1 < m->length0; index1 = index1 + 1) {
    for (int64_t index2 = 0; index2 < m->length1; index2 = index2 + 1) {
      assert(m != NULL);
      assert(m->m != NULL);
      if (index1 >= m->length0) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      if (index2 >= m->length1) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      m->m[index1][index2] = initValue + index1 + index2 ;
    }
  }
  return ;
}

void matrixMultiplication (C_matrix * m1, C_matrix * m2, C_matrix * m3){

  // Check the length
  if (m1->length1 != m2->length0) {
    return ;
  }
  if (m3->length0 != m1->length0){
    return ;
  }
  if (m3->length1 != m2->length1) {
    return ;
  }

  // Initialize the result matrix
  for (int64_t i = 0; i < m1->length0; i = i + 1) {
    for (int64_t j = 0; j < m2->length1; j = j + 1) {
      for (int64_t k = 0; k < m1->length1; k = k + 1) {
        int64_t tmp = 1;

        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = 0 ;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        tmp = m3->m[i][j];
        tmp = tmp + 4;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = tmp;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        tmp = m3->m[i][j];
        tmp = tmp * 4;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = tmp;

        k <- k + 1;
      }
    }
  }

  // Multiply the matrices
  int64_t tot = 0;
  for (int64_t i = 0; i < m1->length0; i = i + 1) {
    for (int64_t j = 0; j < m2->length1; j = j + 1) {
      for (int64_t k = 0; k < m1->length1; k = k + 1) {
        int64_t A, B, C, D, E, F;

        if (i >= m1->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (k >= m1->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        A = m1->m[i][k];

        if (k >= m2->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m2->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        B = m2->m[k][j];
        C = A * B;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        D = m3->m[i][j];
        E = D * 4;
        F = E + 2;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = F;

        int64_t G;
        G = F * 1;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = G;
        G = F + 0;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = G ;


        G = F * 1;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = G;
        G = F + 0;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = G;

        int64_t tmp ;
        tmp = G;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp << 2;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp << 2;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp << 4;
        tmp = tmp + 2;
        tmp = tmp >> 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;
        tmp = tmp * 4;
        tmp = tmp + 2;
        tmp = tmp * 8;

        int64_t tot2, tot3;
        tot2 = tot * 4;
        tot3 = tot2 + 2;
        tot = tot;
      }
    }
  }

  return ;
}

int64_t totalSum (C_matrix * m){
  int64_t sum = 0 ;
  for (int64_t index1 = 0; index1 < m->length0; index1 = index1 + 1) {
    for (int64_t index2 = 0; index2 < m->length1; index2 = index2 + 1) {

      if (index1 >= m->length0) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      if (index2 >= m->length1) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      sum = sum + m->m[index1][index2] ;
    }    
  }
  return sum ;
}
