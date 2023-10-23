#include <stdio.h>
#include <stdlib.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<unistd.h>
#include<string.h>
#include<conio.h>

struct Agenda{
    char nombreNodo[20];
    char correoNodo[50];
    int telefonoNodo;

    struct Agenda * sig;
};

struct Agenda *Inicio = NULL;

void Menu(){
    system("cls");
    puts("Menú: \n");
    puts("1. Agregar contacto");
    puts("2. Eliminar contacto");
    puts("3. Modificar contacto");
    puts("4. Ver contactos");
    puts("5. Salir");
    puts("---------------------");
    printf("Elegir opción: ");
}

void agregarContactoOrdenado(char *nombre, char *correo, int telefono) {
    struct Agenda *nuevo;

    nuevo = malloc(sizeof(struct Agenda));
    strcpy(nuevo->nombreNodo, nombre);
    strcpy(nuevo->correoNodo, correo);
    nuevo->telefonoNodo = telefono;
    nuevo->sig = NULL;

    if (Inicio == NULL) {
        Inicio = nuevo;
    } else {
        struct Agenda *actual = Inicio;
        struct Agenda *anterior = NULL;

        // Encuentra la posición en la que se debe insertar el nuevo contacto
        while (actual != NULL && strcmp(actual->nombreNodo, nombre) < 0) {
            anterior = actual;
            actual = actual->sig;
        }

        // Inserta el nuevo contacto en la posición adecuada
        if (anterior == NULL) {
            nuevo->sig = Inicio;
            Inicio = nuevo;
        } else {
            anterior->sig = nuevo;
            nuevo->sig = actual;
        }
    }

    puts("-----------------------------");
    puts("¡Contacto agregado con éxito!");
    puts("-----------------------------");
    system("pause");
}

/*agregarContacto(char *nombre, char *correo, int telefono){
    struct Agenda *nuevo;

    nuevo = malloc(sizeof(struct Agenda));
    strcpy(nuevo->nombreNodo, nombre);
    strcpy(nuevo->correoNodo, correo);
    nuevo->telefonoNodo = telefono;

    if(Inicio == NULL){
        Inicio = nuevo;
        nuevo->sig = NULL;
    }else{
        nuevo->sig = Inicio;
        Inicio = nuevo;
    }
    puts("-----------------------------");
    puts("¡Contacto agregado con éxito!");
    puts("-----------------------------");
    system("pause");
}*/

