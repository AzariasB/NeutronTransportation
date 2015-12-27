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
#define WINDOW_MANAGER_H

//#define DEBUG

static pthread_t *cores;

/**
 * add some elements to the window
 * @param window pointer to the main window
 */
void setup_window(GtkWidget* window);

/**
 * main function to call to start the whole process
 * @param  argc number of arguments
 * @param  argv arguments
 * @return      result of the gtk_main_loop
 */
int start(int argc, char **argv);

/**
 * The test core, it updates the UI and create the threads
 * with the calculation to do. Then join them and print the result in
 * the screen
 * @param  mat       the material with all its properties
 * @param  p_builder the builder of the window
 */
void *runTest(material *mat,GtkBuilder *p_builder);

/**
 * Called when click on 'start button'
 * @param  trigerrer     the button that trigerred the Event
 * @param  callback_data data passed
 */
void *init_test(GtkWidget* trigerrer, gpointer callback_data);

/**
 * Little helper to
 * refresh the UI when processing big amout of data
 */
void refreshUI();

/**
 * Helper to create a material object from the user inputs
 * @param  p_builer the main windows's builder
 * @return          the material created from user inputs
 */
material *create_material(GtkBuilder* p_builer);

#endif /* WINDOW_MANAGER_H */
