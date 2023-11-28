#include "NNVisualiser.h"

void perceptron_draw(tRenderer* renderer, int pos_x, int pos_y, int radius) {
    render_disc(renderer, vec2(pos_x, pos_y), radius, color_white());
}

void layer_draw(tNNLayer* layer, tRenderer* renderer, int pos_x, int pos_y, int node_size) {
    for (size_t i = 0; i < layer->perceptrons_count; i++)
        perceptron_draw(renderer, pos_x, pos_y + (node_size * 2 + 10) * i, node_size);    
}


void nn_draw(tNeuralNetwork* nn, tRenderer* renderer, int pos_x, int pos_y, int node_size) {

    int i = 0;
    layer_draw(nn->layers[i], renderer, pos_x + (node_size * 2 + 5) * i, pos_y, node_size);
    i++;
    for (; i < nn->layers_count; i++) {
        layer_draw(nn->layers[i], renderer, pos_x + (node_size * 2 + 5) * i, pos_y, node_size);
        for (int j = 0; j < nn->layers[i - 1]->perceptrons_count; j++) {
            // tVec2 p1 = nn->layers[i - 1]->perceptrons[j];
            tVec2 p1 = vec2(pos_x + (node_size * 2 + 10) * (i - 1), pos_y + (node_size * 2 + 10) * j);
            for (int k = 0; k < nn->layers[i]->perceptrons_count; k++) {
                // tVec2 p2 = nn->layers[i]->perceptrons[k];
                tVec2 p2 = vec2(pos_x + (node_size * 2 + 10) * i, pos_y + (node_size * 2 + 10) * k);
                render_line(renderer, p1, p2, color_white());
            }
            // render_line(renderer, , , color_white());
        }
    }
}

