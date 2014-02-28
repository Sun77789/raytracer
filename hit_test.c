//
//  hit_test.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raytracer.h"

hit_test *hit_test_new(double dist, rgb *surf_color, vec *surf_norm)
{
    hit_test *ht = malloc(sizeof(hit_test));
    if(ht == NULL) {
        printf("hit_test_new: Cannot allocate\n");
        exit (1);
    }
    ht->dist = dist;
    ht->surf_color = rgb_dup(surf_color);
    ht->surf_norm = vec_dup(surf_norm);
    return ht;
}

hit_test *hit_test_dup(hit_test *t)
{
    hit_test *ht = malloc(sizeof(hit_test));
    if(ht == NULL) {
        printf("hit_test_dup: Cannot allocate\n");
        exit (1);
    }
    ht->dist = t->dist;
    ht->surf_color = rgb_dup(t->surf_color);
    ht->surf_norm = vec_dup(t->surf_norm);
    return ht;
}

void hit_test_print(hit_test *t)
{
    printf("\n\tHit test\n");
    printf("Distance %lf:\n", t->dist);
    printf("Surface color: \n");
    rgb_print(t->surf_color);
    printf("Surface normal: \n");
    vec_print(t->surf_norm);
}

void hit_test_free(hit_test *t)
{
    rgb_free(t->surf_color);
    vec_free(t->surf_norm);
    free(t);
    return;
}
