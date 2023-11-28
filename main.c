#include <stdio.h>
#include <stdlib.h>

#include "Models/Regression.h"
#include "Models/NeuralNetwork.h"
#include "../CMaths/MLMaths.h"
#include "../CGraph/Graph.h"

#include "Models/NNVisualiser.h"
#include "../SEngine/App.h"

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

void test_nn_visualiser() {
    uint32_t layers_sizes[3] = { 4, 5, 8 };
    tNeuralNetwork* nn = nn_create(3, layers_sizes);
    nn_print(nn);

    tApp* app = (tApp*)malloc(sizeof(tApp));
    app_create(app);

    time_reset(&app->time);

    while (app->is_running)
    {
        time_compute(&app->time);
        input_check_events(&app->input);
        if (input_getkeydown(&app->input, SDL_SCANCODE_A) || app->input.quit)
            app_quit(app);

        render_init_frame(app->renderer);
        nn_draw(nn, app->renderer, 100, 100, 20);
        render_end_frame(app->renderer);
    }

    app_destroy(app);
    nn_destroy(nn);
}

int main(int argc, char const *argv[])
{
    const char *filename = (argc > 1 ? argv[1] : "test.txt");
    // test_regression(filename);
    // test_nn();

    test_nn_visualiser();

    return 0;
}
