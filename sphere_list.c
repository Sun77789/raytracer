//
//  sphere_list.c
//  
//
//  Created by Malika Aubakirova on 2/18/14.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "raytracer.h"
#include <string.h>

sphere_list *sl_cons(sphere *s, sphere_list *ss)
{
    sphere_list *newsl = malloc(sizeof(sphere_list));
    if(newsl == NULL) {
        printf("sl_cons: Cannot allocate\n");
        exit (1);
    }
    newsl->s = sphere_dup(s);
    newsl->next = ss;
    return newsl;
}

sphere_list *sl_singleton(sphere *s)
{
    sphere_list *newsl = malloc(sizeof(sphere_list));
    if(newsl == NULL) {
        printf("sl_singleton: Cannot allocate\n");
        exit (1);
    }
    newsl->s = sphere_dup(s);
    newsl->next = NULL;
    return newsl;
}

void sl_print(sphere_list *ss)
{
    while (ss != NULL) {
        sphere_print(ss->s);
        printf("\n");
        ss= ss->next;
    }
    return;
}

void sl_free(sphere_list *ss)
{
    while (ss != NULL) {
        sphere_list *head = ss;
        ss = ss->next;
        sphere_free(head->s);
        free(head);
    }
    free(ss);
    return;
}
