# pragma once


#ifndef VECTOR_H
#define VECTOR_H


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


#define MAX_DIMENSIONS 256

typedef struct {
    float m_vec[MAX_DIMENSIONS];
    uint8_t m_dimension;    
} tVec;

tVec vec_create(float* elements, uint8_t dimension);

int vec_get_value(tVec vec, uint8_t ind, float* value);
void vec_print(tVec vec);
uint8_t vec_get_dimenstion(tVec vec);
int vec_equals(tVec v1, tVec v2);

// Operations
tVec vec_mult(tVec vec, float scl);
tVec vec_div(tVec vec, float scl);
tVec vec_add(tVec v1, tVec v2);
tVec vec_sub(tVec v1, tVec v2);


tVec vec_zero(uint8_t dimension);
tVec vec_one(uint8_t dimension);


#endif