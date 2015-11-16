/* 
 * File:   main.c
 * Author: boutina
 *
 * Created on 16 novembre 2015, 09:30
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    printf("coucou");
    return (EXIT_SUCCESS);
}

/*
 * C - mean distance between neutron/atom intercations
 * Ci - Scaterring component of C
 * Cc - Absorbing component of C
 * H - Thickness of plate
 * L - Distance neutron travels before collision
 * d - Direction of neutron (radian)
 * u - Uniform random number
 * x - position of particle in place (0 <= x < H)
 * n - Number of samples
 * a - True while particel still bouncing
 * r,b,t - counts of reflected absorbed, transmitted neutrons
 * 
 * begin
 *  r,b,t = 0;
 *  for(int i = ; i < n;i++){
 *      d = 0;
 *      X = 0;
 *      a = true;
 *      while(a){
 *          L = -(1/C) * ln(u);
 *          x = x + L*cos(d);
 *          if(x<0){
 *              r++;
 *              a =false;
 *          }else if(x >= H){
 *              t++;
 *              a = false;
 *          }else if(u < Cc/C){
 *              b++;
 *              a = false;
 *          }else{
 *              d = u*Math.PI;
 *          }
 *      }
 * }
 * 
 * return r/n,a/nt/n;
 */