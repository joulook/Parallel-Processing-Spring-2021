#include <stdlib.h>
#include <stdio.h>
#define n 5
double a[n][n];
double b[n];
double x[n];
double t[n];

int main(int argc, char *argv[]){
  for( int i = 0; i < n; i++ ){
    for( int j = 0; j < n; j++ ){
      a[i][j] = -5 + rand() % (11);
      if(a[i][j] == 0.0)
        a[i][j] = 1.0;
    }    
  }

  for( int i = 0; i < n; i++ ){
    a[i][i] = (rand()% (5*(n+1) - 5*n +1))+5*n;
  }
  printf("\n");
  printf("Matrix A : ");
  printf("\n");
  
  for(int i = 0;i < n; i++){
    for(int j = 0;j <n;j++)
      printf("%f\t", a[i][j]);
    printf("\n");  
  }
  for( int i = 0;i < n; i++ ){
    b[i] = -10 + rand() % (21);
    if(b[i] == 0.0)
      b[i] = 1.0;
  }
  printf("\n");
  printf("Matrix B : ");
  printf("\n");
  for(int i = 0;i < n; i++){
    printf("\n");
    printf("%f\t", b[i]);
  }
  printf("\n");
  for( int i = 0;i < n; i++ ){
    t[i] = 0;
  }

  double eps = 0.0001;
  double sum;
  int end = 0;
  while(end == 0){
    for( int i = 0; i < n; i++ ){
      sum = 0;
      for( int j = 0; j < n; j++ ){
        if(i != j)
          sum = sum + (a[i][j]*t[j]);
      }
      x[i] = (1/a[i][i])*(b[i]-sum);
    }
    int c = 0;
    for( int i = 0; i < n; i++ ){
      if(x[i] >= t[i] && eps >= x[i]-t[i]){
        c++;
      if(x[i] < t[i] && eps >= t[i]-x[i])
        c++;
      }
    }
    if(c == n){
      end = 1;
    }else{
      for( int i = 0; i < n; i++ ){
        t[i] = x[i];
      }    
    }
  }

  printf("\n");
  printf("Matrix X : ");
  for(int i = 0;i < n; i++){
    printf("\n");
    printf("%f\t", x[i]);
  }
  printf("\n");
  return 0;
}

