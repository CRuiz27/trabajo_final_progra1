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
    int ronda;  // Indica en que ronda fue encontrado
} Tesoro;

typedef struct
{
    int canttesoros;
    int canttripulantes;
    Capitan capitan;
    int id;
    int activo; //Inicializar en 1
    Tesoro tesoros[30];
    int puntaje; // Inicializar en 0
} Barco;

typedef struct
{
    int cantBarcos;
    int idBarcoGanador;
    Capitan capitanGanador;
    int puntaje;
} Historico;

void leertexto(char texto[], int dimension);
int cantidadbarcos();
Barco cargarbarco();
void arreglodebarcos(Barco barcos[], int cant);
void mostrartodoslosbarcos(Barco barcos[], int cant);

void modificaCapitan(Capitan capitan);
void modificarDatos();
void darDeBaja(int id);
void darAlta(int id);
void guardarCompetencia(Barco barquitos[], int cantBarcos);
int maxPuntaje(Barco barquitos[], int cantBarcos);
void actualizaPuntajes(Barco barquitos[], int cantBarcos, int ronda);

Historico cargarHistorico(Barco barquitos[], int cantBarcos, int posGanador);
void guardarHistorico(Barco barquitos[], int cantBarcos, int posGanador);
void muestraHistorico(Historico historico);
void consultarDatosHistoricos();

int submenu(Barco barquito[],Pila historial, int cant);
int menu(Barco barquito[], Pila historial, int cant);

void cargartesoro(Barco *barquito, Pila *historial, int ronda);
void iniciarPartida(Barco barquitos[], int cant, Pila historial);
void mostrarhistorial(Pila historial);

void listarCapitanesAlfabeticamente(Barco barquitos[], int cant);
void ordenarCapitanesSeleccion(Barco copia[], int cant);
void mostrarCapitanes(Barco barquitos[], int cant);
void mostrarClasificacion(Barco barquitos[], int cant);
void ordenarPorPuntaje(Barco barquitos[], int cant);

int main()
{
    Pila historial;
    inicpila(&historial);
    int cant;
    printf("\n***     BIENVENIDO    ***\n");
    cant=cantidadbarcos();
    Barco *barcos = malloc(sizeof(Barco)*cant);
    while(1)
    {
        menu(barcos, historial,cant);
    }
    //poner en un while el menu hasta que ingrese salir
    free(barcos);
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
    barquito.puntaje = 0;

    return barquito;
}

void arreglodebarcos(Barco barcos[], int cant)
{
    printf("**Carga de barcos**\n");

    int i = 0;
    int esta;
    Barco barquito;

    while (i < cant)
    {
        esta = 0;
        barquito = cargarbarco();

        for (int j = 0; j < i; j++)
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
            printf("Ya existe ese barco. Ingrese otro.\n");
        }
    }
}


void mostrartodoslosbarcos(Barco barcos[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        printf("Barco n°: %d \n",barcos[i].id);
        printf("Capitan del barco: %s %s \n", barcos[i].capitan.nombre,barcos[i].capitan.apellido);
        printf("Años de experiencia del capitan: %d \n", barcos[i].capitan.aniosexperiencia);
        printf("Cantidad de tripulantes: %d \n", barcos[i].canttripulantes);
        printf("Cantidad de tesoros del barco: %d \n", barcos[i].canttesoros);
        printf("Puntaje obtenido: %d \n", barcos[i].puntaje);

    }

}
void mostrarbarcoespecifico(Barco barcos[],  int cant, int idAux)
{
    int encontrado=0;
    int pos;
    for (int i =0; i<cant; i++)
    {
        if (idAux == barcos[i].id)
        {
            encontrado=1;
            pos=i;
        }

    }
    if(encontrado==1)
    {
        printf("Barco n°: %d \n",barcos[pos].id);
        printf("Capitan del barco: %s %s \n",barcos[pos].capitan.nombre, barcos[pos].capitan.apellido);
        printf("Años de experiencia del capitan: %d \n",barcos[pos].capitan.aniosexperiencia);
        printf("Cantidad de tripulantes: %d \n",barcos[pos].canttripulantes);
        printf("Cantidad de tesoros del barco: %d \n",barcos[pos].canttesoros);
        printf("Puntaje obtenido: %d \n", barcos[pos].puntaje);
    }
    else
    {
        printf("El barco no existe \n");
    }
}
void modificaCapitan(Capitan capitan) //agregar while para el nombre? Agregue lo de char nombre y apellido aca, porque no existia.
{
    char seguir;
    char nombre[20];
    char apellido[20];

    printf("Desea modificar el nombre del capitan? (s/n): ");
    scanf(" %c", &seguir);
    getchar();

    if (seguir == 's')
    {
        printf("\n Nuevo nombre del capitan: ");
        leertexto(nombre, 20);

        if (strcmp(nombre, capitan.nombre) != 0)
        {
            strcpy(capitan.nombre, nombre);
        }
        else
        {
            printf("\n Este nombre es igual al anterior. \n");
        }
    }

    printf("Desea modificar el apellido del capitan? (s/n): ");
    scanf(" %c", &seguir);

    if (seguir == 's')
    {
        printf("\n Nuevo apellido del capitan: ");
        leertexto(apellido, 20);

        if (strcmp(apellido, capitan.apellido) != 0)
        {
            strcpy(capitan.apellido, apellido);
        }
        else
        {
            printf("\n Este apellido es igual al anterior. \n");
        }
    }

    // Aca tocaria modificar años de experiencia y arreglo de tesoros anteriores. Pero no seria mejor asociar eso al barco que al capitan?
}

