/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
*/

#include <iostream>

class Queue {
 public:
  friend std::ostream& operator <<(std::ostream& out, const Queue& queue);
  Queue() {
    array_ = new int[buffer_size_]{0};
  }

  Queue(int buffer_size) : buffer_size_(buffer_size) {
    array_ = new int[buffer_size_]{0};
  }

  ~Queue() {
   delete[] array_;
  }
  void PushBack(int element) {
    if (head_ == -1 || tail_ == -1) {
      head_ = 0;
    }
    if (queue_size_ == buffer_size_)

    array_[queue_size_] = element;
    tail_ = queue_size_;
    queue_size_++;
  }

  int PopFront() {
    int buffer = array_[head_];
    head_++;
    queue_size_--;
    return buffer;
  }

  int GetQueueSize() {
    return this->queue_size_;
  }

  int GetBufferSize() {
    return this->buffer_size_;
  }
 private:
  int* array_ = nullptr;
  int buffer_size_ = 5;
  int queue_size_ = 0;
  int head_ = -1;  // Индекс первого элемента в очереди
  int tail_ = -1;  // Индекс последнего элемента в очереди

  void Expand() {
    if (array_ != nullptr) {
      int* new_array = new int[buffer_size_*2];
      for (int i = 0;)
    }
  }

  void Reduce() {
    /*
     *
     */
  }


};

std::ostream& operator <<(std::ostream& out, const Queue& queue) {
  if (queue.head_ <= queue.tail_) {
    for (int i = queue.head_; i <= queue.tail_; ++i) {
      out << queue.array_[i] << " ";
    }
  } else {

  }
  return out;
}

class Solution {
 public:
 private:
};

void TestFunction() {
}

int main() {
  /*int argument_one = 0;
    int argument_two = 0;
    std::cin >> argument_one >> argument_two;
    std::cout << "Repo" << std::endl;*/
  Queue que;
  que.PushBack(5);
  que.PushBack(2);
  que.PushBack(3);
  std::cout << "Buffer Size " << que.GetBufferSize() << std::endl;
  std::cout << "Queue Size " <<  que.GetQueueSize() << std::endl;
  std::cout << que.PopFront() << std::endl;
  std::cout << "Buffer Size " << que.GetBufferSize() << std::endl;
  std::cout << "Queue Size " << que.GetQueueSize() << std::endl;

    std::cout << que << std::endl;
    return 0;
}
