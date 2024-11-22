#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"

#define TRSH 2.0
#define ITER 1024ull

#define SIZEX 1500
#define SIZEY 1500

// Convertit la coordonnée X en une coordonnée du plan complexe
double cx(int x)
{
    static const double qx = 3.0 / (double)SIZEX; // Facteur de mise à l'échelle
    return -2.0 + x * qx;
}

// Convertit la coordonnée Y en une coordonnée du plan complexe
double cy(int y)
{
    static const double qy = 2.0 / (double)SIZEY; // Facteur de mise à l'échelle
    return -1.0 + y * qy;
}

int main(void)
{
    struct ppm_image im;
    ppm_image_init(&im, SIZEX, SIZEY);

    double colref = 255.0 / log(ITER); // Facteur de conversion pour les couleurs

    for (int i = 0; i < SIZEX; ++i) {
        for (int j = 0; j < SIZEY; ++j) {

            unsigned long int iter = 0;
            double complex c = cx(i) + cy(j) * I; // Coordonnée complexe
            double complex z = 0;

            // Boucle d'itération pour le calcul de Mandelbrot
            while (iter < ITER) {
                double mod = cabs(z);

                if (TRSH < mod) { // Si le point "s'échappe"
                    break;
                }

                z = z * z + c; // Calcul de la prochaine valeur de z
                iter++;
            }

            // Calcul de la couleur en fonction du nombre d'itérations
            int grey = colref * log(iter);
            ppm_image_setpixel(&im, i, j, grey, grey, grey);
        }
    }

    ppm_image_dump(&im, "m.ppm"); // Sauvegarde de l'image
    ppm_image_release(&im); // Libération de la mémoire

    return 0;
}