int posicionBarco(Barco barquitos[], int id, int cant)
{
    int pos = -1;
    for (int i = 0 ; i < cant; i++)
    {
        if (barquitos[i].id == id)
        {
            pos = i;
        }
    }
    return pos;
}

void modificarDatos()   // Modifica los datos de uno o mas barcos
{
    Barco barquito;
    int id;
    char seguir = 's';
    int tripulantes;

    while (seguir == 's')                               // while principal que corta cuando ya no se quiere modificar mas nada
    {
        FILE * arch = fopen("Barcos.dat", "r+b");

        printf("Ingrese id del barco a modificar: ");
        scanf("%d", &id);

        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.id == id)          // Encuentra el barco. Pregunta por campos a modificar
            {
                printf("Desea modificar al capitan? (s/n): ");
                scanf(" %c", &seguir);
                getchar();

                if (seguir == 's')
                {
                    modificaCapitan(barquito.capitan);
                }

                printf("Desea modificar la cantidad de tripulantes? (s/n): ");
                scanf(" %c", &seguir);

                if (seguir == 's')
                {
                    printf("\n Nueva cantidad de tripulantes: ");
                    scanf("%d", &tripulantes);

                    if (tripulantes != barquito.canttripulantes)
                    {
                        // Corroboro que la cantidad de tripulantes ingresada sea distinta a la actual
                        barquito.canttripulantes = tripulantes;
                    }
                    else
                    {
                        printf("No se ha modificado la cantidad de tripulantes.\n");
                    }
                }

                fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);          // Una vez modificados los campos, los reemplazo en el archivo de barcos
                fwrite(&barquito, sizeof(Barco), 1, arch);
            }
        }

        fclose(arch);

        printf("Desea modificar otro barco? (s/n): ");
        scanf(" %c", &seguir);
    }
}

void darDeBaja(int id)    // Busco el barco por id y cuando lo encuentro, lo doy de baja. Se deberia modularizar mas?
{
    FILE * arch = fopen("Barcos.dat", "r+b");
    Barco barquito;

    if (arch == NULL)
    {
        printf("\n No se pudo acceder al archivo Barcos.dat");
    }
    else
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.activo && barquito.id == id)
            {
                barquito.activo = 0;
                fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);
                fwrite(&barquito, sizeof(Barco), 1, arch);
                printf("El barco fue dado de baja \n");
            }
        }
    }
    fclose(arch);
}
void darAlta(int id)    // Busco el barco por id y cuando lo encuentro, lo doy de baja. Se deberia modularizar mas?
{
    FILE * arch = fopen("Barcos.dat", "r+b");
    Barco barquito;

    if (arch == NULL)
    {
        printf("\n No se pudo acceder al archivo Barcos.dat");
    }
    else
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.activo==0 && barquito.id == id)
            {
                barquito.activo = 1;
                fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);
                fwrite(&barquito, sizeof(Barco), 1, arch);
                printf("El barco fue dado de alta \n");
            }
        }
    }
    fclose(arch);
}

int maxPuntaje(Barco barquitos[], int cantBarcos)   // Inicializo con el puntaje del primer barco, y recorro a partir del segundo
{
    int posGanador = 0;
    int max = barquitos[0].puntaje;
    for (int i = 1; i < cantBarcos; i++)
    {
        if (barquitos[i].puntaje > max)
        {
            max = barquitos[i].puntaje;
            posGanador = i;
        }
    }
    return posGanador;
}

