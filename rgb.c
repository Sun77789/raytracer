/*
 Malika Aubakirova
 CS 152
 Lab 4
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raytracer.h"

/* === rgb operations === */

rgb *rgb_new(double r, double g, double b)
{

    if (r>1 || r<0 || b>1 || b<0 || g>1 || g<0)
    {
        printf("rgb_new: Value(s) our of bounds\n");
        exit (1);
    }
   rgb* new_rgb = malloc(sizeof(rgb));
   if(new_rgb == NULL) {
     printf("rgb_new: Cannot allocate\n");
     exit (1);
   }
   new_rgb->r = r;
   new_rgb->g = g;
   new_rgb->b = b;
   return new_rgb;
}

rgb *rgb_dup(rgb *c)
{
   rgb* new_rgb = malloc(sizeof(rgb));
   if(new_rgb == NULL) {
     printf("rgb_dup: Cannot allocate\n");
     exit (1);
   }
    
   new_rgb->r = c->r;
   new_rgb->g = c->g;
   new_rgb->b = c->b;
   return new_rgb;
}

/* multiply the components or two rgbs (allocate) */
/* (r,g,b) * (R,G,B) = (rR,gG,bB) */
rgb *rgb_modulate(rgb *c1, rgb *c2)
{
   rgb* new_rgb = malloc(sizeof(rgb));
   if(new_rgb == NULL) {
     printf("rgb_modulate: Cannot allocate\n");
     exit (1);
   }
   new_rgb->r = c1->r*c2->r;
   new_rgb->g = c1->g*c2->g;
   new_rgb->b = c1->b*c2->b;
    //check for bounds
    new_rgb->r = (new_rgb->r>1)? 1: new_rgb->r;
    new_rgb->g = (new_rgb->g>1)? 1: new_rgb->g;
    new_rgb->b = (new_rgb->b>1)? 1: new_rgb->b;
   return new_rgb;
}

/* scale each component by given scalar, but don't allow */
/* any component in the result to fall outside [0,1] (allocate) */
rgb *rgb_scale(double s, rgb *c)
{
   rgb* new_rgb = malloc(sizeof(rgb));
   if(new_rgb == NULL) {
     printf("rgb_scale: Cannot allocate\n");
     exit (1);
   }
    new_rgb->r = (s*c->r>1)? 1: s*c->r;
    new_rgb->g = (s*c->g>1)? 1: s*c->g;
    new_rgb->b = (s*c->b>1)? 1: s*c->b;
    
    new_rgb->r = (new_rgb->r < 0)? 0: new_rgb->r;
    new_rgb->g = (new_rgb->g < 0)? 0: new_rgb->g;
    new_rgb->b = (new_rgb->b < 0)? 0: new_rgb->b;
    
   if (new_rgb->r>1 || new_rgb->r<0 || new_rgb->b>1 || new_rgb->b<0 || new_rgb->g>1 || new_rgb->g<0)
   {
  	printf("rgb_scale: Value(s) our of bounds\n");
  	exit (1);
   }
   return new_rgb;
}

/* add components of colors (allocate) */
/* but don't allow any component in the result to exceed 1 */
rgb *rgb_add(rgb *c1, rgb *c2)
{
   rgb* new_rgb = malloc(sizeof(rgb));
   if(new_rgb == NULL) {
     printf("rgb_add: Cannot allocate\n");
     exit (1);
   }
    new_rgb->r = c1->r+c2->r;
    new_rgb->g = c1->g+c2->g;
    new_rgb->b = c1->b+c2->b;
   return new_rgb;
}

char *rgb_tos(rgb *c)
{
   char buf[128];
   int i;
   for (i=0; i<127; i++)
        buf[i] = '\0';
   sprintf(buf, "rgb(%lf, %lf, %lf)\n", c->r, c->g, c->b);
   return strdup(buf);
}

void rgb_print(rgb *c)
{
   printf("rgb(%lf, %lf, %lf)\n", c->r, c->g, c->b);
   return;
}

void rgb_free(rgb *c)
{
    free(c);
    return;
}

/* print three integer values on [0,255] with spaces in between and a newline */
/* for example, printing the bytes for rgb (1.0,1.0,0.0) should print */
/* "255 255 0\n" */
void rgb_print_bytes(rgb *c)
{
    printf("%d %d %d\n", (int)((c->r)*255), (int)((c->g)*255), (int)((c->b)*255));
    //printf("%lf %lf %lf\n", (c->r)*255, (c->g)*255, (c->b)*255);
    return;
}
