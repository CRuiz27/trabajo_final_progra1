#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    char nombre[20];
    char apellido[20];
    int aniosexperiencia;
    int tesoroEncontrado;
    int activo;
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
    int cantTesorosTotales;
    int idBarcoGanador;
    Capitan capitanGanador;
    int puntaje;
} Historico;

void leertexto(char texto[], int dimension);
int cantidadBarcos();

void menu(Barco barquito[], Pila historial, int cant);
int subMenu(Barco barquito[],Pila historial, int cant);

Barco cargarBarco();
void arregloDeBarcos(Barco barcos[], int cant);
void cargarTesoro(Barco *barquito, Pila *historial, int ronda);

void mostrarTodosLosBarcos();
void mostrarBarcoEspecifico(int idAux);
int posicionBarco(Barco barquitos[], int id, int cant); // no se esta usando creo

void modificaCapitan(Capitan *capitan);
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

int cuentaTesoros();
void guardarTesoro(Tesoro tesoro);
void iniciarPartida(Barco barquitos[], int cant, Pila historial);
void mostrarHistorial(Pila historial);

void listarCapitanesAlfabeticamente(Barco barquitos[], int cant);
void ordenarCapitanesSeleccion(Barco copia[], int cant);
void mostrarCapitanes(Barco barquitos[], int cant);
void guardarCapitan(Capitan capitan);
void modificarCapitanArchivo(Capitan capitan);
void marcarCapitanesConTesoros(Barco barquitos[], int cant);
void capitanesConTesoros();
void mostrarClasificacion(Barco barquitos[], int cant);
void ordenarPorPuntaje(Barco barquitos[], int cant);

void gestionarCapitanes(Barco barquitos[], int cant);

