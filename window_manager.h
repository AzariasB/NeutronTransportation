/* 
 * File:   window_manager.h
 * Author: boutina
 *
 * Created on 26 novembre 2015, 14:57
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

#ifndef WINDOW_MANAGER_H
#define	WINDOW_MANAGER_H


void activate(GtkApplication* app, gpointer user_data);
void start(int argc,char **argv);

#endif	/* WINDOW_MANAGER_H */

