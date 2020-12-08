/* tensor/tensor_complex_long_double.h
 * 
 * Copyright (C) 2020 Viktor Slavkovikj
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __TENSOR_COMPLEX_LONG_DOUBLE_H__
#define __TENSOR_COMPLEX_LONG_DOUBLE_H__

#include <stdlib.h>
#include <stdarg.h>

#include <gsl/gsl_types.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_inline.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_check_range.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_vector_complex_long_double.h>
#include <gsl/gsl_matrix_complex_long_double.h>

#include <tensor/tensor_int.h>
#include <tensor/range.h>


#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif


__BEGIN_DECLS

typedef struct
{
  size_t dim;
  size_t * size;
  size_t * stride;
  long double * data;
  gsl_block_complex_long_double * block;
  int owner;
} tensor_complex_long_double;

/* Allocation */

tensor_complex_long_double *
tensor_complex_long_double_valloc (const size_t dim, va_list argp);

tensor_complex_long_double *
tensor_complex_long_double_alloc (const size_t dim, ...);

tensor_complex_long_double *
tensor_complex_long_double_aalloc (const size_t dim, const size_t * size);

tensor_complex_long_double *
tensor_complex_long_double_calloc (const size_t dim, ...);

void
tensor_complex_long_double_free (tensor_complex_long_double * t);

/* Tensor element access */

gsl_complex_long_double
tensor_complex_long_double_get (const tensor_complex_long_double * t, ...);

gsl_complex_long_double *
tensor_complex_long_double_ptr (tensor_complex_long_double * t, ...);

const gsl_complex_long_double *
tensor_complex_long_double_const_ptr (const tensor_complex_long_double * t, ...);

size_t
tensor_complex_long_double_index (const tensor_complex_long_double * t, const size_t i);

INLINE_DECL
gsl_complex_long_double *
tensor_complex_long_double_ptr_idx (tensor_complex_long_double * t,
                           const size_t idx);

INLINE_DECL
const gsl_complex_long_double *
tensor_complex_long_double_const_ptr_idx (const tensor_complex_long_double * t,
                                 const size_t idx);

void
tensor_complex_long_double_set (tensor_complex_long_double * t, const gsl_complex_long_double x, ...);

void
tensor_complex_long_double_set_zero (tensor_complex_long_double * t);

void
tensor_complex_long_double_set_one (tensor_complex_long_double * t);

void
tensor_complex_long_double_set_all (tensor_complex_long_double * t, const gsl_complex_long_double x);

/* Tensor properties */

int
tensor_complex_long_double_vfits_size (const tensor_complex_long_double * t, va_list argp);

int
tensor_complex_long_double_fits_size (const tensor_complex_long_double * t, ...);

int
tensor_complex_long_double_match_size (const tensor_complex_long_double * t1,
                              const tensor_complex_long_double * t2);

int
tensor_complex_long_double_match_tsize (const tensor_complex_long_double * t1,
                               const tensor_complex_long_double * t2);

int
tensor_complex_long_double_is_null (const tensor_complex_long_double * t);

int
tensor_complex_long_double_is_pos (const tensor_complex_long_double * t);

int
tensor_complex_long_double_is_neg (const tensor_complex_long_double * t);

int
tensor_complex_long_double_is_nonneg (const tensor_complex_long_double * t);

int
tensor_complex_long_double_is_nonpos (const tensor_complex_long_double * t);

int
tensor_complex_long_double_equal (const tensor_complex_long_double * t1,
                         const tensor_complex_long_double * t2);
int
tensor_complex_long_double_is_same (const tensor_complex_long_double * t);

int
tensor_complex_long_double_is_const (const tensor_complex_long_double * t,
                            const gsl_complex_long_double c);

INLINE_DECL
size_t
tensor_complex_long_double_tsize (const tensor_complex_long_double * t);

INLINE_DECL
int
tensor_complex_long_double_is_view (const tensor_complex_long_double * t);

