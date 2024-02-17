#pragma once

#include "math/plane.h"
#include "math/mat.h"
#include "math/quat.h"

namespace GLEEC::math
{
	template <length_t dim> using bvec   = vec<dim, bool>;
	template <length_t dim> using cvec   = vec<dim, signed char>;
	template <length_t dim> using ucvec  = vec<dim, unsigned char>;
	template <length_t dim> using svec   = vec<dim, short>;
	template <length_t dim> using usvec  = vec<dim, unsigned short>;
	template <length_t dim> using ivec   = vec<dim, int>;
	template <length_t dim> using uvec   = vec<dim, unsigned int>;
	template <length_t dim> using lvec   = vec<dim, long>;
	template <length_t dim> using ulvec  = vec<dim, unsigned long>;
	template <length_t dim> using llvec  = vec<dim, long long>;
	template <length_t dim> using ullvec = vec<dim, unsigned long long>;

	template <length_t dim> using fvec  = vec<dim, float>;
	template <length_t dim> using dvec  = vec<dim, double>;
	template <length_t dim> using ldvec = vec<dim, long double>;

	template <length_t dim> using i8vec  = vec<dim, int8_t>;
	template <length_t dim> using i16vec = vec<dim, int16_t>;
	template <length_t dim> using i32vec = vec<dim, int32_t>;
	template <length_t dim> using i64vec = vec<dim, int64_t>;

	template <length_t dim> using u8vec  = vec<dim, uint8_t>;
	template <length_t dim> using u16vec = vec<dim, uint16_t>;
	template <length_t dim> using u32vec = vec<dim, uint32_t>;
	template <length_t dim> using u64vec = vec<dim, uint64_t>;

	template <length_t dim> using il8vec  = vec<dim, int_least8_t>;
	template <length_t dim> using il16vec = vec<dim, int_least16_t>;
	template <length_t dim> using il32vec = vec<dim, int_least32_t>;
	template <length_t dim> using il64vec = vec<dim, int_least64_t>;

	template <length_t dim> using ul8vec  = vec<dim, uint_least8_t>;
	template <length_t dim> using ul16vec = vec<dim, uint_least16_t>;
	template <length_t dim> using ul32vec = vec<dim, uint_least32_t>;
	template <length_t dim> using ul64vec = vec<dim, uint_least64_t>;

	template <length_t dim> using if8vec  = vec<dim, int_fast8_t>;
	template <length_t dim> using if16vec = vec<dim, int_fast16_t>;
	template <length_t dim> using if32vec = vec<dim, int_fast32_t>;
	template <length_t dim> using if64vec = vec<dim, int_fast64_t>;

	template <length_t dim> using uf8vec  = vec<dim, uint_fast8_t>;
	template <length_t dim> using uf16vec = vec<dim, uint_fast16_t>;
	template <length_t dim> using uf32vec = vec<dim, uint_fast32_t>;
	template <length_t dim> using uf64vec = vec<dim, uint_fast64_t>;

	template <length_t dim> using imaxvec = vec<dim, intmax_t>;
	template <length_t dim> using umaxvec = vec<dim, uintmax_t>;

	using bvec2 = bvec<2>;
	using bvec3 = bvec<3>;
	using bvec4 = bvec<4>;

	using cvec2 = cvec<2>;
	using cvec3 = cvec<3>;
	using cvec4 = cvec<4>;

	using ucvec2 = ucvec<2>;
	using ucvec3 = ucvec<3>;
	using ucvec4 = ucvec<4>;

	using svec2 = svec<2>;
	using svec3 = svec<3>;
	using svec4 = svec<4>;

	using usvec2 = usvec<2>;
	using usvec3 = usvec<3>;
	using usvec4 = usvec<4>;

	using ivec2 = ivec<2>;
	using ivec3 = ivec<3>;
	using ivec4 = ivec<4>;

	using uvec2 = uvec<2>;
	using uvec3 = uvec<3>;
	using uvec4 = uvec<4>;

	using lvec2 = lvec<2>;
	using lvec3 = lvec<3>;
	using lvec4 = lvec<4>;

	using ulvec2 = ulvec<2>;
	using ulvec3 = ulvec<3>;
	using ulvec4 = ulvec<4>;

	using llvec2 = llvec<2>;
	using llvec3 = llvec<3>;
	using llvec4 = llvec<4>;

	using ullvec2 = ullvec<2>;
	using ullvec3 = ullvec<3>;
	using ullvec4 = ullvec<4>;

	using fvec2 = fvec<2>;
	using fvec3 = fvec<3>;
	using fvec4 = fvec<4>;

	using dvec2 = dvec<2>;
	using dvec3 = dvec<3>;
	using dvec4 = dvec<4>;

	using ldvec2 = ldvec<2>;
	using ldvec3 = ldvec<3>;
	using ldvec4 = ldvec<4>;

	using i8vec2 = i8vec<2>;
	using i8vec3 = i8vec<3>;
	using i8vec4 = i8vec<4>;

	using i16vec2 = i16vec<2>;
	using i16vec3 = i16vec<3>;
	using i16vec4 = i16vec<4>;

	using i32vec2 = i32vec<2>;
	using i32vec3 = i32vec<3>;
	using i32vec4 = i32vec<4>;

	using i64vec2 = i64vec<2>;
	using i64vec3 = i64vec<3>;
	using i64vec4 = i64vec<4>;

	using u8vec2 = u8vec<2>;
	using u8vec3 = u8vec<3>;
	using u8vec4 = u8vec<4>;

	using u16vec2 = u16vec<2>;
	using u16vec3 = u16vec<3>;
	using u16vec4 = u16vec<4>;

	using u32vec2 = u32vec<2>;
	using u32vec3 = u32vec<3>;
	using u32vec4 = u32vec<4>;

	using u64vec2 = u64vec<2>;
	using u64vec3 = u64vec<3>;
	using u64vec4 = u64vec<4>;

	using il8vec2 = il8vec<2>;
	using il8vec3 = il8vec<3>;
	using il8vec4 = il8vec<4>;

	using il16vec2 = il16vec<2>;
	using il16vec3 = il16vec<3>;
	using il16vec4 = il16vec<4>;

	using il32vec2 = il32vec<2>;
	using il32vec3 = il32vec<3>;
	using il32vec4 = il32vec<4>;

	using il64vec2 = il64vec<2>;
	using il64vec3 = il64vec<3>;
	using il64vec4 = il64vec<4>;

	using ul8vec2 = ul8vec<2>;
	using ul8vec3 = ul8vec<3>;
	using ul8vec4 = ul8vec<4>;

	using ul16vec2 = ul16vec<2>;
	using ul16vec3 = ul16vec<3>;
	using ul16vec4 = ul16vec<4>;

	using ul32vec2 = ul32vec<2>;
	using ul32vec3 = ul32vec<3>;
	using ul32vec4 = ul32vec<4>;

	using ul64vec2 = ul64vec<2>;
	using ul64vec3 = ul64vec<3>;
	using ul64vec4 = ul64vec<4>;

	using if8vec2 = if8vec<2>;
	using if8vec3 = if8vec<3>;
	using if8vec4 = if8vec<4>;

	using if16vec2 = if16vec<2>;
	using if16vec3 = if16vec<3>;
	using if16vec4 = if16vec<4>;

