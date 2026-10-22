#include <cstddef>
#include <iostream>
#include <limits>
int main()
{
  constexpr long long initial_max = std::numeric_limits< long long >::min();
  constexpr long long initial_min = std::numeric_limits< long long >::max();
  constexpr size_t min_length_for_sub_max = 2;
  constexpr int invalid_input_code = 1;
  constexpr int short_sequence_code = 2;
  long long max = initial_max;
  long long sub_max = initial_max;
  size_t ctn_min = 0;
  long long min = initial_min;
  size_t count = 0;

  long long a = 0;
  while (std::cin >> a && a != 0)
  {
    if (a > max)
    {
      sub_max = max;
      max = a;
    }
    else if (a >= sub_max && a < max)
    {
      sub_max = a;
    }
    if (a < min)
    {
      min = a;
      ctn_min = 1;
    }
    else if (a == min)
    {
      ++ctn_min;
    }
    ++count;
  }

  if (std::cin.fail())
  {
    std::cerr << "Error: input is not a valid sequence of integers\n";
    return invalid_input_code;
  }
  int exit_code = 0;
  if (count < min_length_for_sub_max)
  {
    std::cerr << "Error: sequence too short for SUB-MAX\n";
    exit_code = short_sequence_code;
  }
  else
  {
    std::cout << sub_max << '\n';
  }
  std::cout << ctn_min << '\n';
  return exit_code;
}