INLINE_DECL
int
tensor_complex_long_double_is_contiguous (const tensor_complex_long_double * t);

/* Tensor file io */

int
tensor_complex_long_double_fread (FILE * stream, tensor_complex_long_double * t);

int
tensor_complex_long_double_fwrite (FILE * stream, const tensor_complex_long_double * t);

int
tensor_complex_long_double_fscanf (FILE * stream, tensor_complex_long_double * t);

int
tensor_complex_long_double_fprintf (FILE * stream, const tensor_complex_long_double * t, const char * format);

/* Tensor views */

tensor_complex_long_double *
tensor_complex_long_double_view (tensor_complex_long_double * t, ...);

const tensor_complex_long_double *
tensor_complex_long_double_const_view (const tensor_complex_long_double * t, ...);

tensor_complex_long_double *
tensor_complex_long_double_aview (tensor_complex_long_double * t, const size_t * range);

const tensor_complex_long_double *
tensor_complex_long_double_const_aview (const tensor_complex_long_double * t, const size_t * range);

tensor_complex_long_double *
tensor_complex_long_double_view_array (long double * array, const size_t dim, ...);

const tensor_complex_long_double *
tensor_complex_long_double_const_view_array (const long double * array, const size_t dim, ...);

tensor_complex_long_double *
tensor_complex_long_double_view_vector (gsl_vector_complex_long_double * vector);

const tensor_complex_long_double *
tensor_complex_long_double_const_view_vector (const gsl_vector_complex_long_double * vector);

_gsl_vector_complex_long_double_view
gsl_vector_complex_long_double_view_tensor (tensor_complex_long_double * t);

_gsl_vector_complex_long_double_const_view
gsl_vector_complex_long_double_const_view_tensor (const tensor_complex_long_double * t);

tensor_complex_long_double *
tensor_complex_long_double_view_matrix (gsl_matrix_complex_long_double * matrix);

const tensor_complex_long_double *
tensor_complex_long_double_const_view_matrix (const gsl_matrix_complex_long_double * matrix);

_gsl_matrix_complex_long_double_view
gsl_matrix_complex_long_double_view_tensor (tensor_complex_long_double * t);

_gsl_matrix_complex_long_double_const_view
gsl_matrix_complex_long_double_const_view_tensor (const tensor_complex_long_double * t);

/* Tensor operators */

tensor_complex_long_double *
tensor_complex_long_double_copy (const tensor_complex_long_double * t_in);

int
tensor_complex_long_double_assign (tensor_complex_long_double * t1, const tensor_complex_long_double * t2);

int
tensor_complex_long_double_swap (tensor_complex_long_double * t1, tensor_complex_long_double * t2);

void
tensor_complex_long_double_adjoin (tensor_complex_long_double * t);

int
tensor_complex_long_double_morph (tensor_complex_long_double * t, ...);

void
tensor_complex_long_double_deflate (tensor_complex_long_double * t);

int
tensor_complex_long_double_inflate (tensor_complex_long_double * t, const size_t didx);

tensor_complex_long_double *
tensor_complex_long_double_concat (const size_t didx, const size_t n, ...);

/* Arithmetic operators */

void
tensor_complex_long_double_abs (tensor_complex_long_double * t);

void
tensor_complex_long_double_neg (tensor_complex_long_double * t);

void
tensor_complex_long_double_inv (tensor_complex_long_double * t);