	using if32vec2 = if32vec<2>;
	using if32vec3 = if32vec<3>;
	using if32vec4 = if32vec<4>;

	using if64vec2 = if64vec<2>;
	using if64vec3 = if64vec<3>;
	using if64vec4 = if64vec<4>;

	using uf8vec2 = uf8vec<2>;
	using uf8vec3 = uf8vec<3>;
	using uf8vec4 = uf8vec<4>;

	using uf16vec2 = uf16vec<2>;
	using uf16vec3 = uf16vec<3>;
	using uf16vec4 = uf16vec<4>;

	using uf32vec2 = uf32vec<2>;
	using uf32vec3 = uf32vec<3>;
	using uf32vec4 = uf32vec<4>;

	using uf64vec2 = uf64vec<2>;
	using uf64vec3 = uf64vec<3>;
	using uf64vec4 = uf64vec<4>;

	using imaxvec2 = imaxvec<2>;
	using imaxvec3 = imaxvec<3>;
	using imaxvec4 = imaxvec<4>;

	using umaxvec2 = umaxvec<2>;
	using umaxvec3 = umaxvec<3>;
	using umaxvec4 = umaxvec<4>;

	using vec2 = vec<2, default_t>;
	using vec3 = vec<3, default_t>;
	using vec4 = vec<4, default_t>;

	using fquat = quaternion<float>;
	using dquat = quaternion<double>;
	using ldquat = quaternion<long double>;

	using quat = quaternion<default_t>;

	template <length_t r, length_t c> using bmat   = matrix<r, c, bool>;
	template <length_t r, length_t c> using cmat   = matrix<r, c, signed char>;
	template <length_t r, length_t c> using ucmat  = matrix<r, c, unsigned char>;
	template <length_t r, length_t c> using smat   = matrix<r, c, short>;
	template <length_t r, length_t c> using usmat  = matrix<r, c, unsigned short>;
	template <length_t r, length_t c> using imat   = matrix<r, c, int>;
	template <length_t r, length_t c> using umat   = matrix<r, c, unsigned int>;
	template <length_t r, length_t c> using lmat   = matrix<r, c, long>;
	template <length_t r, length_t c> using ulmat  = matrix<r, c, unsigned long>;
	template <length_t r, length_t c> using llmat  = matrix<r, c, long long>;
	template <length_t r, length_t c> using ullmat = matrix<r, c, unsigned long long>;

	template <length_t r, length_t c> using fmat  = matrix<r, c, float>;
	template <length_t r, length_t c> using dmat  = matrix<r, c, double>;
	template <length_t r, length_t c> using ldmat = matrix<r, c, long double>;

	template <length_t r, length_t c> using i8mat  = matrix<r, c, int8_t>;
	template <length_t r, length_t c> using i16mat = matrix<r, c, int16_t>;
	template <length_t r, length_t c> using i32mat = matrix<r, c, int32_t>;
	template <length_t r, length_t c> using i64mat = matrix<r, c, int64_t>;

	template <length_t r, length_t c> using u8mat  = matrix<r, c, uint8_t>;
	template <length_t r, length_t c> using u16mat = matrix<r, c, uint16_t>;
	template <length_t r, length_t c> using u32mat = matrix<r, c, uint32_t>;
	template <length_t r, length_t c> using u64mat = matrix<r, c, uint64_t>;

	template <length_t r, length_t c> using il8mat  = matrix<r, c, int_least8_t>;
	template <length_t r, length_t c> using il16mat = matrix<r, c, int_least16_t>;
	template <length_t r, length_t c> using il32mat = matrix<r, c, int_least32_t>;
	template <length_t r, length_t c> using il64mat = matrix<r, c, int_least64_t>;

	template <length_t r, length_t c> using ul8mat  = matrix<r, c, uint_least8_t>;
	template <length_t r, length_t c> using ul16mat = matrix<r, c, uint_least16_t>;
	template <length_t r, length_t c> using ul32mat = matrix<r, c, uint_least32_t>;
	template <length_t r, length_t c> using ul64mat = matrix<r, c, uint_least64_t>;

	template <length_t r, length_t c> using if8mat  = matrix<r, c, int_fast8_t>;
	template <length_t r, length_t c> using if16mat = matrix<r, c, int_fast16_t>;
	template <length_t r, length_t c> using if32mat = matrix<r, c, int_fast32_t>;
	template <length_t r, length_t c> using if64mat = matrix<r, c, int_fast64_t>;

	template <length_t r, length_t c> using uf8mat  = matrix<r, c, uint_fast8_t>;
	template <length_t r, length_t c> using uf16mat = matrix<r, c, uint_fast16_t>;
	template <length_t r, length_t c> using uf32mat = matrix<r, c, uint_fast32_t>;
	template <length_t r, length_t c> using uf64mat = matrix<r, c, uint_fast64_t>;
	
	template <length_t r, length_t c> using imaxmat = matrix<r, c, intmax_t>;
	template <length_t r, length_t c> using umaxmat = matrix<r, c, uintmax_t>;

	using bmat1x1 = bmat<1, 1>;
	using bmat1   = bmat<1, 1>;
	using bmat1x2 = bmat<1, 2>;
	using bmat1x3 = bmat<1, 3>;
	using bmat1x4 = bmat<1, 4>;

	using bmat2x1 = bmat<2, 1>;
	using bmat2x2 = bmat<2, 2>;
	using bmat2   = bmat<2, 2>;
	using bmat2x3 = bmat<2, 3>;
	using bmat2x4 = bmat<2, 4>;

	using bmat3x1 = bmat<3, 1>;
	using bmat3x2 = bmat<3, 2>;
	using bmat3x3 = bmat<3, 3>;
	using bmat3   = bmat<3, 3>;
	using bmat3x4 = bmat<3, 4>;

	using bmat4x1 = bmat<4, 1>;
	using bmat4x2 = bmat<4, 2>;
	using bmat4x3 = bmat<4, 3>;
	using bmat4x4 = bmat<4, 4>;
	using bmat4   = bmat<4, 4>;

	using cmat1x1 = cmat<1, 1>;
	using cmat1   = cmat<1, 1>;
	using cmat1x2 = cmat<1, 2>;
	using cmat1x3 = cmat<1, 3>;
	using cmat1x4 = cmat<1, 4>;

	using cmat2x1 = cmat<2, 1>;
	using cmat2x2 = cmat<2, 2>;
	using cmat2   = cmat<2, 2>;
	using cmat2x3 = cmat<2, 3>;
	using cmat2x4 = cmat<2, 4>;

	using cmat3x1 = cmat<3, 1>;
	using cmat3x2 = cmat<3, 2>;
	using cmat3x3 = cmat<3, 3>;
	using cmat3   = cmat<3, 3>;
	using cmat3x4 = cmat<3, 4>;

	using cmat4x1 = cmat<4, 1>;
	using cmat4x2 = cmat<4, 2>;
	using cmat4x3 = cmat<4, 3>;
	using cmat4x4 = cmat<4, 4>;
	using cmat4   = cmat<4, 4>;

	using ucmat1x1 = ucmat<1, 1>;
	using ucmat1   = ucmat<1, 1>;
	using ucmat1x2 = ucmat<1, 2>;
	using ucmat1x3 = ucmat<1, 3>;
	using ucmat1x4 = ucmat<1, 4>;

