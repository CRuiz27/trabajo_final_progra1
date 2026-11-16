#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"

typedef struct
{
    char nombre[20];
    char apellido[20];
    int aniosExperiencia;
    int tesoroEncontrado;
    int activo;
} Capitan;

typedef struct
{
    int nivel;
    char material[30];
    int cantOro;
    int ronda;  // Indica en que ronda fue encontrado
} Tesoro;

typedef struct
{
    int cantTesoros;
    int cantTripulantes;
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

void leerTexto(char texto[], int dimension);
int cantidadBarcos();

void menu();
void subMenu();

Capitan cargarCapitan();
Barco cargarBarco();
void arregloDeBarcos(Barco barcos[], int cant);
void cargarTesoro(Barco *barquito, Pila *historial, int ronda);
int verificarTesoro(int nivelTes);

void mostrarTodosLosBarcos();
void mostrarBarcoEspecifico(int idAux);

void modificaCapitan(Capitan *capitan);
void modificarDatos();
void darDeBaja(int id);
void darDeAlta(int id);
void guardarCompetencia(Barco barquitos[], int cantBarcos);
int maxPuntaje(Barco barquitos[], int cantBarcos);
void actualizaPuntajes(Barco barquitos[], int cantBarcos, int ronda);

Historico cargarHistorico(Barco barquitos[], int cantBarcos, int posGanador);
void guardarHistorico(Barco barquitos[], int cantBarcos, int posGanador);
void muestraHistorico(Historico historico);
void actualizaHistorico();
void consultarDatosHistoricos();

int cuentaTesoros();
void guardarTesoro(Tesoro tesoro);
void iniciarPartida(Barco barquitos[], int cant, Pila historial);
void mostrarHistorial(Pila historial);

void listarCapitanesAlfabeticamente();
void ordenarCapitanesSeleccion(Capitan filtrados[], int cantFiltrados);
void mostrarCapitanes();
void guardarCapitan(Capitan capitan);
void modificarCapitanArchivo(Capitan capitan);
void marcarCapitanesConTesoros(Barco barquitos[], int cant);
void capitanesConTesoros();

void mostrarClasificacion(Barco barquitos[], int cant);
void ordenarPorPuntaje(Barco barquitos[], int cant);

int main()
{
    printf("\n -- BIENVENIDO AL SISTEMA DE COMPETENCIA DE BARCOS --\n\n");
    printf("                  |    |    |\n");
    printf("                 )_)  )_)  )_)\n");
    printf("                )___))___))___)\\\n");
    printf("               )____)____)_____)\\\\\n");
    printf("             _____|____|____|____\\\\\\__\n");
    printf("     ________|  PIRATAS DEL MAR   |______\n");
    printf("     \\                                   /\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("          ~     ~       ~      ~\n");

    while(1)
    {
        menu();
    }

    return 0;
}

void leerTexto(char texto[], int dimension)
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
        printf("\nIngrese la cantidad de barcos que desean jugar: ");
        scanf("%d", &aux);
        if (aux >= 2 && aux <= 5)
        {
            cant = aux;
        }
        else
        {
            printf("La cantidad debe ser entre 2 y 5, ingrese otra cantidad. \n");
        }
    }
    return cant;
}

void menu(Barco barquito[], Pila historial, int cant)
{
    int opcion;
    printf("\nIngrese una opcion\n");

    printf("1. Gestionar barcos de la ultima competencia. \n");
    printf("2. Ver registros historicos. \n");
    printf("3. Salir. \n");

    printf("\nOpcion: ");
    scanf("%d", &opcion);

    switch (opcion)
    {
    case 1:

        subMenu();
        break;

    case 2:

        consultarDatosHistoricos();
        break;

    case 3:

        printf("\nSaliendo... ");
        exit(0);
        break;

    default:

        printf("\nOpcion no valida.\n");
    }
}

