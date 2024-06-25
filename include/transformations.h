#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include<stdio.h>
#include<graphics.h>
#include<math.h>

#define MAT_ROW 4
#define MAT_COLUMN 4
#define FIXED_POINT 1
#define ORIGIN 1


typedef float* Coordinates;
typedef float* Transformer;

Coordinates initalizeCoordinates(float x, float y, float z);
Transformer translation(float* const);
void deleteCoordinates(Coordinates p);
void deleteTransformer(Transformer t);
void displayTransformer(Transformer);
void displayCoordinate(float * const);


#endif 
