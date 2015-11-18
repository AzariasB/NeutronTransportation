/* 
 * File:   main.c
 * Author: boutina
 *
 * Created on 16 novembre 2015, 09:30
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define TRUE 1
#define FALSE 0

typedef struct material {
    //Free path : path a molecule before interact with one of the atom of the material
    double mean_free_path;
    //double scattering; // useless for the moment
    double absorbing; //Absorbing component of the material
    float thickness; //Thickness of the material
} material;

static int numberOfNeutron = 1000;
static pthread_mutex_t* mutexes;
static pthread_t* cores;
static int coreNumber = 4;

// Number of : {reflected,transmitted,absorbed}
static int answer[3] = {0, 0, 0};

static material mat;

double r2() {
    return (double) rand() / (double) RAND_MAX;
}

void *calcTransportation() {
    for (int i = 0; i < (int) (numberOfNeutron / coreNumber); i++) {
        double direction = 0;
        double position = 0;
        int bouncing = TRUE;
        while (bouncing) {
            double u = r2();
            double distance = -(1 / mat.mean_free_path) * log(u);
            position += distance * cos(direction);
            if (position < 0) { // Reflected
                pthread_mutex_lock(&mutexes[0]);
                answer[0]++;
                pthread_mutex_unlock(&mutexes[0]);
                bouncing = FALSE;
            } else if (position >= mat.thickness) { // Transmitted
                pthread_mutex_lock(&mutexes[2]);
                answer[2]++;
                pthread_mutex_unlock(&mutexes[2]);
                bouncing = FALSE;
            } else if (u < (mat.absorbing / mat.mean_free_path)) {//Absorbed
                pthread_mutex_lock(&mutexes[1]);
                answer[1]++;
                pthread_mutex_unlock(&mutexes[1]);
                bouncing = FALSE;
            } else {
                direction = u * M_PI;
            }
        }
    }
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t)); // Reseting random number generation

    //Init material caracteristics
    mat.mean_free_path = 5e-1; // Random value ...
    mat.absorbing = 0.49; // Why this value .... I dont' know :-(
    mat.thickness = 10; // In meters

    int ans_length = sizeof (answer) / sizeof (int);
    mutexes = malloc(sizeof (pthread_mutex_t) * ans_length);

    for (int i = 0; i < ans_length; i++) {
        if (pthread_mutex_init(&mutexes[i], NULL) != 0) {
            return EXIT_FAILURE;
        }
    }

    cores = malloc(sizeof (pthread_t) * coreNumber);
    for (int i = 0; i < coreNumber; i++) {
        int err = pthread_create(&cores[i], NULL, calcTransportation, (void *) &i);
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

    printf("Number of transmitted : %d\nNumber of absorbed : %d\nNumber of rereflected : %d\n",answer[1],answer[2],answer[0]);
    return (EXIT_SUCCESS);
}