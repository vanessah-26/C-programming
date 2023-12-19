#include "mathlib.h"

#include <math.h>

//absolute val
double Abs(double x) {
    if (x < 0) {
        return -x; // negate negation = positive val
    }
    return x;
}
//Sqrt
double Sqrt(double x) {
    // Check domain.
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        // Specifically, this is the Babylonian method--a simplification of
        // Newton's method possible only for Sqrt(x).
        old = new;
        new = 0.5 * (old + (x / old));
    }
    return new;
}

//normalize to range 0-2pi
//
double normalize(double x) {
    while (x < 0) {
        x += 2 * M_PI;
    }
    while (x >= 2 * M_PI) {
        x -= 2 * M_PI;
    }
    return x;
}

double Sin(double x) {
    x = normalize(x);
    double res = 0.0;
    double term = x;

    for (int k = 1; Abs(term) > EPSILON; k += 2) {
        res += term;
        term = -term * x * x / ((k + 1) * (k + 2));
    }
    //when term < e
    return res;
}

double Cos(double x) {
    x = normalize(x);
    double res = 1.0;
    double term = 1.0;

    for (int k = 1; Abs(term) > EPSILON; k += 1) {
        term *= (-x * x) / ((2 * k - 1) * (2 * k));
        res += term;
    }
    //when Abs(term) < e
    return res;
}
double Tan(double x) {
    //fixed here:
    x = normalize(x);
    return Sin(x) / Cos(x);
}
