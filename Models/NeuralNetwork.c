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

    for (int i = 0; i < (int)perc->weights_count; i++)
        perc->weights[i] = 1.0f;
    
    return perc; 
}

void perceptron_print(tPerceptron* perc) {
    if (!perc) 
        return;

    fprintf(stdout, "perc<%u>(", perc->weights_count);
    for (int i = 0; i < (int)perc->weights_count; i++)
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

    for (int i = 0; i < (int)layer->perceptrons_count; i++)
        layer->perceptrons[i] = perceptron_create(prev_layer_size);


    layer->bias = 0;
    return layer;
}

void layer_print(tNNLayer* layer) {
    if (!layer)
        return;
    
    fprintf(stdout, "Layer<%u>{\n", layer->perceptrons_count);
    for (int i = 0; i < (int)layer->perceptrons_count; i++)
        perceptron_print(layer->perceptrons[i]);
    
    fprintf(stdout, "bias: %f\n}\n", layer->bias);
}

void layer_destroy(tNNLayer* layer) {
    if (layer) {
        if (layer->perceptrons) {
            for (int i = 0; i < (int)layer->perceptrons_count; i++)
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

    for (int i = 1; i < (int)nn->layers_count; i++) {
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
    for (int i = 0; i < (int)nn->layers_count; i++)
        layer_print(nn->layers[i]);
    
    fprintf(stdout, "]\n");
}

void nn_single_forward_propagation(tNeuralNetwork* nn, float input_x[], uint32_t size, float (*loos_fn)(float, float)) {
    float prev_layer_values[32];
    // memcpy(prev_layer_values, input_x, size); 
    for (int i = 0; i < (int)size; i++)
        prev_layer_values[i] = input_x[i];

    for (int layer_indx = 1; layer_indx < nn->layers_count; layer_indx++)
    {
        float next_layer_values[32];
        uint32_t perc_count = nn->layers[layer_indx]->perceptrons_count;
        for (int j = 0; j < (int)perc_count; j++)
        {
            tPerceptron* p = nn->layers[layer_indx]->perceptrons[j];
            float val = 0;

            for (int k = 0; k < p->weights_count; k++)
                val += p->weights[k] * prev_layer_values[k];

            val += nn->layers[layer_indx]->bias;

            next_layer_values[j] = val;
            printf("Layer: %d [%d --> %f, %f]\n", layer_indx, p->weights_count, next_layer_values[j], prev_layer_values[j]);
        }

        for (int j = 0; j < (int)perc_count; j++)
            prev_layer_values[j] = next_layer_values[j];       
    }
}

void nn_destroy(tNeuralNetwork* nn) {
    if (nn) {
        if (nn->layers) {
            for (int i = 0; i < (int)nn->layers_count; i++)
                layer_destroy(nn->layers[i]);

            nn->layers_count = 0;
            free(nn);
            nn = NULL;
        }
    }
}
