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
    Tesoro tesoros[30];
} Barco;


void leertexto(char texto[], int dimension);
int cantidadbarcos();
Barco cargarbarco();
void arreglodebarcos(Barco barcos[], int cant);
void mostrartodoslosbarcos(Barco barcos[], int cant);
void modificaCapitan(Capitan capitan);
void modificarBarcos(Barco barcos[], int cant);
void darDeBaja(Barco barcos[], int cant);
int submenu(Barco barquito[],Pila historial, int cant);
int menu(Barco barquito[], Pila historial, int cant);
void cargartesoro(Barco *barquito, Pila *historial);
void iniciarPartida(Barco barquitos[], Pila historial);
void mostrarhistorial (Pila historial);
int main()
{
    Pila historial;
    inicpila(&historial);
    int cant;
    printf("\n***     BIENVENIDO    ***\n");
    cant=cantidadbarcos();
    Barco *barcos = malloc(sizeof(Barco)*cant);
    menu(barcos, historial,cant);

    //poner en un while el menu hasta que ingrese salir
    return 0;
}

void leertexto(char texto[], int dimension)
{
    fgets(texto, dimension, stdin);
    texto[strcspn(texto, "\n")]= '\0';
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

Barco cargarbarco()
{
    Barco barquito;
    printf("Ingrese el id del barco: \n");
    scanf(" %d", &barquito.id);
    getchar();

    printf("Ingrese el nombre del capitan del barco: \n");
    leertexto(barquito.capitan.nombre, 20);

    printf("Ingrese el apellido del capitan del barco: \n");
    leertexto(barquito.capitan.apellido, 20);

    printf("Ingrese los años de experiencia: \n");
    scanf("%d",&barquito.capitan.aniosexperiencia);
    getchar();

    printf("Ingrese la cantidad de tripulantes:\n");
    scanf("%d",&barquito.canttripulantes);
    getchar();

    barquito.canttesoros = 0;
    barquito.activo = 1;
    return barquito;
}

void arreglodebarcos(Barco barcos[], int cant)
{
    printf("**Carga de barcos**\n");
    int i = 0;
    int esta = 0;
    Barco barquito;
    while (i < cant)
    {
        barquito = cargarbarco();
        for (int j = 0; j < cant; j++)
        {
            if (barquito.id == barcos[j].id)
            {
                esta = 1;
            }
        }
        if (esta == 0)
        {
            barcos[i] = barquito;
            i++;
        }
        else
        {
            printf("Ya existe ese barco. Ingrese otro. \n");
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
void modificaCapitan(Capitan capitan) //agregar while para el nombre? Agregue lo de char nombre y apellido aca, porque no existia.
{
    char seguir;
    char nombre[20];
    char apellido[20];

    printf("Desea modificar el nombre del capitan? (s/n): ");
    scanf(" %c", &seguir);

    if (seguir == 's') {
        printf("\n Nuevo nombre del capitan: ");
        leertexto(nombre, 20);

        if (strcmp(nombre, capitan.nombre) != 0) {
            strcpy(capitan.nombre, nombre);
        } else {
            printf("\n Este nombre es igual al anterior. \n");
        }
    }

    printf("Desea modificar el apellido del capitan? (s/n): ");
    scanf(" %c", &seguir);

    if (seguir == 's') {
        printf("\n Nuevo apellido del capitan: ");
        leertexto(apellido, 20);

        if (strcmp(apellido, capitan.apellido) != 0) {
            strcpy(capitan.apellido, apellido);
        } else {
            printf("\n Este apellido es igual al anterior. \n");
        }
    }

    // Aca tocaria modificar años de experiencia y arreglo de tesoros anteriores. Pero no seria mejor asociar eso al barco que al capitan?
}

int posicionBarco(Barco barquitos[],int id,int cant){
    int pos=-1;
    for(int i=0;i<cant;i++){
        if(barquitos[i].id==id){
            pos=i;
        }
    }
    return pos;
}

void modificarDatos(Barco barquitos[],int cant)   // Modifica los datos de uno o mas barcos
{
    int id;
    char seguir = 's';
    int pos;
    int tripulantes;
    while (seguir == 's') {                                 // while principal que corta cuando ya no se quiere modificar mas nada
        printf("Ingrese id del barco a modificar: ");
        scanf("%d", &id);

        pos = posicionBarco(barquitos, id, cant);                  // Pido la id del barco y ciclo hasta que lo encuentre

        while (pos == -1) {
            printf("No se encontro la id ingresada. Ingrese id del barco a modificar: ");
            scanf("%d", &id);

            pos = posicionBarco(barquitos, id, cant);
        }

        // Encuentra el barco. Pregunta por campos a modificar

        printf("Desea modificar al capitan? (s/n): ");
        scanf(" %c", &seguir);   // reciclo constantemente la misma variable "seguir"

        if (seguir == 's') {
            modificaCapitan(barquitos[pos].capitan);
        }

        printf("Desea modificar la cantidad de tripulantes? (s/n): ");
        scanf(" %c", &seguir);

        if (seguir == 's') {
            printf("\n Nueva cantidad de tripulantes: ");
            scanf("%d", &tripulantes);

            if (tripulantes != barquitos[pos].canttripulantes) {         // Corroboro que la cantidad de tripulantes ingresada sea distinta a la actual
                barquitos[pos].canttripulantes = tripulantes;
            } else {
                printf("No se ha modificado la cantidad de tripulantes.\n");
            }
        }

        printf("Desea modificar otro barco? (s/n): ");
        scanf(" %c", &seguir);
    }
}

void darDeBaja(Barco barquitos[], int cant)    // Busco el barco por id y cuando lo encuentro, lo doy de baja. Se deberia modularizar mas?
{
    int pos;
    int id;

    printf("Ingrese id del barco a dar de baja: ");
    scanf("%d", &id);

    pos = posicionBarco(barquitos, id, cant);

    while (pos == -1) {
        printf("No se encontro la id ingresada. Ingrese id del barco a dar de baja: ");
        scanf("%d", &id);

        pos = posicionBarco(barquitos, id, cant);
    }
    barquitos[pos].activo = 0;
}


int submenu(Barco barquitos[], Pila historial, int cant)
{
    int opcion;
    printf("Ingrese una opcion: \n");
    printf("1. Iniciar partida. \n");
    printf("2. Modificar datos. \n");
    printf("3. Ver informacion de participantes. \n");
    printf("4. Ver informacion especifica. \n");
    printf("5. Dar de baja un barco participante. \n");
    printf("6. Salir \n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        arreglodebarcos(barquitos, cant);
        iniciarPartida(barquitos, historial);
        break;

    case 2:

        modificarDatos(barquitos,cant);
       /* -preguntar que barco modificar (por id) (verificar que lo encuentre)
        -preguntar por todos los campos si se quieren modificar o no
        -modificar es/os datos
        -preguntar si se quiere seguir modificando (otro barco)*/
        break;

    case 3:

        mostrartodoslosbarcos(barquitos, cant);

        break;

    case 4:
        mostrarbarcoespecifico(barquitos, cant);

        break;

    case 5:

        darDeBaja(barquitos,cant);

        break;
    case 6:

        printf("Saliendo... ");
        return 0;
        break;

    default:

        printf("El valor no es valido. \n");

    }
}
int menu(Barco barquito[], Pila historial,int cant)
{
    int opcion;



    printf("Ingrese una opcion \n");

    printf("1. Iniciar nueva competencia. \n");
    printf("2. Ver registros historicos. \n");
    printf("3. Salir. ");
    scanf("%d",&opcion);

    switch (opcion)
    {
    case 1:

    submenu(barquito, historial, cant);

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
void iniciarPartida(Barco barquitos[], Pila historial)
{
    char letra;
    int contador = 1;
    int cantRondas;

    printf("Ingrese la cantidad de rondas: ");
    scanf("%i", &cantRondas);

    while(cantRondas <= 0 || cantRondas > 5)
    {
        printf("Solo se permiten hasta 5 rondas. Vuelva a intentar");
        scanf("%i", &cantRondas);
    }
    for (int i = 0; i < cantRondas; i++)
    {
        printf("Comienza la ronda. %d \n", contador);
        printf("Comienza: %d \n", barquitos[i].id);
        printf("Resultado de la primera busqueda: \n");
        printf("¿Se encontro algun tesoro? (s/n)\n"); //validacion con letra== s ?
        scanf(" %c", &letra);
        if (letra == 's')
        {
            cargartesoro(&barquitos[i],&historial);
            barquitos[i].canttesoros++;

        }

        printf("Resultado de la segunda busqueda: \n");
        printf("¿Se encontro algun tesoro? S/N \n");
        scanf(" %c", &letra);
        if (letra=='s')
        {
            cargartesoro(&barquitos[i],&historial);
            barquitos[i].canttesoros++;

        }
        contador++;
    }
    mostrarhistorial(historial);


}
void cargartesoro(Barco *barquitos, Pila *historial)
{


    printf("Ingrese el nivel del tesoro: \n");
    scanf("%d", &barquitos->tesoros->nivel);
    getchar();
    printf("Ingrese el material del tesoro: \n");
    leertexto(barquitos->tesoros->material, 30);
    printf("Ingrese la cantidad de oro: \n");
    scanf("%d", &barquitos->tesoros->cantoro);
    apilar(historial, barquitos->tesoros->nivel);


}
void mostrarhistorial (Pila historial) //despues de cada ronda para cada barco? lo puse al final de inciar partida por las dudas
{
    Pila aux;
    inicpila(&aux);
    int dato;
    printf("Historial de niveles de ultimos tesoros encontrados: \n");
    while(!pilavacia(&historial)){
        printf("Tesoro nivel: %d \n", tope(&historial));
        dato=desapilar(&historial);
        apilar(&aux,dato);
    }
    while(!pilavacia(&aux)){
        dato=desapilar(&aux);
        apilar(&historial,dato);
    }
}