int
tensor_complex_long_double_add (tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

int
tensor_complex_long_double_sub (tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

int
tensor_complex_long_double_mul (tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

int
tensor_complex_long_double_div (tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

int
tensor_complex_long_double_mod (tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

void
tensor_complex_long_double_scale_add (tensor_complex_long_double * t,
                                 const long double s,
                                 const long double a);

/* Arithmetic complex only operators */

void
tensor_complex_long_double_conj (tensor_complex_long_double * t);

void
tensor_complex_long_double_arg (tensor_complex_long_double * t);

/* Trigonometric operators */

void
tensor_complex_long_double_sin (tensor_complex_long_double * t);

void
tensor_complex_long_double_cos (tensor_complex_long_double * t);

void
tensor_complex_long_double_tan (tensor_complex_long_double * t);

/* Reciprocal trigonometric operators */

void
tensor_complex_long_double_sec (tensor_complex_long_double * t);

void
tensor_complex_long_double_csc (tensor_complex_long_double * t);

void
tensor_complex_long_double_cot (tensor_complex_long_double * t);

/* Inverse trigonometric operators */

void
tensor_complex_long_double_arcsin (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccos (tensor_complex_long_double * t);

void
tensor_complex_long_double_arctan (tensor_complex_long_double * t);

tensor_complex_long_double *
tensor_complex_long_double_arctan2 (const tensor_complex_long_double * y,
                           const tensor_complex_long_double * x);

/* Reciprocal inverse trigonometric operators */

void
tensor_complex_long_double_arcsec (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccsc (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccot (tensor_complex_long_double * t);

/* Hyperbolic operators */

void
tensor_complex_long_double_sinh (tensor_complex_long_double * t);

void
tensor_complex_long_double_cosh (tensor_complex_long_double * t);

void
tensor_complex_long_double_tanh (tensor_complex_long_double * t);

/* Reciprocal hyperbolic operators */

void
tensor_complex_long_double_sech (tensor_complex_long_double * t);

void
tensor_complex_long_double_csch (tensor_complex_long_double * t);

void
tensor_complex_long_double_coth (tensor_complex_long_double * t);

/* Inverse hyperbolic operators */

void
tensor_complex_long_double_arcsinh (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccosh (tensor_complex_long_double * t);

void
tensor_complex_long_double_arctanh (tensor_complex_long_double * t);

/* Reciprocal inverse hyperbolic operators */

void
tensor_complex_long_double_arcsech (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccsch (tensor_complex_long_double * t);

void
tensor_complex_long_double_arccoth (tensor_complex_long_double * t);

/* Exponential operators */

void
tensor_complex_long_double_pow (tensor_complex_long_double * t, gsl_complex_long_double p);

void
tensor_complex_long_double_pow_real (tensor_complex_long_double * t, long double p);

void
tensor_complex_long_double_sqrt (tensor_complex_long_double * t);

void
tensor_complex_long_double_cbrt (tensor_complex_long_double * t);

void
tensor_complex_long_double_exp (tensor_complex_long_double * t);

void
tensor_complex_long_double_exp2 (tensor_complex_long_double * t);

void
tensor_complex_long_double_exp10 (tensor_complex_long_double * t);

void
tensor_complex_long_double_expm1 (tensor_complex_long_double * t);

/* Logarithmic operators */
 
void
tensor_complex_long_double_log (tensor_complex_long_double * t);

void
tensor_complex_long_double_log2 (tensor_complex_long_double * t);

void
tensor_complex_long_double_log10 (tensor_complex_long_double * t);

void
tensor_complex_long_double_log1p (tensor_complex_long_double * t);

void
tensor_complex_long_double_logb (tensor_complex_long_double * t);

/* Tensor statistics */

long double
tensor_complex_long_double_max (const tensor_complex_long_double * t);

long double
tensor_complex_long_double_min (const tensor_complex_long_double * t);

void
tensor_complex_long_double_minmax (const tensor_complex_long_double * t,
                          long double * min, long double * max);

size_t
tensor_complex_long_double_max_index (const tensor_complex_long_double * t);

size_t
tensor_complex_long_double_min_index (const tensor_complex_long_double * t);

void
tensor_complex_long_double_minmax_index (const tensor_complex_long_double * t,
                                size_t * min_index,
                                size_t * max_index);

double
tensor_complex_long_double_sum (const tensor_complex_long_double * t);

double
tensor_complex_long_double_prod (const tensor_complex_long_double * t);

double
tensor_complex_long_double_mean (const tensor_complex_long_double * t);

double
tensor_complex_long_double_var (const tensor_complex_long_double * t);

double
tensor_complex_long_double_std (const tensor_complex_long_double * t);

/* Rounding and truncation operators */

void
tensor_complex_long_double_ceil (tensor_complex_long_double * t);

void
tensor_complex_long_double_floor (tensor_complex_long_double * t);

void
tensor_complex_long_double_round (tensor_complex_long_double * t);

void
tensor_complex_long_double_clip (tensor_complex_long_double * t,
                        const gsl_complex_long_double min, const gsl_complex_long_double max);

/* Logical operators */

void
tensor_complex_long_double_not (tensor_complex_long_double * t);

tensor_int *
tensor_complex_long_double_fcmp (const tensor_complex_long_double * t1,
                        const tensor_complex_long_double * t2,
                        const long double eps);

tensor_int *
tensor_complex_long_double_fcmpc (const tensor_complex_long_double * t,
                         const long double x, const long double eps);

tensor_int *
tensor_complex_long_double_cmp (const tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

tensor_int *
tensor_complex_long_double_cmpc (const tensor_complex_long_double * t,
                        const long double x);

tensor_int *
tensor_complex_long_double_and (const tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

tensor_int *
tensor_complex_long_double_or (const tensor_complex_long_double * t1,
                      const tensor_complex_long_double * t2);

tensor_int *
tensor_complex_long_double_xor (const tensor_complex_long_double * t1,
                       const tensor_complex_long_double * t2);

/* Tensor distributions */

void
tensor_complex_long_double_set_uniform (tensor_complex_long_double * t, const gsl_rng * rng);

void
tensor_complex_long_double_set_normal (tensor_complex_long_double * t, const gsl_rng * rng,
                              double mu, double sigma);

void
tensor_complex_long_double_set_std_normal (tensor_complex_long_double * t,
                                  const gsl_rng * rng);

void
tensor_complex_long_double_set_uniform_int (tensor_complex_long_double * t,
                                   const gsl_rng * rng,
                                   unsigned long int max);

/* Tensor sorting */

void
tensor_complex_long_double_sort (tensor_complex_long_double * t);

void
tensor_complex_long_double_sort_index (size_t * p, const tensor_complex_long_double * t);


#ifdef HAVE_INLINE

INLINE_FUN
gsl_complex_long_double *
tensor_complex_long_double_ptr_idx (tensor_complex_long_double * t,
                           const size_t idx)
{
  return (gsl_complex_long_double *) (t->data + idx);
}

INLINE_FUN
const gsl_complex_long_double *
tensor_complex_long_double_const_ptr_idx (const tensor_complex_long_double * t,
                                 const size_t idx)
{
  return (const gsl_complex_long_double *) (t->data + idx);
}

INLINE_FUN
size_t
tensor_complex_long_double_tsize (const tensor_complex_long_double * t)
{
  if (t->dim == 0)
    return 0;
  
  size_t i, total_size;
  for (i = 0, total_size = 1; i < t->dim; ++i)
    {
      total_size *= t->size[i];
    }
  
  return total_size;
}

INLINE_FUN
int
tensor_complex_long_double_is_view (const tensor_complex_long_double * t)
{
  return (t->owner) ? 0 : 1;
}

INLINE_FUN
int
tensor_complex_long_double_is_contiguous (const tensor_complex_long_double * t)
{
  if (t->dim == 0)
    {
      return 1;
    }
  else
    {
      size_t i, stride = 1;
      for (i = 0; i < t->dim; ++i)
        {
          if (t->stride[t->dim - i - 1] != stride)
            {
              return 0;
            }

          stride *= t->size[t->dim - i - 1];
        }

      return 1;
    }
}

#endif  /* HAVE_INLINE */

__END_DECLS

#endif /* __TENSOR_COMPLEX_LONG_DOUBLE_H__ */
