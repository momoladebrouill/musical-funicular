struct Vecteur {
    double x;
    double y;
    double z;
};
typedef struct Vecteur vecteur;

struct Aabb {
    vecteur v_min;
    vecteur v_max;
};
typedef struct Aabb aabb;

vecteur vecteur_cree(double x, double y, double z)
vecteur vecteur_nul();
double vecteur_norme(vecteur v);
vecteur vecteur_ajoute(vecteur v1, vecteur v2);

aabb aabb_create(vecteur v_min, vecteur v_max);
aabb aabb_union(aabb b1, aabb b2);