	using ucmat2x1 = ucmat<2, 1>;
	using ucmat2x2 = ucmat<2, 2>;
	using ucmat2   = ucmat<2, 2>;
	using ucmat2x3 = ucmat<2, 3>;
	using ucmat2x4 = ucmat<2, 4>;

	using ucmat3x1 = ucmat<3, 1>;
	using ucmat3x2 = ucmat<3, 2>;
	using ucmat3x3 = ucmat<3, 3>;
	using ucmat3   = ucmat<3, 3>;
	using ucmat3x4 = ucmat<3, 4>;

	using ucmat4x1 = ucmat<4, 1>;
	using ucmat4x2 = ucmat<4, 2>;
	using ucmat4x3 = ucmat<4, 3>;
	using ucmat4x4 = ucmat<4, 4>;
	using ucmat4   = ucmat<4, 4>;

	using smat1x1 = smat<1, 1>;
	using smat1   = smat<1, 1>;
	using smat1x2 = smat<1, 2>;
	using smat1x3 = smat<1, 3>;
	using smat1x4 = smat<1, 4>;

	using smat2x1 = smat<2, 1>;
	using smat2x2 = smat<2, 2>;
	using smat2   = smat<2, 2>;
	using smat2x3 = smat<2, 3>;
	using smat2x4 = smat<2, 4>;

	using smat3x1 = smat<3, 1>;
	using smat3x2 = smat<3, 2>;
	using smat3x3 = smat<3, 3>;
	using smat3   = smat<3, 3>;
	using smat3x4 = smat<3, 4>;

	using smat4x1 = smat<4, 1>;
	using smat4x2 = smat<4, 2>;
	using smat4x3 = smat<4, 3>;
	using smat4x4 = smat<4, 4>;
	using smat4   = smat<4, 4>;

	using usmat1x1 = usmat<1, 1>;
	using usmat1   = usmat<1, 1>;
	using usmat1x2 = usmat<1, 2>;
	using usmat1x3 = usmat<1, 3>;
	using usmat1x4 = usmat<1, 4>;

	using usmat2x1 = usmat<2, 1>;
	using usmat2x2 = usmat<2, 2>;
	using usmat2   = usmat<2, 2>;
	using usmat2x3 = usmat<2, 3>;
	using usmat2x4 = usmat<2, 4>;

	using usmat3x1 = usmat<3, 1>;
	using usmat3x2 = usmat<3, 2>;
	using usmat3x3 = usmat<3, 3>;
	using usmat3   = usmat<3, 3>;
	using usmat3x4 = usmat<3, 4>;

	using usmat4x1 = usmat<4, 1>;
	using usmat4x2 = usmat<4, 2>;
	using usmat4x3 = usmat<4, 3>;
	using usmat4x4 = usmat<4, 4>;
	using usmat4   = usmat<4, 4>;

	using imat1x1 = imat<1, 1>;
	using imat1   = imat<1, 1>;
	using imat1x2 = imat<1, 2>;
	using imat1x3 = imat<1, 3>;
	using imat1x4 = imat<1, 4>;

	using imat2x1 = imat<2, 1>;
	using imat2x2 = imat<2, 2>;
	using imat2   = imat<2, 2>;
	using imat2x3 = imat<2, 3>;
	using imat2x4 = imat<2, 4>;

	using imat3x1 = imat<3, 1>;
	using imat3x2 = imat<3, 2>;
	using imat3x3 = imat<3, 3>;
	using imat3   = imat<3, 3>;
	using imat3x4 = imat<3, 4>;

	using imat4x1 = imat<4, 1>;
	using imat4x2 = imat<4, 2>;
	using imat4x3 = imat<4, 3>;
	using imat4x4 = imat<4, 4>;
	using imat4   = imat<4, 4>;

	using umat1x1 = umat<1, 1>;
	using umat1   = umat<1, 1>;
	using umat1x2 = umat<1, 2>;
	using umat1x3 = umat<1, 3>;
	using umat1x4 = umat<1, 4>;

	using umat2x1 = umat<2, 1>;
	using umat2x2 = umat<2, 2>;
	using umat2   = umat<2, 2>;
	using umat2x3 = umat<2, 3>;
	using umat2x4 = umat<2, 4>;

	using umat3x1 = umat<3, 1>;
	using umat3x2 = umat<3, 2>;
	using umat3x3 = umat<3, 3>;
	using umat3   = umat<3, 3>;
	using umat3x4 = umat<3, 4>;

	using umat4x1 = umat<4, 1>;
	using umat4x2 = umat<4, 2>;
	using umat4x3 = umat<4, 3>;
	using umat4x4 = umat<4, 4>;
	using umat4   = umat<4, 4>;

	using lmat1x1 = lmat<1, 1>;
	using lmat1   = lmat<1, 1>;
	using lmat1x2 = lmat<1, 2>;
	using lmat1x3 = lmat<1, 3>;
	using lmat1x4 = lmat<1, 4>;

	using lmat2x1 = lmat<2, 1>;
	using lmat2x2 = lmat<2, 2>;
	using lmat2   = lmat<2, 2>;
	using lmat2x3 = lmat<2, 3>;
	using lmat2x4 = lmat<2, 4>;

	using lmat3x1 = lmat<3, 1>;
	using lmat3x2 = lmat<3, 2>;
	using lmat3x3 = lmat<3, 3>;
	using lmat3   = lmat<3, 3>;
	using lmat3x4 = lmat<3, 4>;

	using lmat4x1 = lmat<4, 1>;
	using lmat4x2 = lmat<4, 2>;
	using lmat4x3 = lmat<4, 3>;
	using lmat4x4 = lmat<4, 4>;
	using lmat4   = lmat<4, 4>;

	using ulmat1x1 = ulmat<1, 1>;
	using ulmat1   = ulmat<1, 1>;
	using ulmat1x2 = ulmat<1, 2>;
	using ulmat1x3 = ulmat<1, 3>;
	using ulmat1x4 = ulmat<1, 4>;

	using ulmat2x1 = ulmat<2, 1>;
	using ulmat2x2 = ulmat<2, 2>;
	using ulmat2   = ulmat<2, 2>;
	using ulmat2x3 = ulmat<2, 3>;
	using ulmat2x4 = ulmat<2, 4>;

	using ulmat3x1 = ulmat<3, 1>;
	using ulmat3x2 = ulmat<3, 2>;
	using ulmat3x3 = ulmat<3, 3>;
	using ulmat3   = ulmat<3, 3>;
	using ulmat3x4 = ulmat<3, 4>;

	using ulmat4x1 = ulmat<4, 1>;
	using ulmat4x2 = ulmat<4, 2>;
	using ulmat4x3 = ulmat<4, 3>;
	using ulmat4x4 = ulmat<4, 4>;
	using ulmat4   = ulmat<4, 4>;

	using llmat1x1 = llmat<1, 1>;
	using llmat1   = llmat<1, 1>;
	using llmat1x2 = llmat<1, 2>;
	using llmat1x3 = llmat<1, 3>;
	using llmat1x4 = llmat<1, 4>;

	using llmat2x1 = llmat<2, 1>;
	using llmat2x2 = llmat<2, 2>;
	using llmat2   = llmat<2, 2>;
	using llmat2x3 = llmat<2, 3>;
	using llmat2x4 = llmat<2, 4>;

