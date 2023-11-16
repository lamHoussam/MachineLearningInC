#include <stdio.h>
#include <stdlib.h>

#include "Models/Regression.h"

int main(int argc, char const *argv[])
{
    const char *filename = (argc > 1 ? argv[1] : "test.txt");


    tUnivariateRegression reg;
    uniregression_load_data_from_file(filename, &reg);

    uniregression_print_train_data(reg);

    return 0;
}
