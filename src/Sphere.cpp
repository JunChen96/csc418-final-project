#include "Sphere.h"
#include "Ray.h"

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = center;
  bool hit = false;
  double A = d.dot(d);
  double B = 2 * d.dot(e-c);
  double C = (e-c).dot(e-c) - pow(radius,2);
  double discriminant = pow(B,2) - 4*A*C;

  if (discriminant < 0) {
    // No intersection
    return hit;
  } else if (discriminant == 0) {
    // one intersection
    double x = -B/(2*A);
    if (x >= min_t) {
    t = x;
    Eigen::Vector3d p = e + t * d;
    n = (p - c) / radius;
    hit = true;
    }
  } else {
    // two intersections
    double x1 = (-B + sqrt(discriminant)) / (2*A);
    double x2 = (-B - sqrt(discriminant)) / (2*A);
    if (x2 >= min_t) {
      t = x2;
      Eigen::Vector3d p = e + t * d;
      n = (p - c) / radius;
      hit = true;
    } else if (x1 >= min_t) {
      t = x1;
      Eigen::Vector3d p = e + t * d;
      n = (p - c) / radius;
      hit = true;
    }
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}