	using llmat3x1 = llmat<3, 1>;
	using llmat3x2 = llmat<3, 2>;
	using llmat3x3 = llmat<3, 3>;
	using llmat3   = llmat<3, 3>;
	using llmat3x4 = llmat<3, 4>;

	using llmat4x1 = llmat<4, 1>;
	using llmat4x2 = llmat<4, 2>;
	using llmat4x3 = llmat<4, 3>;
	using llmat4x4 = llmat<4, 4>;
	using llmat4   = llmat<4, 4>;

	using ullmat1x1 = ullmat<1, 1>;
	using ullmat1   = ullmat<1, 1>;
	using ullmat1x2 = ullmat<1, 2>;
	using ullmat1x3 = ullmat<1, 3>;
	using ullmat1x4 = ullmat<1, 4>;

	using ullmat2x1 = ullmat<2, 1>;
	using ullmat2x2 = ullmat<2, 2>;
	using ullmat2   = ullmat<2, 2>;
	using ullmat2x3 = ullmat<2, 3>;
	using ullmat2x4 = ullmat<2, 4>;

	using ullmat3x1 = ullmat<3, 1>;
	using ullmat3x2 = ullmat<3, 2>;
	using ullmat3x3 = ullmat<3, 3>;
	using ullmat3   = ullmat<3, 3>;
	using ullmat3x4 = ullmat<3, 4>;

	using ullmat4x1 = ullmat<4, 1>;
	using ullmat4x2 = ullmat<4, 2>;
	using ullmat4x3 = ullmat<4, 3>;
	using ullmat4x4 = ullmat<4, 4>;
	using ullmat4   = ullmat<4, 4>;

	using fmat1x1 = fmat<1, 1>;
	using fmat1   = fmat<1, 1>;
	using fmat1x2 = fmat<1, 2>;
	using fmat1x3 = fmat<1, 3>;
	using fmat1x4 = fmat<1, 4>;

	using fmat2x1 = fmat<2, 1>;
	using fmat2x2 = fmat<2, 2>;
	using fmat2   = fmat<2, 2>;
	using fmat2x3 = fmat<2, 3>;
	using fmat2x4 = fmat<2, 4>;

	using fmat3x1 = fmat<3, 1>;
	using fmat3x2 = fmat<3, 2>;
	using fmat3x3 = fmat<3, 3>;
	using fmat3   = fmat<3, 3>;
	using fmat3x4 = fmat<3, 4>;

	using fmat4x1 = fmat<4, 1>;
	using fmat4x2 = fmat<4, 2>;
	using fmat4x3 = fmat<4, 3>;
	using fmat4x4 = fmat<4, 4>;
	using fmat4   = fmat<4, 4>;

	using dmat1x1 = dmat<1, 1>;
	using dmat1   = dmat<1, 1>;
	using dmat1x2 = dmat<1, 2>;
	using dmat1x3 = dmat<1, 3>;
	using dmat1x4 = dmat<1, 4>;

	using dmat2x1 = dmat<2, 1>;
	using dmat2x2 = dmat<2, 2>;
	using dmat2   = dmat<2, 2>;
	using dmat2x3 = dmat<2, 3>;
	using dmat2x4 = dmat<2, 4>;

	using dmat3x1 = dmat<3, 1>;
	using dmat3x2 = dmat<3, 2>;
	using dmat3x3 = dmat<3, 3>;
	using dmat3   = dmat<3, 3>;
	using dmat3x4 = dmat<3, 4>;

	using dmat4x1 = dmat<4, 1>;
	using dmat4x2 = dmat<4, 2>;
	using dmat4x3 = dmat<4, 3>;
	using dmat4x4 = dmat<4, 4>;
	using dmat4   = dmat<4, 4>;

	using ldmat1x1 = ldmat<1, 1>;
	using ldmat1   = ldmat<1, 1>;
	using ldmat1x2 = ldmat<1, 2>;
	using ldmat1x3 = ldmat<1, 3>;
	using ldmat1x4 = ldmat<1, 4>;

	using ldmat2x1 = ldmat<2, 1>;
	using ldmat2x2 = ldmat<2, 2>;
	using ldmat2   = ldmat<2, 2>;
	using ldmat2x3 = ldmat<2, 3>;
	using ldmat2x4 = ldmat<2, 4>;

	using ldmat3x1 = ldmat<3, 1>;
	using ldmat3x2 = ldmat<3, 2>;
	using ldmat3x3 = ldmat<3, 3>;
	using ldmat3   = ldmat<3, 3>;
	using ldmat3x4 = ldmat<3, 4>;

	using ldmat4x1 = ldmat<4, 1>;
	using ldmat4x2 = ldmat<4, 2>;
	using ldmat4x3 = ldmat<4, 3>;
	using ldmat4x4 = ldmat<4, 4>;
	using ldmat4   = ldmat<4, 4>;

	using i8mat1x1 = i8mat<1, 1>;
	using i8mat1   = i8mat<1, 1>;
	using i8mat1x2 = i8mat<1, 2>;
	using i8mat1x3 = i8mat<1, 3>;
	using i8mat1x4 = i8mat<1, 4>;

	using i8mat2x1 = i8mat<2, 1>;
	using i8mat2   = i8mat<2, 2>;
	using i8mat2x3 = i8mat<2, 3>;
	using i8mat2x4 = i8mat<2, 4>;

	using i8mat3x1 = i8mat<3, 1>;
	using i8mat3x2 = i8mat<3, 2>;
	using i8mat3   = i8mat<3, 3>;
	using i8mat3x4 = i8mat<3, 4>;

	using i8mat4x1 = i8mat<4, 1>;
	using i8mat4x2 = i8mat<4, 2>;
	using i8mat4x3 = i8mat<4, 3>;
	using i8mat4   = i8mat<4, 4>;

	using i16mat1x1 = i16mat<1, 1>;
	using i16mat1   = i16mat<1, 1>;
	using i16mat1x2 = i16mat<1, 2>;
	using i16mat1x3 = i16mat<1, 3>;
	using i16mat1x4 = i16mat<1, 4>;

	using i16mat2x1 = i16mat<2, 1>;
	using i16mat2x2 = i16mat<2, 2>;
	using i16mat2   = i16mat<2, 2>;
	using i16mat2x3 = i16mat<2, 3>;
	using i16mat2x4 = i16mat<2, 4>;

	using i16mat3x1 = i16mat<3, 1>;
	using i16mat3x2 = i16mat<3, 2>;
	using i16mat3x3 = i16mat<3, 3>;
	using i16mat3   = i16mat<3, 3>;
	using i16mat3x4 = i16mat<3, 4>;

	using i16mat4x1 = i16mat<4, 1>;
	using i16mat4x2 = i16mat<4, 2>;
	using i16mat4x3 = i16mat<4, 3>;
	using i16mat4x4 = i16mat<4, 4>;
	using i16mat4   = i16mat<4, 4>;

	using i32mat1x1 = i32mat<1, 1>;
	using i32mat1   = i32mat<1, 1>;
	using i32mat1x2 = i32mat<1, 2>;
	using i32mat1x3 = i32mat<1, 3>;
	using i32mat1x4 = i32mat<1, 4>;

