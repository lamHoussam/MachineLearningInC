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



/**
 * @brief Loads training data from a file to univariate regression model
 * 
 * @param filename name of data file
 * @param res regression model
 * @return int status
 */
int uniregression_load_data_from_file(
    const char filename[], 
    tUnivariateRegression* res
);

/**
 * @brief Loads training data from array of values to univariate regression model
 * 
 * @param values_x array of x values
 * @param values_y array of y values
 * @param size size of the array
 * @param res regression model
 * @return int status
 */
int uniregression_load_data_from_array(
    float values_x[],
    float values_y[],
    size_t size,
    tUnivariateRegression* res    
);

/**
 * @brief Prints univariate regression training data to stdout
 * 
 * @param reg regression model
 */
void uniregression_print_train_data(tUnivariateRegression reg);

/**
 * @brief Train univariate regression model on its data
 * 
 * @param reg regression model
 * @return int status
 */
int uniregression_train_on_loaded_data(tUnivariateRegression* reg);

/**
 * @brief Make prediction with univariate regression model
 * 
 * @param reg regression model
 * @param x value 
 * @return float prediction
 */
float uniregression_predict(tUnivariateRegression* reg, float x);

/**
 * @brief Calculates mean squared error loss of the univariate regression model
 * 
 * @param reg regression model
 * @return float computed loss
 */
float mean_sqrd_error_loss(tUnivariateRegression* reg);

#endif