#ifndef KMUCS_GRAPHICS_VEC_HPP
#define KMUCS_GRAPHICS_VEC_HPP

#include <iostream>
#include <algorithm>

namespace kmuvcl {
  namespace math {

    template <unsigned int N, typename T>
    class vec
    {
    public:
      vec(){
        set_to_zero(); //0으로 초기화
      }

      vec(const T elem){
        for(int i = 0 ; i < N ; i++){
          val[i] = elem;
        }
      }

      vec(const T s, const T t) : vec(){ //2차원 벡터
        // TODO: Fill up this function properly
        val[0] = s; val[1] =t;
      }

      vec(const T s, const T t, const T u) : vec(){ //3차원 벡터
        // TODO: Fill up this function properly
            val[0] = s; val[1] =t; val[2] = u;

      }

      vec(const T s, const T t, const T u, const T v) : vec(){
        // TODO: Fill up this function properly
        val[0] = s; val[1] =t; val[2] = u; val[3] = v;
      }
      /**********************************************************/
      vec(const vec<N, T>& other){
        // TODO: Fill up this function properly
          for(int i = 0 ; i < N ; i++)
            this->val[i] = other.val[i];
      }

      vec& operator= (const vec<N, T>& other){
        // TODO: Fill up this function properly
        for(int i = 0 ; i < N ; i++)
          this->val[i] = other.val[i];

        return  *this;
      }

      T& operator()(unsigned int i){
	      // TODO: Fill up this function properly
        return  val[i];
      }

      const T& operator()(unsigned int i) const{
	      // TODO: Fill up this function properly
        return  val[i];
      }

      // type casting operators
      operator const T* () const{
        return  val;
      }

      operator T* (){
        return  val;
      }

      vec& operator+=(const vec<N, T>& other) {
        // TODO: Fill up this function properly
        for(int i = 0; i < N ; i++)
            this->val[i] += other.val[i];

        return *this;
      }

      vec& operator-=(const vec<N, T>& other)  {
        // TODO: Fill up this function properly
        for(int i = 0; i < N ; i++)
            this->val[i] -= other.val[i];

        return *this;
      }

      void set_to_zero()  {
      for(int i = 0 ; i < N ; i++)
        val[i] = 0;
      }

    protected:
      T val[N];
    };

    // typedef 템플릿 자료형 종류
    typedef vec<2, float>   vec2f;
    typedef vec<2, double>  vec2d;

    typedef vec<3, float>   vec3f;
    typedef vec<3, double>  vec3d;

    typedef vec<4, float>   vec4f;
    typedef vec<4, double>  vec4d;


  } // namespace math
} // namespace kmuvcl


#include "operator.hpp"

#endif // KMUCS_GRAPHICS_VEC_HPP