	using i32mat2x1 = i32mat<2, 1>;
	using i32mat2x2 = i32mat<2, 2>;
	using i32mat2   = i32mat<2, 2>;
	using i32mat2x3 = i32mat<2, 3>;
	using i32mat2x4 = i32mat<2, 4>;

	using i32mat3x1 = i32mat<3, 1>;
	using i32mat3x2 = i32mat<3, 2>;
	using i32mat3x3 = i32mat<3, 3>;
	using i32mat3   = i32mat<3, 3>;
	using i32mat3x4 = i32mat<3, 4>;

	using i32mat4x1 = i32mat<4, 1>;
	using i32mat4x2 = i32mat<4, 2>;
	using i32mat4x3 = i32mat<4, 3>;
	using i32mat4x4 = i32mat<4, 4>;
	using i32mat4   = i32mat<4, 4>;

	using i64mat1x1 = i64mat<1, 1>;
	using i64mat1   = i64mat<1, 1>;
	using i64mat1x2 = i64mat<1, 2>;
	using i64mat1x3 = i64mat<1, 3>;
	using i64mat1x4 = i64mat<1, 4>;

	using i64mat2x1 = i64mat<2, 1>;
	using i64mat2x2 = i64mat<2, 2>;
	using i64mat2   = i64mat<2, 2>;
	using i64mat2x3 = i64mat<2, 3>;
	using i64mat2x4 = i64mat<2, 4>;

	using i64mat3x1 = i64mat<3, 1>;
	using i64mat3x2 = i64mat<3, 2>;
	using i64mat3x3 = i64mat<3, 3>;
	using i64mat3   = i64mat<3, 3>;
	using i64mat3x4 = i64mat<3, 4>;

	using i64mat4x1 = i64mat<4, 1>;
	using i64mat4x2 = i64mat<4, 2>;
	using i64mat4x3 = i64mat<4, 3>;
	using i64mat4x4 = i64mat<4, 4>;
	using i64mat4   = i64mat<4, 4>;

	using u8mat1x1 = u8mat<1, 1>;
	using u8mat1   = u8mat<1, 1>;
	using u8mat1x2 = u8mat<1, 2>;
	using u8mat1x3 = u8mat<1, 3>;
	using u8mat1x4 = u8mat<1, 4>;

	using u8mat2x1 = u8mat<2, 1>;
	using u8mat2x2 = u8mat<2, 2>;
	using u8mat2   = u8mat<2, 2>;
	using u8mat2x3 = u8mat<2, 3>;
	using u8mat2x4 = u8mat<2, 4>;

	using u8mat3x1 = u8mat<3, 1>;
	using u8mat3x2 = u8mat<3, 2>;
	using u8mat3x3 = u8mat<3, 3>;
	using u8mat3   = u8mat<3, 3>;
	using u8mat3x4 = u8mat<3, 4>;

	using u8mat4x1 = u8mat<4, 1>;
	using u8mat4x2 = u8mat<4, 2>;
	using u8mat4x3 = u8mat<4, 3>;
	using u8mat4x4 = u8mat<4, 4>;
	using u8mat4   = u8mat<4, 4>;

	using u16mat1x1 = u16mat<1, 1>;
	using u16mat1   = u16mat<1, 1>;
	using u16mat1x2 = u16mat<1, 2>;
	using u16mat1x3 = u16mat<1, 3>;
	using u16mat1x4 = u16mat<1, 4>;

	using u16mat2x1 = u16mat<2, 1>;
	using u16mat2x2 = u16mat<2, 2>;
	using u16mat2   = u16mat<2, 2>;
	using u16mat2x3 = u16mat<2, 3>;
	using u16mat2x4 = u16mat<2, 4>;

	using u16mat3x1 = u16mat<3, 1>;
	using u16mat3x2 = u16mat<3, 2>;
	using u16mat3x3 = u16mat<3, 3>;
	using u16mat3   = u16mat<3, 3>;
	using u16mat3x4 = u16mat<3, 4>;

	using u16mat4x1 = u16mat<4, 1>;
	using u16mat4x2 = u16mat<4, 2>;
	using u16mat4x3 = u16mat<4, 3>;
	using u16mat4x4 = u16mat<4, 4>;
	using u16mat4   = u16mat<4, 4>;

	using u32mat1x1 = u32mat<1, 1>;
	using u32mat1   = u32mat<1, 1>;
	using u32mat1x2 = u32mat<1, 2>;
	using u32mat1x3 = u32mat<1, 3>;
	using u32mat1x4 = u32mat<1, 4>;

	using u32mat2x1 = u32mat<2, 1>;
	using u32mat2x2 = u32mat<2, 2>;
	using u32mat2   = u32mat<2, 2>;
	using u32mat2x3 = u32mat<2, 3>;
	using u32mat2x4 = u32mat<2, 4>;

	using u32mat3x1 = u32mat<3, 1>;
	using u32mat3x2 = u32mat<3, 2>;
	using u32mat3x3 = u32mat<3, 3>;
	using u32mat3   = u32mat<3, 3>;
	using u32mat3x4 = u32mat<3, 4>;

	using u32mat4x1 = u32mat<4, 1>;
	using u32mat4x2 = u32mat<4, 2>;
	using u32mat4x3 = u32mat<4, 3>;
	using u32mat4x4 = u32mat<4, 4>;
	using u32mat4   = u32mat<4, 4>;

	using u64mat1x1 = u64mat<1, 1>;
	using u64mat1   = u64mat<1, 1>;
	using u64mat1x2 = u64mat<1, 2>;
	using u64mat1x3 = u64mat<1, 3>;
	using u64mat1x4 = u64mat<1, 4>;

	using u64mat2x1 = u64mat<2, 1>;
	using u64mat2x2 = u64mat<2, 2>;
	using u64mat2   = u64mat<2, 2>;
	using u64mat2x3 = u64mat<2, 3>;
	using u64mat2x4 = u64mat<2, 4>;

	using u64mat3x1 = u64mat<3, 1>;
	using u64mat3x2 = u64mat<3, 2>;
	using u64mat3x3 = u64mat<3, 3>;
	using u64mat3   = u64mat<3, 3>;
	using u64mat3x4 = u64mat<3, 4>;

	using u64mat4x1 = u64mat<4, 1>;
	using u64mat4x2 = u64mat<4, 2>;
	using u64mat4x3 = u64mat<4, 3>;
	using u64mat4x4 = u64mat<4, 4>;
	using u64mat4   = u64mat<4, 4>;

	using il8mat1x1 = il8mat<1, 1>;
	using il8mat1   = il8mat<1, 1>;
	using il8mat1x2 = il8mat<1, 2>;
	using il8mat1x3 = il8mat<1, 3>;
	using il8mat1x4 = il8mat<1, 4>;

	using il8mat2x1 = il8mat<2, 1>;
	using il8mat2x2 = il8mat<2, 2>;
	using il8mat2   = il8mat<2, 2>;
	using il8mat2x3 = il8mat<2, 3>;
	using il8mat2x4 = il8mat<2, 4>;

	using il8mat3x1 = il8mat<3, 1>;
	using il8mat3x2 = il8mat<3, 2>;
	using il8mat3x3 = il8mat<3, 3>;
	using il8mat3   = il8mat<3, 3>;
	using il8mat3x4 = il8mat<3, 4>;

