#include <stdio.h>
#include <math.h>

/* 
 * Implements quadratic Bspline a la Anders Peterson
 * Basis function have local support with width = 3*dtknot, 
 * where dtknot = T/(nsplines -2) is the time knot vector spacing.
 */
class Bspline{
    int nsplines;     // number of splines basis functions

    double dtknot;    // spacing of time knot vector    
    double width;     // support of each spline basis function (d*dtknot)
    double *tcenter;  // vector of basis function center positions
    double* coeff;    // spline coefficients

    public:
        /* Constructor */
        Bspline(int NSplines, double T);

        /* Destructor */
        ~Bspline();

        /* Evaluate the spline at time t */
        double evaluate(double t);

        /* 
         * Copy the values of alpha into the splines coefficients 
         * alpha must have the size nsplines! 
         */
        void setCoeff(double* alpha);
};