void subMenu()
{
    FILE * arch = fopen("Barcos.dat", "rb");

    Pila historial;
    int opcion = -1;
    int posGanador;
    int id;
    int cant;
    int flag = 0;

    if (arch != NULL)   // Corroboro que exista el archivo de barcos
    {
        flag = 1; //nuevo2
        fclose(arch);
    }

    while (opcion != 0)
    {
        printf("\n Ingrese una opcion \n");

        printf("1. Iniciar nueva competencia. \n");             // Si no existe el archivo de barcos, solo la primera opcion esta disponible
        printf("2. Modificar datos. \n");
        printf("3. Mostrar barcos activos. \n");
        printf("4. Buscar un barco especifico. \n");
        printf("5. Dar de baja un barco participante. \n");
        printf("6. Dar de alta un barco participante. \n");
        printf("7: Ver capitanes por orden alfabetico. \n");
        printf("0. Volver al menu principal. \n");

        printf("\n Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:

            inicpila(&historial);

            cant = cantidadBarcos();
            Barco * barquitos = malloc(sizeof(Barco) * cant);

            arregloDeBarcos(barquitos, cant);
            iniciarPartida(barquitos, cant, historial);
            marcarCapitanesConTesoros(barquitos, cant); //nuevo2
            posGanador = maxPuntaje(barquitos, cant);

            guardarCompetencia(barquitos, cant);
            guardarHistorico(barquitos, cant, posGanador);      //problema: si despues de la competencia queremos modificar datos, el historico podría
                                                                //seguir conservando algun dato viejo (ej: si se modifica nombre de capitan)
            printf("\nGANADOR: \n");
            mostrarBarcoEspecifico(barquitos[posGanador].id);
            free(barquitos);
            flag = 1;

            break;

        case 2:

            if (flag)
            {
                modificarDatos();
            }
            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 3:

            if (flag)
            {
                mostrarTodosLosBarcos();
            }
            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 4:

            if (flag)
            {
                printf("Ingrese el id del barco que desea ver: ");
                scanf("%d", &id);
                mostrarBarcoEspecifico(id);
            }
            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 5:

            if (flag)
            {
                printf("Ingrese el id del barco que desea dar de baja: ");
                scanf(" %d", &id);
                darDeBaja(id);
            }
            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 6:

            if (flag)
            {
                printf("Ingrese el id del barco que desea dar de alta: ");
                scanf(" %d", &id);
                darDeAlta(id);
            }
            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 7:

            if (flag)
            {
               listarCapitanesAlfabeticamente();//nuevo2
            }

            else
            {
                printf("\nNo hay barcos cargados. \n");
            }

            break;

        case 0:
            if(flag)
            {
                 actualizaHistorico();//nuevo2
            }

            printf("\n -- MENU PRINCIPAL -- \n");
            break;

        default:

            printf("\nEl valor ingresado no es valido. \n");
            break;
        }
    }
}

Capitan cargarCapitan()
{
    Capitan capitan;

    printf("\nIngrese el nombre del capitan del barco: ");
    leerTexto(capitan.nombre, 20);

    printf("Ingrese el apellido del capitan del barco: ");
    leerTexto(capitan.apellido, 20);

    printf("Ingrese los anios de experiencia: ");
    scanf("%d", &capitan.aniosExperiencia);

    return capitan;
}

Barco cargarBarco()
{
    Barco barquito;
    printf("\nIngrese el id del barco: ");
    scanf(" %d", &barquito.id);
    getchar();

    barquito.capitan = cargarCapitan();

    printf("Ingrese la cantidad de tripulantes: ");
    scanf("%d", &barquito.cantTripulantes);
    getchar();

    barquito.cantTesoros = 0;
    barquito.activo = 1;
    barquito.puntaje = 0;
    barquito.capitan.tesoroEncontrado = 0; //nuevo
    barquito.capitan.activo=1; //nuevo2

    guardarCapitan(barquito.capitan);

    return barquito;
}

