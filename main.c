//  @see: https://gmplib.org/manual/
//  @see: https://www.mpfr.org/mpfr-current/mpfr.html

/*
 * compiled with:
 *   gcc-14
 *     -Wall
 *     -std=gnu2x
 *     -I/usr/local/Cellar/mpfr/4.2.1/include
 *     -I/usr/local/Cellar/gmp/6.3.0/include
 *     -L/usr/local/Cellar/mpfr/4.2.1/lib
 *     -L/usr/local/Cellar/gmp/6.3.0/lib
 *     -o ../../bin/GMP_Floats-C00
 *     GMP_Floats-C00.c
 *     -lgmp
 *     -lmpfr
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <gmp.h>

#include "version_info.h"

/*
 * MARK: gmp_fp()
 */
static
inline
void gmp_fp(void) {
  printf("In %s()\n", __func__);
  gmp_printf("GMP Default precision: %5ld\n", mpf_get_default_prec());

  mpf_t x0, y0;
  mpf_t x1, y1;
  mpf_t r0, r1;

  mpf_init(x0);
  mpf_init2(y0, 256);
  mpf_init(y1);
  mpf_init2(x1, 256);

  mpf_init2(r0, 256);
  mpf_init(r1);

  gmp_printf("Precision of x0:%5lu, x1:%5lu\n", mpf_get_prec(x0), mpf_get_prec(x1));
  gmp_printf("Precision of y0:%5lu, y1:%5lu\n", mpf_get_prec(y0), mpf_get_prec(y1));
  gmp_printf("Precision of r0:%5lu, r1:%5lu\n", mpf_get_prec(r0), mpf_get_prec(r1));

  mpf_set_d(x0, 123456.0e-9);
  mpf_set_d(y0, 456.789e-6);
  mpf_set(x1, x0);
  mpf_set(y1, y0);
  gmp_printf("x0: %15.9Ff, x1: %15.9Ff\n", x0, x1);
  gmp_printf("y0: %15.9Ff, y1: %15.9Ff\n", y0, y1);

  mpf_add(r0, x0, y0);
  gmp_printf("%15.9Ff + %15.9Ff = %15.9Ff\n", x0, y0, r0);

  mpf_add(r1, y1, x1);
  gmp_printf("%15.9Ff + %15.9Ff = %15.9Ff\n", x1, y1, r1);

  int cmp = mpf_cmp(r0, r1);
  gmp_printf("r0 %s r1\n", (cmp == 0 ? ".EQ." : cmp > 0 ? ".GT." : ".LT."));

  mpf_clears(x0, x1, y0, y1, NULL);

  putchar('\n');

  return;
}

/*
 * MARK: mpfr_fp()
 */
static
inline
void mpfr_fp(void) {
  printf("In %s()\n", __func__);
  gmp_printf("MPFR Default precision: %5ld\n", mpfr_get_default_prec());

  mpfr_t x0, y0;
  mpfr_t x1, y1;
  mpfr_t r0, r1;

  mpfr_init(x0);
  mpfr_init2(y0, 256);
  mpfr_init2(x1, 256);
  mpfr_init(y1);

  mpfr_init(r0);
  mpfr_init2(r1, 256);
  mpfr_printf("Precision of x0:%5Pu, x1:%5Pu\n", mpfr_get_prec(x0), mpfr_get_prec(x1));
  mpfr_printf("Precision of y0:%5Pu, y1:%5Pu\n", mpfr_get_prec(y0), mpfr_get_prec(y1));
  mpfr_printf("Precision of r0:%5Pu, r1:%5Pu\n", mpfr_get_prec(r0), mpfr_get_prec(r1));

  mpfr_set_d(x0, 123456.0e-9, MPFR_RNDD);
  mpfr_set_d(y0, 456.789e-6, MPFR_RNDU);
  mpfr_set(x1, x0, MPFR_RNDU);
  mpfr_set(y1, y0, MPFR_RNDD);
  mpfr_printf("x0: %15.9RNf, x1: %15.9RNf\n", x0, x1);
  mpfr_printf("y0: %15.9RUf, y1: %15.9RUf\n", y0, y1);

  mpfr_add(r0, x0, y0, MPFR_RNDU);
  mpfr_printf("%15.9RUf + %15.9RUf = %15.9RUf\n", x0, y0, r0);

  mpfr_add(r1, y1, x1, MPFR_RNDD);
  mpfr_printf("%15.9RNf + %15.9RNf = %15.9RNf\n", x1, y1, r1);

  int cmp = mpfr_cmp(r0, r1);
  mpfr_printf("r0 %s r1\n", (cmp == 0 ? ".EQ." : cmp > 0 ? ".GT." : ".LT."));

  mpfr_clears(x0, x1, y0, y1, r0, r1, NULL);

  putchar('\n');

  return;
}

/*
 * MARK: point1()
 */
static
inline
void point1(void) {

  mpf_t gmp1;
  mpfr_t mpfr1;

  mpf_init2(gmp1, 64);
  mpfr_init2(mpfr1, 64);

  mpf_set_d(gmp1, 1.0 / 10.0);
  mpfr_set_d(mpfr1, 1.0 / 10.0, MPFR_RNDD);

  mpfr_printf("gmp1: %18.15Ff, mpfr1: %18.15RNf\n", gmp1, mpfr1);

  mpf_clear(gmp1);
  mpfr_clear(mpfr1);

  return;
}

/*
 * MARK: main()
 */
int main(int argc, char const * argv[]) {
  printf("GMP_Floats-C00\n");
  version_details();

  printf("GMP library : %-12s\n",
         gmp_version);
  printf("MPFR library: %-12s\n"
         "MPFR header : %s (based on %d.%d.%d)\n",
         mpfr_get_version(),
         MPFR_VERSION_STRING,
         MPFR_VERSION_MAJOR,
         MPFR_VERSION_MINOR,
         MPFR_VERSION_PATCHLEVEL);
  putchar('\n');

  gmp_fp();

  mpfr_fp();  // use system default precision

  mpfr_set_default_prec(64);  // user assigned default precision
  mpfr_fp();

  point1();

  return 0;
}
