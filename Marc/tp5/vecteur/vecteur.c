#include "vecteur.h"
#include "math.h"

#include <stdio.h>

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

vecteur vecteur_cree(double x, double y, double z){
    vecteur p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

vecteur vecteur_nul(void){
    return vecteur_cree(.0,.0,.0);
}

vecteur vecteur_norme(vecteur v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

vecteur vecteur_ajoute(vecteur v1, vecteur v2){
    vecteur p;
    p.x=v1.x+v2.x;
    p.y=v1.y+v2.y;
    p.z=v1.z+v2.z;
    return p;
}

aabb aabb_create(vecteur v_min, vecteur v_max){
    aabb p;
    p.v_min=v_min;
    p.v_max=v_max;
    return p;
}

aabb aabb_union(aabb b1, aabb b2)
{
    aabb p;
    p.v_min.x=max(b1.v_min.x,b2.v_min.x);
    p.v_min.y=max(b1.v_min.y,b2.v_min.y);
    p.v_min.z=max(b1.v_min.z,b2.v_min.z);

    p.v_max.x=min(b1.v_max.x,b2.v_max.x);
    p.v_max.y=min(b1.v_max.y,b2.v_max.y);
    p.v_max.z=min(b1.v_max.z,b2.v_max.z);
    return p;
}
