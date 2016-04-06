//
// this provide functions to set up the scene
//
#include "sphere.h"
#include "chessBoard.h"
#include "triangle.h"
#include <stdio.h>
#include "errno.h"

using namespace std;

extern Point light1;
extern vec3 light1_intensity;

extern vec3 global_ambient;

extern Color background_clr;
extern float decay_a;
extern float decay_b;
extern float decay_c;

extern bool chessBoard_on;


void addChessBoard(vector<object*> &scene);
void readPolygonsFromFile(char* filename, vector<object*>& scene);

//////////////////////////////////////////////////////////////////////////

/*******************************************
 * set up the default scene - DO NOT CHANGE
 *******************************************/
vector<object*> set_up_default_scene(int n) {
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
  vector<object*> scene;


  // sphere 1
  Point sphere1_ctr = vec3(1.5, -0.2, -3.2);
  float sphere1_rad = 1.23;
  vec3 sphere1_ambient = vec3(0.7, 0.7, 0.7);
  vec3 sphere1_diffuse = vec3(0.1, 0.5, 0.8);
  vec3 sphere1_specular = vec3(1.0, 1.0, 1.0);
  float sphere1_shineness = 10;
  float sphere1_reflectance = 0.4;
  float sphere1_refractive_index = 1.55;
  float sphere1_transmissity = 0.2;
  float sphere1_diffuse_coefficient = 0.1;


  object *obj1 = new sphere(
    sphere1_ctr, 
    sphere1_rad, 
    sphere1_ambient,
    sphere1_diffuse, 
    sphere1_specular, 
    sphere1_shineness,
		sphere1_reflectance,
    sphere1_refractive_index,
    sphere1_transmissity,
    sphere1_diffuse_coefficient);
  scene.push_back(obj1);


  // sphere 2
  Point sphere2_ctr = vec3(-1.5, 0.0, -3.5);
  float sphere2_rad = 1.5;
  vec3 sphere2_ambient = vec3(0.6, 0.6, 0.6);
  vec3 sphere2_diffuse = vec3(1.0, 0.0, 0.25);
  vec3 sphere2_specular = vec3(1.0, 1.0, 1.0);
  float sphere2_shineness = 6;
  float sphere2_reflectance = 0.3;
  float sphere2_refractive_index = 1.67;
  float sphere2_transmissity = 0.3;
  float sphere2_diffuse_coefficient = 0.1;

  object *obj2 = new sphere(
    sphere2_ctr, 
    sphere2_rad, 
    sphere2_ambient,
    sphere2_diffuse, 
    sphere2_specular, 
    sphere2_shineness,
		sphere2_reflectance,
    sphere2_refractive_index,
    sphere2_transmissity,
    sphere2_diffuse_coefficient);
  scene.push_back(obj2);

  // sphere 3
  Point sphere3_ctr = vec3(-0.35, 1.75, -2.25);
  float sphere3_rad = 0.5;
  vec3 sphere3_ambient = vec3(0.2, 0.2, 0.2);
  vec3 sphere3_diffuse = vec3(0.0, 1.0, 0.25);
  vec3 sphere3_specular = vec3(0.0, 1.0, 0.0);
  float sphere3_shineness = 30;
  float sphere3_reflectance = 0.3;
  float sphere3_refractive_index = 2.1;
  float sphere3_transmissity = 0.3;
  float sphere3_diffuse_coefficient = 0.1;

  object *obj3 = new sphere(
    sphere3_ctr, 
    sphere3_rad, 
    sphere3_ambient,
    sphere3_diffuse, 
    sphere3_specular, 
    sphere3_shineness,
		sphere3_reflectance,
    sphere3_refractive_index,
    sphere3_transmissity,
    sphere3_diffuse_coefficient);
  scene.push_back(obj3);


  if (chessBoard_on)
  {
    addChessBoard(scene);
    cout << "size " << scene.size() << endl;
  }

  return scene;
}

/***************************************
 * You can create your own scene here
 ***************************************/
vector<object*> set_up_user_scene(int n) {

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


  // set up meshes
  vector<object*> scene;

  // add triangles of meshes
  char *filename = "chess_pieces/chess_piece.smf";
  readPolygonsFromFile(filename, scene);

  // add chess board
  if (chessBoard_on)
  {
    addChessBoard(scene);
  }

  return scene;

}

void readPolygonsFromFile(char* filename, vector<object*>& scene) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL)
  {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  vector<vec3> vetices;

  float x, y, z;
  int a, b, c;
  char ch;
  while(fscanf(fp, "%c", &ch) != EOF) {
    if (ch == 'v')
    {
      fscanf(fp, " %f %f %f\n", &x, &y, &z);
      vetices.push_back(vec3(x, y, z));
    }
    if (ch == 'f')
    {
      fscanf(fp, " %d %d %d\n", &a, &b, &c);
      vec3 vet[3] = { vetices[a-1], vetices[b-1], vetices[c-1]};
      vec3 ambient = vec3(0.3, 0.4, 0.8);
      vec3 diffuse = vec3(0.1, 0.5, 0.3);
      vec3 specular = vec3(1.0, 1.0, 1.0);
      float shine = 30.0;
      float reflectance = 0.6;
      float refractive_index = 1.55;
      float transmissity = 0.4;
      float diffuse_index = 0.1;

      triangle *tri = new triangle(vet, ambient, diffuse, specular, 
        shine, reflectance, refractive_index, transmissity, diffuse_index);

      scene.push_back(tri);
      /*
      for (int i = 0; i < 3; ++i)
      {
        cout << vet[i] << endl;
      }
      cout << endl << endl;
      */
    }

  }

}


void addChessBoard(vector<object*> &scene) {
  object *board = new chessBoard();
  scene.push_back(board);
}