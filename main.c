#include<transformations.h>

int main()
{
  Coordinates p1;
  p1 = initalizeCoordinates(4, 5, 6);

  float T[3] = {25, 45, 55};
  Transformer t1 = translation(T);

  displayCoordinate(p1);
  displayTransformer(t1);

  deleteCoordinates(p1);
  deleteTransformer(t1);
  return 0;
}


