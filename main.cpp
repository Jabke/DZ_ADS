/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
*/

#include <iostream>

class Solution {
 public:
 private:
};

template<typename T>
class DefaultComparator {
 public:
  bool operator()(const T &first_element, const T &second_element) {
    if (first_element >= second_element) {
      return true;
    } else {
      return false;
    }
  }
};

template<typename T, typename Comparator = DefaultComparator<T>>
void Partition(int size_array, int* array) {
  Comparator comparator;  // 1st > 2nd
  int index_partition = std::rand()%(size_array-1);
  int partition = array[index_partition];
  std::cout << partition << std::endl;
  std::swap(array[size_array-1], array[index_partition]);
  int i = -1;
  int j = -1;
  while (true) {
    if (j == size_array-2)
      break;
    j++;
    if (comparator(array[j], partition)) { // array[j] > partition
      continue;
    } else {
      i++;
      std::swap(array[j], array[i]);
    }
  }
  std::cout << i << " |";
  for (int i = 0; i < j - 1; ++i)
    std::cout << "   ";
  std::cout << j << " | " << std::endl;
}

void TestFunction() {
}

int main() {
  int array[6] = {21, 20, 13, 14, 38, 16};
  Partition<int>(6, array);
  for (int i = 0; i < 6; i++) {
    std::cout << array[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
