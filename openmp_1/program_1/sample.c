#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]){
  int i;

  #pragma omp parallel shared(i)
  {
    i = omp_get_thread_num();
    printf("thread num = %d\n", i);
  }

  return 0;
}
