
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
#> @0x00000000139df0f8 13 INTSXP g0c0 [REF(3)] I am altrep
x1 <- x
x1[1] <- 1.0 
#> Duplicating object
#> Coercing object
.Internal(inspect(x1))
#> @0x0000000013940d08 14 REALSXP g0c0 [REF(1)] I am altrep

## No duplicate and coerce
x <- make_integer_altrep(1024)
.Internal(inspect(x))
#> @0x0000000012335658 13 INTSXP g0c0 [REF(3)] I am altrep
x1 <- x
x1[1] <- 1.0 
.Internal(inspect(x1))
#> @0x000000001d6e94d8 14 REALSXP g0c7 [REF(1)] (len=1024, tl=0) 1,0,2,0,3.99433e+08,...
```

# Session Info

``` r
sessionInfo()
#> R Under development (unstable) (2020-09-03 r79126)
#> Platform: x86_64-w64-mingw32/x64 (64-bit)
#> Running under: Windows 10 x64 (build 18362)
#> 
#> Matrix products: default
#> 
#> locale:
#> [1] LC_COLLATE=English_United States.1252 
#> [2] LC_CTYPE=English_United States.1252   
#> [3] LC_MONETARY=English_United States.1252
#> [4] LC_NUMERIC=C                          
#> [5] LC_TIME=English_United States.1252    
#> 
#> attached base packages:
#> [1] stats     graphics  grDevices utils     datasets  methods   base     
#> 
#> other attached packages:
#> [1] testPkg_1.0
#> 
#> loaded via a namespace (and not attached):
#>  [1] Rcpp_1.0.5        rstudioapi_0.11   knitr_1.29        magrittr_1.5     
#>  [5] usethis_1.6.1     devtools_2.3.1    pkgload_1.1.0     R6_2.4.1         
#>  [9] rlang_0.4.7       fansi_0.4.1       stringr_1.4.0     tools_4.1.0      
#> [13] pkgbuild_1.1.0    xfun_0.16         sessioninfo_1.1.1 cli_2.0.2        
#> [17] withr_2.2.0       remotes_2.2.0     htmltools_0.5.0   ellipsis_0.3.1   
#> [21] yaml_2.2.1        assertthat_0.2.1  digest_0.6.25     rprojroot_1.3-2  
#> [25] crayon_1.3.4      processx_3.4.4    callr_3.4.3       fs_1.5.0         
#> [29] ps_1.3.4          testthat_2.3.2    memoise_1.1.0     glue_1.4.2       
#> [33] evaluate_0.14     rmarkdown_2.3     stringi_1.4.6     compiler_4.1.0   
#> [37] backports_1.1.9   desc_1.2.0        prettyunits_1.1.1
```
