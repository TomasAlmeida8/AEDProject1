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




//Função Brute-force 
char bruteForce(int n,integer_t p[],integer_t desired_sum,int result[])
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

//Função Branch and Bound

char branchAndBound(int n,integer_t *p,integer_t desired_sum,integer_t current_sum,int current_index,int result[])
{
    if(current_sum==desired_sum)
        return 1;

    if(current_sum>desired_sum)
        return 0;
    
    if(current_index==n)
        return 0;

    
    for (int index = current_index; index < n; index++){
        result[index] = 1;
        if(branchAndBound(n, p, desired_sum, current_sum + p[index], ++current_index,result))
            return 1;
        result[index]= 0;
    }

    return 0;
}


//--------------------------------------------------------------------3ª Função-----------------------------------------------------------------------------------
void swap(integer_t *a, integer_t *b)
{
    integer_t t = *a;
    *a = *b;
    *b = t;
}



/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
integer_t partition (integer_t array[], integer_t low, integer_t high)
{
    // pivot (Element to be placed at right position)
    integer_t pivot = array[high];  
 
    integer_t i = (low - 1);  // Index of smaller element and indicates the 
                   // right position of pivot found so far

    for (integer_t j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (array[j] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}



/* low  --> Starting index,  high  --> Ending index */
void quickSort(integer_t array[], integer_t low, integer_t high){
    
    if (low < high)
    {
        /* pi is partitioning index, arr[pi] is now
           at right place */
        integer_t pi = partition(array, low, high);

        quickSort(array, low, pi - 1);  // Before pi
        quickSort(array, pi + 1, high); // After pi
    }
}


int decimalToBinary(integer_t n, integer_t c, int index, int result[]){


  for (integer_t i = index; i < (c+index); i++)
  {
    integer_t k = (n>>(i-index));

    if (k & 1)
      result[i]=1;
    else
      result[i]=0;
  }

  return 0;
}

//Função final
char meetInMiddle(integer_t sum1[], integer_t sum2[], integer_t s1, integer_t s2, integer_t desired_sum,int result[], integer_t sum11[], integer_t sum22[], int x1, int x2){

    
    integer_t k1 = 0;
    integer_t k2 = s2-1;

    while (k1 < s1 && k2 >= 0){
        if (sum1[k1] + sum2[k2] == desired_sum){
            for(integer_t count1 = 0; count1 < s1; count1++){
                if(sum11[count1] == sum1[k1]){
                    decimalToBinary(count1, x1, 0, result);
                    break;
                }
            }
            for(integer_t count2 = 0; count2 < s2; count2++){
                if(sum22[count2] == sum2[k2]){
                    decimalToBinary(count2, x2, x1, result);
                    break;
                }
            }
            return 1;

        } else if (sum1[k1] + sum2[k2] > desired_sum){
            k2--;
        } else if (sum1[k1] + sum2[k2] < desired_sum){
            k1++;
        } 
    }
    return 0;
}


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
        integer_t *p = all_subset_sum_problems[i].p; // The weights
        int n = all_subset_sum_problems[i].n; // The value of n
            

            //Tirar proxima linha de comentário se pretende executar o Meet in the Middle bem como a linha 343

             double tempoSums1 = cpu_time();
            int x1 = n/2 + n%2; //tamanho array 1
            int x2 = n/2; //tamanho array 2
            int x3 = 0 ; //counter para adicionar ao segundo array

            integer_t s1 = 1<<x1; //tamanho array soma 1
            integer_t s2 = 1<<x2; //tamanho array soma 2


            integer_t firstHalf[x1]; //criaçao primeiro array
            integer_t secondHalf[x2]; //criaçao segundo array
            integer_t *sum1; //criaçao array soma 1
            integer_t *sum2; //criaçao array soma 2
            integer_t *sum11; //criaçao outro array sum1 usado para o res em binario
            integer_t *sum22; //criaçao outro array sum2 usado para o res em binario

            sum1 = (integer_t *)malloc(s1 * sizeof(integer_t));
            sum2 = (integer_t *)malloc(s2 * sizeof(integer_t));
            sum11 = (integer_t *)malloc(s2 * sizeof(integer_t));
            sum22 = (integer_t *)malloc(s2 * sizeof(integer_t));


            //Adicionar os numeros aos arrays 1 e 2
            for (int i = 0; i < n; i++){
                if (i < (n/2+n%2)){
                    firstHalf[i]=p[i]; //adicionar ao primeiro array
                } else {
                    secondHalf[x3]=p[i]; //adicionar ao segundo array
                    x3++;
                }
            }

            //Fazer soma array 1 e adicionar ao array sum1
            for (integer_t i = 0;i < s1; i++){

               integer_t soma1=0;

                for (int j = 0; j < n; j++){
                    if (i & (1ull<<j)){
                        soma1 += firstHalf[j];
                    }
                }
                sum1[i] = soma1;
                sum11[i] = soma1;
            }

            //Fazer soma array 2 e adicionar ao array sum2
            for (integer_t i = 0; i < s2; i++){

                integer_t soma2=0;

                for (int j = 0; j < n; j++){
                    if (i & (1ull<<j)){
                        soma2 += secondHalf[j];
                    }
                }
                sum2[i] = soma2;
                sum22[i] = soma2;
            }

            // for (int counter = 0; counter < s1; counter++){
            //     printf("%lld  ",sum1[counter]);
            // }

            quickSort(sum1, 0, s1-1);
            quickSort(sum2,0,s2-1);

           double tempoSums2 = cpu_time();

           double tempoSums = (tempoSums2 - tempoSums1) / (double)20;


            

        if (n > 60)
            continue; // Skip large values of n

        
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            
            // Array with the result
            int result[n];
            for (int j = 0; j < n; j++)
                result[j] = 0;

            char found;
            double t1 = cpu_time();

            //Tirar proxima linha de comentário se pretende executar o Brute-Force

            //found = bruteForce(n, p, desired_sum, result);



            //Tirar proxima linha de comentário se pretende executar o Recursiva

            //found = branchAndBound(n, p, desired_sum, 0, 0, result);



            //Tirar proxima linha de comentário se pretende executar o Meet in the Middle bem como as linhas 240-305

            found = meetInMiddle(sum1, sum2, s1, s2, desired_sum, result, sum11, sum22, x1, x2);




            double t2 = cpu_time();
            
            
            // printf("Para n = %d | Found: %d | Time: %.6f seconds ", n, found, (t2 - t1)+tempoSums);
            

            // printf("Result: ");

            //  for (int j = 0; j < n; j++)
            //      printf("%d", result[j]);

            //  printf("\n");

            //break; //1 n ou varios n's.
            
            printf("%d %d %d %d %f\n", 2, n, k, found, (t2 - t1)+tempoSums);
            
        }

 
    }

    return 0;
}