void arregloDeBarcos(Barco barcos[], int cant)
{
    printf("\n -- CARGA DE BARCOS -- \n");

    int i = 0;
    int esta;
    Barco barquito;

    FILE * arch = fopen("Capitanes.dat", "wb");//nuevo2
    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }

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
    fopen("Tesoros.dat", "wb"); // Reinicio archivo de tesoros por cada partida
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
                    barquitos[j].cantTesoros++;
                }

                printf("\nResultado de la segunda busqueda: \n");
                printf("Se encontro algun tesoro? (s/n): ");
                scanf(" %c", &letra);
                if (letra == 's')
                {
                    cargarTesoro(&barquitos[j], &historial, i+1);
                    barquitos[j].cantTesoros++;
                }
            }
        }
        actualizaPuntajes(barquitos, cantBarcos, i+1);

        printf("\nDesea ver el estado de la competencia (s/n): ");
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
    int i = barquito->cantTesoros;
    int nivel;

    printf("\nIngrese el nivel del tesoro: ");
    scanf("%d", &nivel);

    nivel = verificarTesoro(nivel);
    barquito->tesoros[i].nivel = nivel;

    getchar();
    printf("\nIngrese el material del tesoro: ");
    leerTexto(barquito->tesoros[i].material, 30);

    printf("\nIngrese la cantidad de oro: ");
    scanf("%d", &barquito->tesoros[i].cantOro);

    apilar(historial, barquito->tesoros[i].nivel);

    barquito->tesoros[i].ronda = ronda;
    guardarTesoro(barquito->tesoros[i]);

    barquito->capitan.tesoroEncontrado = 1; //nuevo.
}
int verificarTesoro(int nivelTes)
{
    while (nivelTes < 1 || nivelTes > 4)
    {
           printf("Los niveles de tesoros validos son del 1 al 4. Vuelva a intentarlo: \n");
           scanf("%d", &nivelTes);
    }
    return nivelTes;
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
                printf("Anios de experiencia del capitan: %d \n", barquito.capitan.aniosExperiencia);
                printf("Cantidad de tripulantes: %d \n", barquito.cantTripulantes);
                printf("Cantidad de tesoros del barco: %d \n", barquito.cantTesoros);
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
    FILE * arch = fopen("Barcos.dat", "rb");

    if (arch)
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.id == idAux)
            {
                printf("\nID del barco: %d \n",barquito.id);
                printf("Capitan del barco: %s %s \n", barquito.capitan.nombre,barquito.capitan.apellido);
                printf("Anios de experiencia del capitan: %d \n", barquito.capitan.aniosExperiencia);
                printf("Cantidad de tripulantes: %d \n", barquito.cantTripulantes);
                printf("Cantidad de tesoros del barco: %d \n", barquito.cantTesoros);
                printf("Puntaje obtenido: %d \n", barquito.puntaje);
                printf("Estado: ");
                if (barquito.activo)
                {
                    printf("ACTIVO.\n");
                }
                else
                {
                    printf("INACTIVO.\n");
                }

                encontrado = 1;
            }
        }

        if (encontrado == 0)
        {
            printf("\nEse barco no existe. \n");
        }

        fclose(arch);
    }
    else
    {
        printf("No se pudo abrir el archivo. \n");
    }
}

void modificaCapitan(Capitan * capitan)
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
        leerTexto(nombre, 20);

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
        printf("\nNuevo apellido del capitan: ");
        getchar();
        leerTexto(apellido, 20);

        if (strcmp(apellido, capitan->apellido) != 0)
        {
            strcpy(capitan->apellido, apellido);
        }
        else
        {
            printf("\nEste apellido es igual al anterior. \n");
        }
    }

    printf("Desea modificar anios de experiencia del capitan? (s/n): ");
    scanf(" %c", &seguir);

    if (seguir == 's')
    {
        printf("Anios de experiencia del capitan: ");
        scanf("%d", &anios);

        if (anios != capitan->aniosExperiencia)
        {
            capitan->aniosExperiencia = anios;
        }
        else
        {
            printf("\nNo se han modificado los anios de experiencia. \n");
        }
    }
}

