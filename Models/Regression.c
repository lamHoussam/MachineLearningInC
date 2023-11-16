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
    while (fscanf(fp, "%f:%f", &x, &y) != EOF) {
        data_x[i] = x;
        data_y[i++] = y;
    }

    fclose(fp);
    
    res->m_data_size = (uint8_t)data_size;
    res->m_input_data_x = vec_create(data_x, res->m_data_size);
    res->m_input_data_y = vec_create(data_y, res->m_data_size);

    res->m_bias = 0;
    res->m_weight = 1;


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

