/*
 * File:   calc_transportation.h
 * Author: boutina
 *
 * Created on 26 novembre 2015, 14:25
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#ifndef CALC_TRANSPORTATION_H
#define	CALC_TRANSPORTATION_H

#ifndef M_PI
#define M_PI 3.141592654
#endif

/* In case of .. (also defined in GTK) */
#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

/* Number of neutron to simulate */
extern int numberOfNeutron;

/* Number of threads */
extern int coreNumber;

extern pthread_mutex_t* mutexes;

// Number of : {reflected,transmitted,absorbed}
extern int answer[3];

typedef struct _material material;

/**
 * Create a material object from a minimum amout of data
 * @param  mean_f_path the mean free path of the object see : https://en.wikipedia.org/wiki/Mean_free_path
 * @param  absorbing   The absorbing of the material
 * @param  thickness   thickness of the material (in meters)
 * @return             The newly created material
 */
material *material_new(double mean_f_path,double absorbing,float thickness );

/* Simple random generator*/
double r2();

/**
 * Main calculation. Perform the cacluation for a single neutron
 * Will simulate its traject through the material and depending on the result
 * will change the answer array.
 * @param  mat_prop passed by a thread, must be a material objet converted to void*
 */
void *calc_transportation(void* mat_prop);



#endif	/* CALC_TRANSPORTATION_H */
