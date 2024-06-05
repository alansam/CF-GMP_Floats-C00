#pragma once

#ifndef VERSION_INFO_H_
#define VERSION_INFO_H_ 

#include <gmp.h>

#ifdef __GNUC__
#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 \
                   + __GNUC_MINOR__ * 100 \
                   + __GNUC_PATCHLEVEL__)
#endif
#endif

#ifdef __GNU_MP_VERSION
#ifndef GNU_MP_VERSION
#define GNU_MP_VERSION (__GNU_MP_VERSION * 10000 \
                      + __GNU_MP_VERSION_MINOR * 100 \
                      + __GNU_MP_VERSION_PATCHLEVEL)
#endif
#endif

static
inline
void version_details(void) {
#ifdef __cplusplus
  std::cout << "C++ version: " << __cplusplus << '\n'
# ifdef _LIBCPP_STD_VER
            << "libcpp standard version: " <<  _LIBCPP_STD_VER << '\n'
# endif
#ifdef __STDC_VERSION__
            << "C version: iso9899:" << __STDC_VERSION__ << '\n'
#endif
            << "Compiler version: " << __VERSION__ << '\n'
#ifdef GCC_VERSION
            << "GNU C version: " << GCC_VERSION << '\n'
#endif
#ifdef GNU_MP_VERSION
            << "GNU MP Version Number: " << gmp_version << '\n'
            << "GNU multiple precision arithmetic library (GMP): " << GNU_MP_VERSION << '\n'
#endif
            << std::endl;

#else
# ifdef _LIBCPP_STD_VER
  printf("libcpp standard version: %s\n", _LIBCPP_STD_VER );
# endif
#ifdef __STDC_VERSION__
  printf("C version: iso9899%ld\n", __STDC_VERSION__);
# endif
  printf("Compiler version: %s\n", __VERSION__);
# ifdef GCC_VERSION
  printf("GNU C version: %d\n", GCC_VERSION);
# endif

#ifdef GNU_MP_VERSION
  printf("GNU MP Version Number: %s\n", gmp_version);
  printf("GNU multiple precision arithmetic library (GMP): %d\n", GNU_MP_VERSION);
#endif
  puts("");
#endif

  return;
}

#endif
