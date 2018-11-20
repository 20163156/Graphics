#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"
#include "transform.hpp"

#define offset1 1
#define offset2 2
#define offset3 3

#define minmax1 4
#define minmax2 5
#define minmax3 6

#define ratio1 7
#define ratio2 8
#define ratio3 9

using namespace std;

void init();
void mydisplay();
GLuint create_shaer_from_file(const std::string& filename, GLuint shader_type);
void lev1();
void lev2();
void lev3();
void lev4();
void lev5();
void lev6();
void hilbert(vector<float>* curve, int n, float x, float y, float xi, float xj, float yi, float yj);
void createGLUTMenus();
void processMenuEvents(int option);


GLuint program;
GLint loc_a_position;
GLint loc_a_color;
vector<float> curve;
int change_size = 20;
int num_rects = 5;
int min_rects, max_rects;
int ratio = 1;
int check = 1;
bool displayFlag = 0;

int main(int argc, char* argv[])
{
  srand((unsigned)time(0));

  glutInit(&argc, argv);
  glutInitWindowSize(500, 500);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutCreateWindow("HW3 FreeGLUT");

  init();
  glutDisplayFunc(mydisplay);
  createGLUTMenus();
  glutMainLoop();

  return 0;
}

GLuint create_shader_from_file(const std::string& filename, GLuint shader_type)
{
  GLuint shader = 0;
  shader = glCreateShader(shader_type);
  std::ifstream shader_file(filename.c_str());
  std::string shader_string;
  shader_string.assign(
    (std::istreambuf_iterator<char>(shader_file)),
    std::istreambuf_iterator<char>());

  const GLchar* shader_src = shader_string.c_str();

  glShaderSource(shader, 1, (const GLchar**)&shader_src, NULL);
  glCompileShader(shader);

  return shader;
}

void init()
{
  glewInit();

  GLuint vertex_shader
    = create_shader_from_file("./shader/vertex.glsl", GL_VERTEX_SHADER);

  GLuint fragment_shader
    = create_shader_from_file("./shader/fragment.glsl", GL_FRAGMENT_SHADER);

  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  loc_a_position = glGetAttribLocation(program, "a_position");
  loc_a_color    = glGetAttribLocation(program, "a_color");

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void mydisplay()
{
  if(check==displayFlag) return;
  check = displayFlag;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //배경색상 지우는거라 겹쳐서 사각형 그릴때 삭제해야할수도
  glUseProgram(program);

  lev1();
  lev2();
  lev3();
  lev4();
  //lev5();
  //lev6();

  glUseProgram(0);
  glutSwapBuffers();
}


void hilbert(vector<float>* curve, int n, float x, float y, float xi, float xj, float yi, float yj)
{
    if (n <= 0) {
        curve->push_back(x + (xi + yi)/2);
        curve->push_back(y + (xj + yj)/2);
    } else {
         hilbert(curve,n-1,x,           y,           yi/2, yj/2,  xi/2,  xj/2);
         hilbert(curve,n-1,x+xi/2,      y+xj/2 ,     xi/2, xj/2,  yi/2,  yj/2);
         hilbert(curve,n-1,x+xi/2+yi/2, y+xj/2+yj/2, xi/2, xj/2,  yi/2,  yj/2);
         hilbert(curve,n-1,x+xi/2+yi,   y+xj/2+yj,  -yi/2,-yj/2, -xi/2, -xj/2);
    }
}

void draw(int random_num ,vector<float> curve,float size)
{
  float arr1[2];
  float arr2[2];
  float point[2];

  arr1[0] = curve[random_num];
  arr1[1] = curve[random_num+1];

  arr2[0] = curve[random_num+2];
  arr2[1] = curve[random_num+3];

  if(arr1[0]==arr2[0])
  {
    if(arr1[1] < arr2[1])
    { point[0] =  arr1[0];
      point[1] =  ((arr2[1] - arr1[1]) * ((float)rand() / RAND_MAX)) + arr1[1];
    }
    else
    {
       point[0] =  arr1[0];
       point[1] =  ((arr1[1] - arr2[1]) * ((float)rand() / RAND_MAX)) + arr2[1];
    }
  }
  else if(arr1[1] == arr2[1])
  {
    if(arr1[1] < arr2[1])
    {
      point[0] =  ((arr2[0] - arr1[0]) * ((float)rand() / RAND_MAX)) + arr1[0];
      point[1] =  arr1[1];
    }
    else
    {
       point[0] =  ((arr1[0] - arr2[0]) * ((float)rand() / RAND_MAX)) + arr2[0];
       point[1] =  arr1[0];
    }
  }

  float centerX = point[0];
  float centerY = point[1];

  float offset = size;

  for(int i = 0; i < 10; i++)
  {
    float position[] = {
    centerX-offset, centerY-offset, 0,     1.0f,
    centerX+offset, centerY-offset, 0,     1.0f,
    centerX+offset, centerY+offset, 0,     1.0f,

    centerX+offset, centerY+offset, 0,     1.0f,
    centerX-offset, centerY+offset, 0,     1.0f,
    centerX-offset, centerY-offset, 0,     1.0f,
  };

    offset -= size/change_size;

  float color[] = {
    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f,
  };

  int temp;
  temp = rand()%10;
  glVertexAttribPointer(loc_a_position, 4, GL_FLOAT, GL_FALSE, 0, position);
  glVertexAttribPointer(loc_a_color, 4, GL_FLOAT, GL_FALSE, 12*sizeof(float), &color[temp]);

  glEnableVertexAttribArray(loc_a_color);
  glEnableVertexAttribArray(loc_a_position);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glDisableVertexAttribArray(loc_a_color);
  glDisableVertexAttribArray(loc_a_position);
 }
}

void lev1()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  int size;
  size = 0.2f;
  hilbert(&curve,1,-1.5f,-1.5f,3.0f,0.0f,0.0f,3.0f);

//  num_rects = min, max rand * ratio
  for(int j = 0; j < num_rects; j++)
  {
    // ((b - a) * ((float)rand() / RAND_MAX)) + a;
    random_num = rand()%3*2;
    draw(random_num,curve, 0.2f);
  }
}

