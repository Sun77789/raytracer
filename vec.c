
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "raytracer.h"

/* === vector operations === */

vec *vec_new(double x, double y, double z)
{
   vec* newv = malloc(sizeof(vec));
  if(newv == NULL) {
  printf("vec_new: Cannot allocate\n");
  exit (1);
  }
   newv->x = x;
   newv->y = y;
   newv->z = z;
   return newv;
}

/* create a fresh vector (new heap allocation) with same components as argument */
vec *vec_dup(vec *v)
{
  vec* newv = malloc(sizeof(vec));
  if(newv == NULL) {
      printf("vec_dup: Cannot allocate\n");
      exit (1);
  }
   newv->x = v->x;
   newv->y = v->y;
   newv->z = v->z;
   return newv;
}

/* add two vectors (allocate) */
/* (x,y,z) + (X,Y,Z) = (x+X,y+Y,z+Z) */
vec *vec_add(vec *v1, vec *v2)
{
	  vec* newv = malloc(sizeof(vec));
	  if(newv == NULL) {
	      printf("vec_add: Cannot allocate\n");
	      exit (1);
	  }
	  newv->x = v1->x+v2->x;
	  newv->y = v1->y+v2->y;
	  newv->z = v1->z+v2->z;
    return newv;
}

/* subtract the second vector from the first (allocate) */
/* (x,y,z) - (X,Y,Z) = (x-X,y-Y,z-Z) */
vec *vec_sub(vec *v1, vec *v2)
{
    vec* newv = malloc(sizeof(vec));
    if(newv == NULL) {
    printf("vec_sub: Cannot allocate\n");
    exit (1);
    }
    newv->x = v1->x-v2->x;
    newv->y = v1->y-v2->y;
    newv->z = v1->z-v2->z;
    return newv;
}

/* negate a vector (allocate) */
/* -(x,y,z) = (-x,-y,-z) */
vec *vec_neg(vec *v)
{
   vec* newv = malloc(sizeof(vec));
    if(newv == NULL) {
    printf("vec_neg: Cannot allocate\n");
    exit (1);
    }
   newv->x = -v->x;
   newv->y = -v->y;
   newv->z = -v->z;
   return newv;
}

/* scale the components of a vector by scalar s (allocate) */
/* s(x,y,z) = (sx,sy,sz) */
vec *vec_scale(double s, vec *v)
{
   vec* newv = malloc(sizeof(vec));
    if(newv == NULL) {
    printf("vec_scale: Cannot allocate\n");
    exit (1);
    }
   newv->x = s*v->x;
   newv->y = s*v->y;
   newv->z = s*v->z;
   return newv;
}

/* compute the dot product of two vectors */
/* (x,y,z) . (X,Y,Z) = xX+yY+zZ */
double vec_dot(vec *v1, vec *v2)
{
    return (v1->x*v2->x+v1->y*v2->y+v1->z*v2->z);
}


/* compute the magnitude of a vector */
/* the magnitude is the square root of the sum of the squares of the components */
double vec_mag(vec *v)
{
  return sqrt(v->x*v->x+v->y*v->y+v->z*v->z);
}

/* normalize the vector (allocate) */
/* to normalize a vector is to produce a vector pointing in the same direction whose magnitude is 1 */
/* - normalize a vector by scaling by 1 over its magnitude */
/* - if a vector's magnitude is zero, it can't be normalized; simply return it */
vec *vec_norm(vec *v)
{
   double mag = fabs(vec_mag(v));
   if (mag==0)
       return v;
    
      vec* newv = malloc(sizeof(vec));
      if(newv == NULL) {
      printf("vec_norm: Cannot allocate\n");
      exit (1);
      }
   newv->x = v->x/mag;
   newv->y = v->y/mag;
   newv->z = v->z/mag;
   return newv;
}

/* produce a string representation of a vector */
char *vec_tos(vec *v)
{
   char buf[128];  
   int i;
   for (i=0; i<127; i++)
        buf[i] = '\0';
   sprintf(buf, "<%.2lf, %.2lf, %.2lf>", v->x, v->y, v->z);
   return strdup(buf);
}
   

/* print the string representation of a vector */
void vec_print(vec *v)
{
    printf("<%lf, %lf, %lf>\n", v->x, v->y, v->z);
    return;
}

void vec_free(vec *v)
{
  free(v);
  return;
}
