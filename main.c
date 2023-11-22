#include <stdio.h>
#include <stdlib.h>

#include "Models/Regression.h"
#include "Models/NeuralNetwork.h"
#include "../CMaths/MLMaths.h"
#include "../CGraph/Graph.h"

void test_regression(const char *filename) {
    tUnivariateRegression reg;
    uniregression_load_data_from_file(filename, &reg);

    uniregression_print_train_data(reg);

    uniregression_train_on_loaded_data(&reg);

    // uniregression_print_train_data(reg);

    float y = uniregression_predict(&reg, 12);
    printf("Predicted for %d: %f\n", 12, y);

   
}

void test_nn() {
    uint32_t layers_sizes[3] = { 4, 3, 8 };
    tNeuralNetwork* nn = nn_create(3, layers_sizes);
    nn_print(nn);
    nn_destroy(nn);
}

int main(int argc, char const *argv[])
{
    const char *filename = (argc > 1 ? argv[1] : "test.txt");
    // test_regression(filename);
    test_nn();

    return 0;
}
