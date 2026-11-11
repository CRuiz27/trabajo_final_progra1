#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    char nombre[20];
    char apellido[20];
    int aniosexperiencia;
    int canttesorosxanio[30];
} Capitan;
typedef struct
{
    int canttesoros;
    int canttripulantes;
    Capitan capitan;
    int id;
} Barco;

void leertexto(char texto[],int dimension);
int cantidadbarcos();
Barco cargarbarcos();
void arreglodebarcos(Barco barcos[], int cant);
void mostrartodoslosbarcos(Barco barcos[],int cant);
int main()
{
    int cant=cantidadbarcos();
    Barco *barcos=malloc(sizeof(Barco)*cant);
    arreglodebarcos(barcos,cant);
    mostrartodoslosbarcos(barcos,cant);
    return 0;
}

void leertexto(char texto[],int dimension)
{
    fgets(texto,dimension,stdin);
    texto[strcspn(texto,"\n")]='\0';
}

int cantidadbarcos()
{
    int cant=0;
    int aux=0;
    while (cant<2)
    {
        printf("Ingrese la cantidad de barcos que desean jugar: \n");
        scanf(" %d", &aux);
        if (aux>=2)
        {
            cant=aux;
        }
        else
        {
            printf("La cantidad es menor a 2, ingrese otra cantidad \n");
        }
    }
    return cant;
}

Barco cargarbarcos()
{
    Barco barquito;
    printf("Ingrese el id del barco: \n");
    scanf(" %d", &barquito.id);
    printf("Ingrse el nombre del capitan del barco: \n");
    leertexto(barquito.capitan.nombre,20);
    printf("Ingrse el apellido del capitan del barco: \n");
    leertexto(barquito.capitan.apellido,20);
    printf("Ingrese los años de experiencia: \n");
    scanf(" %d",&barquito.capitan.aniosexperiencia);
    printf("Ingrese la cantidad de tripulantes:\n");
    scanf(" %d",&barquito.canttripulantes);
    barquito.canttesoros=0;
    return barquito;
}

void arreglodebarcos(Barco barcos[], int cant)
{
    printf("**Carga de barcos**\n");
    int i=0;
    int esta=0;
    Barco barquito;
    while (i<cant)
    {
        barquito=cargarbarcos();
        for (int j=0; j<cant; j++)
        {
            if(barquito.id==barcos[j].id)
            {
                esta=1;
            }
        }
        if(esta==0)
        {
            barcos[i]=barquito;
            i++;
        }
        else
        {
            printf("Ya existe ese barco ingrese otro \n");
        }

    }
}

void mostrartodoslosbarcos(Barco barcos[],int cant)
{


    for (int i =0; i<cant; i++)
    {
        printf("Barco n°: %d \n",barcos[i].id);
        printf("Capitan del barco: %29s %29s \n",barcos[i].capitan.nombre,barcos[i].capitan.apellido);
        printf("Años de experiencia del capitan: %d \n",barcos[i].capitan.aniosexperiencia);
        printf("Cantidad de tripulantes: %d \n",barcos[i].canttripulantes);
        printf("Cantidad de tesoros del barco: %d \n",barcos[i].canttesoros);

    }

}
void mostrarbarcoespecifico(Barco barcos[],int cant)
{

    int aux;
    printf("Ingrese el id del barco que desea ver:");
    scanf(" %d", &aux);

    for (int i =0; i<cant; i++)
    {
        if (aux==barcos[i].id)
        {
            printf("Barco n°: %d \n",barcos[i].id);
            printf("Capitan del barco: %s %s \n",barcos[i].capitan.nombre,barcos[i].capitan.apellido);
            printf("Años de experiencia del capitan: %d \n",barcos[i].capitan.aniosexperiencia);
            printf("Cantidad de tripulantes: %d \n",barcos[i].canttripulantes);
            printf("Cantidad de tesoros del barco: %d \n",barcos[i].canttesoros);
        }
        else
        {
            printf("Ese barco no existe.");
        }
    }

}
