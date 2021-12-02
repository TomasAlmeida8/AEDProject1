//
// AED, November 2021
//
// Solution of the first practical assignement (subset sum problem)
//
// Place your student numbers and names here
//

#if __STDC_VERSION__ < 199901L
# error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
# define STUDENT_H_FILE "000000.h"
#endif


//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "../AEDProject1/elapsed_time.h"
#include "../AEDProject1/000000.h"


//
// custom data types
//
// the STUDENT_H_FILE defines the following constants and data types
//
//   #define min_n       24                   --- the smallest n value we will handle
//   #define max_n       57                   --- the largest n value we will handle
//   #define n_sums      20                   --- the number of sums for each n value
//   #define n_problems  (max_n - min_n + 1)  --- the number of n values
//
//   typedef unsigned long long integer_t;    ---  64-bit unsigned integer
//   typedef struct
//   {
//     int n;                                 --- number of elements of the set (for a valid problem, min_n <= n <= max_n)
//     integer_t p[max_n];                    --- the elements of the set, already sorted in increasing order (only the first n elements are used)
//     integer_t sums[n_sums];                --- several sums (problem: for each sum find the corresponding subset)
//   }
//   subset_sum_problem_data_t;               --- weights p[] and sums for a given value of n
//
//   subset_sum_problem_data_t all_subset_sum_problems[n_problems]; --- // the problems
//


//
// place your code here
//
// possible function prototype for a recursive brute-force function:
//   int brute_force(int n,integer_t p[n],integer_t desired_sum,int current_index,integer_t partial_sum,int b[n]);
// it sould return 1 when the solution is found and 0 otherwise
// note, however, that you may get a faster function by reducing the number of function arguments (maybe a single pointer to a struct?)
//

int solve_iter(int n,integer_t *p,integer_t desired_sum)
{
 integer_t test_sum;
 for (int comb = 0;comb<(1<<n); comb++)
 {
  test_sum=0;
  for (int bit = 0;bit< n; bit++)
  {
   if (comb & (1<<bit))
    test_sum += p[bit];   
  }
  
  if (test_sum == desired_sum)
  {//sucesso
   //Imprime a combinação descoberta
   printf("\n A soma %lld é obtida por: ", desired_sum);
   for (int bit = 0;bit< n; bit++)
  {
   if (comb & (1<<bit))
    printf("%lld +",p[bit]);   
  }
   return 1;
  }
 }
  
 return 0; //valor desired_sum não encontrado 
}

//
// main program
//

int main(void)
{
  fprintf(stderr,"Program configuration:\n");
  fprintf(stderr,"  min_n ....... %d\n",min_n);
  fprintf(stderr,"  max_n ....... %d\n",max_n);
  fprintf(stderr,"  n_sums ...... %d\n",n_sums);
  fprintf(stderr,"  n_problems .. %d\n",n_problems);
  fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
  //
  // solve all the problems
  
 for (int j = 0; j<30 ; j++){ 
    int n = all_subset_sum_problems[j].n;
    integer_t *p = all_subset_sum_problems[j].p;
    integer_t desired_sum = all_subset_sum_problems[j].sums[j];
    printf("Quero resolver o problema de ordem %d e encontrar a soma que dá %lld \n", n,desired_sum);
    if (solve_iter(n, p, desired_sum)==1)
      printf("Solução Encontrada\n");
    else
      printf("Solução Não Encontrada\n");
  }


  return 0;
}
