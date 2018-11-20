#ifndef KMUCS_GRAPHICS_TRANSFORM_HPP
#define KMUCS_GRAPHICS_TRANSFORM_HPP

#include <cmath>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"

namespace kmuvcl
{
    namespace math
    {
#ifndef M_PI
        const float M_PI = 3.14159265358979323846;
#endif

        template <typename T>
        mat<4, 4, T> translate(T dx, T dy, T dz)
        {
            mat<4, 4, T> translateMat;

            kmuvcl::math::vec4f temp1(1,0,0,0);
            kmuvcl::math::vec4f temp2(0,1,0,0);
            kmuvcl::math::vec4f temp3(0,0,1,0);
            kmuvcl::math::vec4f temp4(dx,dy,dz,1);

            translateMat.set_ith_column(0,temp1);
            translateMat.set_ith_column(1,temp2);
            translateMat.set_ith_column(2,temp3);
            translateMat.set_ith_column(3,temp4);


            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;

            T temp = angle*M_PI/180;
            T ux = 1 /  sqrt( x * x + y * y + z * z ) * x  ; //x단위벡터
            T uy = 1 /  sqrt( x * x + y * y + z * z ) * y ; //y단위벡터
            T uz = 1 /  sqrt( x * x + y * y + z * z ) * z ; //z단위벡터

            kmuvcl::math::vec4f temp1(cos(temp)+ux*ux*(1-cos(temp)),uy*ux*(1-cos(temp))+uz*sin(temp),uz*ux*(1-cos(temp))-uy*sin(temp),0);
            kmuvcl::math::vec4f temp2(ux*uy*(1-cos(temp))-uz*sin(temp),cos(temp)+uy*uy*(1-cos(temp)),uz*uy*(1-cos(temp))+ux*sin(temp),0);
            kmuvcl::math::vec4f temp3(ux*uz*(1-cos(temp))+uy*sin(temp),uy*uz*(1-cos(temp))-ux*sin(temp),cos(temp)+uz*uz*(1-cos(temp)),0);
            kmuvcl::math::vec4f temp4(0,0,0,1);

            rotateMat.set_ith_column(0,temp1);
            rotateMat.set_ith_column(1,temp2);
            rotateMat.set_ith_column(2,temp3);
            rotateMat.set_ith_column(3,temp4);

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            kmuvcl::math::vec4f temp1(sx,0,0,0);
            kmuvcl::math::vec4f temp2(0,sy,0,0);
            kmuvcl::math::vec4f temp3(0,0,sz,0);
            kmuvcl::math::vec4f temp4(0,0,0,1);

            scaleMat.set_ith_column(0,temp1);
            scaleMat.set_ith_column(1,temp2);
            scaleMat.set_ith_column(2,temp3);
            scaleMat.set_ith_column(3,temp4);

            return scaleMat;
        }

        template<typename T>
        mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            mat<4, 4, T> viewMat;

            mat<4, 4, T> cam_axis;
            mat<4, 4, T> cam_pos;

            vec<3, T> a;
            vec<3, T> b;
            vec<3, T> res;
            //z축 설정
            cam_axis(0,2) = -(centerX-eyeX)/sqrt( (centerX-eyeX)*(centerX-eyeX)+(centerY-eyeY)*(centerY-eyeY)+(centerZ-eyeZ)*(centerZ-eyeZ) );
            cam_axis(1,2) = -(centerY-eyeY)/sqrt( (centerX-eyeX)*(centerX-eyeX)+(centerY-eyeY)*(centerY-eyeY)+(centerZ-eyeZ)*(centerZ-eyeZ) );
            cam_axis(2,2) = -(centerZ-eyeZ)/sqrt( (centerX-eyeX)*(centerX-eyeX)+(centerY-eyeY)*(centerY-eyeY)+(centerZ-eyeZ)*(centerZ-eyeZ) );
            cam_axis(3,2) = 0;

            //원점
            cam_axis(0,3) = 0;   cam_axis(1,3) = 0; cam_axis(2,3) = 0; cam_axis(3,3) = 1;


            a(0) = cam_axis(0,2); a(1) = cam_axis(1,2); a(2) = cam_axis(2,2); a(3) = cam_axis(3,2); //z축 반환
            b(0) = upX; b(1) = upY; b(2) = upZ;

            res  = cross(b,a);

            cam_axis(0,0) = res(0) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(1,0) = res(1) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(2,0) = res(2) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(3,0) =  0;

            a(0) = cam_axis(0,0); a(1) = cam_axis(1,0); a(2) = cam_axis(2,0); a(3) = cam_axis(3,0); //x축 반환
            b(0) = cam_axis(0,2); b(1) = cam_axis(1,2); b(2) = cam_axis(2,2); b(3) = cam_axis(3,2); //z축 반환

            res = cross(b,a);

            cam_axis(1,0) = res(0) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(1,1) = res(1) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(1,2) = res(2) / sqrt(res(0)*res(0) + res(1)*res(1) + res(2)*res(2) );
            cam_axis(1,3) =  0;

            cam_pos(0,0) = 1; cam_pos(1,0) = 0; cam_pos(2,0) = 0; cam_pos(3,0) = 0;
            cam_pos(0,1) = 0; cam_pos(1,1) = 1; cam_pos(2,1) = 0; cam_pos(3,1) = 0;
            cam_pos(0,2) = 0; cam_pos(1,2) = 0; cam_pos(2,2) = 1; cam_pos(3,2) = 0;
            cam_pos(0,3) = -eyeX; cam_pos(1,3) = -eyeY; cam_pos(2,3) = -eyeZ; cam_pos(3,3) = 1;

            viewMat = cam_axis*cam_pos;

            return viewMat;

        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;

            kmuvcl::math::vec4f temp1(2/(right-left),0,0,0);
            kmuvcl::math::vec4f temp2(0,2/(top-bottom),0,0);
            kmuvcl::math::vec4f temp3(0,0,(-2)/(farVal-nearVal),0);
            kmuvcl::math::vec4f temp4( -(right+left)/(right-left),-(top+bottom)/(top-bottom),-(farVal+nearVal)/(farVal-nearVal),1);

            orthoMat.set_ith_column(0,temp1);
            orthoMat.set_ith_column(1,temp2);
            orthoMat.set_ith_column(2,temp3);
            orthoMat.set_ith_column(3,temp4);

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           frustumMat(0,0) = 2*nearVal/(right-left); frustumMat(1,0) = 0; frustumMat(2,0) = 0; frustumMat(3,0) = 0;

           frustumMat(0,1) = 0; frustumMat(1,1) = 2*nearVal/(top-bottom); frustumMat(2,1) = 0; frustumMat(3,1) = 0;

           frustumMat(0,2) = (right+left)/(right-left); frustumMat(1,2) = (top+bottom)/(top-bottom);
           frustumMat(2,2) = -(farVal+nearVal)/(farVal-nearVal);  frustumMat(3,2) = -1;

           frustumMat(0,3) = 0; frustumMat(1,3) = 0; frustumMat(2,3) = (-2)*farVal*nearVal/(farVal-nearVal);
           frustumMat(3,3) = 0;


           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right, top;
          fovy /= 2;
          fovy = fovy *M_PI / 180;

          top = zNear * tan(fovy);
          right = top * aspect;


          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
