#include "./math.h"

#include <math.h>
#include <stdio.h>

float HALF_FOV_ANGLE_RADIANS = ((FOV_ANGLE / 180.0) * M_PI) / 2;

float transform3Dto2D(float xy, float z) {
  // return xy;
  // printf("\nIn %f %f Out %f", xy, z, xy / (z * tan(HALF_FOV_ANGLE_RADIANS)));
  return xy / ((z)*tan(HALF_FOV_ANGLE_RADIANS));
}