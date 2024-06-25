#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "pila.h"
#include <ctype.h>
#include <time.h>

/// Cargar una venta

void registrarVenta(Auto arreglo[],int validos,char archivo_autos[],char archivo_personas[],char archivo_ventas[])
{

    Patente p;
    int dniValido = 0;
    int anioActual = obtenerAnioActual();
    int mesActual = obtenerMesActual();
    int diaActual = obtenerDiaActual();

    printf("Patente del auto que se va a vender: \n");
    printf("Letras: \n");
    fflush(stdin);
    scanf("%3s",&p.letras);
    printf("Numeros: \n");
    fflush(stdin);
    scanf("%3s",&p.numeros);

    int posicion = buscar_posicion_auto_en_venta(arreglo,validos,p);
    int posicion_archivoAuto = buscar_auto(archivo_autos,p);

    if(posicion == -1)
    {

        printf("La patente no se encuentra entre los autos en venta. \n");
        return;

    }

    Venta a;
    AutoArchivo b;
    float ganancia;

    FILE *archivoVentas = fopen(archivo_ventas,"ab");
    FILE *archivoAutos = fopen(archivo_autos,"r+b");

    if(archivoVentas != NULL && archivoAutos != NULL)
    {
        system("cls");
        if(!dniValido)
        {
            printf("Ingrese el DNI del comprador: \n");
            fflush(stdin);
            scanf("%i", &a.dniComprador);

            if (buscar_dni_comprador(archivo_personas, a.dniComprador))
            {
                dniValido = 1;
            }
            else
            {
                fclose(archivoVentas);
                fclose(archivoAutos);
                system("cls");
                printf("El DNI no corresponde a un comprador registrado.\n");
                return;
            }
        }


        a.dniVendedor = arreglo[posicion].Titular.dni;

        system("cls");
        do
        {

            printf("Ingrese la fecha de la transaccion. \n");
            printf("Dia: \n");
            fflush(stdin);
            scanf("%2i", &a.fecha.dia);

            printf("Mes: \n");
            fflush(stdin);
            scanf("%2i", &a.fecha.mes);

            printf("Anio: \n");
            fflush(stdin);
            scanf("%4i", &a.fecha.anio);

            if(a.fecha.mes < 1 || a.fecha.mes > 12 || a.fecha.dia < 1 || a.fecha.dia > 31 ||
                    (a.fecha.anio > anioActual) ||
                    ((a.fecha.mes == 4 || a.fecha.mes == 6 || a.fecha.mes == 9 || a.fecha.mes == 11) && a.fecha.dia > 30) ||
                    (a.fecha.mes == 2 && (((a.fecha.anio % 4 == 0 && a.fecha.anio % 100 != 0) || a.fecha.anio % 400 == 0) ? a.fecha.dia > 29 : a.fecha.dia > 28)) ||
                    (a.fecha.anio == anioActual && a.fecha.mes == mesActual && a.fecha.dia > diaActual))
            {

                system("cls");
                printf("Ingrese una fecha valida. \n");

            }

        }
        while (a.fecha.mes < 1 || a.fecha.mes > 12 || a.fecha.dia < 1 || a.fecha.dia > 31 ||
                (a.fecha.anio > anioActual) ||
                ((a.fecha.mes == 4 || a.fecha.mes == 6 || a.fecha.mes == 9 || a.fecha.mes == 11) && a.fecha.dia > 30) ||
                (a.fecha.mes == 2 && (((a.fecha.anio % 4 == 0 && a.fecha.anio % 100 != 0) || a.fecha.anio % 400 == 0) ? a.fecha.dia > 29 : a.fecha.dia > 28)) ||
                (a.fecha.anio == anioActual && a.fecha.mes == mesActual && a.fecha.dia > diaActual));


        strcpy(a.autoAVender.letras,p.letras);
        strcpy(a.autoAVender.numeros,p.numeros);

        system("cls");
        printf("Ingrese el precio de venta: \n");
        fflush(stdin);
        scanf("%f", &a.precioVenta);

        ganancia = a.precioVenta - arreglo[posicion].precioDeAdquisicion;
        a.ganancia = ganancia;



        fseek(archivoAutos, posicion_archivoAuto * sizeof(AutoArchivo), SEEK_SET);
        fread(&b, sizeof(AutoArchivo), 1, archivoAutos);

        b.dniTitular = a.dniComprador;

        fwrite(&a,sizeof(Venta),1,archivoVentas);
        fseek(archivoAutos, posicion_archivoAuto * sizeof(AutoArchivo), SEEK_SET);
        fwrite(&b,sizeof(AutoArchivo),1,archivoAutos);
        printf("Se ha registrado la venta. \n");

        fclose(archivoVentas);
        fclose(archivoAutos);
    }

}

///Busca la posicion de un auto en venta

int buscar_posicion_auto_en_venta(Auto arreglo[],int validos,Patente p)
{

    int i=0;
    int posicion=-1;

    while(i<validos)
    {

        if(strcmp(arreglo[i].patente.letras,p.letras) == 0 && strcmp(arreglo[i].patente.numeros,p.numeros) == 0)
        {

            if(strcmp(arreglo[i].Titular.rol,"vendedor") == 0)
            {

                posicion = i;
                break;

            }

        }

        i++;


    }

    return posicion;

}

///Verifica si el dni de un comprador se encuentra en el archivo. Si el dni no se encuentra o se encuentra pero no es de un comprador retorna 0

