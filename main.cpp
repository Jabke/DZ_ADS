/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
 *
 *

Реализовать очередь с динамическим зацикленным буфером.

Обрабатывать команды push back и pop front.
Формат ввода

В первой строке количество команд n. n ≤ 1000000.

Каждая команда задаётся как 2 целых числа: a b.

a = 2 - pop front
a = 3 - push back

Если дана команда pop front, то число b - ожидаемое значение. Если команда pop front вызвана для пустой структуры данных, то ожидается “-1”.
Формат вывода

Требуется напечатать YES - если все ожидаемые значения совпали. Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
*/

#include <iostream>
#include <string>
#include <sstream>

class Queue {
 public:
  friend std::ostream& operator <<(std::ostream& out, const Queue& queue);
  Queue() {
    array_ = new int[buffer_size_]{0};
  }

  Queue(int buffer_size) : buffer_size_(buffer_size) {
    array_ = new int[buffer_size_]{0};
  }

  Queue(int array_size, int* array) {
    buffer_size_ = 2*array_size;
    queue_size_ = array_size;
    array_ = new int[buffer_size_]{0};
    for(int i = 0; i < queue_size_; ++i) {
      array_[i] = array[i];
    }
    head_ = 0;
    tail_ = array_size - 1;
  }

  ~Queue() {
   delete[] array_;
  }
  void PushBack(int element) {
    if (head_ == -1 || tail_ == -1) {
      head_ = 0;
      tail_ = 0;
    }
    if (queue_size_ == buffer_size_)
      Expand();
    int debug_buffer = (tail_ + 1)%buffer_size_;
    if (queue_size_ == 0)
      debug_buffer = 0;
    array_[debug_buffer] = element;
    tail_ = queue_size_;
    queue_size_++;
  }

  int PopFront() {
    if (queue_size_ == 0)
      return -1;  // Условие задачи
    int buffer = array_[head_];
    queue_size_--;
    /*if (queue_size_ != 0)
      head_++;
    if (head_ == buffer_size_ - 1)
      head_ = 0;*/
    head_ = (head_ + 1)%buffer_size_;
    if (queue_size_ == 0) {
      head_ = 0;
      tail_ = 0;
    }
    //if (queue_size_ > 3 && queue_size_ <= (buffer_size_/3))
    // Reduce();
    return buffer;
  }

  int GetQueueSize() {
    return this->queue_size_;
  }

  int GetBufferSize() {
    return this->buffer_size_;
  }

  int GetHeadElement() {
    return array_[head_];
  }

  int GetTailElement() {
    return array_[tail_];
  }
  void OutBuffer() {
    std::cout << "Buffer ";
    for (int i = 0; i < buffer_size_; ++i) {
      std::cout << array_[i] << " " ;
    }
    std::cout << std::endl;
  }
  void OutQueue() {
    std::cout << "Queue ";
    for (int i = 0; i < queue_size_; ++i) {
      if ((head_ + i) < (buffer_size_ - 1)) {
        std::cout << array_[head_ + i] << " ";
      } else {
        std::cout << array_[i] << " ";
      }
    }
    std::cout << std::endl;
  }
 private:
  int* array_ = nullptr;
  int buffer_size_ = 3;
  int queue_size_ = 0;
  int head_ = -1;  // Индекс первого элемента в очереди
  int tail_ = -1;  // Индекс последнего элемента в очереди

  void Expand() {
    if (array_ != nullptr) {
      int* new_array = new int[2*buffer_size_]{0};
      int j = 0;
      /*for (int i = tail_; i != head_; i = ((i + 1)%buffer_size_)) {
        new_array[j] = array_[i];
        std::cout << array_[i] << std::endl;
        j++;
      }*/
      for (int i = 0; i < queue_size_; ++i) {
        /*
         * head_ + i - ищем элемент в середине массива;
         * buffer_size_ - 1 - пока не дойдем до кона массива
         */
        if ((head_ + i) < (buffer_size_ - 1)) {
          new_array[i] = array_[head_ + i];
        } else {
          new_array[i] = array_[i];
        }
      }
      buffer_size_ *= 2;
      delete[] array_;
      head_ = 0;
      tail_ = queue_size_ - 1;
      array_ = new_array;
    }
  }

  void Reduce() {
    if (queue_size_ <= (buffer_size_ / 3) && buffer_size_ / 2 > 2) {
      buffer_size_ /= 2;
      int* new_array = new int[buffer_size_]{0};
      int j = 0;
      for (int i = head_; i != queue_size_; i = (i + 1)%buffer_size_) {
        new_array[j] = array_[i];
        ++j;
      }
      delete[] array_;
      head_ = 0;
      tail_ = queue_size_ - 1;
      array_ = new_array;
    }
  }


};

std::ostream& operator <<(std::ostream& out, const Queue& queue) {
  if (queue.head_ <= queue.tail_) {
    for (int i = queue.head_; i <= queue.tail_; ++i) {
      out << queue.array_[i] << " ";
    }
  } else {

  }
  /*for (int i = 0; i < queue.buffer_size_; ++i) {
    out << queue.array_[i] << " ";
  }*/
  return out;
}

