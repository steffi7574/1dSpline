#include "bspline.hpp"

Bspline::Bspline(int NSplines, double T){
    nsplines = NSplines;

    dtknot = T / (double)(nsplines - 2);
	width = 3.0*dtknot;

    /* Compute center points of the splines */
    tcenter = new double[nsplines];
    for (int i = 0; i < nsplines; i++){
        tcenter[i] = dtknot * ( (i+1) - 1.5 );
    }

    /* Initialize spline coefficients */
    coeff = new double[nsplines];
    for (int i = 0; i < nsplines; i++){
      coeff[i] = 0;   
    }
}

Bspline::~Bspline(){

    delete [] coeff;
    delete [] tcenter;
}



double Bspline::evaluate(double t){

    double val = 0.0;
    double tau;

    /* Find k such that t \in [t_k, t_k+1) */
    int k = floor(t / dtknot) + 1;
    if (k <= 0 || k >= nsplines) {  // sanity check
        printf("\n ERROR: Can't find interval for spline evaluation!\n\n");
        exit(0);
    }

    /* 3rd segment of basis function k */
    tau = (t - tcenter[k-1]) / width;
    val += coeff[k-1] * (9./8. - 4.5*tau + 4.5 * pow(tau,2));

    /* 2nd segment of basis function k+1 */
    tau = (t - tcenter[k]) / width;
    val += coeff[k] * (0.75 - 9. * pow(tau,2));

    /* 1st segment of basis function k+2 */
    if (k < nsplines - 1)
    {
        tau = (t - tcenter[k+1]) / width;
        val += coeff[k+1] * (9./8. + 4.5*tau + 4.5 * pow(tau,2));
    }

    return val;
}



void Bspline::setCoeff(double* alpha){

    for (int i=0; i<nsplines; i++){
        coeff[i] = alpha[i];
    }
}