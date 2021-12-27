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
#include <math.h>
#include "elapsed_time.h"
#include <string.h>
#include STUDENT_H_FILE


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


//Brute-force lesma
char solve_iter(int n,integer_t p[],integer_t desired_sum,int result[])
{
 for (int comb = 0;comb<(1<<n); comb++){

    integer_t test_sum=0;

    for (int bit = 0; bit < n; bit++){
        if (comb & (1<<bit)){
            test_sum += p[bit];
            result[bit]=1;
        }

        else{
            result[bit]=0;
        }        
  }
  
    if (test_sum == desired_sum)
        return 1;
  

 }
  
 return 0; //valor desired_sum não encontrado 
}

//função recursiva lesma

char cleverBruteForce(int n,integer_t *p,integer_t desired_sum,integer_t current_sum,int current_index,int result[])
{
    if(current_sum==desired_sum)
        return 1;

    if(current_sum>desired_sum)
        return 0;
    
    if(current_index==n)
        return 0;

    
    for (int index = current_index; index < n; index++){
        result[index] = 1;
        if(cleverBruteForce(n, p, desired_sum, current_sum + p[index], ++current_index,result))
            return 1;
        result[index]= 0;
    }

    return 0;
}


//--------------------------------------------------------------------3ª Função-----------------------------------------------------------------------------------

//Função final
char algoritmo(int n,integer_t p[],integer_t desired_sum){

}



//-------------------------------Dividir o array n em dois arrays com o mesmo tamanho-------------------
int divideArrays (integer_t p[], int n){

    int x1 = n/2; //tamanho do primeiro array
    int x2 = n/2 + n%2; //tamanho do segundo array
    int x3 = 0 ; //counter para adicionar ao segundo array

    integer_t firstHalf[x1]; //criaçao primeiro array
    integer_t secondHalf[x2]; //criaçao segundo array

    for (int i=0; i < n; i++){
        if (i < n/2){
            firstHalf[i]=p[i]; //adicionar ao primeiro array
        } else {
            secondHalf[x3]=p[i]; //adicionar ao segundo array
            x3++;
        }
    }
    


    //TESTES

    //printf("%lld    ",firstHalf[15]);
    //printf("%lld    ",secondHalf[5]);

    return 0;
}


//------------------------------------------------------- SOMAS DOS ARRAYS CRIADOS firstHalf e secondHalf -------------------------
int somaArrays(integer_t halfArray[], int n){ //POR FAZER


    for (int comb = 0;comb<(1<<n); comb++){

        integer_t test_sum=0;

        for (int bit = 0; bit < n; bit++){
            if (comb & (1<<bit)){
                test_sum += halfArray[bit];
            }
    }

  return 0;
 }











//quickSort

/* low  --> Starting index,  high  --> Ending index */
// quickSort(integer_t p[], low, high)
// {
    
//     if (low < high)
//     {
//         /* pi is partitioning index, arr[pi] is now
//            at right place */
//         pi = partition(arr, low, high);

//         quickSort(arr, low, pi - 1);  // Before pi
//         quickSort(arr, pi + 1, high); // After pi
//     }
// }

















//
// main program
//

int main(void) {
    /*
    fprintf(stderr,"Program configuration:\n");
    fprintf(stderr,"  min_n ....... %d\n",min_n);
    fprintf(stderr,"  max_n ....... %d\n",max_n);
    fprintf(stderr,"  n_sums ...... %d\n",n_sums);
    fprintf(stderr,"  n_problems .. %d\n",n_problems);
    fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
     */

    for (int i = 0; i < n_problems; i++) {
        int n = all_subset_sum_problems[i].n; // The value of n

        if (n > 30)
            continue; // Skip large values of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            
            // Array with the result
            int result[n];
            for (int j = 0; j < n; j++)
                result[j] = 0;

            int found = 0;
            //double t1 = cpu_time();
            //found = solve_iter(n, p, desired_sum, result);
            //found = cleverBruteForce(n, p, desired_sum, 0, 0, result);
            //double t2 = cpu_time();
            divideArrays (p, n);
            
            //printf("Para n = %d | Found: %d | Time: %.6f seconds ", n, found, t2 - t1);
            
            

            // printf("Result: ");

            //  for (int j = 0; j < n; j++)
            //      printf("%d", result[j]);

            //  printf("\n");

            // break;
        }
    }
    return 0;
}