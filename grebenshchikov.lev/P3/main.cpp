#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstddef>

namespace grebenshchikov
{
  size_t cntColNsm(const int *mtx, size_t rows, size_t cols)
  {
    size_t count = 0;
    for (size_t i = 0; i < cols; ++i)
    {
      int flag = 0;
      for (size_t j = 1; j < rows; ++j)
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

  bool uppTriMtx(const int *mtx, size_t rows, size_t cols)
  {
    if (rows == 0 || cols == 0)
    {
      return false;
    }
    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        if (i > j && mtx[i * cols + j] != 0)
        {
          return false;
        }
      }
    }
    return true;
  }
}

int main(int argc, char *argv[])
{
  const int args_count = 4;
  const size_t input_arg = 2;
  const size_t output_arg = 3;
  const int file_error = 2;

  if (argc < args_count)
  {
    std::cerr << "Not enough arguments";
    return 1;
  }
  if (argc > args_count)
  {
    std::cerr << "Too many arguments";
    return 1;
  }
  if (argv[1][1] != '\0' || (argv[1][0] != '1' && argv[1][0] != '2'))
  {
    std::cerr << "First parameter isnt a number or out of range\n";
    return 1;
  }

  std::ifstream in(argv[input_arg]);
  if (!in.is_open())
  {
    std::cerr << "Cannot open input file\n";
    return file_error;
  }
  int rows_in = 0;
  int cols_in = 0;
  if (!(in >> rows_in >> cols_in) || rows_in < 0 || cols_in < 0)
  {
    std::cerr << "Error reading file\n";
    return file_error;
  }
  const size_t rows = rows_in;
  const size_t cols = cols_in;

  const size_t kmax = 10000;
  int static_mtx[kmax] = {};
  int *dynamic_mtx = nullptr;
  int *mtx = nullptr;
  switch (*argv[1])
  {
  case '1':
    if (cols != 0 && rows > kmax / cols)
    {
      std::cerr << "Matrix size exceeds maximum allowed size\n";
      return file_error;
    }
    mtx = static_mtx;
    break;
  case '2':
    dynamic_mtx = static_cast< int * >(std::malloc(rows * cols * sizeof(int)));
    if (dynamic_mtx == nullptr && rows * cols > 0)
    {
      std::cerr << "Not enough memory\n";
      return file_error;
    }
    mtx = dynamic_mtx;
    break;
  }

  for (size_t i = 0; i < rows * cols; ++i)
  {
    if (!(in >> mtx[i]))
    {
      std::cerr << "Error reading file\n";
      std::free(dynamic_mtx);
      return file_error;
    }
  }

  std::ofstream out(argv[output_arg]);
  if (!out.is_open())
  {
    std::cerr << "Cannot open output file\n";
    std::free(dynamic_mtx);
    return file_error;
  }
  out << std::boolalpha << grebenshchikov::uppTriMtx(mtx, rows, cols) << '\n';
  out << grebenshchikov::cntColNsm(mtx, rows, cols) << '\n';
  std::free(dynamic_mtx);
  return 0;
}
