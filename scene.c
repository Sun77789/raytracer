//
//  scene.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdio.h>
#include "raytracer.h"
#include <stdlib.h>


scene *scene_new(rgb *bg, sphere_list *ss, light *light, rgb *amb)
{
    scene *news = malloc(sizeof(scene));
    if(news == NULL) {
        printf("scene_new: Cannot allocate\n");
        exit (1);
    }
    news->bg = rgb_dup(bg);
    
    sphere_list *sl = NULL;
    while (ss != NULL) {
        sl = sl_cons(ss->s, sl);
        ss= ss->next;
    }
    news->spheres = sl;
    news->light = light_dup(light);
    news->amb = rgb_dup(amb);
    return news;
}

void scene_print(scene *s)
{
    printf("\n\tScene\n");
    printf("Background color:\n");
    rgb_print(s->bg);
    sl_print(s->spheres);
    light_print(s->light);
    rgb_print(s->amb);
}

void scene_free(scene *s)
{
    rgb_free(s->bg);
    sl_free(s->spheres);
    light_free(s->light);
    rgb_free(s->amb);
    free(s);
    return;
}
