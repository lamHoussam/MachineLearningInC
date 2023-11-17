#include "Regression.h"
#include <stdlib.h>



int uniregression_load_data_from_file(
    const char filename[], 
    tUnivariateRegression* res
) {
    if (!res) {
        fprintf(stderr, "Could not store univariate regression\n");
        return -1;
    }

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Could not open file %s\n", filename);
        return -1;
    }

    unsigned int data_size;
    fscanf(fp, " %u", &data_size);

    if (data_size == 0) {
        fprintf(stderr, "Data size can't be 0\n");
    }

    float* data_x = malloc(sizeof(float) * data_size);
    float* data_y = malloc(sizeof(float) * data_size);

    if (!data_x || !data_y) { 
        fprintf(stderr, "Could not initialize data");
        return -1;
    }

    float x, y;

    res->m_data_size = data_size;

    uint8_t i = 0;
    while (fscanf(fp, "%f:%f", &x, &y) != EOF && i < res->m_data_size) {
        data_x[i] = x;
        data_y[i++] = y;
    }

    fclose(fp);
    
    res->m_data_size = (uint8_t)data_size;
    res->m_input_data_x = vec_create(data_x, res->m_data_size);
    res->m_input_data_y = vec_create(data_y, res->m_data_size);

    res->m_bias = 0;
    res->m_weight = 1;
    res->m_learning_rate = .05f;

    return 0;
}

int uniregression_load_data_from_array(
    float values_x[],
    float values_y[],
    size_t size,
    tUnivariateRegression* res
) {
    if (!values_x || !values_y || size == 0) {
        fprintf(stderr, "No data provided\n");
        return -1;
    }

    res->m_bias = 0;
    res->m_weight = 1;
    res->m_learning_rate = .05f;

    res->m_data_size = (uint8_t)size;
    res->m_input_data_x = vec_create(values_x, res->m_data_size);
    res->m_input_data_y = vec_create(values_y, res->m_data_size);

    return 0;
}

void uniregression_print_train_data(tUnivariateRegression reg) {
    printf("Univariate Regression Training Data of size %u: \n{\n", reg.m_data_size);
    for (size_t i = 0; i < (size_t)reg.m_data_size; i++)
        printf("\t%f: %f\n", reg.m_input_data_x.m_vec[i], reg.m_input_data_y.m_vec[i]);

    printf("}\n");
}


int uniregression_train_on_loaded_data(tUnivariateRegression* reg) {
    if (!reg) {
        fprintf(stderr, "Regression model is NULL\n");
        return -1;
    }

    printf("Train Univariate Regression Model on loaded data\n");

    reg->m_weight = 1;
    reg->m_bias = 0;

    uint8_t size = reg->m_input_data_x.m_dimension;

    float xy = 0, ys = 0, xx = 0, xs = 0;
    for (size_t i = 0; i < (size_t)size; i++)
    {
        float x = reg->m_input_data_x.m_vec[i];
        float y = reg->m_input_data_y.m_vec[i];

        xy += x * y;
        xx += x * x;
        ys += y;
        xs += x;
    }

    float val = xs / size;

    reg->m_weight = (xy - (val * ys)) / (xx - (val * xs));
    reg->m_bias = (ys / size) - (reg->m_weight * val); 

    printf("Training over\nComputed weight: %f; Computed bias: %f\n", reg->m_weight, reg->m_bias);
    return 0;
}


float uniregression_predict(tUnivariateRegression* reg, float x) {
    if (!reg) {
        fprintf(stderr, "Regression model is NULL\n");
        return -1;
    }

    return reg->m_weight * x + reg->m_bias;
}


float mean_sqrd_error_loss(tUnivariateRegression* reg) {
    if (!reg) {
        fprintf(stderr, "Need regression model\n");
        return 0;
    }

    float res = 0;
    uint8_t size = reg->m_input_data_x.m_dimension;
    for (size_t i = 0; i < (size_t)size; i++)
    {
        float x = reg->m_input_data_x.m_vec[i];
        float pred_y = uniregression_predict(reg, x);
        float diff = pred_y - reg->m_input_data_y.m_vec[i];

        res += diff * diff;
    }

    return res / size;
}

