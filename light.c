//
//  light.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raytracer.h"

light *light_new(vec *direction, rgb *color)
{
    light* newl = malloc(sizeof(light));
    if(newl == NULL) {
        printf("light_new: Cannot allocate\n");
        exit (1);
    }
    newl->direction = vec_dup(direction);
    newl->color = rgb_dup(color);
    return newl;
}

light *light_dup(light *l)
{
    light* newl = malloc(sizeof(light));
    if(newl == NULL) {
        printf("light_new: Cannot allocate\n");
        exit (1);
    }
    newl->direction = vec_dup(l->direction);
    newl->color = rgb_dup(l->color);
    return newl;
}

void light_print(light *l)
{
    printf("Light's direction: \n");
    vec_print(l->direction);
    printf("Light's color: \n");
    rgb_print(l->color);
    return;
}

void light_free(light *l)
{
    vec_free(l->direction);
    rgb_free(l->color);
    free(l);
    return;
}