void modificarDatos()   // Modifica los datos de uno o mas barcos
{
    Barco barquito;
    int id;
    char seguir = 's';
    int tripulantes;
    int encontrado;

    while (seguir == 's')                               // while principal que corta cuando ya no se quiere modificar mas nada
    {
        FILE * arch = fopen("Barcos.dat", "r+b");
        encontrado = 0;

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

                    if (tripulantes != barquito.cantTripulantes)
                    {
                        // Corroboro que la cantidad de tripulantes ingresada sea distinta a la actual
                        barquito.cantTripulantes = tripulantes;
                    }
                    else
                    {
                        printf("No se ha modificado la cantidad de tripulantes.\n");
                    }
                }
                encontrado = 1;

                fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);          // Una vez modificados los campos, los reemplazo en el archivo de barcos
                fwrite(&barquito, sizeof(Barco), 1, arch);
            }
        }

        if (!encontrado)
        {
            printf("\nNo se encontro ese barco.\n");
        }

        fclose(arch);

        printf("Desea modificar otro barco? (s/n): ");
        scanf(" %c", &seguir);
    }
}

void darDeBaja(int id)    // Busco el barco por id y cuando lo encuentro, lo doy de baja.
{
    FILE * arch = fopen("Barcos.dat", "r+b");
    Barco barquito;
    int encontrado = 0;

    if (arch == NULL)
    {
        printf("\n No se pudo acceder al archivo Barcos.dat");
    }
    else
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.id == id)
            {
                if (barquito.activo)
                {
                    barquito.activo = 0;
                    fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);
                    fwrite(&barquito, sizeof(Barco), 1, arch);
                    printf("\nEl barco fue dado de BAJA exitosamente. \n");
                    fclose(arch);
                }
                else
                {
                    printf("\nEl barco ya estaba dado de baja. No se realizaron cambios.");
                }
                encontrado = 1;
            }
        }
        if (encontrado == 0)
        {
            printf("\nNo se encontro el barco buscado.\n");
        }
    }
}