class Solution {
 public:
  void YesOrNo(std::ostream& out, std::istream& in) {
    int quantity_elements = 0;
    in >> quantity_elements;
    int method_selection = 0;
    int expected_value = 0;
    Queue queue;
    bool flag = true;
    int debug_buffer = 0;
    for (int i = 0; i < quantity_elements; ++i) {
      in >> method_selection;
      in >> expected_value;
      switch (method_selection) {
        case 2:
          /*queue.OutQueue();
          queue.OutBuffer();*/
          debug_buffer = queue.PopFront();
          if (expected_value == debug_buffer && flag) {
            flag = true;
          } else {
            flag = false;
          }
          break;
        case 3:
          queue.PushBack(expected_value);
          break;
      }
      /*queue.OutQueue();
      queue.OutBuffer();*/
    }
    if (flag == true) {
      out << "YES";
    } else {
      out << "NO";
    }

  }
 private:
};

void TestFunction() {
  constexpr int count_of_tests = 20;
  std::istringstream streams_string[count_of_tests];
  streams_string[0].str("3 3 44 3 50 2 44");
  streams_string[1].str("2 2 -1 3 10");
  streams_string[2].str("2 3 44 2 66");
  streams_string[3].str("5 2 -1 2 -1 3 44 3 -44 2 44");
  streams_string[4].str("10 3 5 3 6 3 44 3 -44 3 54 3 44 3 20 3 30 3 20 2 5");  // должно быть yes
  streams_string[5].str("6 3 5 3 6 3 44 3 -44 2 5 2 6 2 44 2 -44");  // Сначала расширяется потом сжимается
  streams_string[6].str("6 3 5 3 6 3 44 2 5 3 54 2 6");  // 5 6 44 -> 0 6 44 -> 54 6 44
  streams_string[7].str("6 3 5 3 6 3 44 3 55 2 5 2 6 3 56 2 44"); // Сначала расширяемся, потом получаем нечто такое 0 * * * 0 0
  streams_string[8].str("8 3 5 3 6 3 44 3 55 2 5 2 6 3 56 2 -1");  // Расширение -> выем -> добавление -> расширение
  streams_string[9].str("9 3 5 3 6 3 44 3 55 2 5 2 6 3 56 2 -1 2 55");  // Не верно одно число в середине
  streams_string[11].str("13 3 118 2 118 3 101 2 101 3 6 3 110 3 3 2 6 2 110 2 3 3 91 2 91 3 70"); // 7 тест контест
  streams_string[10].str("14 3 118 3 110 3 101 3 105 3 109 3 110 3 3 2 118 2 110 2 101 2 105 2 109 2 110 2 3");
  streams_string[12].str("15 3 118 3 110 3 101 2 118 2 110 2 101 2 -1 3 105 3 109 3 110 3 3 2 105 2 109 2 110 2 3");
  streams_string[13].str("16 3 118 3 110 3 101 2 118 2 110 2 101 2 -1 3 105 3 109 3 110 3 3 2 105 2 109 2 110 2 3 2 -1");
  streams_string[14].str("6 2 -1 3 1 3 2 2 1 2 2 2 -1");
  streams_string[15].str("7 3 0 3 0 3 0 2 0 2 0 2 0 2 -1");
  streams_string[16].str("7 3 -1 3 -1 3 -1 2 -1 2 -1 2 -1 2 -1");
  streams_string[17].str("7 3 10 3 11 3 12 2 -1 2 11 2 12 2 -1");
  streams_string[18].str("8 2 2 2 11 3 10 3 -1 2 10 3 10 2 -1 2 10");
  streams_string[19].str("7 3 -2 3 -11 2 -2 2 -11 2 -10 3 -10 2 -10");
  // streams_string[10].str("9 3 5 3 4 3 6 2 5 2 4 3 7 3 8 2 6 2 7");

    // Значение не совпало где-то посередине
  Solution s;
  std::ostringstream answer;
 /* std::string buffer_string = "";
  s.YesOrNo(answer, streams_string[0]);
  buffer_string = answer.str();
  answer.str("");
  if (buffer_string == answers[0]) {
    std::cout << "Test " << 0 << " OK" << std::endl;
  } else {
    std::cout << "Test " << 0 << " WA" << std::endl;
  }*/
  std::string answers[count_of_tests] = {
      {"YES"},
      {"YES"},
      {"NO"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"NO"},
      {"NO"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"YES"},
      {"NO"},
      {"NO"},
      {"NO"},
  };

  std::string buffer_string = "";
  for (int i = 0; i < count_of_tests; ++i) {
    s.YesOrNo(answer, streams_string[i]);
    buffer_string = answer.str();
    answer.str("");
    if (buffer_string == answers[i]) {
      std::cout << "Test " << i << " OK" << std::endl;
    } else {
      std::cout << "Test " << i << " WA" << std::endl;
    }
  }

}

int main() {
  // TestFunction();
  Solution s;
  s.YesOrNo(std::cout, std::cin);
  return 0;
}
