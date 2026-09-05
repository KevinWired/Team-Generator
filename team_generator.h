#ifndef TEAM_GENERATOR
#define TEAM_GENERATOR

#define NAME_MAX_SIZE 32
#define LIMIT_RANGE 101 

typedef unsigned int uint;

typedef struct player_t {
    uint id;
    char username[NAME_MAX_SIZE];
} player;

uint pseudo_random_number_generator(); // Genera un numero psudo-aleatorio dentro del 0 al 100.

void line_spacing();

void trim_newline(char *str);

void to_uppercase(char *str);

#endif // TEAM_GENERATOR