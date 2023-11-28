#include "NeuralNetwork.h"


tPerceptron* perceptron_create(uint32_t weights_count) {
    tPerceptron* perc = (tPerceptron*)malloc(sizeof(tPerceptron));
    if (!perc) {
        fprintf(stderr, "Couldnt create perceptron\n");
        return NULL;
    }

    perc->weights_count = weights_count;
    perc->weights = (float*)malloc(sizeof(float) * perc->weights_count);

    if (!perc->weights) {
        fprintf(stderr, "Couldnt create perceptron weigts\n");
        free(perc);
        perc = NULL;
        return NULL;
    }

    for (size_t i = 0; i < (size_t)perc->weights_count; i++)
        perc->weights[i] = 1.0f;
    
    return perc; 
}

void perceptron_print(tPerceptron* perc) {
    if (!perc) 
        return;

    fprintf(stdout, "perc<%u>(", perc->weights_count);
    for (size_t i = 0; i < (size_t)perc->weights_count; i++)
        fprintf(stdout, "%f, ", perc->weights[i]);
    
    fprintf(stdout, ")\n");
}

void perceptron_destroy(tPerceptron* perc) {
    if (perc) {
        if (perc->weights) {
            free(perc->weights);
            perc->weights = NULL;
        }

        perc->weights_count = 0;
        free(perc);
        perc = NULL;
    }
}

tNNLayer* layer_create(uint32_t size, uint32_t prev_layer_size) {
    tNNLayer* layer = (tNNLayer*)malloc(sizeof(tNNLayer));
    if (!layer) {
        fprintf(stderr, "Couldnt create nn layer\n");
        return NULL;
    }

    layer->perceptrons_count = size;
    layer->perceptrons = (tPerceptron**)malloc(sizeof(tPerceptron*) * size);
    if (!layer->perceptrons) {
        fprintf(stderr, "Couldnt create perceptrons for layer\n");
        free(layer);
        layer = NULL;
        return NULL;
    }

    for (size_t i = 0; i < (size_t)layer->perceptrons_count; i++)
        layer->perceptrons[i] = perceptron_create(prev_layer_size);


    layer->bias = 0;
    return layer;
}

void layer_print(tNNLayer* layer) {
    if (!layer)
        return;
    
    fprintf(stdout, "Layer<%u>{\n", layer->perceptrons_count);
    for (size_t i = 0; i < (size_t)layer->perceptrons_count; i++)
        perceptron_print(layer->perceptrons[i]);
    
    fprintf(stdout, "bias: %f\n}\n", layer->bias);
}

void layer_destroy(tNNLayer* layer) {
    if (layer) {
        if (layer->perceptrons) {
            for (size_t i = 0; i < (size_t)layer->perceptrons_count; i++)
                perceptron_destroy(layer->perceptrons[i]);

            free(layer->perceptrons);
            layer->perceptrons = NULL;
        }

        layer->bias = 0;
        layer->perceptrons_count = 0;
        free(layer);
        layer = NULL;
    }
}

tNeuralNetwork* nn_create(uint32_t num_layers, uint32_t layer_sizes[]) {
    tNeuralNetwork* nn = (tNeuralNetwork*)malloc(sizeof(tNeuralNetwork));
    if (!nn) {
        fprintf(stderr, "Couldnt create NN\n");
        return NULL;
    }
    nn->layers_count = num_layers;
    // Input Layer
    nn->layers[0] = layer_create(layer_sizes[0], 0);
    if (!nn->layers[0]) {
        free(nn);
        nn = NULL;
        return NULL;
    }

    for (size_t i = 1; i < (size_t)nn->layers_count; i++) {
        nn->layers[i] = layer_create(layer_sizes[i], layer_sizes[i - 1]);
        if (!nn->layers[i]) {
            free(nn);
            nn = NULL;
            return NULL;
        }
        // Change later
    }

    return nn;
}

void nn_print(tNeuralNetwork* nn) {
    if (!nn) 
        return;
    
    fprintf(stdout, "NN<%u>[\n", nn->layers_count);
    for (size_t i = 0; i < (size_t)nn->layers_count; i++)
        layer_print(nn->layers[i]);
    
    fprintf(stdout, "]\n");
}

void nn_forward_propagation(tNeuralNetwork* nn, float (*loos_fn)(float, float)) {
    
}

void nn_destroy(tNeuralNetwork* nn) {
    if (nn) {
        if (nn->layers) {
            for (size_t i = 0; i < (size_t)nn->layers_count; i++)
                layer_destroy(nn->layers[i]);

            nn->layers_count = 0;
            free(nn);
            nn = NULL;
        }
    }
}