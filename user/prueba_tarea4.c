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
