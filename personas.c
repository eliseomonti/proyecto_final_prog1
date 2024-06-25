#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "pila.h"
#include <ctype.h>
#include <time.h>



///Agregar una persona

void agregar_persona(char nombrearchivo[])
{

    Persona a;
    int dniValido = 0;
    int telefonoValido = 0;

    FILE *archivo = fopen(nombrearchivo,"ab");

    if(archivo != NULL)
    {

        while (!dniValido)
        {
            printf("dni: \n");
            fflush(stdin);
            scanf("%i", &a.dni);

            if (buscar_persona(nombrearchivo, a.dni) == -1)
            {
                dniValido = 1;
            }
            else
            {
                system("cls");
                printf("El DNI ya existe. Ingrese un DNI valido.\n");
            }
        }

        system("cls");
        printf("Nombre completo: \n");
        fflush(stdin);
        gets(a.nombre);

        system("cls");
        while (!telefonoValido)
        {
            printf("Telefono: \n");
            fflush(stdin);
            gets(a.telefono);

            telefonoValido = 1;
            for (int i = 0; a.telefono[i] != '\0'; i++)
            {
                if (!isdigit(a.telefono[i]))
                {
                    telefonoValido = 0;
                    system("cls");
                    printf("El telefono debe contener solo numeros. Ingrese un telefono valido.\n");
                    break;
                }
            }
        }

        system("cls");
        printf("Direccion: \n");
        fflush(stdin);
        gets(a.direccion);

        strcpy(a.rol,"comprador");

        fwrite(&a,sizeof(Persona),1,archivo);
        printf("Persona cargada exitosamente. \n");

        fclose(archivo);
    }
}

///Modificar una persona
//Esta funcion puede utilizar estos archivos.
char archivo_autos[] = "autos.dat";
char archivo_ventas[] = "ventas.bin";


void modificar_persona(char nombrearchivo[])
{

    Persona a;
    int dniValido = 0;
    int telefonoValido = 0;
    int dniViejo;
    int opcion;

    int dni;
    printf("Ingrese el DNI de la persona que desea modificar. \n");
    fflush(stdin);
    scanf("%i",&dni);

    int posicion = buscar_persona(nombrearchivo,dni);

    if(posicion == -1)
    {
        system("cls");
        printf("Persona inexistente. \n");
        return;
    }

    int posicion_final = posicion * sizeof(Persona);

    FILE *archivo = fopen(nombrearchivo,"r+b");

    if(archivo != NULL)
    {

        do
        {
            system("cls");

            printf("\n******************************\n");
            printf("*                            *\n");
            printf("*  Seleccione que desea       *\n");
            printf("*  modificar.                 *\n");
            printf("*                            *\n");
            printf("******************************\n");
            printf("*                            *\n");
            printf("*  1. DNI                     *\n");
            printf("*                            *\n");
            printf("******************************\n");
            printf("*                            *\n");
            printf("*  2. Nombre                  *\n");
            printf("*                            *\n");
            printf("******************************\n");
            printf("*                            *\n");
            printf("*  3. Telefono                *\n");
            printf("*                            *\n");
            printf("******************************\n");
            printf("*                            *\n");
            printf("*  4. Direccion               *\n");
            printf("*                            *\n");
            printf("******************************\n");
            printf("*                            *\n");
            printf("*  0. Volver al menu          *\n");
            printf("*                            *\n");
            printf("******************************\n");

            fflush(stdin);
            scanf("%i",&opcion);

            fseek(archivo,posicion_final,SEEK_SET);
            fread(&a,sizeof(Persona),1,archivo);

            switch(opcion)
            {

            case 1:
                system("cls");
                dniViejo = a.dni;
                while (!dniValido)
                {
                    printf("dni: \n");
                    fflush(stdin);
                    scanf("%i", &a.dni);

                    if (buscar_persona(nombrearchivo, a.dni) == -1)
                    {
                        dniValido = 1;
                    }
                    else
                    {
                        system("cls");
                        printf("El DNI ya existe. Ingrese un DNI valido.\n");
                    }
                }
                Rescribir_dni(archivo_ventas,archivo_autos,dniViejo,a.dni);
                break;
            case 2:
                system("cls");
                printf("Nombre completo: \n");
                fflush(stdin);
                gets(a.nombre);
                break;
            case 3:
                system("cls");
                while (!telefonoValido)
                {
                    printf("Telefono: \n");
                    fflush(stdin);
                    gets(a.telefono);

                    telefonoValido = 1;
                    for (int i = 0; a.telefono[i] != '\0'; i++)
                    {
                        if (!isdigit(a.telefono[i]))
                        {
                            telefonoValido = 0;
                            printf("El telefono debe contener solo numeros. Ingrese un telefono valido.\n");
                            break;
                        }
                    }
                }
                break;
            case 4:
                system("cls");
                printf("Direccion: \n");
                fflush(stdin);
                gets(a.direccion);
                break;
            case 0:
                system("cls");
                fclose(archivo);
                break;
            }

            fseek(archivo,posicion_final,SEEK_SET);
            fwrite(&a,sizeof(Persona),1,archivo);


        }
        while(opcion != 0);

        fclose(archivo);
    }

}

