#include <R.h>
#include <Rmath.h>
#include <Rdefines.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <Rinternals.h>

///////////////////////////////////
// don't think I need all of these
// any more ....
//////////////////////////////////

SEXP c_ylagxCOR(SEXP X, SEXP Y){

// X and Y are pointers need to make these protected c objects...
  //PROTECT(X);
  //PROTECT(Y);

  //if(TYPEOF(X) != REALSXP || TYPEOF(Y) != REALSXP) error("invalid input");
  int lenx = LENGTH(X);
  int leny = LENGTH(Y);
  SEXP ans;
  PROTECT(ans = allocVector(REALSXP, (leny-lenx+1)));
  //double ans[(leny-lenx+1)];
  double *x = REAL(X);
  double *y = REAL(Y);

  //y0 = allocVector(REALSXP, (leny));
  //double y0 = asReal(lenx);
  double y0[leny];

  double *ans2 = REAL(ans);
  for(int i = 0; i < (leny-lenx+1); ++i) {
    //this does not seem to be slowing it down much...
    for(int k = 0; k < lenx; ++k){
      y0[k] = y[k + i];
    }
    double sumx = 0;
    double sumy = 0;
    double sumxy = 0;
    double sumx2 = 0;
    double sumy2 = 0;
    int n = 0;
    //above might be better as other data types


    for(int j = 0; j < lenx; ++j) {
      // the two if loops that follow appear to be adding
      // about 30% to time...
      /////////////////////////////////////////
      // this this works...
      // NB: for SEXP X : !ISNA(REAL(X)[j])
      if (!ISNA(x[j]) && !ISNA(y0[j])) {
        n += 1;
        sumx += x[j];
        sumx2 += (x[j]*x[j]);
        sumy += y0[j];
        sumy2 += (y0[j]*y0[j]);
        sumxy += (x[j]*y0[j]);
      }
      ////////////////////////////////////////
    }
    if (n>0) {
      //ans2[i] =  5;
      ans2[i] = (sumxy - ((sumx * sumy)/n)) / sqrt((sumx2-((sumx*sumx)/n))*(sumy2-((sumy*sumy)/n)));
    }
  }
  UNPROTECT(1);
  return ans;
}

//from is_true(any(is_na(x)))
// assume is_false(is_na(x)) says is this single value not missing
// doesn't seem to....
// ended up with !NumericVector::is_na(x) as single value not missing
// noNA() might work?

//if
//if (testExpression) {
// statement(s) inside the body of if
// }
// else {
//  // statement(s) inside the body of else
//}


// this this should generate 1,1,1
// /*** R
// C_ylagxCOR(1:10, 1:12)
// */


/// at the moment this works
/// .Call("c_ylagxCOR", as.numeric(1:10), as.numeric(1:12))
/// currently needs to be numeric... REAL() trips on integers...
