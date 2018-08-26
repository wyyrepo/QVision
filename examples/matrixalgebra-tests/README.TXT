This directory contains a number of subdirectories with test programs for all the functions available in the matrix algebra module of the QVision library. Each one contains a program which can be used both to test correctness of a decomposition / matrix equation solving method, and to measure its performance. 

Each program has many options available, which allow to vary among the several methods available for each decomposition / solving problem, change the coefficient matrix size, or the number of tests to measure execution time, among other options. Execute "XXX-test --help" to see help on how to use each of them.

Of course, the source of the tests programs can also be used as an exhaustive set of examples of use of the matrix algebra module of QVision.

Also, each directory contains two bash scripts (script-test-all and script-measure-all), which are in principle designed to test validity of the methods (by computing adequate residuals of the decomposition / solving methods, in different conditions) and execute performance measures, respectively, but they can also be used as templates to execute other user defined tests (where the several relevant parameters can be changed at will).

Finally, each subdirectory also contains a measure directory, where you can find the results of a set of performance tests executed on a Quad Q6600 2.4Ghz (using only one core), for several underlying algebra packages (GSL, standard LAPACK, base ATLAS, SSE ATLAS, SSE2 ATLAS, and Intel MKL).