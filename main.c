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

/*
 * 
 */
typedef struct material {
    //Free path : path a molecule before interact with one of the atom of the material
    double mean_free_path;
    //double scattering; // useless for the moment
    double absorbing; //Absorbing component of the material
    float thickness; //Thickness of the material
} material;

double r2()
{
    return (double)rand() / (double)RAND_MAX ;
}

void calcTransportation(int numberOfNeutron, material mat, int* res) {
    unsigned int absorbed = 0,
            reflected = 0,
            transmitted = 0;
    for (int i = 0; i < numberOfNeutron; i++) {
        double direction = 0;
        double position = 0;
        int bouncing = TRUE;
        while (bouncing) {
            double u = r2();
            double distance = -(1 / mat.mean_free_path) * log(u);
            position += distance * cos(direction);
            printf("rand : %f, distance : %f,position : %f\n",u,distance,position);
            if (position < 0) { // Reflected
                printf("Reflected\n");
                reflected++;
                bouncing = FALSE;
            } else if (position >= mat.thickness) { // Transmitted
                printf("transmitted !\n");
                transmitted++;
                bouncing = FALSE;
            } else if (u < (mat.absorbing / mat.mean_free_path )) {//Absorbed
                printf("Absorbed : beacuse %f less than : %f\n",u,(mat.absorbing/mat.mean_free_path));
                absorbed++;
                bouncing = FALSE;
            } else {
                direction = u * M_PI;
            }
        }
        printf("---end---\n");
    }
    res[0] = reflected;
    res[1] = absorbed;
    res[2] = transmitted;
}

int main(int argc, char** argv) {
    time_t t;
    srand((unsigned) time(&t));
    material mat;
    mat.mean_free_path = 1e-1; //Mean free path for ambiant pressure : 68 nm
    mat.absorbing = 5e-2;
    mat.thickness = 1; // In meters
    int answer[3];
    calcTransportation(10, mat, answer);
    printf("reflected : %d, absorbed : %d, transmitted : %d", answer[0], answer[1], answer[2]);

    return (EXIT_SUCCESS);
}

/*
* Neutron scattering lengths and cross sections : https://www.ncnr.nist.gov/resources/n-lengths/
 */