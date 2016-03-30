//
// this provide functions to set up the scene
//
#include "sphere.h"
#include <stdio.h>

extern Point light1;
extern vec3 light1_intensity;

extern vec3 global_ambient;

extern Color background_clr;
extern float decay_a;
extern float decay_b;
extern float decay_c;

//////////////////////////////////////////////////////////////////////////

/*******************************************
 * set up the default scene - DO NOT CHANGE
 *******************************************/
sphere** set_up_default_scene(int n) {
  // set background color
  background_clr.x = 0.5;   // r
  background_clr.y = 0.05;  // g
  background_clr.z = 0.8;   // b

  // set up global ambient term
  global_ambient = vec3(0.2, 0.2, 0.2);

  // set up light 1
  light1 = vec3(-2.0, 5.0, 1.0);
  light1_intensity = vec3(1.0, 1.0, 1.0);

  // set up decay parameters
  decay_a = 0.5;
  decay_b = 0.3;
  decay_c = 0.0;

  // set up spheres
  sphere **scene = new sphere*[n];


  // sphere 1
  Point sphere1_ctr = vec3(1.5, -0.2, -3.2);
  float sphere1_rad = 1.23;
  vec3 sphere1_ambient = vec3(0.7, 0.7, 0.7);
  vec3 sphere1_diffuse = vec3(0.1, 0.5, 0.8);
  vec3 sphere1_specular = vec3(1.0, 1.0, 1.0);
  float sphere1_shineness = 10;
  float sphere1_reflectance = 0.4;
  scene[0] = new sphere(
    sphere1_ctr, 
    sphere1_rad, 
    sphere1_ambient,
    sphere1_diffuse, 
    sphere1_specular, 
    sphere1_shineness,
		sphere1_reflectance);

  // sphere 2
  Point sphere2_ctr = vec3(-1.5, 0.0, -3.5);
  float sphere2_rad = 1.5;
  vec3 sphere2_ambient = vec3(0.6, 0.6, 0.6);
  vec3 sphere2_diffuse = vec3(1.0, 0.0, 0.25);
  vec3 sphere2_specular = vec3(1.0, 1.0, 1.0);
  float sphere2_shineness = 6;
  float sphere2_reflectance = 0.3;
  scene[1] = new sphere(
    sphere2_ctr, 
    sphere2_rad, 
    sphere2_ambient,
    sphere2_diffuse, 
    sphere2_specular, 
    sphere2_shineness,
		sphere2_reflectance);

  // sphere 3
  Point sphere3_ctr = vec3(-0.35, 1.75, -2.25);
  float sphere3_rad = 0.5;
  vec3 sphere3_ambient = vec3(0.2, 0.2, 0.2);
  vec3 sphere3_diffuse = vec3(0.0, 1.0, 0.25);
  vec3 sphere3_specular = vec3(0.0, 1.0, 0.0);
  float sphere3_shineness = 30;
  float sphere3_reflectance = 0.3;
  scene[2] = new sphere(
    sphere3_ctr, 
    sphere3_rad, 
    sphere3_ambient,
    sphere3_diffuse, 
    sphere3_specular, 
    sphere3_shineness,
		sphere3_reflectance);

  return scene;
}

/***************************************
 * You can create your own scene here
 ***************************************/
sphere** set_up_user_scene(int n) {
}
