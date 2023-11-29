# pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUM_LAYERS 8

typedef struct
{
    float* weights;
    uint32_t weights_count;
} tPerceptron;

typedef struct
{
    float bias;
    tPerceptron** perceptrons;
    uint32_t perceptrons_count;
} tNNLayer;

typedef struct
{
    tNNLayer* layers[MAX_NUM_LAYERS];
    uint32_t layers_count;
} tNeuralNetwork;


/**
 * ?Steps to make Neural Network: 
 * 1: Initialize weights and biases
 * 2: Forward Propagation
 * TODO 3: Compute the loss
 * TODO 4: Back propagation
 * TODO 5: Update weights and biases
*/

tPerceptron* perceptron_create(uint32_t weights_count);
void perceptron_print(tPerceptron* perc);
void perceptron_destroy(tPerceptron* perc);


tNNLayer* layer_create(uint32_t size, uint32_t prev_layer_size);
void layer_print(tNNLayer* layer);
void layer_destroy(tNNLayer* layer);

tNeuralNetwork* nn_create(uint32_t num_layers, uint32_t layer_sizes[]);
void nn_print(tNeuralNetwork* nn);
void nn_single_forward_propagation(tNeuralNetwork* nn, float input_x[], uint32_t size, float (*loos_fn)(float, float));
void nn_destroy(tNeuralNetwork* nn);
