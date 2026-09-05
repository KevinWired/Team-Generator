/******************************************************************************
 *
 *              Date create: Nov 14, 2024
 *
 *              Last update: Sep 5, 2026
 *
 *              Author: Kevin Santillan
 *
 *              File: teams.c
 *
 ******************************************************************************/

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "team_generator.h"
#include "shuffle.h"

// Límite razonable de jugadores para evitar pedir cantidades de memoria
// absurdas ante una entrada inválida o maliciosa.
#define MAX_PLAYERS 10000u
#define INPUT_BUFFER_SIZE 64

// Lee una línea completa de stdin y la interpreta como un entero sin signo.
// Devuelve true si se pudo leer y convertir un número válido, false en caso
// contrario (fin de archivo, error de lectura, texto no numérico, etc.).
// A diferencia de scanf("%u", ...), esta función controla explícitamente
// signos negativos y desbordes, en vez de dejar que se conviertan
// silenciosamente en números sin signo enormes.
static bool read_uint_line(uint *out)
{
    char buffer[INPUT_BUFFER_SIZE];

    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return false;
    }

    trim_newline(buffer);

    // Rechazar explícitamente signos negativos: strtoul los aceptaría y
    // los envolvería en un valor sin signo enorme.
    size_t start = strspn(buffer, " \t");
    if (buffer[start] == '-') {
        return false;
    }

    if (buffer[start] == '\0') {
        return false;
    }

    char *end = NULL;
    errno = 0;
    unsigned long value = strtoul(buffer + start, &end, 10);

    if (errno == ERANGE || value > (unsigned long)MAX_PLAYERS) {
        return false;
    }

    // Debe consumirse toda la línea (salvo espacios finales) para
    // considerarla un número válido.
    while (*end == ' ' || *end == '\t') {
        end++;
    }
    if (*end != '\0') {
        return false;
    }

    *out = (uint)value;
    return true;
}

// Pide la cantidad total de jugadores hasta obtener un número par, mayor
// que 0 y dentro de un límite razonable. Aborta el programa si la entrada
// no puede leerse (por ejemplo, fin de archivo).
static uint read_total_players(void)
{
    uint total;

    printf("Ingresa la cantidad TOTAL de jugadores:\n");

    if (!read_uint_line(&total)) {
        printf("Error: La entrada no es un número válido. Abortando programa.\n");
        exit(EXIT_FAILURE);
    }

    while (total == 0 || total % 2 != 0 || total > MAX_PLAYERS) {
        printf("Cantidad de jugadores inválida. Debe ser un número par, mayor que 0 y menor o igual a %u.\n", MAX_PLAYERS);

        if (!read_uint_line(&total)) {
            printf("Error: La entrada no es un número válido. Abortando programa.\n");
            exit(EXIT_FAILURE);
        }
    }

    return total;
}

int main(void)
{
    srand((unsigned)time(NULL));

    line_spacing();
    printf("Team Generator\n");
    line_spacing();

    uint total = read_total_players();

    printf("Ingresa el nombre de cada uno de los jugadores:\n");

    // Se usa memoria dinámica (en vez de arrays de tamaño variable sobre
    // la pila) para no arriesgarse a un desborde de stack si 'total' es
    // grande.
    player *array = malloc((size_t)total * sizeof(player));
    if (!array) {
        fprintf(stderr, "Error: no se pudo reservar memoria para los jugadores.\n");
        return EXIT_FAILURE;
    }

    for (uint i = 0; i < total; i++) {
        printf("Nombre del jugador #%u: ", i + 1);

        if (fgets(array[i].username, NAME_MAX_SIZE, stdin)) {
            trim_newline(array[i].username);
            to_uppercase(array[i].username);
            array[i].id = i; // Antes quedaba sin inicializar.
        } else {
            fprintf(stderr, "Error al leer el nombre del jugador %u\n", i + 1);
            free(array);
            return EXIT_FAILURE;
        }
    }

    shuffle(array, total);

    uint half = total / 2;

    player *team_1 = malloc((size_t)half * sizeof(player));
    player *team_2 = malloc((size_t)half * sizeof(player));
    if (!team_1 || !team_2) {
        fprintf(stderr, "Error: no se pudo reservar memoria para los equipos.\n");
        free(array);
        free(team_1);
        free(team_2);
        return EXIT_FAILURE;
    }

    // Dividir jugadores en dos equipos.
    for (uint i = 0; i < half; i++) {
        team_1[i] = array[i];
        team_2[i] = array[i + half];
    }

    line_spacing();

    printf("<TEAM 1>\n");

    for (uint i = 0; i < half; i++) {
        printf("-%s.\n", team_1[i].username);
    }

    printf("\n<TEAM 2>\n");

    for (uint i = 0; i < half; i++) {
        printf("-%s.\n", team_2[i].username);
    }

    free(array);
    free(team_1);
    free(team_2);

    return EXIT_SUCCESS;
}
