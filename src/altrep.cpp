#include <Rcpp.h>
#include "R_ext/Altrep.h"

R_altrep_class_t altrep_integer_class;
R_altrep_class_t altrep_real_class;

//Defined in the end of the file
SEXP make_altrep(int type, size_t n);

/*
==========================================
ALTREP operations
==========================================
*/
Rboolean altrep_Inspect(SEXP x, int pre, int deep, int pvec,
                        void (*inspect_subtree)(SEXP, int, int, int))
{
    Rprintf("I am altrep\n");
    return TRUE;
}
R_xlen_t altrep_length(SEXP x)
{
    return Rcpp::as<R_xlen_t>(R_altrep_data2(x));
}

void *altrep_dataptr(SEXP x, Rboolean writeable)
{
    return R_ExternalPtrAddr(R_altrep_data1(x));
}

const void *altrep_dataptr_or_null(SEXP x)
{
    return R_ExternalPtrAddr(R_altrep_data1(x));
}
SEXP altrep_duplicate(SEXP x, Rboolean deep)
{
    Rprintf("Duplicating object\n");
    return make_altrep(TYPEOF(x),XLENGTH(x));
}
SEXP altrep_coerce(SEXP x, int type)
{
    Rprintf("Coercing object\n");
    return make_altrep(type,XLENGTH(x));
}

#define ALT_COMMOM_REGISTRATION(ALT_CLASS, ALT_TYPE)         \
    ALT_CLASS = R_make_##ALT_TYPE##_class(class_name, "testPkg", dll); \
    /* common ALTREP methods */                                           \
    R_set_altrep_Inspect_method(ALT_CLASS, altrep_Inspect);               \
    R_set_altrep_Length_method(ALT_CLASS, altrep_length);                 \
    R_set_altrep_Duplicate_method(ALT_CLASS, altrep_duplicate);           \
    R_set_altrep_Coerce_method(ALT_CLASS, altrep_coerce);                 \
    /* ALTVEC methods */                                                  \
    R_set_altvec_Dataptr_method(ALT_CLASS, altrep_dataptr);               \
    R_set_altvec_Dataptr_or_null_method(ALT_CLASS, altrep_dataptr_or_null);

//[[Rcpp::init]]
void init_altrep_integer_class(DllInfo *dll)
{
    char class_name[] = "integer_altrep";
    ALT_COMMOM_REGISTRATION(altrep_integer_class, altinteger);
}

//[[Rcpp::init]]
void ini_altrep_real_class(DllInfo *dll)
{
    char class_name[] = "real_altrep";
    ALT_COMMOM_REGISTRATION(altrep_real_class, altreal);
}

// [[Rcpp::export]]
SEXP make_real_altrep(size_t n){
    double* ptr = new double[n];
    SEXP extptr = Rf_protect(R_MakeExternalPtr(ptr, R_NilValue,R_NilValue));
    SEXP x = R_new_altrep(altrep_real_class, extptr, Rcpp::wrap(n));
    UNPROTECT(1);
    return x;
}

// [[Rcpp::export]]
SEXP make_integer_altrep(size_t n){
    int* ptr = new int[n];
    SEXP extptr = Rf_protect(R_MakeExternalPtr(ptr, R_NilValue,R_NilValue));
    SEXP x = R_new_altrep(altrep_integer_class, extptr, Rcpp::wrap(n));
    UNPROTECT(1);
    return x;
}

SEXP make_altrep(int type, size_t n){
    switch (type)
    {
    case INTSXP:
        return make_integer_altrep(n);
        break;
    case REALSXP:
        return make_real_altrep(n);
    default:
        Rf_error("unknow type");
    }
    return R_NilValue;
}
