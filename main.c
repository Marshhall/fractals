// created by Marçal H.B

/*
 compile using
 cc -lm main.c image.c -o programa
 and then
 ./programa
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <complex.h>
#include "image.h"



double complex c_function(double complex z, double complex c);

int main(int argc, char **argv) {
	
	// dimensions of image
	int dim_x = 3072, dim_y = 1920;			/* only even numbers */
	Image *im = createImage(dim_x, dim_y);
	
	// iterations to check for stability
	int f_iterations = 200;
	
	// complex number initialization --- it is changed later!!!
	double complex z = 0;
	double complex c = 0.44;
	
	// range of values in C to check for points
	double re_range = 2, im_range = re_range * dim_y / dim_x;				/* |Re(z)| < re_range --- |Im(z)| < im_range and WE KEEP IMAGE STRAIGHT */

	double z_x_min = - dim_x/2, z_x_max = dim_x/2;
	double z_y_min = - dim_y/2, z_y_max = dim_y/2;
	
	
	double r = 0;					/* R = max(2, |c|) by escape criterion */
	if (2 <= cabs(c)) {
		r = cabs(c);
	}
	else {
		r = 2;
	}
	
	double complex O_prime = dim_x/2 + (dim_y/2)*I;							/* origin O' */

	for (int x = 0; x < dim_x; x++) {
		for (int y = 0; y < dim_y; y++) {
			
			// canviem el sistema de coordenades --> passem d'origen a top left i y creixents cap avall a origen al centre de la imagte i creixement "normal"
			double complex pixel_O = x + y*I;												/* pixel in O */
			double complex new_pixel = (creal(pixel_O) - creal(O_prime)) - (cimag(pixel_O) - cimag(O_prime))*I;						/* pixel in new origin O' */

			z = (2*re_range)*(((double) creal(new_pixel) - z_x_min) / (z_x_max - z_x_min)) + 2*(im_range)*(((double) cimag(new_pixel) - z_y_min) / (z_y_max - z_y_min))*I - (re_range + im_range*I);

			// iterem la funció i comprovem convergència
			for (int j = 1; j <= f_iterations; j++) {
				z = c_function(z, c);
				if (creal(z)*creal(z) + cimag(z)*cimag(z) > r*r) {
					imageSetPixel(im, x, y, 2*j + 1);
					break;
				}
				else {
					imageSetPixel(im, x, y, 255);
				}
			}
		}
	}

	imageSaveAsGif(im, "test.gif", "bu.map");

	return 0;
}

double complex c_function(double complex z, double complex c) {
	return cpow(z, 4) + c;
}


