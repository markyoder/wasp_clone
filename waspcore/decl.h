#ifndef WASP_WASPCORE_DECL_HH_
#define WASP_WASPCORE_DECL_HH_
#if defined _WIN32 || defined __CYGWIN__
  #define WASP_PUBLIC __declspec(dllexport)
  #define WASP_LOCAL
#else
  #define WASP_PUBLIC
  #define WASP_LOCAL __declspec(dllimport)
#endif
#endif /* WASP_WASPCORE_DECL_HH_*/
