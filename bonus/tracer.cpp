#include "tracer.h"

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
    cout << "rendering: " << i << "(" << win_height << ")" << endl;
    for (j = 0; j < win_width; j++) {
      ray = normalize(cur_pixel_pos - eye_pos);

      // recursive ray trace
      ret_color = recursive_ray_trace(eye_pos, ray, 0, NULL);

      if (supersampling_on)
      {
        float halfXGrid = x_grid_size / 4.0;
        float halfYGrid = y_grid_size / 4.0;
        ret_color += recursive_ray_trace(eye_pos, ray + vec3( halfXGrid,  halfYGrid, 0), 0, NULL);
        ret_color += recursive_ray_trace(eye_pos, ray + vec3( halfXGrid, -halfYGrid, 0), 0, NULL);
        ret_color += recursive_ray_trace(eye_pos, ray + vec3(-halfXGrid,  halfYGrid, 0), 0, NULL);
        ret_color += recursive_ray_trace(eye_pos, ray + vec3(-halfXGrid, -halfYGrid, 0), 0, NULL);

        ret_color /= 5.0;
      }

      frame[i][j] = ret_color;
      cur_pixel_pos.x += x_grid_size;
    }

    cur_pixel_pos.y += y_grid_size;
    cur_pixel_pos.x = x_start;
  }

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

  return color;
}


Color tracer::phong(Point p, vec3 ray, object *obj, int step) {
  float shadow = 1.0;

  if (shadow_on)
  {
    if (obj->in_shadow(p, LightSource, scene))
    {
      shadow = 0.0;
    } 
  }

  vec3 l = normalize(LightSource - p);      // pointing to light
  vec3 n = normalize(obj->getNormal(p));    // surface normal
  vec3 v = normalize(eye_pos - p);          // viewpoint
  vec3 r = 2.0 * dot(n, l) * n - l;         // reflection vector

  float dst = length(p - LightSource);
  float decay = 1.0 / (decay_a + decay_b*dst +decay_c*dst*dst);

  vec3 ambientReflection = obj->getAmbient(p) * global_ambient;
  vec3 diffuseReflection = decay * LightIntensity *  obj->getDiffuse(p) * max(dot(n, l), 0) ;
  vec3 specularReflection = decay * LightIntensity * obj->getSpecular(p) * pow(max(dot(r, v),0), obj->getShineness(p));


  vec3 color = ambientReflection + shadow * (diffuseReflection + specularReflection);

  // reflection
  if (reflection_on && step < step_max)
  {
     //recursively trace
    vec3 reflectedRay = 2.0*dot(v, n)*n - v;
    color += obj->getReflectance(p)*recursive_ray_trace(p, reflectedRay, step+1, obj);
  }

  // refraction
  if (refraction_on && step < max(step_max, 2))
  {
    // recursively trace refracted ray
    Point outPoint;
    vec3 refractedRay;

    if(obj->getRefractedRayOutObject(p, v, outPoint, refractedRay))
    {
      color += obj->getTransmissivity()*recursive_ray_trace(outPoint, refractedRay, step+1, obj);
    } 
  }

  // stochastic diffuse reflection
  if (stochastic_on && step < max(step_max, 2))
  {
    for (int i = 0; i < numOfStochasticRay; ++i)
    {
      vec3 ray = generateDiffuseRay(n);
      color += obj->getDiffuseCoefficient() * recursive_ray_trace(p, ray, step+1, obj);
    }
  }

  return color;
}

vec3 tracer::generateDiffuseRay(vec3 n) {
  while (true) {
    vec3 ray = vec3(randFloat(-1, 1), randFloat(-1, 1), randFloat(-1, 1));
    if (dot(n, ray) >= 0)
    {
      return normalize(ray);
    }
  }
}



void tracer::set(bool shadow, bool refl, bool stoch, bool refra, bool super_samp) {
  this->shadow_on = shadow;
  this->reflection_on = refl;
  this->stochastic_on = stoch;
  this->refraction_on = refra;
  this->supersampling_on = super_samp;
}


float tracer::max(float a, float b) {
  return a > b? a : b;
}

float tracer::randFloat(float min, float max) {
  return ((float)rand() / (float)RAND_MAX) * (max - min) + min;
}