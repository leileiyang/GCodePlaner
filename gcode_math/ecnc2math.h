#ifndef ECNC2MATH
#define ECNC2MATH

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PI
#define PI 3.1415926535897932384626
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MID
#define MID(a, b, c) (a < b ? (b < c ? b: a < c ? c : a) : (b > c ? b: a > c ? c: a))
#endif

/// 0: a != b
/// 1; a == b
int IsEqual(double a, double b);

/// 0: a != 0
/// 1: a == 0
int IsZero(double a);

/// 1: a > b
/// 0: a <= b
int IsGreater(double a, double b);

/// 1: a < b
/// 0: a >= b
int IsLesser(double a, double b);

/// 1: a >= b
/// 0: a < b
int IsGreaterEqual(double a, double b);

/// 1: a <= b
/// 0: a > b
int IsLesserEqual(double a, double b);

#ifdef __cplusplus
}
#endif

#endif // ECNC2MATH

