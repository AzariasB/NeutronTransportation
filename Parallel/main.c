/* 
 * File:   main.c
 * Author: boutina
 *
 * Created on 16 novembre 2015, 09:30
 */

#include <time.h>
#include <string.h>

#include "calc_transportation.c"


static pthread_t* cores;

void *calcTransportation(void* mat_prop);

void set_options(char **options) {
    if (strcmp(options[0], "--core") == 0 && options[1] != NULL) {
        printf("Setting number of cores\n");
        coreNumber = atoi(options[1]);
    } else if (strcmp(options[0], "--neutrons") == 0 && options[1] != NULL) {
        printf("Setting number of neutrons");
        numberOfNeutron = atoi(options[1]);
    }
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t)); // Reseting random number generation

    if (argc < 4 || argv[1] == "--help") {
        printf("----HELP-----\n");
        printf("USAGE : ./transportation MEAN_FREE_PATH ABSORBING WALL_THICKNESS\n");
        printf("Options :\n");
        printf("--core NUMBER_OF_THREADS\n");
        printf("--neutrons NUMBER_OF_NEUTRONS\n");
        exit(EXIT_SUCCESS);
    }

    if (argc >= 4) {
        for (int opt = 4; opt < argc; opt += 2) {

            set_options((char *[]) {
                argv[opt], argv[opt + 1]});
        }
    }

    //Init material caracteristics
    const material mat = {.mean_free_path = atof(argv[1]), .absorbing = atof(argv[2]), .thickness = atoi(argv[3])};

    int ans_length = sizeof (answer) / sizeof (int);
    mutexes = malloc(sizeof (pthread_mutex_t) * ans_length);

    for (int i = 0; i < ans_length; i++) {
        if (pthread_mutex_init(&mutexes[i], NULL) != 0) {
            return EXIT_FAILURE;
        }
    }

    cores = malloc(sizeof (pthread_t) * coreNumber);
    for (int i = 0; i < coreNumber; i++) {
        int err = pthread_create(&cores[i], NULL, calcTransportation, (void *) &mat);
        if (err != 0) {
            perror("Coult not create thread");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < coreNumber; i++) {
        pthread_join(cores[i], NULL);
    }
    free(cores);

    for (int i = 0; i < ans_length; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }
    free(mutexes);

    printf("Number of transmitted : %d\nNumber of absorbed : %d\nNumber of rereflected : %d\n", answer[1], answer[2], answer[0]);
    return (EXIT_SUCCESS);
}