void eliminarContacto(char *nombre) {
    struct Agenda *actual = Inicio;
    struct Agenda *anterior = NULL;

    while (actual != NULL) {
        if (strcmp(actual->nombreNodo, nombre) == 0) {
            if (anterior != NULL) {
                anterior->sig = actual->sig;
            } else {
                Inicio = actual->sig;
            }
            free(actual); // Liberar la memoria de la estructura actual
            system("cls");
            printf("¡El contacto de %s se eliminó con éxito!\n", nombre);
            puts("----------------------------------------------------");
            system("pause");
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
    system("cls");
    printf("No se encontró un contacto con el nombre '%s'\n", nombre);
    puts("--------------------------------------------------------");
    system("pause");
}

void modificarContacto(char *nombre) {
    struct Agenda *actual = Inicio;

    while (actual != NULL) {
        if (strcmp(actual->nombreNodo, nombre) == 0) {
            system("cls");
            printf("Nombre actual: %s\n", actual->nombreNodo);
            printf("Nuevo nombre: ");
            fflush(stdin);
            gets(actual->nombreNodo);
            printf("Nuevo correo: ");
            gets(actual->correoNodo);
            printf("Nuevo teléfono (6 dígitos): ");
            scanf("%d", &actual->telefonoNodo);
            while (actual->telefonoNodo > 999999 || actual->telefonoNodo < 100000) {
                puts("--------------------------------------");
                puts("Teléfono inválido, intente de nuevo...");
                puts("--------------------------------------");
                printf("Nuevo teléfono (6 dígitos): ");
                scanf("%d", &actual->telefonoNodo);
            }
            puts("-----------------------------");
            puts("¡Contacto modificado con éxito!");
            puts("-----------------------------");
            system("pause");
            return;
        }
        actual = actual->sig;
    }
    system("cls");
    printf("No se encontró un contacto con el nombre '%s'\n", nombre);
    puts("--------------------------------------------------------");
    system("pause");
}

verContactos(){
    struct Agenda *actual = Inicio;

    if (actual == NULL) {
        puts("La lista de contactos está vacía.");
        puts("---------------------------------");
    } else {
        puts("Lista de contactos:\n");
        while (actual != NULL) {
            printf("Nombre: %s\n", actual->nombreNodo);
            printf("Correo: %s\n", actual->correoNodo);
            printf("Teléfono: 2657-%d\n", actual->telefonoNodo);
            printf("------------------------------\n");
            actual = actual->sig;
        }
    }
    system("pause");
}

int main()
{

    setlocale(LC_ALL, "");
    srand(time(NULL));

    int op,op2,telefono;
    char nombre[20];
    char correo[50];

    puts("CONSIGNA: \n");
    puts("Se pide crear una agenda, donde pueda almacenar el nombre, teléfono y correo electrónico de sus amigos; \nhaciendo uso de una lista enlazada. Dicha agenda, debe permitirle: \nañadir un nuevo registro, eliminar y Mostrar la lista de todos los registros");
    puts("\nProponga una mejora individual en el código que agregue una funcionalidad.");
    puts("---------------------------------------------------------------------------------------------------------");
    puts("Le agregué la función de modificar contacto y que los contactos aparezcan en orden alfabetico descendente");
    puts("---------------------------------------------------------------------------------------------------------");
    system("pause");

    do{
        Menu();
        scanf("%d",&op);
        while(op>5 || op<1){
            puts("------------------------------------");
            puts("¡Opción no valida, intente de nuevo!");
            puts("------------------------------------");
            printf("Elegir opción: ");
            scanf("%d",&op);
        }
        switch(op){
            case 1:
                system("cls");
                fflush(stdin);
                printf("Ingrese el nombre del contacto: ");
                gets(nombre);
                fflush(stdin);
                printf("Ingrese el correo de %s: ",nombre);
                gets(correo);
                printf("Ingrese el telefono de %s (6 digitos): ",nombre);
                scanf("%d",&telefono);
                while(telefono>999999 || telefono<100000){
                    puts("--------------------------------------");
                    puts("Telefono invalido, intente de nuevo...");
                    puts("--------------------------------------");
                    printf("Ingrese el telefono de %s (6 digitos): ",nombre);
                    scanf("%d",&telefono);
                }
                /*agregarContacto(nombre, correo, telefono);*/
                agregarContactoOrdenado(nombre, correo, telefono);
                break;
            case 2:
                system("cls");
                fflush(stdin);
                printf("Ingrese el nombre del contacto que desea eliminar: ");
                gets(nombre);
                eliminarContacto(nombre);
                break;
            case 3:
                system("cls");
                fflush(stdin);
                printf("Ingrese el nombre del contacto que desea modificar: ");
                gets(nombre);
                modificarContacto(nombre);
                break;
            case 4:
                system("cls");
                verContactos();
                break;
            case 5:
                system("cls");
                puts("¿Está seguro que desea salir?\n1.Si\n2.No");
                puts("-----------------");
                printf("Elegir opción: ");
                scanf("%d",&op2);
                while(op2>2 || op2<1){
                    puts("------------------------------------");
                    puts("¡Opción no valida, intente de nuevo!");
                    puts("------------------------------------");
                    printf("Elegir opción: ");
                    scanf("%d",&op2);
                }
                switch(op2){
                case 1:
                    system("cls");
                    puts("Saliendo del programa...");
                    sleep(2);
                    break;
                case 2:
                    system("cls");
                    puts("Volviendo al menú...");
                    sleep(2);
                    op=1;
                    break;
                }
                break;
        }
    }while(op!=5);
    return 0;
}
