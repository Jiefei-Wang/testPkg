
<!-- README.md is generated from README.Rmd. Please edit that file -->

# testPkg

For reproduce the problem, run code:

    devtools::load_all()
    
    ## Duplicate and coerce
    x <- make_integer_altrep(10)
    .Internal(inspect(x))
    x1 <- x
    x1[1] <- 1.0 
    .Internal(inspect(x1))
    
    ## No duplicate and coerce
    x <- make_integer_altrep(1024)
    .Internal(inspect(x))
    x1 <- x
    x1[1] <- 1.0 
    .Internal(inspect(x1))

Results:

``` r
devtools::load_all()
#> Loading testPkg

## Duplicate and coerce
x <- make_integer_altrep(10)
.Internal(inspect(x))
#> @0x0000000013006528 13 INTSXP g0c0 [REF(3)] I am altrep
x1 <- x
x1[1] <- 1.0 
#> Duplicating object
#> Coercing object
.Internal(inspect(x1))
#> @0x00000000138e0c10 14 REALSXP g0c0 [REF(1)] I am altrep

## No duplicate and coerce
x <- make_integer_altrep(1024)
.Internal(inspect(x))
#> @0x00000000123e9930 13 INTSXP g0c0 [REF(3)] I am altrep
x1 <- x
x1[1] <- 1.0 
.Internal(inspect(x1))
#> @0x000000001ccdc9f8 14 REALSXP g0c7 [REF(1)] (len=1024, tl=0) 1,0,2,0,4.00596e+08,...
```