void actualizaPuntajes(Barco barquitos[], int cantBarcos, int ronda) // Funcion que calcula puntajes de todos
{
    for (int i = 0; i < cantBarcos; i++)
    {
        for (int j = 0; j < barquitos[i].canttesoros; j++)
        {
            if (barquitos[i].tesoros[j].ronda == ronda)     // Siempre recorremos los arreglos de tesoros desde el principio, pero solo actualizamos el puntaje
            {
                switch (barquitos[i].tesoros[j].nivel)      // si los tesoros son de la ronda pasada por parametro, para evitar cargar datos repetidos /*
                {
                case 1:
                    barquitos[i].puntaje += 1;
                    break;

                case 2:
                    barquitos[i].puntaje += 3;
                    break;

                case 3:
                    barquitos[i].puntaje += 5;
                    break;

                case 4:
                    barquitos[i].puntaje += 10;
                    break;
                }
            }
        }
    }
}

void guardarCompetencia(Barco barquitos[], int cantBarcos)    // Guarda los datos de la ultima competencia
{
    FILE * arch = fopen("Barcos.dat", "wb");    // wb sobreescribe competencia del año anterior. ¿Está bien o mal? De todos modos se guardan las competencias
    // anteriores en el historico...
    if (arch == NULL)
    {
        printf("\n No se ha podido guardar la competencia. \n");
    }
    else
    {
        for (int i = 0; i < cantBarcos; i++)
        {
            fwrite(&barquitos[i], sizeof(Barco), 1, arch);
        }
    }

    fclose(arch);
}

Historico cargarHistorico(Barco barquitos[], int cantBarcos, int posGanador)
{
    Historico historico;

    historico.cantBarcos = cantBarcos;
    strcpy(historico.capitanGanador.nombre, barquitos[posGanador].capitan.nombre);
    strcpy(historico.capitanGanador.apellido, barquitos[posGanador].capitan.apellido);
    historico.idBarcoGanador = barquitos[posGanador].id;
    historico.puntaje = barquitos[posGanador].puntaje;

    return historico;
}

void guardarHistorico(Barco barquitos[], int cantBarcos, int posGanador)
{
    FILE * arch = fopen("Historico.dat", "ab");
    Historico historico;

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Historicos.dat. \n");
    }
    else
    {
        historico = cargarHistorico(barquitos, cantBarcos, posGanador);
        fwrite(&historico, sizeof(Historico), 1, arch);
    }

    fclose(arch);
}

void muestraHistorico(Historico historico)
{
    printf("Cantidad de barcos: %d \n", historico.cantBarcos);
    printf("Capitan ganador: %s %s \n", historico.capitanGanador.nombre, historico.capitanGanador.apellido);
    printf("ID del barco ganador: %d \n", historico.idBarcoGanador);
    printf("Puntaje: %d \n", historico.puntaje);
}

void consultarDatosHistoricos()
{
    FILE * arch = fopen("Historico.dat", "rb");
    Historico historico;
    int contador = 1;

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Historicos.dat. \n");
    }
    else
    {
        while (fread(&historico, sizeof(Historico), 1, arch) > 0)
        {
            printf("\n -- ANIO %d DE LA COMPETENCIA: -- \n", contador);
            muestraHistorico(historico);
            contador++;
        }
    }

    fclose(arch);
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
    printf("6. Dar de alta un barco participante. \n");
    printf("7. Salir \n");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:
        arreglodebarcos(barquitos, cant);
        iniciarPartida(barquitos, cant, historial);
        int posGanador = maxPuntaje(barquitos, cant);

        printf("GANADOR: \n");
        mostrarbarcoespecifico(barquitos, cant, barquitos[posGanador].id);

        guardarCompetencia(barquitos, cant);
        guardarHistorico(barquitos, cant, posGanador);

        break;

    case 2:

        modificarDatos();
        /* -preguntar que barco modificar (por id) (verificar que lo encuentre)
         -preguntar por todos los campos si se quieren modificar o no
         -modificar es/os datos
         -preguntar si se quiere seguir modificando (otro barco)*/
        break;

    case 3:

        mostrartodoslosbarcos(barquitos, cant);

        break;

    case 4:

        printf("Ingrese el id del barco que desea ver: ");
        int id;
        scanf(" %d", &id);

        mostrarbarcoespecifico(barquitos, cant, id);

        break;

    case 5:

        printf("Ingrese el id del barco que desea dar de baja: ");
        scanf(" %d", &id);
        darDeBaja(id);

        break;
    case 6:

        printf("Ingrese el id del barco que desea dar de alta: ");
        scanf(" %d", &id);
        darAlta(id);

        break;
    case 7:

        printf("Saliendo... ");
        return 0;
        break;

    default:

        printf("El valor no es valido. \n");

    }
    return 0;
}

