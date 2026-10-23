#include <iostream>
#include <fstream>
#include <cstdlib>

int cntColNsm(const int *mtx, int rows, int cols)
{
  int count = 0;
  for (int i = 0; i < cols; ++i)
  {
    int flag = 0;
    for (int j = 1; j < rows; ++j)
    {
      const int preel = mtx[(j - 1) * cols + i];
      if (mtx[j * cols + i] == preel)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      ++count;
    }
  }
  return count;
}

int cntColNsm(const int *const *mtx, int rows, int cols)
{
  int count = 0;
  for (int i = 0; i < cols; ++i)
  {
    int flag = 0;
    for (int j = 1; j < rows; ++j)
    {
      const int preel = mtx[j - 1][i];
      if (mtx[j][i] == preel)
      {
        flag = 1;
        break;
      }
    }
    if (flag == 0)
    {
      ++count;
    }
  }
  return count;
}

bool uppTriMtx(const int *mtx, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return false;
  }
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (i > j && mtx[i * cols + j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

bool uppTriMtx(const int *const *mtx, int rows, int cols)
{
  if (rows == 0 || cols == 0)
  {
    return false;
  }
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (i > j && mtx[i][j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

void freeMtx(int **mtx, int rows)
{
  for (int i = 0; i < rows; ++i)
  {
    std::free(mtx[i]);
  }
  std::free(mtx);
}

int main(int argc, char *argv[])
{
  const int argsCount = 4;
  const int inputArg = 2;
  const int outputArg = 3;
  const int fileError = 2;

  if (argc < argsCount)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > argsCount)
  {
    std::cerr << "Too many arguments";
    return 1;
  }

  switch (*argv[1])
  {
  case '1':
  {
    std::ifstream in(argv[inputArg]);
    int rows = 0;
    int cols = 0;
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    {
      std::cerr << "Error reading file\n";
      return fileError;
    }

    const int kmax = 10000;
    if (rows * cols > kmax)
    {
      std::cerr << "Matrix size exceeds maximum allowed size\n";
      return fileError;
    }

    int mtx[kmax];
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(in >> mtx[i * cols + j]))
        {
          std::cerr << "Error reading file\n";
          return fileError;
        }
      }
    }

    if (uppTriMtx(mtx, rows, cols))
    {
      std::cout << "true\n";
    }
    else
    {
      std::cout << "false\n";
    }

    std::cout << cntColNsm(mtx, rows, cols) << '\n';

    std::ofstream out(argv[outputArg]);
    out << rows << " " << cols;
    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        out << " " << mtx[i * cols + j];
      }
    }
    out << '\n';
    if (uppTriMtx(mtx, rows, cols))
    {
      out << "true\n";
    }
    else
    {
      out << "false\n";
    }
    out << cntColNsm(mtx, rows, cols) << '\n';
    std::cout << '\n';
    return 0;
  }
  case '2':
  {
    std::ifstream in(argv[inputArg]);
    int rows = 0;
    int cols = 0;
    if (!(in >> rows >> cols) || rows < 0 || cols < 0)
    {
      std::cerr << "Error reading file\n";
      return fileError;
    }

    int **const mtx = static_cast< int ** >(std::malloc(rows * sizeof(int *)));
    if (mtx == nullptr && rows > 0)
    {
      std::cerr << "Not enough memory\n";
      return fileError;
    }
    for (int i = 0; i < rows; ++i)
    {
      mtx[i] = static_cast< int * >(std::malloc(cols * sizeof(int)));
      if (mtx[i] == nullptr && cols > 0)
      {
        freeMtx(mtx, i);
        std::cerr << "Not enough memory\n";
        return fileError;
      }
    }

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        if (!(in >> mtx[i][j]))
        {
          std::cerr << "Error reading file\n";
          freeMtx(mtx, rows);
          return fileError;
        }
      }
    }

    if (uppTriMtx(mtx, rows, cols))
    {
      std::cout << "true\n";
    }
    else
    {
      std::cout << "false\n";
    }

    std::cout << cntColNsm(mtx, rows, cols) << '\n';

    std::ofstream out(argv[outputArg]);
    out << rows << " " << cols;

    for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; ++j)
      {
        out << " " << mtx[i][j];
      }
    }
    out << '\n';
    if (uppTriMtx(mtx, rows, cols))
    {
      out << "true\n";
    }
    else
    {
      out << "false\n";
    }
    out << cntColNsm(mtx, rows, cols) << '\n';
    std::cout << '\n';
    freeMtx(mtx, rows);
    return 0;
  }

  default:
    std::cout << "First parameter isnt a number or out of range\n";
    return 1;
  }
}
