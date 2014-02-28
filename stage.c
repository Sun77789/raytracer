//
//  stage.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdio.h>
#include "raytracer.h"
#include <stdlib.h>

stage *stage_new(camera *c, scene *s)
{
    stage *news = malloc(sizeof(stage));
    if(news == NULL) {
        printf("stage_new: Cannot allocate\n");
        exit (1);
    }
    news->c = camera_dup(c);
    news->s = s;
    return news;
}

stage *stage_dup(stage *st)
{
    stage *news = malloc(sizeof(stage));
    if(news == NULL) {
        printf("stage_dup: Cannot allocate\n");
        exit (1);
    }
    news->c = camera_dup(st->c);
    news->s = st->s;
    return news;
}

void stage_print(stage *s)
{
    printf("\n\n\tStage\n");
    camera_print(s->c);
    scene_print(s->s);
    return;
}

void stage_free(stage *st)
{
    camera_free(st->c);
    scene_free(st->s);
    free(st);
    return;
}
