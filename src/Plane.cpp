#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  double q = normal.dot(point);
  double tmp_t = (q - normal.dot(e)) / (normal.dot(d));

  if (tmp_t >= min_t) {
    hit = true;
    n = normal;
    t = tmp_t;
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

