#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
//size of data
#define n 10
//data array
int data[n];
//finding the place of pivot
int partition(int data[],int s,int f){
  int index = s-1;
  int pivot = data[f];
  for(int i=s ; i<=f-1; i++){
    if(data[i] < pivot){
       index++;
       int temp = data[index];
       data[index] = data[i];
       data[i] = temp;
    }
  }
  int temp = data[index+1];
  data[index+1] = data[f];
  data[f] = temp;
  return (index+1);
}

void quicksort(int data[],int s,int f){
  int p;
  if(s < f){
    p = partition(data,s,f);
    //make recursion in parallel
    #pragma omp task default(none) firstprivate(data,s,p)
    {
      quicksort(data,s,p-1);
    }
    #pragma omp task default(none) firstprivate(data,f,p)
    {
      quicksort(data,p+1,f);
    }
  }
}

int main(int argc, char *argv[]){
  int i;
  double start_time, stop_time;
  //generating random numbers
  for( int i = 0; i < n; i++ ){
    data[i] = rand() % 1000 +1;
  }
  printf("\n");
  printf("Input : ");
  printf("\n");
  for( i = 0;i < n; i++){
  printf("%d\t", data[i]);
  }
  printf("\n");
  //set num of threads
  omp_set_num_threads(2);
  // start timer
  start_time = omp_get_wtime();
  // creating master thread
  #pragma omp parallel default(none) shared(data)
  {
    #pragma omp single nowait
    {
      quicksort(data,0,n-1);
    }
  }
  // stop timer
  stop_time = omp_get_wtime();
  printf("\n");
  printf("output : ");
  printf("\n");
  for( i = 0;i < n; i++){
  printf("%d\t", data[i]);
  }
  printf("\n");
  // output time
  double run_time = stop_time - start_time;
  printf("\n Execution time was %lf seconds\n ",run_time);
  printf("\n");
  return 0;
}
