#include<transformations.h>

int main()
{
  Coordinates p1;
  initalizeCoordinates(p1, 4, 5, 6);

  Transformer t1;
  float angle = PI/6;
  rotation(t1, ROTATE_ABOUT_Y_AXIS, angle, NULL);
  displayTransformer(t1);

  return 0;
}


