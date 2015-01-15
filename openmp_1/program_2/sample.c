#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
  int sum = 0;

  #pragma omp parallel private(sum)
  {
    #pragma omp critical
    {
      sum += omp_get_thread_num();
    }
  }

  printf("sum = %d\n", sum);

  return 0;
}
