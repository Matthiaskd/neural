#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define InputNodes 784
#define HiddenNodes 120
#define Outputs 9
#define Trainings 9
double init_weights();
double sigmoid(double x);
double dsigmoid(double x);
double relu(double x);
double drelu(double x);
void shuffle(int *array, size_t n);
int feed(int inputs[InputNodes], int backpropagate);
int setup();
int all(int inputs[InputNodes], int t);