	using il8mat4x1 = il8mat<4, 1>;
	using il8mat4x2 = il8mat<4, 2>;
	using il8mat4x3 = il8mat<4, 3>;
	using il8mat4x4 = il8mat<4, 4>;
	using il8mat4   = il8mat<4, 4>;

	using il16mat1x1 = il16mat<1, 1>;
	using il16mat1   = il16mat<1, 1>;
	using il16mat1x2 = il16mat<1, 2>;
	using il16mat1x3 = il16mat<1, 3>;
	using il16mat1x4 = il16mat<1, 4>;

	using il16mat2x1 = il16mat<2, 1>;
	using il16mat2x2 = il16mat<2, 2>;
	using il16mat2   = il16mat<2, 2>;
	using il16mat2x3 = il16mat<2, 3>;
	using il16mat2x4 = il16mat<2, 4>;

	using il16mat3x1 = il16mat<3, 1>;
	using il16mat3x2 = il16mat<3, 2>;
	using il16mat3x3 = il16mat<3, 3>;
	using il16mat3   = il16mat<3, 3>;
	using il16mat3x4 = il16mat<3, 4>;

	using il16mat4x1 = il16mat<4, 1>;
	using il16mat4x2 = il16mat<4, 2>;
	using il16mat4x3 = il16mat<4, 3>;
	using il16mat4x4 = il16mat<4, 4>;
	using il16mat4   = il16mat<4, 4>;

	using il32mat1x1 = il32mat<1, 1>;
	using il32mat1   = il32mat<1, 1>;
	using il32mat1x2 = il32mat<1, 2>;
	using il32mat1x3 = il32mat<1, 3>;
	using il32mat1x4 = il32mat<1, 4>;

	using il32mat2x1 = il32mat<2, 1>;
	using il32mat2x2 = il32mat<2, 2>;
	using il32mat2   = il32mat<2, 2>;
	using il32mat2x3 = il32mat<2, 3>;
	using il32mat2x4 = il32mat<2, 4>;

	using il32mat3x1 = il32mat<3, 1>;
	using il32mat3x2 = il32mat<3, 2>;
	using il32mat3x3 = il32mat<3, 3>;
	using il32mat3   = il32mat<3, 3>;
	using il32mat3x4 = il32mat<3, 4>;

	using il32mat4x1 = il32mat<4, 1>;
	using il32mat4x2 = il32mat<4, 2>;
	using il32mat4x3 = il32mat<4, 3>;
	using il32mat4x4 = il32mat<4, 4>;
	using il32mat4   = il32mat<4, 4>;

	using il64mat1   = il64mat<1, 1>;
	using il64mat1x2 = il64mat<1, 2>;
	using il64mat1x3 = il64mat<1, 3>;
	using il64mat1x4 = il64mat<1, 4>;

	using il64mat2x1 = il64mat<2, 1>;
	using il64mat2x2 = il64mat<2, 2>;
	using il64mat2   = il64mat<2, 2>;
	using il64mat2x3 = il64mat<2, 3>;
	using il64mat2x4 = il64mat<2, 4>;

	using il64mat3x1 = il64mat<3, 1>;
	using il64mat3x2 = il64mat<3, 2>;
	using il64mat3x3 = il64mat<3, 3>;
	using il64mat3   = il64mat<3, 3>;
	using il64mat3x4 = il64mat<3, 4>;

	using il64mat4x1 = il64mat<4, 1>;
	using il64mat4x2 = il64mat<4, 2>;
	using il64mat4x3 = il64mat<4, 3>;
	using il64mat4x4 = il64mat<4, 4>;
	using il64mat4   = il64mat<4, 4>;

	using ul8mat1x1 = ul8mat<1, 1>;
	using ul8mat1   = ul8mat<1, 1>;
	using ul8mat1x2 = ul8mat<1, 2>;
	using ul8mat1x3 = ul8mat<1, 3>;
	using ul8mat1x4 = ul8mat<1, 4>;

	using ul8mat2x1 = ul8mat<2, 1>;
	using ul8mat2x2 = ul8mat<2, 2>;
	using ul8mat2   = ul8mat<2, 2>;
	using ul8mat2x3 = ul8mat<2, 3>;
	using ul8mat2x4 = ul8mat<2, 4>;

	using ul8mat3x1 = ul8mat<3, 1>;
	using ul8mat3x2 = ul8mat<3, 2>;
	using ul8mat3x3 = ul8mat<3, 3>;
	using ul8mat3   = ul8mat<3, 3>;
	using ul8mat3x4 = ul8mat<3, 4>;

	using ul8mat4x1 = ul8mat<4, 1>;
	using ul8mat4x2 = ul8mat<4, 2>;
	using ul8mat4x3 = ul8mat<4, 3>;
	using ul8mat4x4 = ul8mat<4, 4>;
	using ul8mat4   = ul8mat<4, 4>;

	using ul16mat1x1 = ul16mat<1, 1>;
	using ul16mat1   = ul16mat<1, 1>;
	using ul16mat1x2 = ul16mat<1, 2>;
	using ul16mat1x3 = ul16mat<1, 3>;
	using ul16mat1x4 = ul16mat<1, 4>;

	using ul16mat2x1 = ul16mat<2, 1>;
	using ul16mat2x2 = ul16mat<2, 2>;
	using ul16mat2   = ul16mat<2, 2>;
	using ul16mat2x3 = ul16mat<2, 3>;
	using ul16mat2x4 = ul16mat<2, 4>;

	using ul16mat3x1 = ul16mat<3, 1>;
	using ul16mat3x2 = ul16mat<3, 2>;
	using ul16mat3x3 = ul16mat<3, 3>;
	using ul16mat3   = ul16mat<3, 3>;
	using ul16mat3x4 = ul16mat<3, 4>;

	using ul16mat4x1 = ul16mat<4, 1>;
	using ul16mat4x2 = ul16mat<4, 2>;
	using ul16mat4x3 = ul16mat<4, 3>;
	using ul16mat4x4 = ul16mat<4, 4>;
	using ul16mat4   = ul16mat<4, 4>;

	using ul32mat1x1 = ul32mat<1, 1>;
	using ul32mat1   = ul32mat<1, 1>;
	using ul32mat1x2 = ul32mat<1, 2>;
	using ul32mat1x3 = ul32mat<1, 3>;
	using ul32mat1x4 = ul32mat<1, 4>;

	using ul32mat2x1 = ul32mat<2, 1>;
	using ul32mat2x2 = ul32mat<2, 2>;
	using ul32mat2   = ul32mat<2, 2>;
	using ul32mat2x3 = ul32mat<2, 3>;
	using ul32mat2x4 = ul32mat<2, 4>;

	using ul32mat3x1 = ul32mat<3, 1>;
	using ul32mat3x2 = ul32mat<3, 2>;
	using ul32mat3x3 = ul32mat<3, 3>;
	using ul32mat3   = ul32mat<3, 3>;
	using ul32mat3x4 = ul32mat<3, 4>;

	using ul32mat4x1 = ul32mat<4, 1>;
	using ul32mat4x2 = ul32mat<4, 2>;
	using ul32mat4x3 = ul32mat<4, 3>;
	using ul32mat4x4 = ul32mat<4, 4>;
	using ul32mat4   = ul32mat<4, 4>;

