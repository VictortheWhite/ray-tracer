#include "tracer.h"


tracer::tracer( vec3 **frame, int wWidth, int wHeight,
                float iWidth, float iHeight, float image,
                Point Eye,    Color bgclr, Color nullclr ) 
{
  this->frame = frame;
  this->win_width = wWidth;
  this->win_height = wHeight;
  this->image_width = iWidth;
  this->image_height = iHeight;
  this->image_width = image;
  this->eye_pos = Eye;
  this->background_clr = bgclr;
  this->null_clr = nullclr;
}


/*********************************************************************
 * This function traverses all the pixels and cast rays. It calls the
 * recursive ray tracer and assign return color to frame
 *
 * You should not need to change it except for the call to the recursive
 * ray tracer. Feel free to change other parts of the function however,
 * if you must.
 *********************************************************************/
void tracer::ray_trace(bool shadow_on, int step_max) {
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

  for (i = 0; i < win_height; i++) {
    for (j = 0; j < win_width; j++) {
      ray = cur_pixel_pos - eye_pos;
      //
      // You need to change this!!!
      //
      // ret_color = recursive_ray_trace();
      ret_color = background_clr; // just background for now

      // Parallel rays can be cast instead using below
      //
      // ray.x = ray.y = 0;
      // ray.z = -1.0;
      // ret_color = recursive_ray_trace(cur_pixel_pos, ray, 1);

      // Checkboard for testing
      Color clr = vec3(float(i/32), 0, float(j/32));
      ret_color = clr;

      frame[i][j] = ret_color;

      cur_pixel_pos.x += x_grid_size;
    }

    cur_pixel_pos.y += y_grid_size;
    cur_pixel_pos.x = x_start;
  }
}

Color tracer::recursive_ray_trace() {
//
// do your thing here
//
  Color color;
  return color;
}


Color tracer::phong(Point p, vec3 v, vec3 surf_norm, sphere *sph) {
//
// do your thing here
//
  Color color;
  return color;
}


