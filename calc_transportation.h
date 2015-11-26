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

#define TRUE 1
#define FALSE 0

extern int numberOfNeutron;
extern int coreNumber;

extern pthread_mutex_t* mutexes;

// Number of : {reflected,transmitted,absorbed}
extern int answer[3];

typedef struct _material material;

material *material_new(double mean_f_path,double absorbing,float thickness );

double r2();

void *calc_transportation(void* mat_prop);



#endif	/* CALC_TRANSPORTATION_H */

