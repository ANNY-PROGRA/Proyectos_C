#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LONGITUD 100
#define ARCHIVO "ToDoList.txt"

typedef struct{
    int id;
    char descripcion[MAX_LONGITUD];
} Tarea;

int obtenerUltimoID() {
    FILE *file = fopen(ARCHIVO, "r");
    if (file == NULL){
        return 0;
    }

    Tarea tarea;
    int ultimoID = 0;

    while (fscanf(file, "%d %[^\n]",&tarea.id, tarea.descripcion) != EOF) {
    ultimoID = tarea.id;
    }
    
    fclose(file);
    return ultimoID;        
}

void agregarTarea() {
    FILE *file = fopen(ARCHIVO, "a");
    if (file == NULL) {
        printf ("Error al abrir el archivo. \n");
        return;
    }

    Tarea tarea;
    tarea.id = obtenerUltimoID() + 1;

    printf("Ingrese la descripcion de la tarea: ");
    getchar();
    fgets(tarea.descripcion, MAX_LONGITUD, stdin);
    tarea.descripcion[strcspn(tarea.descripcion, "\n")] = 0;

    fprintf(file, "%d %s\n", tarea.id, tarea.descripcion);
    fclose(file);
    printf("Tarea agregada con éxito.\n");
}

void listarTareas() {
    FILE *file = fopen(ARCHIVO, "r");
    if (file == NULL) {
        printf ("No hay tareas registradas.\n");
        return;
    }

    Tarea tarea;
    int hayTareas = 0;

    printf("\n Lista de Tareas \n");
    while (fscanf(file, "%d %[^\n]", &tarea.id, tarea.descripcion) != EOF) {
        printf("[%d] %s\n", tarea.id, tarea.descripcion);
        hayTareas = 1;
    }
    fclose(file);

    if (hayTareas == 0) {
        printf("No hay tareas registradas.\n");
    }
}

void eliminarTarea() {
    listarTareas();
    FILE *file = fopen(ARCHIVO, "r");
    if (file == NULL) {
        printf ("No hay tareas registradas.\n");
        return;
    }

    int idEliminar;
    printf("Ingrese el ID de la tarea a eliminar: ");
    scanf("%d", &idEliminar);

    Tarea tarea;
    FILE *tempFile = fopen("temporal.txt", "w");

    int tareaEliminada = 0;
    while (fscanf(file, "%d %[^\n]", &tarea.id, tarea.descripcion) != EOF) {
        if (tarea.id != idEliminar) {
            fprintf(tempFile, "%d %s\n", tarea.id, tarea.descripcion);
        } else {
            tareaEliminada = 1;
        }
    }
    
    fclose(file);
    fclose(tempFile);

    remove(ARCHIVO);
    rename("temporal.txt", ARCHIVO);

    if (tareaEliminada) {
        printf("Tarea eliminada con éxito.\n");
    } else {
        printf("No se encontró una tarea con ese ID.\n");
    }
}   

int main() {
    int opcion;
    do{
        printf("\nGestor de Tareas\n");
        printf("1. Agregar tarea\n");
        printf("2. Visualizar tareas\n");
        printf("3. Eliminar tarea\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: 
              agregarTarea();
              break;
            case 2:
              listarTareas();
              break;
            case 3:
              eliminarTarea();
              break;
            case 4:
              printf("Saliendo del gestor de tareas...\n");
              break;
            default:
              printf("Opción no válida. Intente de nuevo.\n");        
        }
    } while (opcion != 4);

    return 0;
}