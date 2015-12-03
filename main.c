/* 
 * File:   main.c
 * Author: boutina
 *
 * Created on 16 novembre 2015, 09:30
 */


#include "window_manager.h"

int main(int argc, char** argv) {
    return start(argc,argv);
}

//    time_t t;
//    srand((unsigned) time(&t)); // Reseting random number generation
//
//
//    if (argc < 4 || argv[1] == "--help") {
//        printf("----HELP-----\n");
//        printf("USAGE : ./transportation MEAN_FREE_PATH ABSORBING WALL_THICKNESS\n");
//        printf("Options :\n");
//        printf("--core NUMBER_OF_THREADS\n");
//        printf("--neutrons NUMBER_OF_NEUTRONS\n");
//        exit(EXIT_SUCCESS);
//    }
//
//    if (argc >= 4) {
//        for (int opt = 4; opt < argc; opt += 2) {
//
//            set_options((char *[]) {
//                argv[opt], argv[opt + 1]
//            });
//        }
//    }
