#include <math.h>

const float FOV_ANGLE = 45;
float HALF_FOV_ANGLE_RADIANS = ((FOV_ANGLE / 180) * M_PI) / 2;

float transform3Dto2D(float xy, float z) {
  return xy / (z * tan(HALF_FOV_ANGLE_RADIANS));
}