#include "kernel/types.h"
#include "user/user.h"
int
main()
{
  int cantidad_procesos = 20;
  printf("Comenzando la creación de %d procesos nuevos\n", cantidad_procesos);
  for(int i = 0; i < cantidad_procesos; i++) {
    int nuevo_proceso = fork();
    if(nuevo_proceso == 0) {
      sleep(i);
      printf("Ejecutando proceso felipe pid: %d\n", getpid());
      exit(0);
    }
    wait(0);
  }
  exit(0);
}

