# Tarea 4

## Funcionamiento y lógica del sistema de prioridades

A continuación se motrarán imagenes sobre el funcionamiento de la llamada al sistema, donde se podrá notar el llamado a la función `prueba_tarea4` que se encargará de mostrar los procesos con su respectivo id.

![Evidencia](Funcionando.png) 


## Expliación de las modificaciones realizadas

Ahora bien, para la realización de esta función se tuvieron que modificar archivos por el lado del kernel y por el lado del usuario.

- Kernel:
	* proc.c: Se le añade la linea de codigo `p->prioridad = 0;` y  `p->boost = 1;`, que se será donde se definen las variables para la prioridad de los procesos. Luego se añade `p->prioridad += p->boost;`, `if(p->prioridad >= 9){ p->boost = -1;}` y `if(p->prioridad <= 0){p->boost = 1;}` en el mismo archivo, pero en la parte de schedule(void). 
	* proc.h: En este archivo añadiremos las variables anteriores pero para definirlas, la cual es `int prioridad` y `int boost`
 * file.h: se define la variable para los permisos
 * syscall.c: se define `extern uint64 sys_chmod(void);` y  `[SYS_chmod]  sys_chmod` logrando asi definir esto para posterior uso. 
 * syscall.h: se define `#define SYS_chmod 25`
 * sysfile.c: Luego ya se utiliza la definicion de la ip para darles permisos con valor 3 que serian para lectura y escritura, luego se realizan las condicionales para cada valor de permisos
- User
 * usys.pl: Se generá el ingreso de `entry("chmod");`
 * user.h: Se genera la definicion de chmod para posterior uso.

- Makefile
	* En este caso debemos ingresar el siguiente codigo en la sección de UPROGS añadimos el siguiente codigo: `$U/_prueba_tarea4\` alfinal.

Además de la creacion de un archivo para la funcion el cual sería `prueba_tarea4.c`, donde se implementará el codigo para la creación de los 20 procesos.

```
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"

int main(int argc, char *argv[])
{
    char *path = "/archivo";
    int fd;
    fd = open(path, O_CREATE | O_RDWR);
    if (fd < 0){
        printf("FAILED cración archivo");
        exit(1);
    }
    else{
        printf("Archivo Creado\n");
    }
    printf("Escribiendo...\n");
    fd = open(path, O_RDWR);
    if (write(fd, "sea ha podido escribir esto\n", 18) != 18)
    {
        printf("Er");
        close(fd);
        exit(1);
    }
    close(fd);
    printf("Archivo escrito\n");
    if (chmod(path, 1) < 0){
        printf("FAILED archivo lectura\n");
        exit(1);
    } else{
        printf("Cambio de permisos a solo lectura\n");
    }
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("Prueba de escritura con solo lectura realizado\n");
    }
    else
    {
        printf("FAILED");
        close(fd);
    }
    if (chmod(path, 3) < 0)
    {
        printf("FAILED\n");
        exit(1);
    }
    else
    {
        printf("Cambio a permisos lectura/escritura realizado\n");
    }
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("FAILED \n");
        exit(1);
    }
    if (write(fd, "probando finalmente\n", 12) != 12)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("lectura/escritura validada \n");
    }
    close(fd);
    if (chmod(path, 5) < 0)
    {
        printf("FAILED\n");
        exit(1);
    }
    else
    {
        printf("Permiso cambiado a inmutable\n");
    }
    fd = open(path, O_WRONLY);
    if (fd < 0)
    {
        printf("archivo abierto\n");
    }
    else{   
	printf("FAILED\n");
        close(fd);
    }
    if (chmod(path, 3) < 0) {
        printf("Inmutabilidad Probada\n");
    }
    else {
        printf("FAILED\n");
    }

    printf("FINALIZADO.\n");
    exit(0);
}

```

Y, así es posible correr la funcion prueba_tarea4 luego de correr `make qemu`.


## Dificultades encontradas y soluciones implementadas

En realidad no tuve muchos problemas o complicaciones, la realidad que es fue más senscillo realizar el paso a paso, quizás lo más complejo se podría decir que es la investigación que tuve que hacer para entender que hacer y prueba y error, pero nada que me complique demasiado como las tareas anteriores.
