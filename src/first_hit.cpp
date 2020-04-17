#include "first_hit.h"

bool first_hit(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id,
  double & t,
  Eigen::Vector3d & n)
{
  bool found = false;
  double t_prev = std::numeric_limits<double>::infinity();
  Eigen::Vector3d ret_normal;

  for (int i=0; i<objects.size(); i++) {
    double t_temp;
    Eigen::Vector3d normal_temp;

    if (objects[i]->intersect(ray, min_t, t_temp, normal_temp) && t_temp < t_prev && t_temp >= min_t) {
      found = true;
      t = t_temp;
      t_prev = t;
      n = normal_temp;
      hit_id = i;
    }
  }
  return found;
}
