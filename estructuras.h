#ifndef ESTRUCTURAS_H_INCLUDED
#define ESTRUCTURAS_H_INCLUDED

///Patente
typedef struct
{
    char letras[4];
    char numeros[4];
} Patente;

///AutoArchivo
typedef struct
{
    Patente patente;
    char marca[20];
    char modelo[20];
    int anio;
    int kms;
    int dniTitular;
    float precioDeAdquisicion;
} AutoArchivo;

///Persona
typedef struct
{
    int dni;
    char nombre[20];
    char telefono[20];
    char direccion[20];
    char rol[20]; //comprador o vendedor
} Persona;

///Auto
typedef struct
{
    Patente patente;
    char marca[20];
    char modelo[20];
    int anio;
    int kms;
    Persona Titular;
    float precioDeAdquisicion;
} Auto;

///Fecha
typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

///Venta
typedef struct
{
    Fecha fecha;
    Patente autoAVender;
    float precioVenta;
    float ganancia;
    int dniComprador;
    int dniVendedor;
} Venta;

///Usuario para el login
typedef struct
{
    char usuario[20];
    char contrasenia[20];
} stUsuario;

#endif // ESTRUCTURAS_H_INCLUDED