void darDeAlta(int id)
{
    FILE * arch = fopen("Barcos.dat", "r+b");
    Barco barquito;
    int encontrado = 0;

    if (arch == NULL)
    {
        printf("\nNo se pudo acceder al archivo Barcos.dat");
    }
    else
    {
        while (fread(&barquito, sizeof(Barco), 1, arch) > 0)
        {
            if (barquito.id == id)
            {
                if (barquito.activo == 0)
                {
                    barquito.activo = 1;
                    fseek(arch, sizeof(Barco)*(-1), SEEK_CUR);
                    fwrite(&barquito, sizeof(Barco), 1, arch);
                    printf("El barco fue dado de ALTA exitosamente. \n");
                    fclose(arch);
                }
                else
                {
                    printf("\nEl barco buscado ya se encuentra activo. No se realizaron cambios.\n");
                }
                encontrado = 1;
            }
        }
        if (encontrado == 0)
        {
            printf("\nNo se encontro el barco buscado.\n");
        }
    }
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
        for (int j = 0; j < barquitos[i].cantTesoros; j++)
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
    FILE * arch = fopen("Barcos.dat", "wb");
    if (arch == NULL)
    {
        printf("\nNo se ha podido guardar la competencia. \n");
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
        printf("\nNo se ha podido abrir el archivo Historicos.dat. \n");
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

void actualizaHistorico()   // Actualiza datos del capitan, en caso de que se hayan modificado despues de la competencia.
{
    FILE * archH = fopen("Historico.dat", "r+b");
    FILE * archB = fopen("Barcos.dat", "rb");
    Barco barquito;
    Historico historico;

    if (archH && archB)
    {
        fseek(archH, sizeof(Historico)*(-1), SEEK_END);
        fread(&historico, sizeof(Historico), 1, archH);
        while (fread(&barquito, sizeof(Barco), 1, archB) > 0)
        {
            if (historico.idBarcoGanador == barquito.id)
            {
                fseek(archH, sizeof(Historico)*(-1), SEEK_CUR);
                historico.capitanGanador = barquito.capitan;
                fwrite(&historico, sizeof(Historico), 1, archH);
            }
        }
        fclose(archH);
        fclose(archB);
        printf("\nCambios guardados exitosamente.\n");
    }
    else
    {
        printf("\nNo se pudieron guardar los cambios.\n");
    }
}

void consultarDatosHistoricos()
{
    FILE * arch = fopen("Historico.dat", "rb");
    Historico historico;
    int contador = 1;

    if (arch == NULL)
    {
        printf("\nNo se ha podido abrir el archivo Historicos.dat. \n");
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
void listarCapitanesAlfabeticamente()
{
    FILE *arch = fopen("Capitanes.dat", "rb");

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }

    fseek(arch, 0, SEEK_END);
    int total = ftell(arch) / sizeof(Capitan);
    rewind(arch);

    if (total == 0)
    {
        printf("\nNo hay capitanes cargados.\n");
    }else
    {
        Capitan *todos = malloc(sizeof(Capitan) * total);
        fread(todos, sizeof(Capitan), total, arch);

        Capitan *filtrados = malloc(sizeof(Capitan) * total);
        int cantFiltrados = 0;

        for (int i = 0; i < total; i++)
        {
            if (todos[i].activo == 1 && todos[i].tesoroEncontrado == 1)
            {
                filtrados[cantFiltrados++] = todos[i];
            }
        }
        if(cantFiltrados == 0)
        {
            printf("Ningun capitan ha encontrado un tesoro \n");
        }else
        {
            ordenarCapitanesSeleccion(filtrados, cantFiltrados);
            mostrarCapitanes(filtrados, cantFiltrados);
        }
    }

}

void ordenarCapitanesSeleccion(Capitan filtrados[], int cantFiltrados)
{
    int posMenor;
    Capitan aux;

    for (int i=0; i<cantFiltrados-1; i++)
    {
        posMenor = i;

        for (int j = i+1; j<cantFiltrados; j++)
        {
            if (strcmp(filtrados[j].apellido, filtrados[posMenor].apellido) < 0)
            {
                posMenor=j;
            }
        }

        aux = filtrados[i];
        filtrados[i] = filtrados[posMenor];
        filtrados[posMenor] = aux;
    }
}
void mostrarCapitanes(Capitan filtrados[], int cantFiltrados) //nuevo2
{
    printf("\n-- Capitanes activos con tesoros --\n");
    for (int i = 0; i < cantFiltrados; i++)
    {
        printf("%d. %s, %s \n", i + 1, filtrados[i].apellido, filtrados[i].nombre);
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
    FILE * arch = fopen("Capitanes.dat", "ab"); //nuevo2
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
void modificarCapitanArchivo(Capitan capitan) //nuevo.
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

void marcarCapitanesConTesoros(Barco barquitos[], int cant) //pasa el capitanes.dat a un arreglo
{
    FILE * arch = fopen("Capitanes.dat", "rb"); //nuevo2

    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }

    fseek(arch, 0, SEEK_END);
    int totalCapitanes = ftell(arch) / sizeof(Capitan);
    rewind(arch);

    if (totalCapitanes == 0)
    {
        printf("No hay capitanes cargados \n");
        fclose(arch);
    }

    Capitan *lista = malloc(sizeof(Capitan) * totalCapitanes);
    fread(lista, sizeof(Capitan), totalCapitanes, arch);
    fclose(arch);

    for (int i=0; i<totalCapitanes; i++)
    {
        for (int j=0; j<cant; j++)
        {
            if (barquitos[j].capitan.tesoroEncontrado == 1 && strcmp(lista[i].nombre, barquitos[j].capitan.nombre) == 0 && strcmp(lista[i].apellido, barquitos[j].capitan.apellido) == 0)
            {
                lista[i].tesoroEncontrado = 1;
            }
        }
    }

    arch = fopen("Capitanes.dat", "wb");
    if (arch == NULL)
    {
        printf("\n No se ha podido abrir el archivo Capitanes.dat. \n");
    }
    else
    {
        fwrite(lista, sizeof(Capitan), totalCapitanes, arch);
        fclose(arch);
    }

}


