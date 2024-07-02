#include<transformations.h>

void initalizeCoordinates(Coordinates c1, float x, float y, float z)
{
  c1[0][0] = x;
  c1[0][1] = y;
  c1[0][2] = z;
  c1[0][3] = 1;
}

void translation(Transformer t1, float parameters[])
{
  int r, c;

  for (r = 0; r < MAT_ROW; r++)
  {
    for (c = 0; c < MAT_COLUMN; c++)
    {
      if(r == c) 
      {
        t1[r][c] = 1;
      }
      else 
      {
        if(c == MAT_COLUMN - 1)
        {
          t1[r][c] = parameters[r];
        }
        else 
        {
          t1[r][c] = 0;
        }
      }
    }
  }
}

void scaling(Transformer scale, int type, float * const scaling_factor, float* const point)
{
  int r, c;

  for (r = 0; r < MAT_ROW; r++)
  {
    for (c = 0; c < MAT_COLUMN; c++)
    {
      if (r == c) 
      {
        if (r == MAT_ROW - 1)
        {
          scale[r][c] = 1;
        }
        else
        {
          scale[r][c] = scaling_factor[r];
        }
      }
      else 
      {
        scale[r][c] = 0;
      }
    }
  }
  if(type == FIXED_POINT)
  {
    if(point == NULL)
    {
      printf("Error: Point not provided for fixed point scaling!!\n");
      return ;
    }
    Transformer tr;
    translation(tr, point);
    for(r = 0; r < 3; r++)
    {
      point[r] *= -1;
    }
    Transformer tr_inverse;
    translation(tr_inverse, point);
    float empty[MAT_ROW][MAT_COLUMN];
    float (*const array[4])[MAT_COLUMN] = {empty, tr, scale, tr_inverse};

    matrixMulitply(scale, array, 3);
  }
}


void rotation(Transformer t1, int type, float theta, float * const line)
{
  int i, r, c;
  int j = 0;

  float value[4] = {cos(theta), -sin(theta), sin(theta), cos(theta)};
  switch (type)
  {
    case ROTATE_ABOUT_Z_AXIS:
      i = 0;
      break;
    
    case ROTATE_ABOUT_Y_AXIS:
      i = 2;
      break;

    case ROTATE_ABOUT_X_AXIS:
      i = 1;
      break;

    case ROTATE_ABOUT_FIXED_LINE:
      fixedLineRotation(t1, theta, line);
      return;
  }

  printf("%d\n", i);
  for (r=0; r<MAT_ROW; r++)
  {
    for (c=0; c <MAT_COLUMN; c++)
    {
      if ((r==i || r==(i+1)%3) && (c==i || c==(i+1)%3))
      {
        printf("%d %d\n", r, c);
        t1[r][c] = value[j];
        j++;
      }
      else 
      {
        if (r == c) 
        {
          t1[r][c] = 1;
        }
        else
        {
          t1[r][c] = 0;
        }
      }
    }
  }
}

void fixedLineRotation(Transformer t1, float theta, float * const line)
{
  Transformer translate, x_rotate, y_rotate, z_rotate;
  Transformer inverse_translate, inverse_y_rotate, inverse_z_rotate;

  float diff[3];

  for (int i = 0; i < 3; i++)
  {
    diff[i] = line[i+3] - line[i]; 
  }

  translation(translate, line);
  for (int i = 0; i < 3; i++)
  {
    line[i] *= -1;
  }
  translation(inverse_translate, line);

  float angle = atan(diff[1]/diff[0]);
  
  rotation(z_rotate, ROTATE_ABOUT_Z_AXIS, angle, NULL);
  rotation(inverse_z_rotate, ROTATE_ABOUT_Z_AXIS, -angle, NULL);

  angle = atan(diff[2]/diff[0]);

  rotation(y_rotate, ROTATE_ABOUT_Y_AXIS, angle, NULL);
  rotation(inverse_y_rotate, ROTATE_ABOUT_Y_AXIS, -angle, NULL);

  
  rotation(x_rotate, ROTATE_ABOUT_X_AXIS, theta, NULL);

  float empty[MAT_ROW][MAT_COLUMN];

  float (*const array[8])[MAT_COLUMN] = {empty, translate, y_rotate, z_rotate, x_rotate, 
    inverse_z_rotate, inverse_y_rotate, inverse_translate};

  matrixMulitply(t1, array, 7);
}

void reflection(Transformer t1, int type)
{
  for(int r = 0; r < MAT_ROW; r++)
  {
    for(int c = 0; c < MAT_COLUMN; c++)
    {
      if (r != c) 
      {
        t1[r][c] = 0;
      }
      else
      {
        t1[r][c] = 1;
      }
    }
  }

  switch (type)
  {
    case REFLECT_ACROSS_XY_PLANE:
      t1[2][2] = -1;
      break;
      
    case REFLECT_ACROSS_YZ_PLANE:
      t1[0][0] = -1;
      break;

    case REFLECT_ACROSS_ZX_PLANE:
      t1[1][1] = -1;
      break;
  }
}

void transform(Transformer t1, Coordinates c1)
{
  int c, i;

  float result[1][MAT_COLUMN];

  for (c = 0; c < MAT_COLUMN; c++)
  {
    result[0][c] = 0;
    for (i = 0; i<MAT_ROW; i++)
    {
      result[0][c] += t1[c][i] * c1[0][i];
    }
  }

  for (c = 0; c < MAT_COLUMN; c++)
  {
    c1[0][c] = result[0][c];
  }
  printf("\n");
}

void matrixMulitply(float results[MAT_ROW][MAT_COLUMN], float (*const *array)[4], int size)
{
  int i, j, k, l;

  for (j = 0; j < MAT_ROW; j ++)
  {
    for (k = 0; k < MAT_COLUMN; k++)
    {
      int sum = 0;
      for (l = 0; l < MAT_ROW; l++)
      {
        sum += array[2][j][l] * array[1][l][k];
      }
      array[0][j][k] = sum;
    }
  }
  for (i = 3; i < size; i ++)
  {
    for (j = 0; j < MAT_ROW; j ++)
    {
      for (k = 0; k < MAT_COLUMN; k++)
      {
        int sum = 0;
        for (l = 0; l < MAT_ROW; l++)
        {
          sum += array[i][j][l] * array[i-3][l][k];
        }
        array[i-2][j][k] = sum;
      }
    }
  }
  for (j = 0; j < MAT_ROW; j ++)
  {
    for (k = 0; k < MAT_COLUMN; k++)
    {
      int sum = 0;
      for (l = 0; l < MAT_ROW; l++)
      {
        sum += array[size][j][l] * array[size-3][l][k];
      }
      results[j][k] = sum;
    }
  }
}

void displayCoordinate(Coordinates c1)
{
  int r;
  for (r = 0; r < MAT_ROW; r++)
  {
    printf("%f ", c1[0][r]);
  }
  printf("\n");
}

void displayTransformer(Transformer t1)
{
  int r, c;
  for (r = 0; r < MAT_ROW; r++)
  {
    for (c = 0; c < MAT_COLUMN; c++)
    {
      printf("%f  ", t1[r][c]);
    }
    printf("\n");
  }
}

