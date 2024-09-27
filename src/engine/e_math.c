#include "e_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double E_Math_Clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}

float E_Math_RandomFloat(float min, float max) {
    float scale = rand() / (float) RAND_MAX;
    return min + scale * (max - min);
}