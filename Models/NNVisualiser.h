#pragma once

#include "NeuralNetwork.h"
#include "../../SEngine/Renderer/Renderer.h"

void nn_draw(tNeuralNetwork* nn, tRenderer* renderer, int pos_x, int pos_y, int node_size);