	using ul64mat1x1 = ul64mat<1, 1>;
	using ul64mat1   = ul64mat<1, 1>;
	using ul64mat1x2 = ul64mat<1, 2>;
	using ul64mat1x3 = ul64mat<1, 3>;
	using ul64mat1x4 = ul64mat<1, 4>;

	using ul64mat2x1 = ul64mat<2, 1>;
	using ul64mat2x2 = ul64mat<2, 2>;
	using ul64mat2   = ul64mat<2, 2>;
	using ul64mat2x3 = ul64mat<2, 3>;
	using ul64mat2x4 = ul64mat<2, 4>;

	using ul64mat3x1 = ul64mat<3, 1>;
	using ul64mat3x2 = ul64mat<3, 2>;
	using ul64mat3x3 = ul64mat<3, 3>;
	using ul64mat3   = ul64mat<3, 3>;
	using ul64mat3x4 = ul64mat<3, 4>;

	using ul64mat4x1 = ul64mat<4, 1>;
	using ul64mat4x2 = ul64mat<4, 2>;
	using ul64mat4x3 = ul64mat<4, 3>;
	using ul64mat4x4 = ul64mat<4, 4>;
	using ul64mat4   = ul64mat<4, 4>;

	using if8mat1x1 = if8mat<1, 1>;
	using if8mat1   = if8mat<1, 1>;
	using if8mat1x2 = if8mat<1, 2>;
	using if8mat1x3 = if8mat<1, 3>;
	using if8mat1x4 = if8mat<1, 4>;

	using if8mat2x1 = if8mat<2, 1>;
	using if8mat2x2 = if8mat<2, 2>;
	using if8mat2   = if8mat<2, 2>;
	using if8mat2x3 = if8mat<2, 3>;
	using if8mat2x4 = if8mat<2, 4>;

	using if8mat3x1 = if8mat<3, 1>;
	using if8mat3x2 = if8mat<3, 2>;
	using if8mat3x3 = if8mat<3, 3>;
	using if8mat3   = if8mat<3, 3>;
	using if8mat3x4 = if8mat<3, 4>;

	using if8mat4x1 = if8mat<4, 1>;
	using if8mat4x2 = if8mat<4, 2>;
	using if8mat4x3 = if8mat<4, 3>;
	using if8mat4x4 = if8mat<4, 4>;
	using if8mat4   = if8mat<4, 4>;

	using if16mat1x1 = if16mat<1, 1>;
	using if16mat1   = if16mat<1, 1>;
	using if16mat1x2 = if16mat<1, 2>;
	using if16mat1x3 = if16mat<1, 3>;
	using if16mat1x4 = if16mat<1, 4>;

	using if16mat2x1 = if16mat<2, 1>;
	using if16mat2x2 = if16mat<2, 2>;
	using if16mat2   = if16mat<2, 2>;
	using if16mat2x3 = if16mat<2, 3>;
	using if16mat2x4 = if16mat<2, 4>;

	using if16mat3x1 = if16mat<3, 1>;
	using if16mat3x2 = if16mat<3, 2>;
	using if16mat3x3 = if16mat<3, 3>;
	using if16mat3   = if16mat<3, 3>;
	using if16mat3x4 = if16mat<3, 4>;

	using if16mat4x1 = if16mat<4, 1>;
	using if16mat4x2 = if16mat<4, 2>;
	using if16mat4x3 = if16mat<4, 3>;
	using if16mat4x4 = if16mat<4, 4>;
	using if16mat4   = if16mat<4, 4>;

	using if32mat1x1 = if32mat<1, 1>;
	using if32mat1   = if32mat<1, 1>;
	using if32mat1x2 = if32mat<1, 2>;
	using if32mat1x3 = if32mat<1, 3>;
	using if32mat1x4 = if32mat<1, 4>;

	using if32mat2x1 = if32mat<2, 1>;
	using if32mat2x2 = if32mat<2, 2>;
	using if32mat2   = if32mat<2, 2>;
	using if32mat2x3 = if32mat<2, 3>;
	using if32mat2x4 = if32mat<2, 4>;

	using if32mat3x1 = if32mat<3, 1>;
	using if32mat3x2 = if32mat<3, 2>;
	using if32mat3x3 = if32mat<3, 3>;
	using if32mat3   = if32mat<3, 3>;
	using if32mat3x4 = if32mat<3, 4>;

	using if32mat4x1 = if32mat<4, 1>;
	using if32mat4x2 = if32mat<4, 2>;
	using if32mat4x3 = if32mat<4, 3>;
	using if32mat4x4 = if32mat<4, 4>;
	using if32mat4   = if32mat<4, 4>;

	using if64mat1x1 = if64mat<1, 1>;
	using if64mat1   = if64mat<1, 1>;
	using if64mat1x2 = if64mat<1, 2>;
	using if64mat1x3 = if64mat<1, 3>;
	using if64mat1x4 = if64mat<1, 4>;

	using if64mat2x1 = if64mat<2, 1>;
	using if64mat2x2 = if64mat<2, 2>;
	using if64mat2   = if64mat<2, 2>;
	using if64mat2x3 = if64mat<2, 3>;
	using if64mat2x4 = if64mat<2, 4>;

	using if64mat3x1 = if64mat<3, 1>;
	using if64mat3x2 = if64mat<3, 2>;
	using if64mat3x3 = if64mat<3, 3>;
	using if64mat3   = if64mat<3, 3>;
	using if64mat3x4 = if64mat<3, 4>;

	using if64mat4x1 = if64mat<4, 1>;
	using if64mat4x2 = if64mat<4, 2>;
	using if64mat4x3 = if64mat<4, 3>;
	using if64mat4x4 = if64mat<4, 4>;
	using if64mat4   = if64mat<4, 4>;

	using uf8mat1x1 = uf8mat<1, 1>;
	using uf8mat1   = uf8mat<1, 1>;
	using uf8mat1x2 = uf8mat<1, 2>;
	using uf8mat1x3 = uf8mat<1, 3>;
	using uf8mat1x4 = uf8mat<1, 4>;

	using uf8mat2x1 = uf8mat<2, 1>;
	using uf8mat2x2 = uf8mat<2, 2>;
	using uf8mat2   = uf8mat<2, 2>;
	using uf8mat2x3 = uf8mat<2, 3>;
	using uf8mat2x4 = uf8mat<2, 4>;

	using uf8mat3x1 = uf8mat<3, 1>;
	using uf8mat3x2 = uf8mat<3, 2>;
	using uf8mat3x3 = uf8mat<3, 3>;
	using uf8mat3   = uf8mat<3, 3>;
	using uf8mat3x4 = uf8mat<3, 4>;

	using uf8mat4x1 = uf8mat<4, 1>;
	using uf8mat4x2 = uf8mat<4, 2>;
	using uf8mat4x3 = uf8mat<4, 3>;
	using uf8mat4x4 = uf8mat<4, 4>;
	using uf8mat4   = uf8mat<4, 4>;

	using uf16mat1x1 = uf16mat<1, 1>;
	using uf16mat1   = uf16mat<1, 1>;
	using uf16mat1x2 = uf16mat<1, 2>;
	using uf16mat1x3 = uf16mat<1, 3>;
	using uf16mat1x4 = uf16mat<1, 4>;

