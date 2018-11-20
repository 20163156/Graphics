#version 120    // GLSL 1.2  (OpenGL 2.x)

//uniform mat4  u_Model; //쉐이더에서 세팅안됨
attribute vec4 a_position;
attribute vec4 a_color;
varying vec4 v_color;


void main()
{
  v_color = a_color;
  gl_Position = a_position;
}
