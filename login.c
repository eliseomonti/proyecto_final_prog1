#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "pila.h"
#include <ctype.h>
#include <time.h>

///Crear un usuario

void crear_usuario(char archivo_usuario[])
{

    stUsuario a;
    char contrasenia[20];

    FILE *archivo = fopen(archivo_usuario,"ab");

    if(archivo != NULL)
    {

        printf("Ingrese un nombre de usuario. \n");
        fflush(stdin);
        gets(a.usuario);

        while (usuario_existe(archivo_usuario, a.usuario))
        {
            system("cls");
            printf("Este nombre ya esta en uso. Ingrese otro. \n");
            fflush(stdin);
            gets(a.usuario);
        }
        system("cls");
        do
        {

            printf("Ingrese una contrasenia. \n");
            fflush(stdin);
            gets(a.contrasenia);

            printf("Confirme su contrasenia. \n");
            fflush(stdin);
            gets(contrasenia);

            if(strcmp(contrasenia,a.contrasenia)!=0)
            {
                system("cls");
                printf("Las contrasenias no coinciden, ingreselas nuevamente. \n");

            }

        }
        while(strcmp(contrasenia,a.contrasenia)!=0);

        fwrite(&a,sizeof(stUsuario),1,archivo);
        printf("Usuario cargado correctamente. \n");

        fclose(archivo);

    }

}

///Verifica si el nombre de usuario ya fue usado

int usuario_existe(char archivo_usuario[], char usuario[])
{

    stUsuario a;

    FILE *archivo = fopen(archivo_usuario, "rb");

    if (archivo != NULL)
    {
        while (fread(&a, sizeof(stUsuario), 1, archivo))
        {
            if (strcmp(a.usuario, usuario) == 0)
            {
                fclose(archivo);
                return 1;
            }
        }
        fclose(archivo);
    }
    return 0;
}

///LOGIN

int login(char archivo_usuario[])
{
    int flag =0;

    char usuario[20];
    char contrasenia[20];
    stUsuario a;

    printf("Ingrese su nombre de usuario. \n");
    fflush(stdin);
    gets(usuario);

    printf("Ingrese su contrasenia \n");
    fflush(stdin);
    gets(contrasenia);

    FILE *archivo = fopen(archivo_usuario,"rb");

    if(archivo != NULL)
    {

        while(fread(&a,sizeof(stUsuario),1,archivo))
        {

            if(strcmp(usuario,a.usuario)==0 && strcmp(contrasenia,a.contrasenia)==0)
            {

                flag = 1;

            }

        }

        fclose(archivo);
    }

    return flag;
}
