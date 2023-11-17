# pragma once


#ifndef REGRESSION_H
#define REGRESSION_H

#include "../../CMaths/Vec.h"

typedef struct
{
    tVec m_input_data_x;
    tVec m_input_data_y;
    uint8_t m_data_size;
    float m_weight, m_bias;
    float m_learning_rate;
} tUnivariateRegression;


int uniregression_load_data_from_file(
    const char filename[], 
    tUnivariateRegression* res
);

int uniregression_load_data_from_array(
    float values_x[],
    float values_y[],
    size_t size,
    tUnivariateRegression* res    
);

void uniregression_print_train_data(tUnivariateRegression reg);
int uniregression_train_on_loaded_data(tUnivariateRegression* reg);

float uniregression_predict(tUnivariateRegression* reg, float x);

float mean_sqrd_error_loss(tUnivariateRegression* reg);

#endif