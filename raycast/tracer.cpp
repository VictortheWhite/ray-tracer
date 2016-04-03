#include "tracer.h"

// debug
static int r_t = 0;
static int r_nt = 0;

tracer::tracer( vec3 **frame, int wWidth, int wHeight,
                float iWidth, float iHeight, float image,
                Point Eye,    Color bgclr, Color nullclr,
                Point lightSource, vec3 lightIntensity, 
                vec3 global_ambient, 
                float decayA, float decayB, float decayC,
                vector<object*> scene ) 
{
  this->frame = frame;
  this->win_width = wWidth;
  this->win_height = wHeight;
  this->image_width = iWidth;
  this->image_height = iHeight;
  this->image_plane = image;
  this->eye_pos = Eye;
  this->background_clr = bgclr;
  this->null_clr = nullclr;
  this->LightSource = lightSource;
  this->LightIntensity = lightIntensity;
  this->global_ambient = global_ambient;
  this->decay_a = decayA;
  this->decay_b = decayB;
  this->decay_c = decayC;
  this->scene = scene;

  this->pixel_in_shadow = 0;
  this->pixel_not_in_shadow = 0;
}


/*********************************************************************
 * This function traverses all the pixels and cast rays. It calls the
 * recursive ray tracer and assign return color to frame
 *
 * You should not need to change it except for the call to the recursive
 * ray tracer. Feel free to change other parts of the function however,
 * if you must.
 *********************************************************************/
void tracer::ray_trace(int step_max) {

  this->step_max = step_max;

  int i, j;
  float x_grid_size = image_width / (float)win_width;
  float y_grid_size = image_height / (float)win_height;

  float x_start = -0.5 * image_width;
  float y_start = -0.5 * image_height;

  Color ret_color;
  Point cur_pixel_pos;
  vec3 ray;

  // ray is cast through center of pixel
  cur_pixel_pos.x = x_start + 0.5 * x_grid_size;
  cur_pixel_pos.y = y_start + 0.5 * y_grid_size;
  cur_pixel_pos.z = image_plane;

  //cout << win_height << endl << win_width << endl;

  for (i = 0; i < win_height; i++) {
    for (j = 0; j < win_width; j++) {

      ray = normalize(cur_pixel_pos - eye_pos);

      // recursive ray trace
      ret_color = recursive_ray_trace(eye_pos, ray, 0, NULL);

      // Parallel rays can be cast instead using below
      //
      // ray.x = ray.y = 0;
      // ray.z = -1.0;
      // ret_color = recursive_ray_trace(cur_pixel_pos, ray, 1);

      frame[i][j] = ret_color;
      cur_pixel_pos.x += x_grid_size;
    }

    cur_pixel_pos.y += y_grid_size;
    cur_pixel_pos.x = x_start;
  }

  cout << "in shadow: " << pixel_in_shadow << endl;
  cout << "not in shadow: " << pixel_not_in_shadow << endl;

  cout << "r_t: " << r_t << endl
    << "r_nt: " << r_nt << endl;
}

Color tracer::recursive_ray_trace(Point o, vec3 ray, int step, object* ignore) {

  Color color;
  Point intersectionPoint;

  object *obj = object::intersect_scene(o, ray, scene, &intersectionPoint, ignore);

  if (obj == NULL)
  {
    return background_clr;
  } 

  color = phong(intersectionPoint, ray, obj, step);

  if (step == 1)
  {
    //cout << "phong: " << color << endl;
  }

  return color;
}


Color tracer::phong(Point p, vec3 ray, object *obj, int step) {
  float shadow = 1.0;

  if (shadow_on)
  {
    if (obj->in_shadow(p, LightSource, scene))
    {
      shadow = 0.0;
      pixel_in_shadow ++;
    } else {
      pixel_not_in_shadow ++;
    }
  }

  vec3 l = normalize(LightSource - p);      // pointing to light
  vec3 n = normalize(obj->getNormal(p));    // surface normal
  vec3 v = normalize(eye_pos - p);          // viewpoint
  vec3 r = 2.0 * dot(n, l) * n - l;         // reflection vector

  if (obj->getIndex() <= 2)
  {
    //cout << n << endl;
  }

  float dst = length(p - LightSource);
  float decay = 1.0 / (decay_a + decay_b*dst +decay_c*dst*dst);

  vec3 ambientReflection = obj->getAmbient(p) * global_ambient;
  vec3 diffuseReflection = decay * LightIntensity *  obj->getDiffuse(p) * max(dot(n, l), 0) ;
  vec3 specularReflection = decay * LightIntensity * obj->getSpecular(p) * pow(max(dot(r, v),0), obj->getShineness(p));


  vec3 color = ambientReflection + shadow * (diffuseReflection + specularReflection);

  if (reflection_on && step < step_max)
  {
     //recursively trace
    vec3 reflectedRay = 2.0*dot(v, n)*n - v;
    color += obj->getReflectance(p)*recursive_ray_trace(p, reflectedRay, step+1, obj);
  }

  if (refraction_on && step < step_max)
  {
    // recursively trace refracted ray
    Point outPoint;
    vec3 refractedRay;

    if(obj->getRefractedRayOutObject(p, v, outPoint, refractedRay))
    {
      color += obj->getTransmissivity()*recursive_ray_trace(outPoint, refractedRay, step+1, obj);
      r_t++;
    } else {
      r_nt++;
    }
  }

  return color;
}



void tracer::set(bool shadow, bool refl, bool stoch, bool refra) {
  this->shadow_on = shadow;
  this->reflection_on = refl;
  this->stochastic_on = stoch;
  this->refraction_on = refra;
}


float tracer::max(float a, float b) {
  return a > b? a : b;
}