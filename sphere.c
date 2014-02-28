//
//  sphere.c
//  
//
//  Created by Malika Aubakirova on 2/17/14.
//
//

#include <stdio.h>
#include "raytracer.h"
#include <stdlib.h>

sphere *sphere_new(vec *center, double radius, rgb *color)
{
    sphere* news = malloc(sizeof(sphere));
    if(news == NULL) {
        printf("shpere_new: Cannot allocate\n");
        exit (1);
    }
    news->center = vec_dup(center);
    news->radius = radius;
    news->color = rgb_dup(color);
    return news;
}

sphere *sphere_dup(sphere *s)
{
    sphere* news = malloc(sizeof(sphere));
    if(news == NULL) {
        printf("shpere_dup: Cannot allocate\n");
        exit (1);
    }
    news->center = vec_dup(s->center);
    news->radius = s->radius;
    news->color = rgb_dup(s->color);
    return news;
}

char *sphere_tos(sphere *s)
{
    char buf[128];
    int i;
    for (i=0; i<127; i++)
        buf[i] = '\0';
    char *cen = vec_tos(s->center);
    char *col= rgb_tos(s->color);
    sprintf(buf, "Center: %s\nRadius: %lf\nColor: %s",
            cen, s->radius, col);
    free(cen);
    free(col);
    return strdup(buf);
}

void sphere_print(sphere *s)
{
    printf("Center: ");
    vec_print(s->center);
    printf("Radius: %.2lf\n", s->radius);
    printf("Color: ");
    rgb_print(s->color);
    return;
}

void sphere_free(sphere *s)
{
    vec_free(s->center);
    rgb_free(s->color);
    free(s);
    return;
}
