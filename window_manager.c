
#include "window_manager.h"

#ifdef WINDOW_MANAGER_H



void setup_window(GtkWidget* window) {
    GtkWindow* win = GTK_WINDOW(window);
    GQuark dom;
    GError *err;
    gtk_window_set_title(win, "Neutron transportation simulation");
    gtk_window_set_position(win, GTK_WIN_POS_CENTER);
    gtk_window_set_icon_from_file(win, "./assets/neutron.jpg", &err);
}

int start(int argc, char** argv) {
    /* Variables */
    GtkWidget * MainWindow = NULL;

    /* Init GTK+ */
     gtk_init(&argc, &argv);


    /* Creating window */    
    GtkBuilder *p_builder = gtk_builder_new();
    GError *p_err = NULL;
    gtk_builder_add_from_file (p_builder, "assets/ui.xml", & p_err);
    if(p_err != NULL){
        printf("You fucked up man\n");
        return EXIT_FAILURE;
    }else{
        MainWindow =  (GtkWidget *) gtk_builder_get_object (p_builder, "window1");
        g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
        setup_window(MainWindow);
    }

    /* Event loop */
    gtk_widget_show_all(MainWindow);
    gtk_main();

    /* Leaving */
    return EXIT_SUCCESS;

}

void initTest(GtkWidget* window){
    
}

void runTest(material* mat) {
    //Init material caracteristics
    //    const material *mat = material_new(atof(argv[1]), atof(argv[2]), atof(argv[3]));

    int ans_length = sizeof (answer) / sizeof (int);
    mutexes = malloc(sizeof (pthread_mutex_t) * ans_length);

    for (int i = 0; i < ans_length; i++) {
        if (pthread_mutex_init(&mutexes[i], NULL) != 0) {
            perror("Could not create mutex");
        }
    }

    cores = malloc(sizeof (pthread_t) * coreNumber);
    for (int i = 0; i < coreNumber; i++) {
        int err = pthread_create(&cores[i], NULL, calc_transportation, (void *) mat);
        if (err != 0) {
            perror("Coult not create thread");
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


}

#endif
