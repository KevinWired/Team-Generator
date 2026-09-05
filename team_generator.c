#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include <string.h>
#include "team_generator.h"

// Nota: la semilla del generador (srand) se establece una única vez en
// main(). Llamar a srand() en cada invocación de esta función volvía a
// sembrar el generador con time(NULL), lo que hacía que llamadas
// consecutivas dentro del mismo segundo devolvieran siempre el mismo
// número (bug de aleatoriedad).
uint pseudo_random_number_generator() {
    return (uint)rand() % LIMIT_RANGE;
}

void line_spacing() {
    printf("\n\n");
}

void trim_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        // Se castea a unsigned char antes de pasarlo a toupper: pasar un
        // char con signo negativo (posible con bytes no ASCII) es
        // comportamiento indefinido según el estándar de C.
        str[i] = (char)toupper((unsigned char)str[i]);
    }
}