int menu(Barco barquito[], Pila historial, int cant)
{
    int opcion;
    printf("Ingrese una opcion \n");

    printf("1. Iniciar nueva competencia. \n");
    printf("2. Ver registros historicos. \n");
    printf("3. Salir. ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:

        submenu(barquito, historial, cant);

        break;

    case 2:

        consultarDatosHistoricos();
        break;

    case 3:

        printf("Saliendo... ");
        exit(0);
        break;
    }

}


void iniciarPartida(Barco barquitos[], int cantBarcos, Pila historial)
{
    char letra;
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
        printf("Comienza la ronda %d \n", i+1);

        for (int j = 0; j < cantBarcos; j++)
        {
            if (barquitos[j].activo == 1)
            {
                printf("Comienza: %d \n", barquitos[j].id);
                printf("Resultado de la primera busqueda: \n");
                printf("¿Se encontro algun tesoro? (s/n): "); //validacion con letra== s ?
                scanf(" %c", &letra);
                if (letra == 's')
                {
                    cargartesoro(&barquitos[j],&historial, i+1);
                    barquitos[j].canttesoros++;
                }

                printf("Resultado de la segunda busqueda: \n");
                printf("¿Se encontro algun tesoro? (s/n): ");
                scanf(" %c", &letra);
                if (letra == 's')
                {
                    cargartesoro(&barquitos[j], &historial, i+1);
                    barquitos[j].canttesoros++;
                }
            }
        }
        actualizaPuntajes(barquitos, cantBarcos, i+1);

        printf("Desea ver el estado de la competencia (s/n): ");
        scanf(" %c", &letra);
        if (letra == 's')
        {
            printf("\n*** Clasificacion despues de la ronda %d***\n", i+1);
            mostrarClasificacion(barquitos, cantBarcos);
        }

    }

    mostrarhistorial(historial);

}
void cargartesoro(Barco *barquito, Pila *historial, int ronda)
{
    int i = barquito->canttesoros;

    printf("Ingrese el nivel del tesoro: \n");
    scanf("%d", &barquito->tesoros[i].nivel);

    getchar();
    printf("Ingrese el material del tesoro: \n");
    leertexto(barquito->tesoros[i].material, 30);

    printf("Ingrese la cantidad de oro: \n");
    scanf("%d", &barquito->tesoros[i].cantoro);

    apilar(historial, barquito->tesoros[i].nivel);

    barquito->tesoros[i].ronda = ronda;
}

void mostrarhistorial (Pila historial) //despues de cada ronda para cada barco? lo puse al final de inciar partida por las dudas
{
    Pila aux;
    inicpila(&aux);
    int dato;
    printf("Historial de niveles de ultimos tesoros encontrados: \n");
    while(!pilavacia(&historial))
    {
        printf("Tesoro nivel: %d \n", tope(&historial));
        dato=desapilar(&historial);
        apilar(&aux,dato);
    }
    while(!pilavacia(&aux))
    {
        dato=desapilar(&aux);
        apilar(&historial,dato);
    }
}
void listarCapitanesAlfabeticamente(Barco barquitos[], int cant)
{
    Barco copia[50];

    for (int i = 0; i < cant; i++)
    {
        copia[i] = barquitos[i];
    }
    ordenarCapitanesSeleccion(copia, cant);
    mostrarCapitanes(copia, cant);


}
void ordenarCapitanesSeleccion(Barco copia[], int cant)
{
    int posMenor;
    Barco aux;

    for (int i=0; i<cant; i++)
    {
        posMenor = i;

        for (int j = i+1; j<cant; j++)
        {
            if (strcmp(copia[j].capitan.nombre, copia[posMenor].capitan.nombre) < 0)
            {
                posMenor=j;
            }
        }

        aux=copia[i];
        copia[i]=copia[posMenor];
        copia[posMenor]=aux;
    }
}
void mostrarCapitanes(Barco barquitos[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        printf("Capitan: %s %s\n", barquitos[i].capitan.nombre, barquitos[i].capitan.apellido);
        printf("Puntaje: %i", barquitos[i].puntaje);
    }
}
void mostrarClasificacion(Barco barquitos[], int cant)
{
    Barco copia[50];
    for(int i=0; i<cant; i++)
    {
        copia[i] = barquitos[i];
    }
    ordenarPorPuntaje(copia, cant);

    for(int i=0; i<cant; i++)
    {
        printf("%d %s - %d puntos\n", i+1, copia[i].capitan.nombre, copia[i].puntaje);
    }
}

void ordenarPorPuntaje(Barco barquitos[], int cant)
{
    int i, j;
    Barco aux;

    for (i = 1; i < cant; i++)
    {
        aux = barquitos[i];
        j = i-1;

        while (j >= 0 && barquitos[j].puntaje < aux.puntaje)
        {
            barquitos[j+1] = barquitos[j];
            j--;
        }
        barquitos[j+1]=aux;
    }
}
