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
    int nivel;
    char material[30];
    int cantoro;

} Tesoro;
typedef struct
{
    int canttesoros;
    int canttripulantes;
    Capitan capitan;
    int id;
    int activo; //Inicializar en 1
    Tesoro tesoros;
} Barco;


void leertexto(char texto[],int dimension);
int cantidadbarcos();
Barco cargarbarcos();
void arreglodebarcos(Barco barcos[], int cant);
void mostrartodoslosbarcos(Barco barcos[],int cant);
int submenu();
int menu();
void cargartesoro(Barco barcos[], Pila historial);

int main()
{
    Pila historial;
    inicpila(&historial);
    int cant=cantidadbarcos();
    Barco *barcos=malloc(sizeof(Barco)*cant);
    arreglodebarcos(barcos,cant);
    mostrartodoslosbarcos(barcos,cant);

    //poner en un while el menu hasta que ingrese salir
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
        if (aux>=2 && aux<=5)
        {
            cant=aux;
        }
        else
        {
            printf("La cantidad debe ser mayor a 2 y menor a 5, ingrese otra cantidad \n");
        }
    }
    return cant;
}

Barco cargarbarcos()
{
    Barco barquito;
    printf("Ingrese el id del barco: \n");
    scanf(" %d", &barquito.id);
    getchar();

    printf("Ingrese el nombre del capitan del barco: \n");
    leertexto(barquito.capitan.nombre,20);

    printf("Ingrese el apellido del capitan del barco: \n");
    leertexto(barquito.capitan.apellido,20);

    printf("Ingrese los años de experiencia: \n");
    scanf("%d",&barquito.capitan.aniosexperiencia);
    getchar();

    printf("Ingrese la cantidad de tripulantes:\n");
    scanf("%d",&barquito.canttripulantes);
    getchar();

    barquito.canttesoros=0;
    barquito.activo=1;
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
        printf("Capitan del barco: %s %s \n",barcos[i].capitan.nombre,barcos[i].capitan.apellido);
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
int submenu()
{
    int opcion;
    printf("Los barcos fueron cargados con exito. \n");
    printf("Ingrese una opcion: \n");
    printf("1. Iniciar partida. \n");
    printf("2. Modificar datos. \n");
    printf("3. Ver datos. \n");
    printf("4. Dar de baja un barco participante. \n");
    printf("5. Salir \n");

    switch (opcion)
    {
    case 1:

        //iniciar partida
        break;

    case 2:

        //modificar datos
        break;

    case 3:

        //Ver datos
        break;
    case 4:

        //dar de baja
        break;
    case 5:

        printf("Saliendo... ");
        return 0;
        break;

    default:

        printf("El valor no es valido. \n");

    }
}
    int menu()
    {
        int opcion;

        printf("\n***     BIENVENIDO    ***\n");

        printf("Ingrese una opcion \n");

        printf("1. Iniciar nueva competencia. \n");
        printf("2. Ver registros historicos. \n");
        printf("3. Salir. ");

        switch (opcion)
        {
        case 1:

            //iniciar competencia
            break;

        case 2:

            //datos historicos
            break;

        case 3:

            printf("Saliendo... ");
            return 0;
            break;
        }
    }
        void iniciarPartida(Barco barquito[],Pila historial)
        {
            char letra;
            int contador=1;
            int cantRondas;

            printf("Ingrese la cantidad de rondas: ");
            scanf("%i", &cantRondas);

            while(cantRondas==0 && cantRondas>5)
            {
                printf("Cantidad de rondas invalido. Vuelva a intentar");
                scanf("%i", &cantRondas);
            }

            printf("Comienza la ronda. \n", contador);

            printf("Comienza: %s", barquito->id);
            printf("Resultado de la primera busqueda: \n");
            printf("¿Se encontro algun tesoro? S/N"); //validacion con letra== s ?
            scanf(" %c", &letra);
            if (letra=='s'){
                    cargartesoro(barquito,historial);
                    barquito->canttesoros++;

            }

            printf("Resultado de la segunda busqueda: \n");
            printf("¿Se encontro algun tesoro? S/N");
            scanf(" %c", &letra);
            if (letra=='s'){
                    cargartesoro(barquito,historial);
                    barquito->canttesoros++;

            }


        }
        void cargartesoro(Barco barcos[], Pila historial){


            printf("Ingrese el nivel del tesoro: \n");
            scanf("%d",&barcos->tesoros.nivel);
            getchar();
            printf("Ingrese el material del tesoro: \n");
            leertexto(barcos->tesoros.material,30);
            printf("Ingrese la cant de oro: \n");
            scanf("%d",&barcos->tesoros.cantoro);
            apilar(&historial,barcos->tesoros.nivel);


        }

