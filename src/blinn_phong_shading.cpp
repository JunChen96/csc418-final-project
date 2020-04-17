#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  Eigen::Vector3d rgb(0, 0, 0);
  Ray shadow_ray;
  Eigen::Vector3d q = ray.origin+t*ray.direction;
  shadow_ray.origin = q;

  for (int i=0;i<lights.size();i++) {
    double max_t;
    Eigen::Vector3d d;
    lights[i]->direction(q, d, max_t);
    shadow_ray.direction = d;

    int tmp_hit_id;
    double shadow_t;
    Eigen::Vector3d tmp_n;

    // Check whether there is object from shadow object to light souce 
    if (!first_hit(shadow_ray, 1.0e-7, objects, tmp_hit_id, shadow_t, tmp_n) || shadow_t>=max_t) {
      Eigen::Vector3d v = -(ray.direction).normalized();
      d = d.normalized();
      Eigen::Vector3d h = (v+d).normalized();
      double phong_exponent = objects[hit_id]->material->phong_exponent;
      Eigen::Vector3d I = lights[i]->I;
      Eigen::Vector3d kd = objects[hit_id]->material->kd;
      Eigen::Vector3d ks = objects[hit_id]->material->ks;

      // Add diffuse and specular
      rgb = rgb + (kd.array()*I.array()*fmax(n.dot(d), 0)).matrix();
      rgb = rgb + (ks.array()*I.array()*pow(fmax(n.dot(h), 0), phong_exponent)).matrix();

    }
  }

  return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
