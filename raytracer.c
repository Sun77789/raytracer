//
//  raytracer.c
//  Created by Malika Aubakirova on 2/16/14.
//  Project 1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raytracer.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

int main()
{
    /*
    // FIRST SET-UP
    //
    //camera
    camera c;
    c.loc = vec_new(0, 0, -5);
    c.h= 180;
    c.w= 180;
    //sphere
    vec *sph_center = vec_new(0,0,3);
    rgb *sph_color = rgb_new(0.8, 0.8, 0.8);
    sphere *s = sphere_new(sph_center, 1, sph_color);
    // light
    vec *l_direction = vec_new(-1,1,-1);
    rgb *l_color = rgb_new(1,1,1);
    light *l = light_new(l_direction, l_color);
    //scene
    rgb *bg = rgb_new(0.3, 0.6, 1.0);
    sphere_list *sl = sl_singleton(s);
    rgb *amb = rgb_new(0.2, 0.2, 0.2);
    scene *sc= scene_new(bg, sl, l, amb);
    // stage
    stage *stage1 = stage_new(&c, sc);
    render(stage1);
    //free
    vec_free(sph_center);
    rgb_free(sph_color);
    sphere_free(s);
    vec_free(l_direction);
    rgb_free(l_color);
    rgb_free(bg);
    sl_free(sl);
    rgb_free(amb);
    scene_free(sc);
    */
    
    
    // SECOND SET-UP
    //
    
    //camera
    camera c;
    c.loc = vec_new(0, 0, -5);
    c.h= 300;
    c.w= 300;
    
    //sphere
    vec *sph_center1 = vec_new(0,1,3);
    rgb *sph_color1 = rgb_new(1,0,0);
    sphere *s1 = sphere_new(sph_center1, 0.3, sph_color1);
    vec *sph_center2 = vec_new(0,-0.5,3.5);
    rgb *sph_color2 = rgb_new (0.3,0.6,1.0);
    sphere *s2 = sphere_new(sph_center2, 0.9, sph_color2);
    
    // light
    vec *l_direction = vec_new(0,1,0);
    rgb *l_color = rgb_new(1,1,1);
    light *l = light_new(l_direction, l_color);
    
    //scene
    rgb *bg = rgb_new(0.8, 0.8, 0.8);
    sphere_list *sl = sl_singleton(s1);
    sl = sl_cons(s2, sl);
    rgb *amb = rgb_new(0.2, 0.2, 0.2);
    scene *sc= scene_new(bg, sl, l, amb);
    
    // stage
    stage *stage1 = stage_new(&c, sc);
    render(stage1);
    
    //free
    vec_free(sph_center1);
    rgb_free(sph_color1);
    vec_free(sph_center2);
    rgb_free(sph_color2);
    sphere_free(s1);
    sphere_free(s2);
    vec_free(l_direction);
    rgb_free(l_color);
    rgb_free(bg);
    sl_free(sl);
    rgb_free(amb);
    scene_free(sc);
    
    return 0;
}


vec *logical_loc(camera *c, vec *pos)
{
    unsigned int h = c->h;
    unsigned int w = c->w;
    unsigned int a = (h>w)? h: w;
    vec *log = malloc(sizeof(vec));
    
    if (log == NULL) {
        printf("Could not allocate\n");
        exit (1);
    }
    
    if (w>h) {
        log->x = -1+(double)2/a*pos->x;
        log->y = 1-(double)((w-h)/2+pos->y)*2/a;
    }
    else {
        log->x = -1+(double)((h-w)/2+pos->x)*2/a;
        log->y = 1-(double)2/a*pos->y;
    }
    log->z = pos->z;
    
    return log;
}

hit_test *intersect(ray *r, sphere *s)
{
    double sr = s->radius;
    vec *A = vec_sub(r->origin, s->center);
    double B = vec_dot(A, r->direction);
    double C = vec_dot(A, A) - (sr * sr);
    double D = (B * B) - C;
    double t = (-B - sqrt(D));
    
    if (D>0 && t>0) {
        vec *pos = ray_position(r, t);
        vec *sub = vec_sub(pos, s->center);
        vec *norm = vec_norm(sub);
        hit_test *ht = hit_test_new(t, s->color, norm);
        vec_free(pos);
        vec_free(A);
        vec_free(norm);
        return ht;
    }
    
    free(A);
    return NULL;
}

int shadow(vec *v, light *l, sphere_list *ss)
{
    vec *norm_dir = vec_norm(l->direction);
    vec *nudge = vec_scale(0.0001, norm_dir);
    vec *lifted = vec_add(v, nudge);
    //this is a shadow ray
    ray *r = ray_new(lifted, norm_dir);
    
    //free immediately
    // since not needed anymore
    vec_free(nudge);
    vec_free(lifted);
    vec_free(norm_dir);
    while (ss != NULL) {
        hit_test *ht = intersect(r, ss->s);
        if (ht != NULL) {
            free(r);
            free(ht);
            return 1;
        }
        free(ht);
        ss = ss->next;
    }
    
    free(r);
    return 0;
}


rgb *lighting(scene *s, ray *r, hit_test *h)
{
    vec *pos = ray_position(r, h->dist);
    
    if (shadow(pos, s->light, s->spheres)) {
        return rgb_modulate(h->surf_color, s->amb);
    }
    else {
        vec *normal = h->surf_norm;
        vec *l_dir = vec_norm(s->light->direction);
        rgb *l_color = s->light->color;
        rgb *diff = rgb_scale(max(0,vec_dot(normal,l_dir)),l_color);
        rgb *add= rgb_add(s->amb, diff);
        rgb *modulate = rgb_modulate(h->surf_color, add);
        
        //free
        vec_free(l_dir);
        rgb_free(diff);
        rgb_free(add);
        return modulate;
    }
}


rgb *trace_ray(scene *s, ray *r)
{
    sphere_list *ls = s->spheres;
    
    while (ls != NULL) {
    hit_test *ht = intersect(r, ls->s);
        if (ht != NULL) {
            return lighting(s, r, ht);
        }
        ls =ls->next;
    }
    
    return s->bg;
}

void render(stage *g)
{
    vec *origin = g->c->loc;
    int i, j;
    unsigned int h = g->c->h;
    unsigned int w = g->c->w;
    
    printf("P3\n");
    printf("%d %d\n", w, h);
    printf("255\n");
    
    for(i=0; i<h; i++) {
        for(j=0; j<w; j++) {
            vec *pos = vec_new(j+0.5, i+0.5, 0);
            vec *loc = logical_loc(g->c, pos);
            vec *tmp_direction = vec_sub(loc, origin);
            vec *direction = vec_norm(tmp_direction);
            ray *r = ray_new(origin, direction);
            rgb *color = trace_ray(g->s, r);
            
            //print
            rgb_print_bytes(color);
            
            //free
            ray_free(r);
            vec_free(pos);
            vec_free(loc);
            vec_free(tmp_direction);
            vec_free(direction);
        }
    }
    return;
}