///Modifica tanto los archivos de venta como de autos si se modifica el dni del titular.
void Rescribir_dni(char archivo_ventas[],char archivo_autos[],int dniViejo,int dniNuevo)
{

    Venta a;
    AutoArchivo b;

    FILE *archivoVentas = fopen(archivo_ventas,"r+b");
    FILE *archivoAutos = fopen(archivo_autos,"r+b");

    if(archivoVentas != NULL && archivoAutos != NULL)
    {

        while(fread(&a,sizeof(Venta),1,archivoVentas))
        {

            if(a.dniComprador == dniViejo)
            {

                a.dniComprador = dniNuevo;
                fseek(archivoVentas, -sizeof(Venta), SEEK_CUR);
                fwrite(&a, sizeof(Venta), 1, archivoVentas);
                fseek(archivoVentas, 0, SEEK_CUR);

            }

        }

        while(fread(&b,sizeof(AutoArchivo),1,archivoAutos))
        {

            if(b.dniTitular == dniViejo)
            {

                b.dniTitular = dniNuevo;
                fseek(archivoAutos, -sizeof(AutoArchivo), SEEK_CUR);
                fwrite(&b, sizeof(AutoArchivo), 1, archivoAutos);
                fseek(archivoAutos, 0, SEEK_CUR);

            }

        }

        fclose(archivoVentas);
        fclose(archivoAutos);
    }

}

///Busca una persona, si se encuentra retorna la posicisión, si no retorna -1

int buscar_persona(char nombrearchivo[],int dni)
{

    Persona a;

    int posicion = -1;
    int contador = 0;

    FILE *archivo = fopen(nombrearchivo,"rb");

    if(archivo != NULL)
    {

        while(fread(&a,sizeof(Persona),1,archivo))
        {

            if(a.dni == dni)
            {

                posicion = contador;
                break;

            }

            contador++;

        }

        fclose(archivo);
    }

    return posicion;

}

/// Muestra el listado de todas las personas (nombre,apellido y dni)

void mostrar_lista_personas(char nombrearchivo[])
{

    Persona a;

    FILE *archivo = fopen(nombrearchivo,"rb");

    if(archivo != NULL)
    {


        printf("|---------------------|-----------|\n");
        printf("|%-20s | %-10s|\n", "Nombre", "DNI");

        while(fread(&a,sizeof(Persona),1,archivo))
        {
            if(strcmp(a.rol,"comprador")== 0)
            {
                printf("|---------------------|-----------|\n");
                printf("|%-20s | %-10i|\n", a.nombre, a.dni);
            }
        }

        printf("|---------------------|-----------|\n");

        fclose(archivo);
    }

}

///Muestra todos los datos de una persona en especifico.

void mostrar_persona(char nombrearchivo[])
{

    Persona a;

    int dni;
    printf("DNI de la persona que busca:\n");
    fflush(stdin);
    scanf("%i",&dni);

    int posicion = buscar_persona(nombrearchivo,dni);

    if(posicion == -1)
    {
        system("cls");
        printf("Persona inexistente. \n");
        return;
    }
    system("cls");
    int posicion_final = posicion * sizeof(Persona);

    FILE *archivo = fopen(nombrearchivo,"rb");

    if(archivo != NULL)
    {

        fseek(archivo,posicion_final,SEEK_SET);
        fread(&a,sizeof(Persona),1,archivo);

        printf("|------------|------------------------------|\n");
        printf("| %-10s | %-28s |\n", "Nombre:", a.nombre);
        printf("|------------|------------------------------|\n");
        printf("| %-10s | %-28i |\n", "Dni:", a.dni);
        printf("|------------|------------------------------|\n");
        printf("| %-10s | %-28s |\n", "Telefono:", a.telefono);
        printf("|------------|------------------------------|\n");
        printf("| %-10s | %-28s |\n", "Direccion:", a.direccion);
        printf("|------------|------------------------------|\n");

        fclose(archivo);
    }

}

///Menu personas
void menu_personas(char archivo_personas[])
{

    int opcion;

    do
    {

        printf("\n******************************\n");
        printf("*                            *\n");
        printf("*  1. Agregar una persona.   *\n");
        printf("*                            *\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*  2. Modificar los datos    *\n");
        printf("*     de una persona.        *\n");
        printf("*                            *\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*  0. Volver al menu         *\n");
        printf("*     principal.             *\n");
        printf("*                            *\n");
        printf("******************************\n");

        fflush(stdin);
        scanf("%i",&opcion);

        if(opcion == 0|| opcion == 1 || opcion == 2)
        {
            switch(opcion)
            {

            case 1:
                system("cls");
                agregar_persona(archivo_personas);
                volver_menu();
                break;
            case 2:
                system("cls");
                modificar_persona(archivo_personas);
                break;
            case 0:
                system("cls");
                break;

            }
        }
        else
        {
            system("cls");
            printf("Ingrese una opcion valida.\n");

        }
    }
    while(opcion != 0);

}
