#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  ray.origin = camera.e;
  double u = camera.width*(j+0.5)/width - camera.width/2.0;
  double v = camera.height*(i+0.5)/height - camera.height/2.0;

  ray.direction = u*camera.u - v*camera.v - camera.d*camera.w;
  ////////////////////////////////////////////////////////////////////////////
}

