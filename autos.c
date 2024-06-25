#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "pila.h"
#include <ctype.h>
#include <time.h>


///Agrega un auto

void agregar_auto(char nombreArchivo[])
{
    AutoArchivo a;
    Patente p;
    int patenteValida = 0;
    int anioValido = 0;
    int anioActual = obtenerAnioActual();

    FILE *archi = fopen(nombreArchivo, "ab");

    if(archi != NULL)
    {

        while (!patenteValida)
        {
            printf("Patente (letras): \n");
            fflush(stdin);
            scanf("%3s", p.letras);
            printf("Patente (numeros): \n");
            fflush(stdin);
            scanf("%3s", p.numeros);

            if (ValidarPatente(p))
            {
                if (buscar_auto(nombreArchivo, p) == -1)
                {
                    patenteValida = 1;
                }
                else
                {
                    system("cls");
                    printf("La patente ya existe. Ingrese una patente valida.\n");
                }
            }
            else
            {
                system("cls");
                printf("Patente invalida. \n");
            }
        }

        strncpy(a.patente.letras, p.letras, 3);
        strncpy(a.patente.numeros, p.numeros, 3);
        a.patente.letras[3] = '\0';
        a.patente.numeros[3] = '\0';

        system("cls");
        printf("Marca: \n");
        fflush(stdin);
        gets(a.marca);

        system("cls");
        printf("Modelo: \n");
        fflush(stdin);
        gets(a.modelo);

        system("cls");
        while (!anioValido)
        {
            printf("Anio: \n");
            fflush(stdin);
            scanf("%i", &a.anio);
            if (a.anio <= anioActual)
            {
                anioValido = 1;
            }
            else
            {
                system("cls");
                printf("Ingrese una fecha valida. \n", anioActual);
            }
        }
        system("cls");
        printf("Kms: \n");
        fflush(stdin);
        scanf("%i", &a.kms);

        system("cls");
        printf("Valor de adquisicion: \n");
        fflush(stdin);
        scanf("%f", &a.precioDeAdquisicion);

        a.dniTitular = 123456789; // dni de la concesionaria

        fwrite(&a, sizeof(AutoArchivo), 1, archi);
        system("cls");
        printf("Auto cargado correctamente. \n");
        fclose(archi);
    }

}

///Verifica si la patente esta ingresada correctamente. (3 letras y 3 numeros)

int ValidarPatente(Patente p)
{
    for (int i = 0; i < 3; i++)
    {
        if (!isalpha(p.letras[i]))
        {
            return 0; // No es una letra
        }
        if (!isdigit(p.numeros[i]))
        {
            return 0; // No es un numero
        }
    }
    return 1;
}


///Modifica un auto
char archivo_personas[] = "personas.dat"; //esta funcion utiliza el archivo de personas.

