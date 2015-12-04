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
//static GtkBuilder *p_builder;

void setup_window(GtkWidget* window);
int start(int argc,char **argv);
void runTest(material *mat,GtkBuilder *p_builder);
void *init_test(GtkWidget* trigerrer,gpointer callback_data);
material *create_material(GtkBuilder* p_builer);

#endif	/* WINDOW_MANAGER_H */

