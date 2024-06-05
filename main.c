// compiled with: -Wall -Wpedantic -std=gnu2x -lmpfr -lgmp

#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include <gmp.h>

/*
 * MARK: main()
 */
int main(int argc, char const * argv[]) {
  printf("CF-GMP_Floats-C00\n");
  printf("GMP library : %-12s\n",
         gmp_version);
  printf("MPFR library: %-12s\n"
         "MPFR header : %s (based on %d.%d.%d)\n",
         mpfr_get_version(),
         MPFR_VERSION_STRING,
         MPFR_VERSION_MAJOR,
         MPFR_VERSION_MINOR,
         MPFR_VERSION_PATCHLEVEL);

  return 0;
}
