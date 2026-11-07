#include <iostream>
#include <istream>
#include <cstddef>
#include <new>
#include <cctype>

namespace grebenshchikov
{
  char *extend(const char *str, size_t size, size_t new_capacity)
  {
    char *const new_str = new char[new_capacity];
    for (size_t i = 0; i < size; ++i)
    {
      new_str[i] = str[i];
    }
    return new_str;
  }

  char *readStr(std::istream &in, size_t &size)
  {
    const size_t initial_capacity = 16;
    size_t capacity = initial_capacity;
    char *str = new char[capacity];
    size = 0;
    const bool is_skipws = in.flags() & std::ios_base::skipws;
    in >> std::noskipws;
    char ch = 0;
    while (in >> ch && ch != '\n')
    {
      if (size + 1 == capacity)
      {
        const size_t new_capacity = capacity * 2;
        char *new_str = nullptr;
        try
        {
          new_str = extend(str, size, new_capacity);
        }
        catch (const std::bad_alloc &)
        {
          delete[] str;
          if (is_skipws)
          {
            in >> std::skipws;
          }
          throw;
        }
        delete[] str;
        str = new_str;
        capacity = new_capacity;
      }
      str[size++] = ch;
    }
    str[size] = '\0';
    if (is_skipws)
    {
      in >> std::skipws;
    }
    return str;
  }

  char *latRmv(const char *src, char *result)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i)
    {
      const unsigned char ch = src[i];
      if (!std::isalpha(ch))
      {
        result[j++] = src[i];
      }
    }
    result[j] = '\0';
    return result;
  }

  char *shrSym(const char *str, char *result)
  {
    size_t j = 0;
    for (char letter = 'a'; letter <= 'z'; ++letter)
    {
      size_t i = 0;
      while (str[i] != '\0' && std::tolower(static_cast< unsigned char >(str[i])) != letter)
      {
        ++i;
      }
      if (str[i] == '\0')
      {
        result[j++] = letter;
      }
    }
    result[j] = '\0';
    return result;
  }
}

int main()
{
  size_t size = 0;
  char *str = nullptr;
  try
  {
    str = grebenshchikov::readStr(std::cin, size);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Empty input\n";
    delete[] str;
    return 1;
  }

  const size_t alphabet_size = 26;
  char *lat_res = nullptr;
  char *shr_res = nullptr;
  try
  {
    lat_res = new char[size + 1];
    shr_res = new char[alphabet_size + 1];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Not enough memory\n";
    delete[] lat_res;
    delete[] str;
    return 1;
  }

  std::cout << grebenshchikov::latRmv(str, lat_res) << '\n';
  std::cout << grebenshchikov::shrSym(str, shr_res) << '\n';

  delete[] shr_res;
  delete[] lat_res;
  delete[] str;
  return 0;
}
