#include "kernel/types.h"
#include "user/user.h"
int
main()
{  
  int n = 20;
  printf("Comenzando la creación de %d procesos nuevos\n", n);
  for(int i = 0; i < n; i++) {
    int nuevo_proceso = fork();
    if(nuevo_proceso == 0) {
      sleep(i);
      printf("Ejecutando proceso felipe pid: %d\n", getpid());
    
      exit(0);
    }
  }
  for(int i = 0; i < n; i++) {
    wait(0);
  }
  exit(0);
}

