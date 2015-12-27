
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
    gtk_builder_add_from_file(p_builder, "assets/ui.xml", & p_err);
    if (p_err != NULL) {
        return EXIT_FAILURE;
    } else {

        MainWindow = (GtkWidget *) gtk_builder_get_object(p_builder, "window1");
        GtkWidget *start_button = (GtkWidget*) gtk_builder_get_object(p_builder, "start");

        g_signal_connect(G_OBJECT(start_button), "clicked", G_CALLBACK(init_test), p_builder);
        g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
        setup_window(MainWindow);
    }

    /* Event loop */
    gtk_widget_show_all(MainWindow);
    gtk_main();

    /* Leaving */
    return EXIT_SUCCESS;
}

material *create_material(GtkBuilder *p_builder) {
    GtkWidget *thickness = (GtkWidget*) gtk_builder_get_object(p_builder, "spin_button_thickness");
    GtkWidget *mean_f_path = (GtkWidget*) gtk_builder_get_object(p_builder, "spin_button_mean_free_path");
    GtkWidget *absorption = (GtkWidget*) gtk_builder_get_object(p_builder, "spin_button_absorption");

    int mat_thickness = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(thickness));
    double mat_mean_f_path = gtk_spin_button_get_value(GTK_SPIN_BUTTON(mean_f_path));
    double mat_absorption = gtk_spin_button_get_value(GTK_SPIN_BUTTON(absorption));

    //Create material from infos
    return material_new(mat_mean_f_path, mat_absorption, mat_thickness);
}

void *init_test(GtkWidget* trigerrer, gpointer callback_data) {
    GtkBuilder *p_builder = GTK_BUILDER(callback_data);

    /* Get the loader */
    GtkWidget *loader = (GtkWidget*) gtk_builder_get_object(p_builder, "loading");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loader), (gdouble) 1 / 20);

    /* Unactivate button */
    gtk_button_set_label(GTK_BUTTON(trigerrer), "Running...");
    gtk_widget_set_sensitive(trigerrer, FALSE);


    /* Create material with properties chosen by the user*/
    material *mat = create_material(p_builder);

    /* Set number of neutrons */
    GtkWidget *spin_neutrons_nb = (GtkWidget*) gtk_builder_get_object(p_builder, "spin_button_nb_neutrons");
    numberOfNeutron = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_neutrons_nb));

    runTest(mat,p_builder);
}

void *runTest(material *mat,GtkBuilder *p_builder) {

    /* Reinit answer*/
    for (int i = 0; i < 3; i++) answer[i] = 0;

    /* Set loader settings */
    GtkWidget *loader = (GtkWidget*) gtk_builder_get_object(p_builder, "loading");
    double loader_value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(loader));
    double threads_inc = 1.f - loader_value - (1 / 20);

#ifdef DEBUG
    printf("Running tests with %d neutrons.\n", numberOfNeutron);
#endif

    int ans_length = sizeof (answer) / sizeof (int);
    mutexes = malloc(sizeof (pthread_mutex_t) * ans_length);

    /* Creating mutexes */
    for (int i = 0; i < ans_length; i++) {
        refreshUI();
        if (pthread_mutex_init(&mutexes[i], NULL) != 0) {
            perror("Could not create mutex");
        }
    }

    /* Creating threads and launching sub-routine */
    cores = malloc(sizeof (pthread_t) * coreNumber);
    for (int i = 0; i < coreNumber; i++) {
        refreshUI();
        int created = pthread_create(&cores[i], NULL, calc_transportation, (void *) mat);
        if (created != 0) {
            perror("Coult not create thread");
        }
    }

    /* Joining thread */
    for (int i = 0; i < coreNumber; i++) {
        int joined = pthread_join(cores[i], NULL);
        if(joined != 0){
            perror("Could not join thread");
        }
        double cur_value = gtk_progress_bar_get_fraction(GTK_PROGRESS_BAR(loader));
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loader), cur_value + threads_inc);
        refreshUI();
    }


    free(cores);

    for (int i = 0; i < ans_length; i++) {
        pthread_mutex_destroy(&mutexes[i]);
    }
    free(mutexes);

    /* Display results */
    GtkWidget *reflected = (GtkWidget*) gtk_builder_get_object(p_builder, "reflect");
    char c_refl[10];
    sprintf(c_refl, "%d", answer[0]);
    gtk_label_set_text(GTK_LABEL(reflected), c_refl);

    GtkWidget *transmitted = (GtkWidget*) gtk_builder_get_object(p_builder, "transmit");
    char c_trans[10];
    sprintf(c_trans, "%d", answer[1]);
    gtk_label_set_text(GTK_LABEL(transmitted), c_trans);

    GtkWidget *absorbed = (GtkWidget*) gtk_builder_get_object(p_builder, "absorb");
    char c_abs[10];
    sprintf(c_abs, "%d", answer[2]);
    gtk_label_set_text(GTK_LABEL(absorbed), c_abs);

    /* Reactivate button */
    GtkWidget *start_button = (GtkWidget*) gtk_builder_get_object(p_builder, "start");
    gtk_widget_set_sensitive(start_button, TRUE);
    gtk_button_set_label(GTK_BUTTON(start_button), "Start");

    /* Reset loader */
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(loader), 0.f);
}

void refreshUI(){
    while(gtk_events_pending()) gtk_main_iteration();
}

#endif