int main()
{
    Pila historial;
    inicpila(&historial);
    int cant;

    printf("\n -- BIENVENIDO AL SISTEMA DE COMPETENCIA DE BARCOS --\n");
    printf("                  |    |    |\n");
    printf("                 )_)  )_)  )_)\n");
    printf("                )___))___))___)\\\n");
    printf("               )____)____)_____)\\\\\n");
    printf("             _____|____|____|____\\\\\\__\n");
    printf("     ________|  PIRATAS DEL MAR   |______\n");
    printf("     \\                                   /\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("          ~     ~       ~      ~\n");

    cant = cantidadBarcos();
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

int cantidadBarcos()
{
    int cant = 0;
    int aux = 0;
    while (cant < 2)
    {
        printf("\n Ingrese la cantidad de barcos que desean jugar: ");
        scanf("%d", &aux);
        if (aux >= 2 && aux <= 5)
        {
            cant = aux;
        }
        else
        {
            printf("La cantidad debe ser mayor a 2 y menor a 5, ingrese otra cantidad \n");
        }
    }
    return cant;
}

void menu(Barco barquito[], Pila historial, int cant)
{
    int opcion;
    printf("\n Ingrese una opcion \n");

    printf("1. Iniciar nueva competencia. \n");
    printf("2. Ver registros historicos. \n");
    printf("3. Salir. \n");

    printf("\n Opcion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:

        subMenu(barquito, historial, cant);
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

int subMenu(Barco barquitos[], Pila historial, int cant)
{
    int opcion;
    int posGanador;
    int id;

    printf("\n Ingrese una opcion \n");

    printf("1. Iniciar partida. \n");
    printf("2. Modificar datos. \n");
    printf("3. Ver informacion de participantes. \n");
    printf("4. Ver informacion especifica. \n");
    printf("5. Dar de baja un barco participante. \n");
    printf("6. Dar de alta un barco participante. \n");
    printf("7: Ver capitanes por orden alfabetico. \n");
    printf("8. Salir \n");

    printf("\n Opcion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:

        arregloDeBarcos(barquitos, cant);
        iniciarPartida(barquitos, cant, historial);
        posGanador = maxPuntaje(barquitos, cant);

        guardarCompetencia(barquitos, cant);
        guardarHistorico(barquitos, cant, posGanador);      //problema: si despues de la competencia queremos modificar datos, el historico podría
        //seguir conservando algun dato viejo (ej: si se modifica nombre de capitan)
        printf("\nGANADOR: \n");
        mostrarBarcoEspecifico(barquitos[posGanador].id);

        break;

    case 2:

        modificarDatos();
        break;

    case 3:

        mostrarTodosLosBarcos();
        break;

    case 4:

        printf("Ingrese el id del barco que desea ver: ");
        scanf("%d", &id);
        mostrarBarcoEspecifico(id);

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
        marcarCapitanesConTesoros(barquitos, cant);
        listarCapitanesAlfabeticamente(barquitos, cant);

        break;

    case 8:

        printf("\nSaliendo... ");
        return 0;
        break;

    default:

        printf("El valor no es valido. \n");
        break;
    }

    return 0;
}

Barco cargarBarco()
{
    Barco barquito;
    printf("\nIngrese el id del barco: ");
    scanf(" %d", &barquito.id);
    getchar();

    printf("\nIngrese el nombre del capitan del barco: ");
    leertexto(barquito.capitan.nombre, 20);

    printf("Ingrese el apellido del capitan del barco: ");
    leertexto(barquito.capitan.apellido, 20);

    printf("Ingrese los anios de experiencia: ");
    scanf("%d", &barquito.capitan.aniosexperiencia);
    getchar();

    printf("Ingrese la cantidad de tripulantes: ");
    scanf("%d", &barquito.canttripulantes);
    getchar();

    barquito.canttesoros = 0;
    barquito.activo = 1;
    barquito.puntaje = 0;
    barquito.capitan.tesoroEncontrado = 0; //nuevo

    guardarCapitan(barquito.capitan);

    return barquito;
}

void arregloDeBarcos(Barco barcos[], int cant)
{
    printf("\n -- CARGA DE BARCOS -- \n");

    int i = 0;
    int esta;
    Barco barquito;

    while (i < cant)
    {
        esta = 0;
        barquito = cargarBarco();

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

void iniciarPartida(Barco barquitos[], int cantBarcos, Pila historial)
{
    char letra;
    int cantRondas;

    printf("\n Ingrese la cantidad de rondas: ");
    scanf("%i", &cantRondas);

    while(cantRondas <= 0 || cantRondas > 5)
    {
        printf("Solo se permiten hasta 5 rondas. Vuelva a intentar");
        scanf("%i", &cantRondas);
    }

    for (int i = 0; i < cantRondas; i++)
    {
        printf("\n Comienza la ronda %d \n", i+1);

        for (int j = 0; j < cantBarcos; j++)
        {
            if (barquitos[j].activo == 1)
            {
                printf("Comienza: ID %d \n", barquitos[j].id);
                printf("\nResultado de la primera busqueda: \n");
                printf("Se encontro algun tesoro? (s/n): "); //validacion con letra== s ?
                scanf(" %c", &letra);
                if (letra == 's')
                {
                    cargarTesoro(&barquitos[j],&historial, i+1);
                    barquitos[j].canttesoros++;
                }

                printf("\nResultado de la segunda busqueda: \n");
                printf("Se encontro algun tesoro? (s/n): ");
                scanf(" %c", &letra);
                if (letra == 's')
                {
                    cargarTesoro(&barquitos[j], &historial, i+1);
                    barquitos[j].canttesoros++;
                }
            }
        }
        actualizaPuntajes(barquitos, cantBarcos, i+1);

        printf("\n Desea ver el estado de la competencia (s/n): ");
        scanf(" %c", &letra);
        if (letra == 's')
        {
            printf("\n -- Clasificacion despues de la ronda %d -- \n\n", i+1);
            mostrarClasificacion(barquitos, cantBarcos);
        }

    }

    marcarCapitanesConTesoros(barquitos, cantBarcos); //nuevo
    mostrarHistorial(historial);
}

void cargarTesoro(Barco *barquito, Pila *historial, int ronda)
{
    int i = barquito->canttesoros;

    printf("\nIngrese el nivel del tesoro: ");
    scanf("%d", &barquito->tesoros[i].nivel);

    getchar();
    printf("\nIngrese el material del tesoro: ");
    leertexto(barquito->tesoros[i].material, 30);

    printf("\nIngrese la cantidad de oro: ");
    scanf("%d", &barquito->tesoros[i].cantoro);

    apilar(historial, barquito->tesoros[i].nivel);

    barquito->tesoros[i].ronda = ronda;
    guardarTesoro(barquito->tesoros[i]);

    barquito->capitan.tesoroEncontrado = 1; //nuevo.
}

void mostrarTodosLosBarcos()
{
    Barco barquito;
    FILE *arch = fopen("Barcos.dat", "rb");
    if (arch)
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.activo == 1)
            {
                printf("\nID del barco: %d \n", barquito.id);
                printf("Capitan del barco: %s %s \n", barquito.capitan.nombre, barquito.capitan.apellido);
                printf("Años de experiencia del capitan: %d \n", barquito.capitan.aniosexperiencia);
                printf("Cantidad de tripulantes: %d \n", barquito.canttripulantes);
                printf("Cantidad de tesoros del barco: %d \n", barquito.canttesoros);
                printf("Puntaje obtenido: %d \n", barquito.puntaje);
            }

        }
    }
    else
    {
        printf("No se pudo abrir el archivo. \n");
    }
}
void mostrarBarcoEspecifico(int idAux)
{
    Barco barquito;
    int encontrado = 0;
    FILE *arch = fopen("Barcos.dat", "rb");

    if (arch)
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.activo && barquito.id == idAux)
            {
                printf("\nID del barco: %d \n",barquito.id);
                printf("Capitan del barco: %s %s \n", barquito.capitan.nombre,barquito.capitan.apellido);
                printf("Anios de experiencia del capitan: %d \n", barquito.capitan.aniosexperiencia);
                printf("Cantidad de tripulantes: %d \n", barquito.canttripulantes);
                printf("Cantidad de tesoros del barco: %d \n", barquito.canttesoros);
                printf("Puntaje obtenido: %d \n", barquito.puntaje);
                encontrado = 1;
            }
        }
        if (encontrado == 0)
        {
            printf("Ese barco no existe. \n");
        }
        fclose(arch);
    }
    else
    {
        printf("No se pudo abrir el archivo. \n");
    }
}

