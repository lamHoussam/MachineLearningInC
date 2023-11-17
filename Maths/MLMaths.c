#include "MLMaths.h"


float sqrd_err_loss(float y, float predicted_y) {
    float diff = (y - predicted_y);
    return diff * diff;
}