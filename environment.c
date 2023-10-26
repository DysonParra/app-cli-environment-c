/*
 * @fileoverview    {FileName}
 *
 * @version         2.0
 *
 * @author          Dyson Arley Parra Tilano <dysontilano@gmail.com>
 *
 * @copyright       Dyson Parra
 * @see             github.com/DysonParra
 *
 * History
 * @version 1.0     Implementation done.
 * @version 2.0     Documentation added.
 */
#include "environment.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char** splitArray(char* array, char* word);

/**
 * Entrada principal del sistema.
 *
 * @param argc cantidad de argumentos pasados en la linea de comandos.
 * @param argv argumentos de la linea de comandos.
 * @return {0} si el programa se ejecutó correctamente.
 */
int main(int argc, char** argv) {
    if (argc != 3)                                                      // Si no se indicaron los parámetros necesarios (nombre del programa, ruta de la variable y operación).
        return 1;                                                       // Devuelve uno indicando error.

    system("path > path.tmp");                                          // Crea archivo con el contenido actual de la variable de entorno path.
    FILE* fp = fopen("Path.tmp", "r+");                                 // Abre el archivo con el contenido de la variable de entorno path.
    char path[10000] = "";                                              // Crea array que tendrá el contenido de la variable de entorno path.
    fgets(path, 10000, fp);                                             // Obtiene el contenido de "path.tmp".
    if (path[strlen(path) - 2] == ';')                                  // Si el último carácter de path es un punto y coma.
        path[strlen(path) - 2] = 0;                                     // Borra el punto y coma y el salto de línea de path.
    else                                                                // Si el último carácter de path no es un punto y coma.
        path[strlen(path) - 1] = 0;                                     // Borra el salto de línea de path.
    fclose(fp);                                                         // Cierra "path.tmp".
    system("DEL path.tmp");                                             // Borra "path.tmp".

    char* aux = path;                                                   // Crea variable para recorrer path.
    for (int i = 0; i < (int)strlen(path); i++)                         // Recorrre path.
        if (path[i] == '=') {                                           // Si encuentra el inidicador de incio de variables de entorno.
            aux = &path[i + 1];                                         // A aux le lleva la primera variable de entorno.
            break;                                                      // Sale del ciclo.
        }

    // printf("Parm: \"%d\"\n", argc);                                  // Muestra la cantidad de parámetros.
    // printf("Argv: \"%s\"\n", argv[1]);                               // Muestra el contenido de del parámetro.
    // printf("Path: \"%s\"\n", path);                                  // Muestra el contenido de path.
    // printf("Path: \"%s\"\n", aux);                                   // Muestra el contenido de path desde la primera variable de entorno.
    // printf("Type: \"%s\"\n", argv[2]);                               // Muestra si se indicó agregar o borrar.

    char** values = splitArray(aux, (char*)";");                        // Crea array de apuntadores con apuntadores a cada variable de entorno.
    char newPath[10000] = "";                                           // Crea array que tendrá el nuevo contenido de la variable de entorno path.

    for (int i = 0; i <= 1000; i++)                                     // Recorre el array de punteros obtenido.
        if (values[i] != NULL) {                                        // Si no es el último puntero.
            // printf("-%s-\n", values[i]);                             // Imprime el puntero.
            if (strncmp(argv[1], values[i], strlen(argv[1]))) {         // Si la variable de entorno actual no es igual a la del parámetro.
                if (strlen(newPath) == 0)                               // Si es la primera variable de entorno.
                    sprintf(newPath, "%s", values[i]);                  // Pone newPath como la variable de entorno actual.
                else                                                    // Si no es la primera variable de entorno.
                    sprintf(newPath, "%s;%s", newPath, values[i]);      // Agrega la vaiable de entorno actual a newPath.
                // printf("-%s-\n", newPath);                           // Imprime el nuevo path.
            }
        } else     // Si es el último puntero.
            break; // Sale del for.

    if (atoi(argv[2]))                                                  // Si se indicó agregar variable de entorno.
        sprintf(newPath, "%s;%s", newPath, argv[1]);                    // Agrega la variable de entorno parámetro a newPath.

    // printf("Path: \"%s\"\n", newPath);                               // Imprime el nuevo path.
    char buf[BUFSIZ] = "";                                              // Crea array para ejecutar comandos.
    sprintf(buf, "setx Path /m \"%s\"", newPath);                       // Almacena el comando de asignación del nuevo valor de path.
    printf("%s", buf);                                                  // Muestra el comando en pantalla.
    system(buf);                                                        // Ejecuta el comando.

    return 0;
}

/**
 * FIXME: Definición de {@code splitArray}.
 * Divide un array en n-array cada que encuentre la cadena indicada por "word".
 */
static char** splitArray(char* array, char* word) {
    int arraySize = (int)strlen(array);                                 // Obtiene la longitud del array parámetro.
    int wordSize = (int)strlen(word);                                   // Obtiene la longitud de la palabra parámetro.
    char** values = malloc((arraySize / wordSize) * sizeof(char*));     // Crea array de apuntadores que tendrá los apuntadores a cada aparición de word.
    int valueNumber = 0;                                                // Variable que contará la cantidad de veces que aparezca "word".

    values[valueNumber] = &array[0]; // Almacena en la primera posión de values la posición de inicio de array.

    for (int i = 0; i < arraySize; i++)                                 // Recorre array.
        if (!strncmp(&array[i], word, wordSize)) {                      // Si encuentra la palabra indicada por word.
            valueNumber++;                                              // Aumenta la cantidad de veces que aparece la palabra.
            values[valueNumber] = &array[i];                            // Almacena el apuntador a la palabra.
        }

    values[valueNumber + 1] = NULL;                                     // Marca el fin de los apuntadores.

    realloc(values, (valueNumber + 2) * sizeof(char*));                 // Redimensiona el tamaño del array de apuntadores.

    for (int i = 1; i <= valueNumber; i++) {                            // Recorre el array de apuntadores desde el segundo elemento.
        values[i][0] = 0;                                               // Marca el fin de la cadena en el array.
        values[i] += wordSize;                                          // Actualiza el puntero actual a después de la palabra.
    }

    return values;                                                      // Devuelve el array con los apuntadores.
}
