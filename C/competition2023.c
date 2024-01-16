#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
  int64_t **m;
  int64_t length0;
  int64_t length1;
} C_matrix ;

int64_t input (void){
  int64_t n = 0;

  int64_t numberSize = 100;
  char *number = malloc(sizeof(char) * numberSize);
  char c;
  int64_t i = 0;
  do {
    if (i == numberSize){
      numberSize += 100;
      number = realloc(number, numberSize);
    }
    c=getc(stdin);

    if ((c != '\n') && c != '\r'){
      number[i] = c;
      i++;

    } else if (c == ' '){

    } else {
      number[i] = '\0';
      i++;
      break ;
    }
  } while (1);

  n = atoi(number);

  free(number);

  return n;
}

static inline __attribute__((always_inline))  int64_t  encode (int64_t v) {
  v = v << 1;
  v = v + 1;
  return v;
}

static inline __attribute__((always_inline)) int64_t decode (int64_t v) {
  v = v >> 1;
  return v;
}

void computeAndPrint (C_matrix * m1, C_matrix * m2, C_matrix * m3);
void initMatrix (C_matrix * m);
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

int main ( ){

  // Fetch the input size
  int64_t dim = input();
  printf("%lld\n", dim);

  // Allocate the matrices
  C_matrix *m1, *m2, *m3;
  m1 = newArray(dim, dim);
  assert(m1 != NULL);
  m2 = newArray(dim, dim);
  assert(m2 != NULL);
  m3 = newArray(dim, dim);
  assert(m3 != NULL);

  // Compute
  computeAndPrint(m1, m2, m3);

  return 0;
}

void computeAndPrint (C_matrix * m1, C_matrix * m2, C_matrix * m3){

  // Initialize the matrices
  initMatrix(m1);
  initMatrix(m2);

  // Multiple the matrices
  matrixMultiplication(m1, m2, m3);
  matrixMultiplication(m3, m2, m1);
  matrixMultiplication(m3, m1, m2);
  matrixMultiplication(m1, m2, m3);
  matrixMultiplication(m3, m2, m1);
  matrixMultiplication(m3, m1, m2);

  // Compute the total sum
  int64_t t = totalSum(m1) ;
  t = decode(t);
  printf("%lld\n", t);

  t = totalSum(m2);
  t = decode(t);
  printf("%lld\n", t);

  t = totalSum(m3);
  t = decode(t);
  printf("%lld\n", t);

  return ;
}

void initMatrix (C_matrix * m){
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
      int64_t t = input();
      m->m[index1][index2] = encode(t);
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
      if (i >= m3->length0) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      if (j >= m3->length1) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      m3->m[i][j] = encode(0) ;
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
        
        C = decode(A) * decode(B);
        C = encode(C);

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        D = m3->m[i][j];

        E = encode(decode(D) * 4);
        
        E = encode(decode(E) * 3);
        E = encode(decode(E) * 3);
        E = encode(decode(E) * 3);
        E = encode(decode(E) * 3);
        E = encode(decode(E) * 3);
        if (E >= 1000){
          E <- encode(10);
        }
        F = encode(decode(E) + 2);
        F = encode(decode(F) << 1);
        F = encode(decode(F) << 1);
        F = encode(decode(F) * 2);
        F = encode(decode(F) + 1);
        F = encode(decode(F) << 1);
        F = encode(decode(F) << 1);
        F = encode(decode(F) * 2);
        F = encode(decode(F) * 2);
        F = encode(decode(F) + 1);
        if (F >= 1500){
          F = F >> 4;
        }
        F = F + 1;

        if (i >= m3->length0) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        if (j >= m3->length1) {
          fprintf(stderr, "ERROR\n");
          abort();
        }
        m3->m[i][j] = F;
      }
    }
  }

  return;
}

int64_t totalSum (C_matrix * m){
  int64_t sum;
 
  // Initialize variables
  sum = encode(0);

  // Iterate over the rows
  for (int64_t index1 = 0; index1 < m->length0; index1++){
    for (int64_t index2 = 0; index2 < m->length1; index2++){
  
      // Sum the current value
      if (index1 >= m->length0) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      if (index2 >= m->length1) {
        fprintf(stderr, "ERROR\n");
        abort();
      }
      int64_t temp = m->m[index1][index2];

      sum = encode(decode(sum) + decode(temp));
    }
  }

  return sum;
}
