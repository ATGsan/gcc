/* PR tree-optimization/109011 */
/* { dg-do compile } */
/* { dg-options "-O3 -fno-unroll-loops --param=vect-epilogues-nomask=0 -fdump-tree-optimized" } */
/* { dg-additional-options "-mno-avx512cd -mbmi -mlzcnt -mavx512vpopcntdq" { target { { { { i?86-*-* x86_64-*-* } && avx512vpopcntdq } && lzcnt } && bmi } } } */
/* { dg-additional-options "-mpower8-vector -mno-power9-vector" { target powerpc_p8vector_ok } } */

void
foo (int *p, int *q)
{
#pragma omp simd
  for (int i = 0; i < 2048; ++i)
    p[i] = __builtin_ctz (q[i]);
}

void
bar (int *p, int *q)
{
#pragma omp simd
  for (int i = 0; i < 2048; ++i)
    p[i] = q[i] ? __builtin_ctz (q[i]) : __SIZEOF_INT__ * __CHAR_BIT__;
}

void
baz (int *p, int *q)
{
#pragma omp simd
  for (int i = 0; i < 2048; ++i)
    p[i] = __builtin_ffs (q[i]);
}

/* { dg-final { scan-tree-dump-times " = \.POPCOUNT \\\(" 3 "optimized" { target { { { { i?86-*-* x86_64-*-* } && avx512vpopcntdq } && lzcnt } && bmi } } } } */
/* { dg-final { scan-tree-dump-times " = \.CLZ \\\(" 3 "optimized" { target powerpc_p8vector_ok } } } */
