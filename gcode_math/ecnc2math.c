#include "ecnc2math.h"

#include <math.h>

static double INFINITESIMAL = 0.000000001;

///  1: a > b
/// -1: a < b
///  0: a = b

int FuzzyCompare(double a, double b) {
    double diff = a - b;
    double small = MAX(MIN(fabs(a), fabs(b)) * INFINITESIMAL, INFINITESIMAL);
    if (diff > small) {
        return 1;
    } else if (diff < -small) {
        return -1;
    } else {
        return 0;
    }
}

int FuzzyEquals(double a, double b) {
    return FuzzyCompare(a, b) == 0 ? 1 : 0;
}

int IsEqual(double a, double b) {
    return FuzzyEquals(a, b);
}

int IsZero(double a) {
    return FuzzyEquals(a, 0.);
}

int IsGreater(double a, double b) {
    return FuzzyCompare(a, b) > 0 ? 1 : 0;
}

int IsLesser(double a, double b) {
    return FuzzyCompare(a, b) < 0 ? 1 : 0;
}

int IsGreaterEqual(double a, double b) {
    return IsGreater(a, b) || IsEqual(a, b);
}

int IsLesserEqual(double a, double b) {
    return IsLesser(a, b) || IsEqual(a, b);
}