void modificaCapitan(Capitan *capitan)
{
    char seguir;
    char nombre[20];
    char apellido[20];
    int anios;

    printf("Desea modificar el nombre del capitan? (s/n): ");
    scanf(" %c", &seguir);
    getchar();

    if (seguir == 's')
    {
        printf("\n Nuevo nombre del capitan: ");
        leertexto(nombre, 20);

        if (strcmp(nombre, capitan->nombre) != 0)
        {
            strcpy(capitan->nombre, nombre);
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

        if (strcmp(apellido, capitan->apellido) != 0)
        {
            strcpy(capitan->apellido, apellido);
        }
        else
        {
            printf("\n Este apellido es igual al anterior. \n");
        }
    }

    printf("Desea modificar anios de experiencia del capitan? (s/n): ");
    scanf(" %c", &seguir);

    if (seguir == 's')
    {
        printf("Anios de experiencia del capitan: ");
        scanf("%d", &anios);

        if (anios != capitan->aniosexperiencia)
        {
            capitan->aniosexperiencia = anios;
        }
        else
        {
            printf("\n No se han modificado los anios de experiencia. \n");
        }
    }
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
                    modificaCapitan(&barquito.capitan);
                    modificarCapitanArchivo(barquito.capitan);
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
                printf("\nEl barco fue dado de baja exitosamente. \n");
                fclose(arch);
            }
        }
    }

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
            if (barquito.activo == 0 && barquito.id == id)
            {
                barquito.activo = 1;
                fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);
                fwrite(&barquito, sizeof(Barco), 1, arch);
                printf("El barco fue dado de alta. \n");
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
    Historico historico = {0};

    historico.cantBarcos = cantBarcos;
    historico.cantTesorosTotales = cuentaTesoros();

    historico.capitanGanador = barquitos[posGanador].capitan;

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
    printf("Tesoros totales encontrados: %d \n", historico.cantTesorosTotales);
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

