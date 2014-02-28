//
//  ray.c
//  
//
//  Created by Malika Aubakirova on 2/17/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raytracer.h"

ray *ray_new(vec *origin, vec *direction)
{
    ray* newr = malloc(sizeof(ray));
    if(newr == NULL) {
        printf("ray_new: Cannot allocate\n");
        exit (1);
    }
    newr->origin = vec_dup(origin);
    newr->direction = vec_dup(direction);
    return newr;
}

ray *ray_dup(ray *r)
{
    ray* newr = malloc(sizeof(ray));
    if(newr == NULL) {
        printf("ray_dup: Cannot allocate\n");
        exit (1);
    }
    newr->origin = vec_dup(r->origin);
    newr->direction = vec_dup(r->direction);
    return newr;
}

vec *ray_position(ray *r, double t)
{
    vec *w = vec_scale(t, r->direction);
    vec *result = vec_add(r->origin, w);
    vec_free(w);
    return result;
}

char *ray_tos(ray *r)
{
    char buf[128];
    int i;
    for (i=0; i<127; i++)
        buf[i] = '\0';
    char *or = vec_tos(r->origin);
    char *dir= vec_tos(r->direction);
    sprintf(buf, "Origin: %s\nDirection: %s", or, dir);
    free(or);
    free(dir);
    return strdup(buf);
}

void ray_print(ray *r)
{
    printf("Origin: ");
    vec_print(r->origin);
    printf("Direction: ");
    vec_print(r->direction);
    return;
}

void ray_free(ray *r)
{
    vec_free(r->direction);
    vec_free(r->origin);
    free(r);
    return;
}