void lev2()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  int size;
  size = 0.15f;
  for(int i = 0;i <=6;i+=2)
  {
    hilbert(&curve,2,curve[i],curve[i+1],1.0f,0.0f,0.0f,1.0f);
  }

  for(int j = 0; j < num_rects*ratio; j++)
  {
    random_num =  (rand()%16 + 4 )* 2;  //random 8~39 even
    //i = (rand()%n + m) * o
    draw(random_num,curve,0.17f);
  }
}

void lev3()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  for(int i = 0;i <=30 ;i+=2)
  {
    hilbert(&curve,3,curve[i+8],curve[i+9],1.0f,0.0f,0.0f,1.0f);
  }

  for(int j = 0; j < num_rects*pow(ratio,2); j++)
  {
    random_num =  (rand()%64 + 20 )* 2;  //random 40~167 even
    draw(random_num,curve,0.15f);
  }
}

void lev4()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  for(int i = 0;i <=126 ;i+=2)
  {
    hilbert(&curve,4,curve[i+40],curve[i+41],1.0f,0.0f,0.0f,1.0f);
  }

  for(int j = 0; j < num_rects*pow(ratio,3); j++)
  {
      random_num =  (rand()%256 + 84 )* 2;  //random 168~679 even
      draw(random_num,curve,0.11f);
  }
}

void lev5()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  for(int i = 0;i <=510 ;i+=2)
  {
    hilbert(&curve,5,curve[i+168],curve[i+169],1.0f,0.0f,0.0f,1.0f);
  }

  for(int j = 0; j < num_rects*pow(ratio,4); j++)
  {
      random_num =  (rand()%1024 + 340 )* 2;  //random 168~679 even
      draw(random_num,curve,0.09f);
  }
}

void lev6()
{
  srand((unsigned)time(NULL));

  float centerX,centerY;
  int random_num;
  for(int i = 0;i <= 2046;i+=2)
  {
    hilbert(&curve,6,curve[i+680],curve[i+681],1.0f,0.0f,0.0f,1.0f);
  }

  for(int j = 0; j < num_rects*pow(ratio,5); j++)
  {
      random_num =  (rand()%4096 + 1364 )* 2;  //random 168~679 even
      draw(random_num,curve,0.05f);
  }
}


void createGLUTMenus()
{
  int menu;
  int offsetSubmenu;
  int minmaxSubMenu;
  int ratioSubMenu;

  offsetSubmenu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("7", offset1);
  glutAddMenuEntry("5", offset2);
  glutAddMenuEntry("3", offset3);

  minmaxSubMenu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("1/5", minmax1);
  glutAddMenuEntry("5/15",minmax2);
  glutAddMenuEntry("15/30", minmax3);

  ratioSubMenu = glutCreateMenu(processMenuEvents);
  glutAddMenuEntry("2", ratio1);
  glutAddMenuEntry("3", ratio2);
  glutAddMenuEntry("5", ratio3);

  menu = glutCreateMenu(processMenuEvents);
  glutAddSubMenu("offset", offsetSubmenu);
  glutAddSubMenu("min/max", minmaxSubMenu);
  glutAddSubMenu("ratio", ratioSubMenu);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuEvents(int option)
{
  switch(option)
  {
    case 1  :
      change_size = 10; check++;
        break;
    case 2 :
      change_size = 25; check++;
        break;
    case 3 :
      change_size = 40; check++;
        break;
    case 4 :
      min_rects = 1;
      max_rects = 5;
      num_rects = min_rects + rand()%(max_rects);
      check++;
        break;
    case 5:
      min_rects = 5;
      max_rects = 15;
      num_rects = min_rects + rand()%(max_rects);
      check++;
        break;
    case 6 :
      min_rects = 15;
      max_rects = 30;
      num_rects = min_rects + rand()%(max_rects);
      check++;
        break;
    case 7 :
      ratio=2;
      check++;
        break;
    case 8 :
      ratio=3;
      check++;
        break;
    case 9 :
      ratio=5;
      check++;
        break;
  }
  glutPostRedisplay();
}
