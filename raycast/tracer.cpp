#include "tracer.h"


tracer::tracer( vec3 **frame, int wWidth, int wHeight,
                float iWidth, float iHeight, float image,
                Point Eye,    Color bgclr, Color nullclr,
                Point LightSource, vec3 LightIntensity, 
                vec3 global_ambient, 
                float decayA, float decayB, float decayC,
                sphere **scene ) 
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
  this->LightSource = LightSource;
  this->LightIntensity = LightIntensity;
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
      ret_color = recursive_ray_trace(ray, step_max);

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
}

Color tracer::recursive_ray_trace(vec3 ray, int step_max) {

  Color color;
  sphere SPH;
  Point intersectionPoint;


  sphere *sph = SPH.intersect_scene(eye_pos, ray, scene, &intersectionPoint);

  //cout << eye_pos << ' ' << ray << endl;

  if (sph == NULL)
  {
    return background_clr;
  } 


  color = phong(intersectionPoint, ray, sph);

  return color;
}


Color tracer::phong(Point p, vec3 ray, sphere *sph) {

  float shadow = 1.0;

  if (shadow_on)
  {
    
  }


  vec3 l = normalize(p - LightSource);      // incomming light
  vec3 n = sph->getNormal(p);                // surface normal
  vec3 v = -ray;                            // viewpoint
  vec3 r = 2.0 * dot(-l, n) * n + l;        // reflection vector

  float dst = length(p - LightSource);
  float decay = 1.0 / (decay_a + decay_b*dst +decay_c*pow(dst,2));

  vec3 ambientReflection = sph->getAmbient() * global_ambient;
  vec3 diffuseReflection = decay * LightIntensity * ( sph->getDiffuse() * dot(n, l)) ;
  vec3 specularReflection = decay * LightIntensity * ( sph->getSpecular() * pow(dot(r, v), sph->getShineness()) );


  return ambientReflection + diffuseReflection + specularReflection;
}



void tracer::set(bool shadow, bool refl, bool stoch) {
  this->shadow_on = shadow;
  this->reflection_on = refl;
  this->stochastic_on = stoch;
}