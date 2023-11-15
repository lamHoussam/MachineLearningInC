#include "Vec.h"

tVec vec_create(float* elements, uint8_t dimension) {
    if (dimension == 0 || !elements)
        return vec_zero(0);

    tVec res;
    res.m_dimension = dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; ++i)
        res.m_vec[i] = elements[i];

    return res;
}

int vec_get_value(tVec vec, uint8_t ind, float* value) {
    if (!value || ind >= vec.m_dimension)
        return -1;

    *value = vec.m_vec[ind];
    return 0;
}

void vec_print(tVec vec) {
    printf("Vec<%u>(", vec.m_dimension);
    for (size_t i = 0; i < (size_t)vec.m_dimension - 1; i++)
        printf("%f, ", vec.m_vec[i]);
    printf("%f)\n", vec.m_vec[vec.m_dimension - 1]);    
}

uint8_t vec_get_dimenstion(tVec vec) {
    return vec.m_dimension;
}

int vec_equals(tVec vec, tVec other) {
    if (vec.m_dimension != other.m_dimension)
        return -1;
    
    for (size_t i = 0; i < (size_t)vec.m_dimension; i++)
        if (vec.m_vec[i] != other.m_vec[i])
            return -1;
    
    return 0;
}

tVec vec_mult(tVec vec, float scal) {
    tVec res;
    res.m_dimension = vec.m_dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = vec.m_vec[i] * scal;

    return res;
}


tVec vec_div(tVec vec, float scal) {
    if (scal == 0)
        return vec_zero(0);

    tVec res;
    res.m_dimension = vec.m_dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = vec.m_vec[i] / scal;

    return res;
}

tVec vec_add(tVec vec, tVec other) {
    if (vec.m_dimension != other.m_dimension)
        return vec_zero(0);

    tVec res;
    res.m_dimension = vec.m_dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = vec.m_vec[i] + other.m_vec[i];   

    return res;
}


tVec vec_sub(tVec vec, tVec other) {
    if (vec.m_dimension != other.m_dimension)
        return vec_zero(0);

    tVec res;
    res.m_dimension = vec.m_dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = vec.m_vec[i] - other.m_vec[i];

    return res;
}


inline tVec vec_zero(uint8_t dimension) {
    tVec res;
    res.m_dimension = dimension;
    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = 0.0f;

    return res;   
}

tVec vec_one(uint8_t dimension) {
    tVec res;
    res.m_dimension = dimension;

    for (size_t i = 0; i < (size_t)res.m_dimension; i++)
        res.m_vec[i] = 1.0f;
    
    return res;
}