//
//  camera.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdio.h>
#include "raytracer.h"
#include <stdlib.h>

camera *camera_new(vec *loc, unsigned int h, unsigned int w)
{
    camera* newc = malloc(sizeof(camera));
    if(newc == NULL) {
        printf("camera_new: Cannot allocate\n");
        exit (1);
    }
    newc->loc = vec_dup(loc);
    newc->h = h;
    newc->w = w;
    return newc;
}

camera *camera_dup(camera *c)
{
    camera* newc = malloc(sizeof(camera));
    if(newc == NULL) {
        printf("camera_new: Cannot allocate\n");
        exit (1);
    }
    newc->loc = vec_dup(c->loc);
    newc->h = c->h;
    newc->w = c->w;
    return newc;
}

void camera_print(camera *c)
{
    printf("\n\tCamera\n");
    printf("Location:\n");
    vec_print(c->loc);
    printf("Size w=%u h=%u:\n", c->w, c->h);
    return;
}

void camera_free(camera *c)
{
    vec_free(c->loc);
    free(c);
    return;
}
