#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "pila.h"
#include <ctype.h>
#include <time.h>

int main()
{

//Archivo donde se guardan los usuarios
    char archivo_usuario[] = "usuarios_cargados.dat";
//Archivo donde se guardan los autos
    char archivo_autos[] = "autos.dat";
//Archivo donde se guardan las personas
    char archivo_personas[] = "personas.dat";
//Archivo donde se guardan las ventas
    char archivo_ventas[] = "ventas.bin";

//Se agregan los datos de la concesionaria y se asegura de que siempre esten cargados en el archivo personas para que el codigo funcione correctamente.
    Persona concesionaria;

    concesionaria.dni = 123456789;
    strcpy(concesionaria.nombre, "Concesionaria");
    strcpy(concesionaria.telefono,"2231234567");
    strcpy(concesionaria.direccion, "Concesionaria 123");
    strcpy(concesionaria.rol, "vendedor");

    FILE *cargar_concesionaria = fopen(archivo_personas,"ab");

    if(cargar_concesionaria != NULL)
    {

        if(buscar_persona(archivo_personas,123456789) == -1)
        {

            fwrite(&concesionaria,sizeof(Persona),1,cargar_concesionaria);

        }

        fclose(cargar_concesionaria);
    }



    int opcion;
    int opcion2;
    int flag;
    int recaudado;
    int anio;
    Auto arreglo[50];
    int validos;


    do
    {
        printf("\n*******************************\n");
        printf("*                             *\n");
        printf("*    1. Crear un usuario      *\n");
        printf("*       y contrasenia.        *\n");
        printf("*                             *\n");
        printf("*******************************\n");
        printf("*                             *\n");
        printf("*    2. Acceder al sistema.   *\n");
        printf("*                             *\n");
        printf("*******************************\n");
        printf("*                             *\n");
        printf("*  0. Finalizar el programa.  *\n");
        printf("*                             *\n");
        printf("*******************************\n");

        fflush(stdin);
        scanf("%i",&opcion);

        if(opcion == 1 || opcion == 2|| opcion == 0)
        {
            switch(opcion)
            {

            case 1:
                system("cls");
                crear_usuario(archivo_usuario);
                volver_menu();
                break;
            case 2:
                system("cls");
                flag = login(archivo_usuario);
                if(flag == 0)
                {

                    system("cls");
                    printf("Usuario o contrasenia incorrectos. \n");
                    volver_menu();
                }
                else
                {
                    system("cls");
                    do
                    {
                        printf("****************************************************\n");
                        printf("*               Menu Principal                    *\n");
                        printf("****************************************************\n");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "1.", "Agregar/Modificar un auto.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "2.", "Agregar/Modificar persona.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "3.", "Listado de personas.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "4.", "Ver toda la informacion de una persona.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "5.", "Listado de autos.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "6.", "Listado de autos en venta.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "7.", "Ver toda la informacion de un auto.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "8.", "Listado de ventas.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "9.", "Ver una venta en especifico.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-49s |\n", "10.", "Registrar una venta.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-49s |\n", "11.", "Calcular ganancia en determinado mes de");
                        printf("|    | determinado anio.\n");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-49s |\n", "12.", "Ver venta con mayor ganancia.");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-49s |\n", "13.", "Ver autos que tengan menos de 10 anios");
                        printf("|    | por orden de antiguedad.\n");
                        printf("|--------------------------------------------------------|\n");
                        printf("| %-2s | %-50s |\n", "0.", "Cerrar sesion.");
                        printf("|--------------------------------------------------------|\n");

                        fflush(stdin);
                        scanf("%i",&opcion2);

                        if(opcion2 == 0 ||opcion2 == 1 ||opcion2 == 2 ||opcion2 == 3 ||opcion2 == 4 ||opcion2 == 5 ||opcion2 == 6 ||opcion2 == 7 ||opcion2 == 8 ||opcion2 == 9 ||opcion2 == 10 ||opcion2 == 11 ||opcion2 == 12 ||opcion2 == 13)
                        {
                            switch(opcion2)
                            {
                            case 1:
                                system("cls");
                                menu_autos(archivo_autos);
                                break;
                            case 2:
                                system("cls");
                                menu_personas(archivo_personas);
                                break;
                            case 3:
                                system("cls");
                                mostrar_lista_personas(archivo_personas);
                                volver_menu();
                                break;
                            case 4:
                                system("cls");
                                mostrar_persona(archivo_personas);
                                volver_menu();
                                break;
                            case 5:
                                system("cls");
                                mostrarListadoAutos2Recursividad(archivo_autos);
                                volver_menu();
                                break;
                            case 6:
                                system("cls");
                                validos = cargar_arreglo_autos(archivo_autos,archivo_personas,arreglo);
                                mostrarAutoEnVenta(arreglo,validos);
                                volver_menu();
                                break;
                            case 7:
                                system("cls");
                                validos = cargar_arreglo_autos(archivo_autos,archivo_personas,arreglo);
                                mostrarInfoAuto(arreglo,validos);
                                volver_menu();
                                break;
                            case 8:
                                system("cls");
                                listaVentas(archivo_ventas);
                                volver_menu();
                                break;
                            case 9:
                                system("cls");
                                verVenta(archivo_ventas);
                                volver_menu();
                                break;
                            case 10:
                                system("cls");
                                validos = cargar_arreglo_autos(archivo_autos,archivo_personas,arreglo);
                                registrarVenta(arreglo,validos,archivo_autos,archivo_personas,archivo_ventas);
                                volver_menu();
                                break;
                            case 11:
                                system("cls");
                                recaudado = calcularRecaudadoMesDeAnio(archivo_ventas);
                                printf("Recaudacion del mes: %i \n",recaudado);
                                volver_menu();
                                break;
                            case 12:
                                system("cls");
                                calcularVentaMayorGanancia(archivo_ventas);
                                volver_menu();
                                break;
                            case 13:
                                system("cls");
                                anio = obtenerAnioActual();
                                int aniomenos10 = anio - 10;

                                int numAutos = 0;
                                AutoArchivo *arregloAuto = autosMenos10anios(archivo_autos, &numAutos, aniomenos10);

                                if (arregloAuto != NULL && numAutos > 0)
                                {
                                    ordenarPorAntiguedad(arregloAuto, numAutos);
                                    mostrarAutosOrdenadosMenos10(arregloAuto, numAutos);
                                }
                                else
                                {
                                    ("No se encontraron autos con menos de 10 años de antiguedad.\n");
                                }
                                volver_menu();
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
                    while(opcion2 != 0);

                }
                break;
            case 0:
                system("cls");
                puts("-----------------------");
                printf("| PROGRAMA FINALIZADO |\n");
                puts("-----------------------");
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




    return 0;
}

///Volver hacia el menu

void volver_menu()
{

    printf("\n Presione cualquier tecla para volver al menu. \n");

    getch();

    system("cls");
}

///Retorna el año actual

int obtenerAnioActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

///Retorna el mes actual

int obtenerMesActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mon + 1;
}

///Retorna el dia actual

int obtenerDiaActual()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}
