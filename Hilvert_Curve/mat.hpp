#ifndef KMUVCL_GRAPHICS_MAT_HPP
#define KMUVCL_GRAPHICS_MAT_HPP

#include <iostream>
#include <cstring>
#include <cstdarg>
#include "vec.hpp"

namespace kmuvcl {
  namespace math {

    template <unsigned int M, unsigned int N, typename T>
    class mat //배열로 행렬표현
    {
    public:
      mat()
      {
        set_to_zero();
      }

      mat(const T elem)
      {
        std::fill(val, val + M*N, elem);
      }

      T& operator()(unsigned int r, unsigned int c)
      {
        // TODO: Fill up this function properly
        // Notice: The matrix is column major
        return  val[c*M+r];
      }

      const T& operator()(unsigned int r, unsigned int c) const
      {
        // TODO: Fill up this function properly
        // Notice: The matrix is column major
        return  val[c*M+r];
      }

      // type casting operators
      operator const T* () const
      {
        return  val;
      }

      operator T* ()
      {
        return  val;
      }

      void set_to_zero() //0으로 초기화
      {
        // TODO: Fill up this function properly
        for(int i = 0; i < M*N ; i++)
          val[i]=0;
      }

      void get_ith_column(unsigned int i, vec<M, T>& col) const
      {
        // TODO: Fill up this function properly


        for(int j = 0 ; j < M ; j++)
          col(j) = val[i*M+j];

      }

      void set_ith_column(unsigned int i, const vec<M, T>& col)
      {
        // TODO: Fill up this function properly


        for(int j = 0 ; j < M ; j++)
          val[i*M+j] = col(j);

      }

      void get_ith_row(unsigned int i, vec<N, T>& row) const
      {
       // TODO: Fill up this function properly
       for(int j = 0 ; j < N ; j++)
         row(j) = val[M*j+i];

      }

      void set_ith_row(unsigned int i, const vec<N, T>& row)
      {
        // TODO: Fill up this function properly
        for(int j = 0 ; j < N ; j++)
          val[M*j+i] = row(j);

      }

      mat<N, M, T> transpose() const
      {
        // TODO: Fill up this function properly
        mat<N, M, T>  trans;

          vec<M,T> AAA;

          for(int i = 0 ; i < N ; i++){
            this->get_ith_column(i,AAA);
            trans.set_ith_row(i,AAA);
          }


        return  trans;
      }

    protected:
      T val[M*N];   // column major
    };

    typedef mat<3, 3, float>    mat3x3f;
    typedef mat<3, 3, double>   mat3x3d;

    typedef mat<4, 4, float>    mat4x4f;
    typedef mat<4, 4, double>   mat4x4d;

  } // math
} // kmuvcl

#include "operator.hpp"

#endif // #ifndef KMUVCL_GRAPHICS_MAT_HPP