void mostrarHistorial(Pila historial)
{
    Pila aux;
    inicpila(&aux);
    int dato;
    printf("\nHistorial de niveles de ultimos tesoros encontrados: \n");
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

        aux = copia[i];
        copia[i] = copia[posMenor];
        copia[posMenor] =  aux;
    }
}
void mostrarCapitanes(Barco barquitos[], int cant)
{
    for (int i = 0; i < cant; i++)
    {
        if (barquitos[i].capitan.activo && barquitos[i].capitan.tesoroEncontrado == 1)
        {
            printf("Capitan: %s %s\n", barquitos[i].capitan.nombre, barquitos[i].capitan.apellido);
            printf("Puntaje: %i", barquitos[i].puntaje);
            printf("Anios de experiencia: %i", barquitos[i].capitan.aniosexperiencia);
        }
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

int cuentaTesoros()
{
    int cantTesoros = 0;
    Tesoro tesoro;
    FILE * arch = fopen("Tesoros.dat", "rb");

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Tesoros.dat. \n");
    }
    else
    {
        while(fread(&tesoro, sizeof(Tesoro), 1, arch))
        {
            cantTesoros++;
        }
        fclose(arch);
    }
    return cantTesoros;
}

void guardarTesoro(Tesoro tesoro)
{
    FILE * arch = fopen("Tesoros.dat", "ab");

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Tesoros.dat. \n");
    }
    else
    {
        fwrite(&tesoro, sizeof(Tesoro), 1, arch);
        fclose(arch);
    }
}

void guardarCapitan(Capitan capitan)
{
    FILE * arch = fopen("Capitanes.dat", "wb"); //nuevo. Cambie a wb. Para que no se repita el mismo capitan que ha participado en mas de una competencia.
    //Que se actualice cada que se inicie une nueva competencia
    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }
    else
    {
        fwrite(&capitan, sizeof(Capitan), 1, arch);
        fclose(arch);
    }
}
void modificarCapitanArchivo(Capitan capitan) //nuevo. Puse nuevo pero creo que no cambie nada.
{
    FILE * arch = fopen("Capitanes.dat", "r+b");
    Capitan aux;

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }
    else
    {
        while (fread(&aux, sizeof(Capitan), 1, arch) > 0)
        {
            if (strcmpi(aux.nombre, capitan.nombre) == 0 && strcmpi(aux.apellido, capitan.apellido) == 0)
            {
                fseek(arch, -sizeof(Capitan), SEEK_CUR);
                fwrite(&capitan, -(long)sizeof(Capitan), 1, arch);
            }
        }
        fclose(arch);
    }
}

void capitanesConTesoros() //busca capitanes con tesoroEncontrado=1
{
    FILE * arch = fopen("Capitanes.dat", "rb");
    Capitan aux;
    int existe=0;

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }
    else
    {
        printf("Capitanes que han encontrado tesoros: \n");
        while(fread(&aux, sizeof(Capitan), 1, arch)>0)
        {
            if(aux.tesoroEncontrado == 1)
            {
                printf("%s %s\n", aux.nombre, aux.apellido);
                existe = 1;

            }
        }
        if(existe==0)
        {
            printf("Ningun capitan ha encontrado tesoro. \n");
        }
        fclose(arch);
    }
}
void marcarCapitanesConTesoros(Barco barquitos[], int cant) //actualiza el archivo de los capitanes para que aparezca el tesorosEncontrado=1 si es que alguno se modifico.
{
    FILE * arch = fopen("Capitanes.dat", "r+b");
    Capitan aux;

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }
    else
    {
        while(fread(&aux, sizeof(Capitan), 1, arch)>0)
        {
            for(int i = 0; i < cant; i++)
            {
                if(barquitos[i].capitan.tesoroEncontrado == 1 && strcmp(aux.nombre, barquitos[i].capitan.nombre)==0 && strcmp(aux.apellido, barquitos[i].capitan.apellido)==0)
                {
                    aux.tesoroEncontrado = 1;
                    fseek(arch, -(long)sizeof(Capitan), SEEK_CUR);
                    fwrite(&aux, sizeof(Capitan), 1, arch);
                    fseek(arch, 0, SEEK_CUR);
                }
            }
        }
    }
}

