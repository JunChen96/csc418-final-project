#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool hit = false;
  Eigen::Vector3d directionD = ray.direction;
  Eigen::Vector3d originE = ray.origin;
  
  Eigen::Vector3d pointA = std::get<0>(corners);
  Eigen::Vector3d pointB = std::get<1>(corners);
  Eigen::Vector3d pointC = std::get<2>(corners);

  double a = pointA[0] - pointB[0];
  double b = pointA[1] - pointB[1];
  double c = pointA[2] - pointB[2];
  double d = pointA[0] - pointC[0];
  double e = pointA[1] - pointC[1];
  double f = pointA[2] - pointC[2];
  double g = directionD[0];
  double h = directionD[1];
  double i = directionD[2];
  double j = pointA[0] - originE[0];
  double k = pointA[1] - originE[1];
  double l = pointA[2] - originE[2];

  double M = a*(e*i-h*f)+b*(g*f-d*i)+c*(d*h-e*g);
  double tmp_t = - (f*(a*k-j*b)+e*(j*c-a*l)+d*(b*l-k*c)) / M;
  if (tmp_t < min_t) {
    return hit;
  }

  double tmp_gamma = (i*(a*k-j*b)+h*(j*c-a*l)+g*(b*l-k*c)) / M;
  if (tmp_gamma<0 || tmp_gamma>1) {
    return hit;
  }

  double tmp_beta = (j*(e*i-h*f)+k*(g*f-d*i)+l*(d*h-e*g)) / M;
  if (tmp_beta<0 || tmp_beta>1-tmp_gamma) {
    return hit;
  }

  hit = true;
  t = tmp_t;
  Eigen::Vector3d u = pointB - pointA;
  Eigen::Vector3d v = pointC - pointA;
  n = u.cross(v).normalized();

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}