void modificar_auto(char nombreArchivo[])
{

    AutoArchivo a;
    Patente b,p;
    int patenteValida = 0;
    int anioValido = 0;
    int dniValido = 0;
    int anioActual = obtenerAnioActual();
    int opcion;

    printf("Ingrese la patente que desea buscar. \n");
    printf("Letras: \n");
    fflush(stdin);
    scanf("%3s",&b.letras);
    printf("Numeros: \n");
    fflush(stdin);
    scanf("%3s",&b.numeros);

    int posicion = buscar_auto(nombreArchivo,b);

    if(posicion == -1)
    {
        system("cls");
        printf("Patente inexistente. \n");
        return;

    }


    int posicion_final = posicion * sizeof(AutoArchivo);

    FILE *archivo = fopen(nombreArchivo,"r+b");

    if(archivo != NULL)
    {

        do
        {
            system("cls");

            printf("\n************************************\n");
            printf("*    Seleccione que desea modificar  *\n");
            printf("************************************\n");
            printf("*                                  *\n");
            printf("*    1. Patente.                    *\n");
            printf("*                                  *\n");
            printf("*    2. Marca.                      *\n");
            printf("*                                  *\n");
            printf("*    3. Modelo.                     *\n");
            printf("*                                  *\n");
            printf("*    4. Anio.                       *\n");
            printf("*                                  *\n");
            printf("*    5. Kms.                        *\n");
            printf("*                                  *\n");
            printf("*    6. Valor de adquisicion.       *\n");
            printf("*                                  *\n");
            printf("*    7. Dni del titular.            *\n");
            printf("*                                  *\n");
            printf("*    0. Volver al menu              *\n");
            printf("************************************\n");

            fflush(stdin);
            scanf("%i",&opcion);

            fseek(archivo,posicion_final,SEEK_SET);
            fread(&a,sizeof(AutoArchivo),1,archivo);

            switch(opcion)
            {

            case 1:
                system("cls");
                while (!patenteValida)
                {
                    printf("Patente (letras): \n");
                    fflush(stdin);
                    scanf("%3s", p.letras);
                    printf("Patente (numeros): \n");
                    fflush(stdin);
                    scanf("%3s", p.numeros);

                    if (ValidarPatente(p))
                    {
                        if (buscar_auto(nombreArchivo, p) == -1)
                        {
                            patenteValida = 1;
                        }
                        else
                        {
                            system("cls");
                            printf("La patente ya existe. Ingrese una patente valida.\n");
                        }
                    }
                    else
                    {
                        system("cls");
                        printf("Patente invalida. \n");
                    }
                }

                strncpy(a.patente.letras, p.letras, 3);
                strncpy(a.patente.numeros, p.numeros, 3);
                a.patente.letras[3] = '\0';
                a.patente.numeros[3] = '\0';
                break;
            case 2:
                system("cls");
                printf("Marca: \n");
                fflush(stdin);
                gets(a.marca);
                break;
            case 3:
                system("cls");
                printf("Modelo: \n");
                fflush(stdin);
                gets(a.modelo);
                break;
            case 4:
                system("cls");
                while (!anioValido)
                {
                    printf("Anio: \n");
                    fflush(stdin);
                    scanf("%i", &a.anio);
                    if (a.anio <= anioActual)
                    {
                        anioValido = 1;
                    }
                    else
                    {
                        printf("Ingrese una fecha valida. \n", anioActual);
                    }
                }
                break;
            case 5:
                system("cls");
                printf("Kms: \n");
                fflush(stdin);
                scanf("%i", &a.kms);
                break;
            case 6:
                system("cls");
                printf("Valor de adquisicion: \n");
                fflush(stdin);
                scanf("%f", &a.precioDeAdquisicion);
                break;
            case 7:
                system("cls");
                if(!dniValido)
                {
                    printf("DNI: \n");
                    fflush(stdin);
                    scanf("%i", &a.dniTitular);

                    if (buscar_dni_comprador(archivo_personas, a.dniTitular))
                    {
                        dniValido = 1;
                    }
                    else
                    {
                        system("cls");
                        printf("DNI no encontrado. \n");
                        volver_menu();

                    }
                }
                break;
            case 0:
                system("cls");
                close(archivo);
                break;

            }

            fseek(archivo,posicion_final,SEEK_SET);
            fwrite(&a,sizeof(AutoArchivo),1,archivo);

        }
        while(opcion != 0);

        fclose(archivo);
    }

}

///Busca un auto, si se encuentra retorna la posicisión, si no retorna -1

