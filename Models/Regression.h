# pragma once


#ifndef REGRESSION_H
#define REGRESSION_H

#include "../Maths/Vec.h"

typedef struct
{
    tVec m_input_data_x;
    tVec m_input_data_y;
    uint8_t m_data_size;

    float m_weight, m_bias;
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

#endif