#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
//size of equations
#define n 10000
//equations
double a[n][n];
//equations answers
double b[n];
//solutions
double x[n];
//one step before solutions
double t[n];
int main(int argc, char *argv[]){
  // i,j --> for loop , c ---> counter for convergence
  int i,j,c;
  // time
  double start_time, stop_time;
  // start timer
  start_time = omp_get_wtime();
  // setting num of threads
  omp_set_num_threads(4);
  // making parallel scope
#pragma omp parallel private ( i , j )
{
//making parallel loop for random initializing
#pragma omp for
  for( i = 0; i < n; i++ ){
    for( j = 0; j < n; j++ ){
      a[i][j] = -5 + rand() % (11);
      if(a[i][j] == 0.0)
        a[i][j] = 1.0;
    }    
  }
//making parallel loop for random initializing of diagonal  
#pragma omp for  
  for( i = 0; i < n; i++ ){
    a[i][i] = (rand()% (5*(n+1) - 5*n +1))+5*n;
  }
//making parallel loop for random initializing  
#pragma omp for
  for( i = 0;i < n; i++ ){
    b[i] = -10 + rand() % (21);
    if(b[i] == 0.0)
      b[i] = 1.0;
  }
//making parallel loop for random initializing  
#pragma omp for
  for( i = 0;i < n; i++ ){
    t[i] = 0;
  }
}
//printing matrices
  printf("\n");
  printf("Matrix A : ");
  printf("\n");
  for( i = 0;i < n; i++){
    for( j = 0;j <n;j++)
      printf("%f\t", a[i][j]);
    printf("\n");  
  }
  printf("\n");
  printf("Matrix B : ");
  printf("\n");
  for( i = 0;i < n; i++){
    printf("\n");
    printf("%f\t", b[i]);
  }
  printf("\n");
// epsilon for convergence  
  double eps = 0.0001;
  double sum;
  int end = 0;
  while(end == 0){
   // making parallel scope and private variables for each thread
#pragma omp parallel private ( i , j , sum) 
{
// calculating solutions for each iterate
#pragma omp for 
    for(  i = 0; i < n; i++ ){
      sum = 0;
      for(  j = 0; j < n; j++ ){
        if(i != j)
          sum = sum + (a[i][j]*t[j]);
      }
      x[i] = (1/a[i][i])*(b[i]-sum);
    }
    c = 0;
 // checking the convergence   
#pragma omp for reduction( +:c )
    for(  i = 0; i < n; i++ ){
      if(x[i] >= t[i] && eps >= x[i]-t[i]){
        c = c+1;
      if(x[i] < t[i] && eps >= t[i]-x[i])
        c = c+1;
      }
    }
    if(c == n){
      end = 1;
    }else{
#pragma omp for    
      for(  i = 0; i < n; i++ ){
        t[i] = x[i];
      }    
    }
}
  }
  //printing solutions  
  printf("\n");
  printf("Matrix X : ");
  for( i = 0;i < n; i++){
    printf("\n");
    printf("%f\t", x[i]);
  }
  printf("\n");
  // stop timer
  stop_time = omp_get_wtime();
  //calculating time
  double run_time = stop_time - start_time;
  printf("\n Execution time was %lf seconds\n ",run_time);
  printf("\n");
  return 0;
}
