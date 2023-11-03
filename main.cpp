/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
 *
 *
  Дано множество целых чисел из [0..10^9] размера n.

  Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
      10% перцентиль
      медиана
      90% перцентиль

 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом
 прохода двумя итераторами от начала массива к концу.

  Требования:
      К дополнительной памяти: O(n).
      Среднее время работы: O(n)
      Должна быть отдельно выделенная функция partition.
      Рекурсия запрещена.
      Решение должно поддерживать передачу функции сравнения снаружи.

  Формат ввода
  Сначала вводится кол-во элементов массива n. После сам массив.
  Формат вывода

  Параметры множества в порядке:
      10% перцентиль
      медиана
      90% перцентиль

  10
  1 2 3 4 5 6 7 8 9 10
  2
  6
  10
 *
*/

#include <iostream>
#include <sstream>
#include <string>

template<typename T>
class DefaultComparator {
 public:
  bool operator()(const T& first_element, const T& second_element) {
    if (first_element > second_element) {
      return true;
    } else {
      return false;
    }
  }
};

template <typename T, typename Comparator = DefaultComparator<T>>
int Partition(int* array, int left_idx, int right_idx) {
  if (left_idx == right_idx)
    return left_idx;

  int p_idx = rand()%(right_idx - left_idx) + left_idx;
  std::swap(array[p_idx], array[right_idx]);
  int i = left_idx;
  int j = left_idx;
  Comparator comp;
  while (i < right_idx && !comp(array[i], array[right_idx])) {  // Останавливается когда i указывает на первый элемент меньше заданного
    ++i;
  }

  if (i == right_idx) {
    j = right_idx;
  } else {
    j = i + 1;
  }

  int debug3 = array[right_idx];
  while (j < right_idx) {  // Останавливается когда указывает на i
    debug3 = array[right_idx];
    if (!comp(array[j], array[right_idx])) { // array[j] < array[right_idx]
      std::swap(array[i], array[j]);
      i++;
    }
    j++;
  }
  std::swap(array[i], array[j]);
  return i;  // индекс элемента в полученном массиве
}

template <typename T, typename Comparator = DefaultComparator<T>>
int kth_stat(int size_array, int* array, float less_then, Comparator comp = Comparator()) {
  int required_idx = less_then*size_array;
  int kth_stat_idx = -1;
  int left_idx = 0;
  int right_idx = size_array - 1;
  while (left_idx <= right_idx) {
    kth_stat_idx = Partition<T>(array, left_idx, right_idx);
    if (kth_stat_idx == required_idx) {
      break;
    } else if (kth_stat_idx > required_idx) {
      right_idx = kth_stat_idx - 1;
    } else {
      left_idx = kth_stat_idx + 1;
    }
  }
  return array[kth_stat_idx];
}

    class Solution {
     public:
      void FindPercentile(std::ostream& out, std::istream& in){
        int size = 0;
        in >> size;
        int* array = new int[size];
        for (int i = 0; i < size; ++i)
          in >> array[i];
        out << kth_stat<int>(size, array, 0.1) << std::endl;
        out << kth_stat<int>(size, array, 0.5) << std::endl;
        out << kth_stat<int>(size, array, 0.9) << std::endl;
        delete[] array;
      }
    };

void Tests() {
  constexpr int count_of_tests = 7;
  std::istringstream streams_string[count_of_tests];
  streams_string[0].str("10 1 2 3 4 5 6 7 8 9 10");
  streams_string[1].str("3 1 2 3");
  streams_string[2].str("5 9 15 22 33 50");
  streams_string[3].str("15 2 9 15 22 32 33 40 41 50 55 60 91 100 101 200");
  streams_string[4].str("10 -2 9 10 21 30 33 40 41 50 55");
  streams_string[5].str("3 2 1 3");
  streams_string[6].str("10 9 -2 10 30 33 21 40 55 50 41");
  std::string answers[count_of_tests] = {
      {"2\n6\n10\n"},
      {"1\n2\n3\n"},
      {"9\n22\n50\n"},
      {"9\n41\n101\n"},
      {"9\n33\n55\n"},
      {"1\n2\n3\n"},
      {"9\n33\n55\n"},
  };
  Solution s;
  std::string buffer_string = "";
  int array_size = 0;
  std::ostringstream answer;

  for (int i = 0; i < count_of_tests; ++i) {
    answer.str("");
    s.FindPercentile(answer, streams_string[i]);
    buffer_string = answer.str();
    std::cout << buffer_string;
    if (buffer_string == answers[i]) {
      std::cout << "Test " << i << " OK" << std::endl;
    } else {
      std::cout << "Test " << i << " WA" << std::endl;
    }
  }
}
int main()
{

  // Tests();
  Solution s;
  s.FindPercentile(std::cout, std::cin);
  return 0;
}