int buscar_dni_comprador(char archivo_personas[], int dni)
{
    Persona p;
    FILE *archivo = fopen(archivo_personas, "rb");
    if (archivo != NULL)
    {

        while (fread(&p, sizeof(Persona), 1, archivo))
        {
            if (p.dni == dni && strcmp(p.rol, "comprador") == 0)
            {
                fclose(archivo);
                return 1;
            }
        }

        fclose(archivo);
    }
    return 0;
}

/// Ver Listado de Ventas

void listaVentas(char archivo_ventas[])
{
    FILE*archivo = fopen(archivo_ventas, "rb");
    Venta a;

    if(archivo != NULL)
    {
        while(fread(&a, sizeof(Venta), 1, archivo))
        {
            printf("------------\n");
            printf("fecha: %i / %i/ %i\n", a.fecha.dia, a.fecha.mes, a.fecha.anio);
            printf("Patente: %s %s \n", a.autoAVender.letras, a.autoAVender.numeros);
            printf("------------\n");
        }
        fclose(archivo);
    }
}

/// Ver venta
void verVenta(char nombrearchivo[])
{
    Venta a;
    Patente p;

    printf("Patente del auto vendido: \n");
    printf("Letras: \n");
    fflush(stdin);
    scanf("%3s",&p.letras);
    printf("Numeros: \n");
    fflush(stdin);
    scanf("%3s",&p.numeros);

    FILE *archivo = fopen(nombrearchivo,"rb");
    if(archivo != NULL)
    {
        while(fread(&a,sizeof(Venta),1,archivo))
        {
            if(strcmp(a.autoAVender.letras,p.letras)==0 && strcmp(a.autoAVender.numeros,p.numeros)==0)
            {
                printf("----------\n");
                printf("Fecha de la venta: %i/%i/%i\n", a.fecha.dia, a.fecha.mes, a.fecha.anio);
                printf("Patente del auto vendido: %s-%s\n", a.autoAVender.letras, a.autoAVender.numeros);
                printf("Precio de venta: %.2f\n", a.precioVenta);
                printf("Ganancia: %.2f\n", a.ganancia);
                printf("DNI del comprador: %i\n", a.dniComprador);
                printf("DNI del vendedor: %i\n", a.dniVendedor);
                printf("---------\n");

            }

        }
        fclose(archivo);
    }
}

///Calcula lo recaudado en un mes especifico

int calcularRecaudadoMesDeAnio(char nombreArchivo[])
{
    int mesEspecifico;
    int anioEspecifico;
    printf("Ingrese el mes que desea saber cuanto se recaudo: \n");
    scanf("%i",&mesEspecifico);
    printf("Ingrese el anio: \n");
    scanf("%i",&anioEspecifico);

    FILE *archi = fopen(nombreArchivo,"rb");
    Venta a;

    int totalRecaudado = 0;
    Pila pila;
    inicpila(&pila);
    if(archi != NULL)
    {
        while(fread(&a,sizeof(Venta),1,archi))
        {
            if(a.fecha.mes == mesEspecifico&& a.fecha.anio == anioEspecifico)
            {
                apilar(&pila,a.ganancia);
            }
        }
        fclose(archi);
    }
    while(!pilavacia(&pila))
    {

        totalRecaudado = tope(&pila)+totalRecaudado;
        desapilar(&pila);


    }

    return totalRecaudado;
}

///Calcula la venta que haya tenido la mayor ganancia

void calcularVentaMayorGanancia(char nombreArchivo[])
{
    FILE *archi = fopen(nombreArchivo, "rb");
    Venta a;
    float mayorGanancia = 0.0;
    if (archi != NULL)
    {
        while (fread(&a, sizeof(Venta), 1, archi) > 0)
        {
            if (a.ganancia > mayorGanancia)
            {
                mayorGanancia = a.ganancia;
            }
        }
        printf("La venta que genero mayor ganancia hasta el momento es: %.2f\n", mayorGanancia);
        fclose(archi);
    }
}

/// Muestra los autos ordenados que tengan menos de 10 años de antiguedad
void mostrarAutosOrdenadosMenos10(AutoArchivo arreglo[], int numAuto)
{
    for (int i = 0; i < numAuto; i++)
    {
        printf("-------------\n");
        printf("Patente: %s%s\n", arreglo[i].patente.letras, arreglo[i].patente.numeros);
        printf("Marca: %s\n", arreglo[i].marca);
        printf("Modelo: %s\n", arreglo[i].modelo);
        printf("Anio: %i\n", arreglo[i].anio);
        printf("-------------\n");
    }
}
///Ordena los autos por año
void ordenarPorAntiguedad(AutoArchivo arreglo[], int numAutos)
{
    AutoArchivo actual;
    for (int i = 0; i < numAutos - 1; i++)
    {
        for (int j = i + 1; j < numAutos; j++)
        {
            if (arreglo[j].anio < arreglo[i].anio)
            {
                actual = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = actual;
            }
        }
    }
}
///Lee el archivo y guarda los autos que tengan menos de 10 anios
AutoArchivo* autosMenos10anios(char nombreArchivo[], int *numAutos, int anio)
{
    FILE *archi = fopen(nombreArchivo, "rb");
    AutoArchivo *arreglo = NULL;
    AutoArchivo a;
    *numAutos = 0;
    if (archi != NULL)
    {
        while (fread(&a, sizeof(AutoArchivo), 1, archi) > 0)
        {
            if (a.anio > anio)
            {
                arreglo = (AutoArchivo *)realloc(arreglo, (*numAutos + 1) * sizeof(AutoArchivo));
                if (arreglo != NULL)
                {
                    arreglo[*numAutos] = a;
                    (*numAutos)++;
                }
            }
        }
        fclose(archi);
    }

    return arreglo;
}
