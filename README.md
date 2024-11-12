# Tarea 3

## Funcionamiento y lógica del sistema de prioridades

A continuación se motrarán imagenes sobre el funcionamiento de la llamada al sistema, donde se podrá notar el llamado a la función `test_protect`. Así, se logro implementar las funciones mprotect y munprotect., donde cada funcion tendra su región de memoria y largo.

![Evidencia](Funcionando.png) 


## Expliación de las modificaciones realizadas

Ahora bien, para la realización de esta función se tuvieron que modificar archivos por el lado del kernel y por el lado del usuario.

- Kernel:
	* proc.c: Se define la función mprotect `int mprotect(void *addr, int len){..}` y la función munprotect `int munprotect(void *addr, int len){..}` para luego ya ser llamados.
	* proc.h: En este archivo añadiremos las funciones anteriores pero para definirlas, la cual es `int mprotect(void *addr, int len);` y `int munprotect(void *addr, int len);`
    * syscall.c: En este archivo se define para ambas funciones el siguiente codigo `extern uint64 sys_mprotect(void);` y `extern uint64 sys_munprotect(void);`. Además se define `[SYS_mprotect] sys_mprotect` y `[SYS_munprotect] sys_munprotect`. Donde por ultimo debemos definir  `uint64 sys_mprotect(void){..}` y `uint64 sys_munprotect(void){..}` para lograr ambas funciones.
    * syscall.h En este archivo debemos definir las variables previamente mencionadas la cual es `#define SYS_mprotect 23` y `#define SYS_munprotect 24`

- Makefile: En este caso debemos ingresar el siguiente codigo en la sección de UPROGS añadimos el siguiente codigo: `$U/_test_protect\` alfinal para definir la función.
  
- User
    * user.h: Se definen las funciones `int mprotect(void *addr, int len);` y `int munprotect(void *addr, int len);`
    * usys.pl: Se define tanto  `entry("mprotect"); y `entry("munprotect");`


Además de la creacion de un archivo para la funcion el cual sería `test_protect.c`, donde se implementará el codigo con las funciones mprotect y munprotect

```
#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"
#define PAGE_SIZE 4096
int main() 
{
    int size = PAGE_SIZE; 
    void *addr = sbrk(size);
    if (addr == (void *)-1) {
      printf("sbrk failed\n");
      exit(1);
    }
    char *p = (char *)addr;
    for (int i = 0; i < size; i++) {
        p[i] = 'A';
    }
    if (mprotect(addr, 1) < 0) {
        printf("mprotect failed\n");
        exit(1);
	}
    int success = 1;
    if (fork() == 0) {
        p[0] = 'B';
        success = 0;
        exit(0);
    } else {
        wait(0);
    }
    if (success) {
        printf("mprotect ha funcionado\n");
    } else {
        printf("mprotect test failed: write succeeded on protected memory\n");
    }
    if (munprotect(addr, 1) < 0) {
        printf("munprotect failed\n");
        exit(1);
    }
    p[0] = 'C';
    printf("munprotect ha funcionado\n");
    exit(0);
}

```

Y, así es posible correr la funcion test_protect luego de correr `make qemu`.


## Dificultades encontradas y soluciones implementadas


Personalmente la dificultad que tuve es en el area investigativa, aunque si se dio un repositorio para llevar a cabo esto, personalmente siento que tuve que realizar varias personalizaciones al codigo, además de que no logro cierto entendimiento de ciertas partes de la logica, por lo tanto, investigar para entender también me atrasa en el progreso.

Uno de los pequeñas dificultades que tuve fue con el direccionamiento y correcta definición de las funciones para llevar a cabo el programa, sin embargo, luego de revisión con la metodologia de las tareas anteriores pude recordar cual era los archivos requeridos para lograr esta implementación de manera correcta.

![Evidencia2](Error.png) 

El error era basicamente que olvide el uso de user.h
