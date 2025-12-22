#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* .Call calls */
// one extern per export; matching arg number/type
extern SEXP c_ylagxCOR(SEXP, SEXP);
extern SEXP c_cow(SEXP, SEXP);

// one per function {"<function-name>", (DL_FUNC) &<function-name>, num_args}
static const R_CallMethodDef CallEntries[] = {
  {"c_ylagxCOR", (DL_FUNC) &c_ylagxCOR, 2},
  {"c_cow", (DL_FUNC) &c_cow, 2},
  {NULL, NULL, 0}
};

void R_init_addr(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
