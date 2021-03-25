#include <iostream>
#include <math.h>

using namespace std;

double cube(double x) {
    return x * x * x;
}

double parabola(double x) {
    return x * x;
}

double RectangleIntegration(double(&func)(double), double bottomEdge, double topEdge, int stepCount) {
    double dx = (topEdge - bottomEdge) / stepCount;
    double total_integral = 0;
    for (int i = 0; i < stepCount; i++) {
        double x = bottomEdge + i * dx;
        total_integral += dx * func(x);
    }
    return total_integral;
}

double AdaptiveIntegration(double(&integration)(double(&func)(double), double, double, int), 
                double(&func)(double), double bottomEdge, double topEdge, double accuracy) {
    int stepCount = 1;
    double tempIntegral2 = (integration(func, bottomEdge, topEdge, stepCount));
    double tempIntegral1;
    do {
        tempIntegral1 = tempIntegral2;
        stepCount = stepCount * 2;
        tempIntegral2 = (integration(func, bottomEdge, topEdge, stepCount));
    } while (tempIntegral2 - tempIntegral1 >= accuracy);
    return tempIntegral2;
}

int main() {
    cout << AdaptiveIntegration(RectangleIntegration, parabola, -10.0, 10.0, 0.0001) << endl;
    cout << AdaptiveIntegration(RectangleIntegration, parabola, -100.0, 100.0, 0.0001) << endl;
    cout << AdaptiveIntegration(RectangleIntegration, parabola, -3.1, 4.7, 0.001) << endl;
    cout << AdaptiveIntegration(RectangleIntegration, parabola, -3.1, 4.7, 0.00001) << endl;
}
