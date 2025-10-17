// Wrapper to suppress warning from Eigen headers
#ifndef __FPSDK_COMMON_EXT_EIGEN_CORE_HPP__
#define __FPSDK_COMMON_EXT_EIGEN_CORE_HPP__

// Make __has_warning available which clang provides; define a safe fallback for other compilers
#ifndef __has_warning
#  define __has_warning(x) 0
#endif

// -------------------------
// Enter "quiet zone" for Eigen
// -------------------------
#if defined(__clang__)

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wall"
#pragma clang diagnostic ignored "-Wextra"
#pragma clang diagnostic ignored "-Wpedantic"
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wshadow"

#if __has_warning("-Wclass-memaccess")
#pragma clang diagnostic ignored "-Wclass-memaccess"
#endif
#if __has_warning("-Wmaybe-uninitialized")
#pragma clang diagnostic ignored "-Wmaybe-uninitialized"
#endif
#if __has_warning("-Wdeprecated-copy")
#pragma clang diagnostic ignored "-Wdeprecated-copy"
#endif

#include <Eigen/Core>
#pragma clang diagnostic pop

#elif defined(__GNUC__) || defined(__GNUG__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wshadow"

#pragma GCC diagnostic ignored "-Wclass-memaccess"

#if (__GNUC__ >= 9)
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#pragma GCC diagnostic ignored "-Wdeprecated-copy"
#endif

#include <Eigen/Core>
#pragma GCC diagnostic pop
#else

// Fallback
#include <Eigen/Core>

#endif

// -------------------------
// Post-include special case
// -------------------------
// For older Eigen (e.g. 3.3.7, which we have in fusion-dev-env and on the sensor), we unfortunately have to disable
// this warning globally (templates instantiation can be anywhere...). :-/ GCC 9 (in Yocto) doesn't like this.
// See https://gitlab.com/libeigen/eigen/-/issues/1788, https://gitlab.com/libeigen/eigen/-/merge_requests/29
#if !EIGEN_VERSION_AT_LEAST(3, 4, 0)

#if defined(__clang__)
#  if __has_warning("-Wdeprecated-copy")
#    pragma clang diagnostic ignored "-Wdeprecated-copy"
#  endif
#elif defined(__GNUC__) || defined(__GNUG__)
#  if (__GNUC__ >= 9)
#    pragma GCC diagnostic ignored "-Wdeprecated-copy"
#  endif
#endif

#endif  // !EIGEN_VERSION_AT_LEAST(3, 4, 0)

#endif  // __FPSDK_COMMON_EXT_EIGEN_CORE_HPP__