	using uf16mat2x1 = uf16mat<2, 1>;
	using uf16mat2x2 = uf16mat<2, 2>;
	using uf16mat2   = uf16mat<2, 2>;
	using uf16mat2x3 = uf16mat<2, 3>;
	using uf16mat2x4 = uf16mat<2, 4>;

	using uf16mat3x1 = uf16mat<3, 1>;
	using uf16mat3x2 = uf16mat<3, 2>;
	using uf16mat3x3 = uf16mat<3, 3>;
	using uf16mat3   = uf16mat<3, 3>;
	using uf16mat3x4 = uf16mat<3, 4>;

	using uf16mat4x1 = uf16mat<4, 1>;
	using uf16mat4x2 = uf16mat<4, 2>;
	using uf16mat4x3 = uf16mat<4, 3>;
	using uf16mat4x4 = uf16mat<4, 4>;
	using uf16mat4   = uf16mat<4, 4>;

	using uf32mat1x1 = uf32mat<1, 1>;
	using uf32mat1   = uf32mat<1, 1>;
	using uf32mat1x2 = uf32mat<1, 2>;
	using uf32mat1x3 = uf32mat<1, 3>;
	using uf32mat1x4 = uf32mat<1, 4>;

	using uf32mat2x1 = uf32mat<2, 1>;
	using uf32mat2x2 = uf32mat<2, 2>;
	using uf32mat2   = uf32mat<2, 2>;
	using uf32mat2x3 = uf32mat<2, 3>;
	using uf32mat2x4 = uf32mat<2, 4>;

	using uf32mat3x1 = uf32mat<3, 1>;
	using uf32mat3x2 = uf32mat<3, 2>;
	using uf32mat3x3 = uf32mat<3, 3>;
	using uf32mat3   = uf32mat<3, 3>;
	using uf32mat3x4 = uf32mat<3, 4>;

	using uf32mat4x1 = uf32mat<4, 1>;
	using uf32mat4x2 = uf32mat<4, 2>;
	using uf32mat4x3 = uf32mat<4, 3>;
	using uf32mat4x4 = uf32mat<4, 4>;
	using uf32mat4   = uf32mat<4, 4>;

	using uf64mat1x1 = uf64mat<1, 1>;
	using uf64mat1   = uf64mat<1, 1>;
	using uf64mat1x2 = uf64mat<1, 2>;
	using uf64mat1x3 = uf64mat<1, 3>;
	using uf64mat1x4 = uf64mat<1, 4>;

	using uf64mat2x1 = uf64mat<2, 1>;
	using uf64mat2x2 = uf64mat<2, 2>;
	using uf64mat2   = uf64mat<2, 2>;
	using uf64mat2x3 = uf64mat<2, 3>;
	using uf64mat2x4 = uf64mat<2, 4>;

	using uf64mat3x1 = uf64mat<3, 1>;
	using uf64mat3x2 = uf64mat<3, 2>;
	using uf64mat3x3 = uf64mat<3, 3>;
	using uf64mat3   = uf64mat<3, 3>;
	using uf64mat3x4 = uf64mat<3, 4>;

	using uf64mat4x1 = uf64mat<4, 1>;
	using uf64mat4x2 = uf64mat<4, 2>;
	using uf64mat4x3 = uf64mat<4, 3>;
	using uf64mat4x4 = uf64mat<4, 4>;
	using uf64mat4   = uf64mat<4, 4>;

	using imaxmat1x1 = imaxmat<1, 1>;
	using imaxmat1   = imaxmat<1, 1>;
	using imaxmat1x2 = imaxmat<1, 2>;
	using imaxmat1x3 = imaxmat<1, 3>;
	using imaxmat1x4 = imaxmat<1, 4>;

	using imaxmat2x1 = imaxmat<2, 1>;
	using imaxmat2x2 = imaxmat<2, 2>;
	using imaxmat2   = imaxmat<2, 2>;
	using imaxmat2x3 = imaxmat<2, 3>;
	using imaxmat2x4 = imaxmat<2, 4>;

	using imaxmat3x1 = imaxmat<3, 1>;
	using imaxmat3x2 = imaxmat<3, 2>;
	using imaxmat3x3 = imaxmat<3, 3>;
	using imaxmat3   = imaxmat<3, 3>;
	using imaxmat3x4 = imaxmat<3, 4>;

	using imaxmat4x1 = imaxmat<4, 1>;
	using imaxmat4x2 = imaxmat<4, 2>;
	using imaxmat4x3 = imaxmat<4, 3>;
	using imaxmat4x4 = imaxmat<4, 4>;
	using imaxmat4   = imaxmat<4, 4>;

	using umaxmat1x1 = umaxmat<1, 1>;
	using umaxmat1   = umaxmat<1, 1>;
	using umaxmat1x2 = umaxmat<1, 2>;
	using umaxmat1x3 = umaxmat<1, 3>;
	using umaxmat1x4 = umaxmat<1, 4>;

	using umaxmat2x1 = umaxmat<2, 1>;
	using umaxmat2x2 = umaxmat<2, 2>;
	using umaxmat2   = umaxmat<2, 2>;
	using umaxmat2x3 = umaxmat<2, 3>;
	using imaxmat2x4 = imaxmat<2, 4>;

	using umaxmat3x1 = umaxmat<3, 1>;
	using umaxmat3x2 = umaxmat<3, 2>;
	using umaxmat3x3 = umaxmat<3, 3>;
	using umaxmat3   = umaxmat<3, 3>;
	using umaxmat3x4 = umaxmat<3, 4>;

	using umaxmat4x1 = umaxmat<4, 1>;
	using umaxmat4x2 = umaxmat<4, 2>;
	using umaxmat4x3 = umaxmat<4, 3>;
	using umaxmat4x4 = umaxmat<4, 4>;
	using umaxmat4   = umaxmat<4, 4>;

	using mat1x1 = matrix<1, 1, default_t>;
	using mat1   = matrix<1, 1, default_t>;
	using mat1x2 = matrix<1, 2, default_t>;
	using mat1x3 = matrix<1, 3, default_t>;
	using mat1x4 = matrix<1, 4, default_t>;

	using mat2x1 = matrix<2, 1, default_t>;
	using mat2x2 = matrix<2, 2, default_t>;
	using mat2   = matrix<2, 2, default_t>;
	using mat2x3 = matrix<2, 3, default_t>;
	using mat2x4 = matrix<2, 4, default_t>;

	using mat3x1 = matrix<3, 1, default_t>;
	using mat3x2 = matrix<3, 2, default_t>;
	using mat3x3 = matrix<3, 3, default_t>;
	using mat3   = matrix<3, 3, default_t>;
	using mat3x4 = matrix<3, 4, default_t>;

	using mat4x1 = matrix<4, 1, default_t>;
	using mat4x2 = matrix<4, 2, default_t>;
	using mat4x3 = matrix<4, 3, default_t>;
	using mat4x4 = matrix<4, 4, default_t>;
	using mat4   = matrix<4, 4, default_t>;

    using planef = plane3d<float>;
    using planed = plane3d<double>;
    using planeld = plane3d<long double>;
    using plane = plane3d<default_t>;
} /*This is a long file*/
