/* 
 * File:   window_manager.h
 * Author: boutina
 *
 * Created on 26 novembre 2015, 14:57
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#include "calc_transportation.h"

#ifndef WINDOW_MANAGER_H
#define	WINDOW_MANAGER_H

static pthread_t *cores;


void setup_window(GtkWidget* window);
int start(int argc,char **argv);
void runTest();
void initTest(GtkWidget* window);

#endif	/* WINDOW_MANAGER_H */

