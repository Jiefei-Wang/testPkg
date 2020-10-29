#include <memory>
#include <cstring>
#include "Rinternals.h"
#include "R_ext/Altrep.h"

R_altrep_class_t altrep_real_class;

SEXP make_real_altrep(size_t n);
/*
==========================================
utilities
==========================================
*/
static void realPtrFinalizer(SEXP extPtr){
    double* ptr = (double*)R_ExternalPtrAddr(extPtr);
    delete ptr;
}
/*
==========================================
ALTREP operations
==========================================
*/
Rboolean altrep_Inspect(SEXP x, int pre, int deep, int pvec,
                        void (*inspect_subtree)(SEXP, int, int, int))
{
    return TRUE;
}

R_xlen_t altrep_length(SEXP x)
{
    return asReal(R_altrep_data2(x));
}

void *altrep_dataptr(SEXP x, Rboolean writeable)
{
    return R_ExternalPtrAddr(R_altrep_data1(x));
}

const void *altrep_dataptr_or_null(SEXP x)
{
    return altrep_dataptr(x, TRUE);
}

SEXP altrep_duplicate(SEXP x, Rboolean deep)
{
    SEXP x_new = PROTECT(make_real_altrep(XLENGTH(x)));
    memcpy(DATAPTR(x_new), DATAPTR(x), XLENGTH(x)*sizeof(double));
    UNPROTECT(1);
    return x_new;
}

SEXP altrep_serialized_state(SEXP x)
{
    SEXP data = PROTECT(Rf_allocVector(TYPEOF(x), XLENGTH(x)));
    memcpy(DATAPTR(data), DATAPTR(x), XLENGTH(x)*sizeof(double));
    UNPROTECT(1);
    return data;
}

SEXP altrep_unserialize(SEXP R_class, SEXP data)
{
    SEXP x = PROTECT(make_real_altrep(XLENGTH(data)));
    memcpy(DATAPTR(x), DATAPTR(data), XLENGTH(data)*sizeof(double));
    UNPROTECT(1);
    return x;
}

#define ALT_COMMOM_REGISTRATION(ALT_CLASS, ALT_TYPE)                          \
    ALT_CLASS = R_make_##ALT_TYPE##_class(class_name, "testPkg", dll);        \
    /* common ALTREP methods */                                               \
    R_set_altrep_Inspect_method(ALT_CLASS, altrep_Inspect);                   \
    R_set_altrep_Length_method(ALT_CLASS, altrep_length);                     \
    R_set_altrep_Duplicate_method(ALT_CLASS, altrep_duplicate);               \
    R_set_altrep_Unserialize_method(ALT_CLASS, altrep_unserialize);           \
    R_set_altrep_Serialized_state_method(ALT_CLASS, altrep_serialized_state); \
    /* ALTVEC methods */                                                      \
    R_set_altvec_Dataptr_method(ALT_CLASS, altrep_dataptr);                   \
    R_set_altvec_Dataptr_or_null_method(ALT_CLASS, altrep_dataptr_or_null);


//[[Rcpp::init]]
void ini_altrep_real_class(DllInfo *dll)
{
    char class_name[] = "real_altrep";
    ALT_COMMOM_REGISTRATION(altrep_real_class, altreal);
}

// [[Rcpp::export]]
SEXP make_real_altrep(size_t n)
{
    double *ptr = new double[n];
    memset(ptr, 0, n*sizeof(double));
    SEXP extptr = PROTECT(R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));
    SEXP length = PROTECT(ScalarReal(n));
    R_RegisterCFinalizerEx(extptr, realPtrFinalizer, TRUE);
    SEXP x = PROTECT(R_new_altrep(altrep_real_class, extptr, length));
    UNPROTECT(3);
    return x;
}
