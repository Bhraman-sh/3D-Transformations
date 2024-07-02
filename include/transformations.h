#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define MAT_ROW 4
#define MAT_COLUMN 4
#define FIXED_POINT 1
#define ROTATE_ABOUT_X_AXIS 5
#define ROTATE_ABOUT_Y_AXIS 6
#define ROTATE_ABOUT_Z_AXIS 7
#define ROTATE_ABOUT_FIXED_LINE 8
#define REFLECT_ACROSS_XY_PLANE 9
#define REFLECT_ACROSS_YZ_PLANE 10
#define REFLECT_ACROSS_ZX_PLANE 11
#define ORIGIN 0

#define PI 3.1415926535 


typedef float Coordinates[1][MAT_COLUMN];
typedef float Transformer[MAT_ROW][MAT_COLUMN];

void initalizeCoordinates(Coordinates, float x, float y, float z);
void translation(Transformer, float* const);
void scaling(Transformer, int type, float* const, float* const);
void rotation(Transformer, int type, float angle, float * const);
void fixedLineRotation(Transformer, float angle, float * const);
void reflection(Transformer, int type);

void transform(Transformer, Coordinates);
void displayTransformer(Transformer);
void displayCoordinate(Coordinates);
void matrixMulitply(float results[MAT_ROW][MAT_COLUMN], float (*const *array)[MAT_COLUMN], int size);

#endif 