int buscar_auto(char nombrearchivo[],Patente p)
{

    AutoArchivo a;

    int posicion = -1;
    int contador = 0;

    FILE *archivo = fopen(nombrearchivo,"rb");

    if(archivo != NULL)
    {

        while(fread(&a,sizeof(AutoArchivo),1,archivo))
        {

            if(strcmp(a.patente.letras,p.letras)==0 && strcmp(a.patente.numeros,p.numeros)==0)
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

///Muestra la lista de todos los autos recursivamente
void mostrarListadoAutosRecursivo(FILE *archi)
{
    AutoArchivo a;
    if(fread(&a, sizeof(AutoArchivo), 1, archi) == 1)
    {
        printf("------------\n");
        printf("Marca: %s\n", a.marca);
        printf("Modelo: %s\n", a.modelo);
        printf("Patente: %s %s\n", a.patente.letras, a.patente.numeros);
        printf("------------\n");
        mostrarListadoAutosRecursivo(archi);
    }
}

void mostrarListadoAutos2Recursividad(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    if(archi != NULL)
    {
        mostrarListadoAutosRecursivo(archi);
        fclose(archi);
    }
}

///Muestra los autos que estan en venta

void mostrarAutoEnVenta(Auto arreglo[],int validos)
{
    for(int i=0; i<validos; i++)
    {
        if(strcmp(arreglo[i].Titular.rol,"vendedor")==0)
        {
            printf("------------\n");
            printf("Patente: %s %s\n", arreglo[i].patente.letras, arreglo[i].patente.numeros);
            printf("Marca: %s\n", arreglo[i].marca);
            printf("Modelo: %s\n", arreglo[i].modelo);
            printf("Anio: %d\n", arreglo[i].anio);
            printf("------------\n");
        }
    }


}

///Muestra la info de un auto en especifico

void mostrarInfoAuto(Auto arreglo[],int validos)
{

    int i=0;
    Patente p;

    printf("Ingrese las letras de la patente: \n");
    fflush(stdin);
    scanf("%3s", &p.letras);
    printf("Ingrese los numeros de la patente: \n");
    fflush(stdin);
    scanf("%3s", &p.numeros);

    system("cls");

    while(i<validos)
    {
        if(strcmp(arreglo[i].patente.letras,p.letras) == 0 && strcmp(arreglo[i].patente.numeros,p.numeros) == 0)
        {

            printf("------------\n");
            printf("Patente: %s %s\n", arreglo[i].patente.letras, arreglo[i].patente.numeros);
            printf("Marca: %s\n", arreglo[i].marca);
            printf("Modelo: %s\n", arreglo[i].modelo);
            printf("Anio: %d\n", arreglo[i].anio);
            printf("Kilometraje: %d\n", arreglo[i].kms);
            printf("Precio de Adquisicion: %.2f\n", arreglo[i].precioDeAdquisicion);
            printf("\n");
            printf("Datos del titular: \n");
            printf("DNI: %d\n", arreglo[i].Titular.dni);
            printf("Nombre: %s\n", arreglo[i].Titular.nombre);
            printf("Telefono: %s\n", arreglo[i].Titular.telefono);
            printf("Direccion: %s\n", arreglo[i].Titular.direccion);
            printf("------------\n");
        }
        i++;
    }
}

///Menu Autos
void menu_autos(char archivo_autos[])
{

    int opcion;

    do
    {
        printf("\n******************************\n");
        printf("*                            *\n");
        printf("*  1. Agregar un auto al     *\n");
        printf("*     sistema.               *\n");
        printf("*                            *\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*  2. Modificar los datos    *\n");
        printf("*     de un auto.            *\n");
        printf("*                            *\n");
        printf("******************************\n");
        printf("*                            *\n");
        printf("*  0. Volver al menu         *\n");
        printf("*     principal.             *\n");
        printf("*                            *\n");
        printf("******************************\n");


        fflush(stdin);
        scanf("%i",&opcion);
        if(opcion ==0 || opcion == 1 || opcion == 2)
        {
            switch(opcion)
            {

            case 1:
                system("cls");
                agregar_auto(archivo_autos);
                volver_menu();
                break;
            case 2:
                system("cls");
                modificar_auto(archivo_autos);
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

///Carga un arreglo de la estructura autos con los datos de AutoArchivo y Personas

int cargar_arreglo_autos(char archivo_autos[], char archivo_personas[],Auto arreglo[])
{

    int i = 0;

    FILE *archivoAutos = fopen(archivo_autos, "rb");
    FILE *archivoPersonas = fopen(archivo_personas, "rb");

    if (archivoAutos != NULL && archivoPersonas != NULL)
    {
        AutoArchivo a;
        Persona b;

        while (fread(&a, sizeof(AutoArchivo), 1, archivoAutos))
        {
            rewind(archivoPersonas);
            while (fread(&b, sizeof(Persona), 1, archivoPersonas))
            {
                if (a.dniTitular == b.dni)
                {
                    strcpy(arreglo[i].patente.letras,a.patente.letras);
                    strcpy(arreglo[i].patente.numeros,a.patente.numeros);
                    strcpy(arreglo[i].marca, a.marca);
                    strcpy(arreglo[i].modelo, a.modelo);
                    arreglo[i].anio = a.anio;
                    arreglo[i].kms = a.kms;
                    arreglo[i].Titular = b;
                    arreglo[i].precioDeAdquisicion = a.precioDeAdquisicion;
                    i++;
                    break;
                }
            }
        }

        fclose(archivoAutos);
        fclose(archivoPersonas);
    }

    return i;
}
