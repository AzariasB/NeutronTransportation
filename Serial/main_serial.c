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

double r2()
{
    return (double)rand() / (double)RAND_MAX ;
}

/**
 * Here is where the magic happen!
 * This is where the simulation is made by making a
 * neutron travelling across a material
 * @param mat [description]
 * @param res [description]
 */
void calcTransportation( material mat, int* res) {
    for (int i = 0; i < numberOfNeutron; i++) {
        double direction = 0;
        double position = 0;
        int bouncing = TRUE;
        while (bouncing) {
            double u = r2();
            double distance = -(1 / mat.mean_free_path) * log(u);
            position += distance * cos(direction);
            if (position < 0) { // Reflected
                res[0]++;
                bouncing = FALSE;
            } else if (position >= mat.thickness) { // Transmitted
                res[2]++;
                bouncing = FALSE;
            } else if (u < (mat.absorbing / mat.mean_free_path )) {//Absorbed
                res[1]++;
                bouncing = FALSE;
            } else {
                direction = u * M_PI;
            }
        }
    }
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t));
    material mat;
    mat.mean_free_path = 5e-1; //Mean free path for ambiant pressure : 68 nm
    mat.absorbing = 0.49; // Why this value .... I dont' know :-(
    mat.thickness = 10; // In meters
    int answer[3] = {0,0,0};
    calcTransportation(mat, answer);
    printf("reflected : %d, absorbed : %d, transmitted : %d\n", answer[0], answer[1], answer[2]);

    return (EXIT_SUCCESS);
}

/*
* Neutron scattering lengths and cross sections : https://www.ncnr.nist.gov/resources/n-lengths/
 */
