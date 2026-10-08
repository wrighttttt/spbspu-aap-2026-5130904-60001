#include <iostream>
int main()
{
  constexpr long long INITIAL_MAX = -1000000000000;
  constexpr long long INITIAL_MIN = 1000000000000;
  constexpr long long MIN_LENGTH_FOR_SUB_MAX = 2;
  constexpr int INVALID_INPUT_CODE = 1;
  constexpr int SHORT_SEQUENCE_CODE = 2;
  long long max = INITIAL_MAX;
  long long sub_max = INITIAL_MAX;
  long long ctn_min = 0;
  long long min = INITIAL_MIN;
  long long count = 0;

  while (true)
  {
    long long a = 0;
    std::cin >> a;

    if (std::cin.fail())
    {
      std::cerr << "Error: input is not a valid sequence of integers\n";
      return INVALID_INPUT_CODE;
    }
    if (a == 0)
    {
      break;
    }
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
      ctn_min = 0;
    }
    if (a == min)
    {
      ++ctn_min;
    }
    ++count;
  }
  int exit_code = 0;
  if (count < MIN_LENGTH_FOR_SUB_MAX)
  {
    std::cerr << "Error: sequence too short for SUB-MAX\n";
    exit_code = SHORT_SEQUENCE_CODE;
  }
  else
  {
    std::cout << sub_max << '\n';
  }
  std::cout << ctn_min << '\n';
  return exit_code;
}
