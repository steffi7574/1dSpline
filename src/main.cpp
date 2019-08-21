#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bspline.hpp"

int main(int argc,char **argv)
{
  double tstop;
  int    nspline;
  int    ntime;
  double dt;
  double time;
  double f;

  /* Define default input */
	tstop   = 120.0;
  ntime   = 2400;
  nspline = 10;

  /* Parse command line */
  int arg_index = 1;
  while (arg_index < argc)
  {
     if ( strcmp(argv[arg_index], "-help") == 0 )
     {
        printf("Toolbox for Bspline implementation. \n\n");
        printf("  -ntime <int>     : set num time points (default: 2400)\n");
        printf("  -tstop <double>  : set final time (default: 120)\n");
        printf("  -nspline <int>   : set number of splines (default: 10)\n");
        exit(1);
     }
     else if ( strcmp(argv[arg_index], "-ntime") == 0 )
     {
        arg_index++;
        ntime = atoi(argv[arg_index++]);
     }
     else if ( strcmp(argv[arg_index], "-tstop") == 0 )
     {
        arg_index++;
        tstop = atof(argv[arg_index++]);
     }
     else if ( strcmp(argv[arg_index], "-nspline") == 0 )
     {
        arg_index++;
        nspline = atoi(argv[arg_index++]);
     }
     else
     {
       arg_index++;
     }
  }

  /* Set time horizon */
  dt = tstop / ntime;
	printf("Time: [0.0,%f]\n", tstop);
	printf("ntime = %d\n", ntime);
	printf("dt = %f\n", dt);
      
  /* Create spline */
  Bspline* myspline = new Bspline(nspline, tstop);

  /* Create coefficients and pass them to the spline */
  double* mycoeff = new double[nspline];
  for (int i = 0; i < nspline; i++){
    mycoeff[i] = pow(-1., i+1);     // alternates 1 and -1
  }
  myspline->setCoeff(mycoeff);

  FILE* splinefile;
  splinefile = fopen("spline.out", "w");

  /* Evaluate spline at regular spaced time-grid in [0,tstop] */
  time = 0.0;
  for (int i=0; i< ntime; i++){

    f = myspline->evaluate(time);
    fprintf(splinefile, "%f  %f\n", time, f);

    time += dt;
  }

  
  /* Cleanup */
  delete myspline;
  fclose(splinefile);


  return 0;
}


