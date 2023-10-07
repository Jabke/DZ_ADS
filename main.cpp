/*
Ссылка на контест: https://contest.yandex.ru/contest/53768/enter

1.4 Инвертируйте значение бита в числе N по его номеру K.
Формат входных данных. Число N, номер бита K.
Формат выходных данных. Число с инвертированным битом в десятичном виде.

in          out
25 1        27
25 4        9 */

#include <iostream>

class Solution {
 public:
  uint InvertBit(uint original_num, uint K);  // K - bit number
};

//-----------------------------------------------------------------------------

uint Solution::InvertBit(uint original_num, uint K) {
    uint second_operand = 1;  // we need number like 00100(only one "1")
    return original_num^(second_operand << K);
}

//-----------------------------------------------------------------------------

void TestFunction() {
}

int main() {
    Solution s;
    std::cout << s.InvertBit(25, 4) << std::endl;
    return 1;
}
