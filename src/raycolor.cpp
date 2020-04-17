#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include <iostream>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_recursive_calls > 3) return false;

  int hit_id;
  double t;
  Eigen::Vector3d n;

  if (first_hit(ray, min_t, objects, hit_id, t, n)) {
    Eigen::Vector3d p = ray.origin+t*ray.direction;

    // ambient color
    Eigen::Vector3d ka = objects[hit_id]->material->ka;
    // Eigen::Vector3d Ia(0.1, 0.1, 0.1);
    // rgb = rgb+(ka.array()*Ia.array()).matrix();
    // ??????
    Eigen::Vector3d Ia(1,1,1);
    rgb = 0.1*(ka.array()*Ia.array()).matrix();

    // blinn_phong_shading
    Eigen::Vector3d blinn_phone_shaded_color = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    rgb = rgb+blinn_phone_shaded_color;

    // reflection
    Ray reflect_ray;
    reflect_ray.origin = p;
    reflect_ray.direction = reflect(ray.direction.normalized(), n);
    Eigen::Vector3d tmp_rgb;

    if (raycolor(reflect_ray, 1.0e-7, objects, lights, num_recursive_calls+1, tmp_rgb)) {
      Eigen::Vector3d km = objects[hit_id]->material->km;
      rgb = rgb+(km.array()*tmp_rgb.array()).matrix();
    }

    return true;

  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
