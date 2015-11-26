

#include "calc_transportation.h"

#ifdef CALC_TRANSPORTATION_H


int numberOfNeutron = 1000;
int coreNumber = 4;

pthread_mutex_t* mutexes;
int answer[3] = {0, 0, 0};

struct _material {
    //Free path : path a molecule before interact with one of the atom of the material
    double mean_free_path;
    //double scattering; // useless for the moment
    double absorbing; //Absorbing component of the material
    float thickness; //Thickness of the material
};

double r2() {
    return (double) rand() / (double) RAND_MAX;
}

material *material_new(double mean_f_path,double absorbing,float thickness ){
    material *mat = malloc(sizeof(material));
    mat->absorbing = absorbing;
    mat->mean_free_path = mean_f_path;
    mat->thickness = thickness;
    return mat;
    
}

/*
 * Main calculus of the program
 */
void *calc_transportation(void* mat_prop) {
    material *mat = (material*) mat_prop;
    for (int i = 0; i < (int) (numberOfNeutron / coreNumber); i++) {
        double direction = 0;
        double position = 0;
        int bouncing = TRUE;
        while (bouncing) {
            double u = r2();
            int answer_index = -1;
            double distance = -(1 / mat->mean_free_path) * log(u);
            position += distance * cos(direction);
            if (position < 0) { // Reflected
                answer_index = 0;
                bouncing = FALSE;
            } else if (position >= mat->thickness) { // Transmitted
                answer_index = 2;
                bouncing = FALSE;
            } else if (u < (mat->absorbing / mat->mean_free_path)) {//Absorbed
                answer_index = 1;
                bouncing = FALSE;
            } else {
                direction = u * M_PI;
            }
            if (answer_index > -1) {
                pthread_mutex_lock(&mutexes[answer_index]);
                answer[answer_index]++;
                pthread_mutex_unlock(&mutexes[answer_index]);
                answer_index = -1;
            }
        }
    }
}

#endif