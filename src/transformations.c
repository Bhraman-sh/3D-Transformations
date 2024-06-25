#include<transformations.h>

Coordinates initalizeCoordinates(float x, float y, float z)
{
  float* mat = (float*)malloc(MAT_ROW * sizeof(float));
  float translate[3] = {5.0, 20.0, 30.0};
  mat[0] = x;
  mat[1] = y;
  mat[2] = z;
  mat[3] = 1;

  Transformer t1 = translation(translate);

  return mat;
}

Transformer translation(float parameters[])
{
  int r, c;
  float *mat = (float*)malloc(MAT_ROW * MAT_COLUMN * sizeof(float));

  for(r = 0; r < MAT_ROW; r++)
  {
    for(c = 0; c < MAT_COLUMN; c++)
    {
      if(r != c) 
      {
        if(c == 3)
        {
           *(mat + MAT_COLUMN * r + c) = parameters[r];
        }
        else 
        {
           *(mat + MAT_COLUMN * r + c) = 0;
        }
      }
      else
      {
        *(mat + MAT_COLUMN * r + c) = 1;
      }
    }
  }

  return mat;
}

void deleteCoordinates(Coordinates p)
{
  free(p);
}

void displayCoordinate(float * const c)
{
  int r;
  for (r = 0; r < MAT_ROW; r++)
  {
    printf("%f\n", *(c+r));
  }
}

void displayTransformer(float * const t)
{
  int r, c;
  for (r = 0; r < MAT_ROW; r++)
  {
    for (c = 0; c < MAT_COLUMN; c++)
    {
      printf("%f  ", *(t + MAT_COLUMN * r + c));
    }
    printf("\n");
  }
}

void deleteTransformer(Transformer t)
{
  free(t);
}
