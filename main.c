#include <stdio.h>
#include <stdlib.h>

#include "Models/Regression.h"
#include "../CMaths/MLMaths.h"


int main(int argc, char const *argv[])
{
    const char *filename = (argc > 1 ? argv[1] : "test.txt");

    tUnivariateRegression reg;
    uniregression_load_data_from_file(filename, &reg);

    uniregression_print_train_data(reg);

    uniregression_train_on_loaded_data(&reg);

    // uniregression_print_train_data(reg);

    float y = uniregression_predict(&reg, 12);
    printf("Predicted for %d: %f\n", 12, y);

    return 0;
}
