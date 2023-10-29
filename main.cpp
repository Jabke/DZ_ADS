/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
 *
 * Требование для всех вариантов Задачи 4
 * Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
 * Решение должно поддерживать передачу функции сравнения снаружи.
 * Куча должна быть динамической.
 * 4.1 Слияние массивов.
 * Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
 * Требования: время работы O(N * logK). Ограничение на размер кучи O(K)..
 * Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива
 * и элементы массива. Каждый массив упорядочен по возрастанию.
 * Формат выходных данных: Итоговый отсортированный массив.
 *
 * in       out
 * 3        1 6 10 50 70 90
 * 1
 * 6
 * 2
 * 50 90
 * 3
 * 1 10 70
*/

#include <iostream>
#include <string>
#include <sstream>

struct OutOfRange : public std::exception {
    const char * what () const throw () {
        return "Out of range";
    }
};

//--Vector------------------------------------------------------------------------
template<typename T>
class Vector {
  public:
  Vector() : size_(0), capacity_(0), idx_last_element_(0) {
  }
//------------------------------------------------------------------------------

  Vector(size_t capacity) {
    size_ = 0;
    capacity_ = capacity;
    array_ = new T[capacity_]{T()};
  }

//------------------------------------------------------------------------------

  Vector(size_t size_array, T* array) {
    size_ = size_array;
    capacity_ = 2 * size_;
    array_ = new T[capacity_]{T()};
    for (int i = 0; i < size_array; ++i) {
      array_[i] = array[i];
    }
    idx_last_element_ = size_ - 1;
  }

//------------------------------------------------------------------------------

  Vector(size_t size, const T& default_value) {
    size_ = size;
    capacity_ = 2 * size_;
    array_ = new T[capacity_];
    for (int i = 0; i < capacity_; ++i) {
      array_[i] = default_value;
    }
    idx_last_element_ = size_ - 1;
  }

//------------------------------------------------------------------------------

    Vector(const Vector& copied_vector) {
        this->size_ = copied_vector.size_;
        this->capacity_ = copied_vector.capacity_;
        this->array_ = new T[this->capacity_];
        for (int i = 0; i < copied_vector.size_; ++i)
            this->array_[i] = copied_vector.array_[i];
      idx_last_element_ = size_ - 1;
    }

//------------------------------------------------------------------------------
    ~Vector() {
        delete[] array_;
    }

//------------------------------------------------------------------------------

  Vector& operator=(const Vector<T>& v) {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    if (!(this->array_ == nullptr))
      delete[] array_;
    array_ = new T[capacity_];
    for (int i = 0; i < v.GetSize(); ++i)
      array_[i] = v.array_[i];
  }

//------------------------------------------------------------------------------

    void SetElement(int idx, const T& value) {
      if (idx < (capacity_ - 1) && capacity_ != 0) {  // Расширение не требуется
        if (idx < size_) {
          array_[idx] = value;
          return;
        }
        size_++;
        array_[idx] = value;
        if (idx != 0)
          idx_last_element_++;
      } else {
        capacity_ *= 2;
        T* new_array = new T[capacity_]{T()};
        for (int i = 0; i < this->size_; ++i) {
          new_array[i] = array_[i];
        }
        delete[] array_;
        array_ = new_array;
        size_++;
        array_[idx] = value;
        if (idx != 0)
          idx_last_element_++;
      }
  /*
      if (size_ + 1 >= capacity_) {
        capacity_ *= 2;
        T* new_array = new T[this->capacity_]{T()};
        for (int i = 0; i < this->size_; ++i)
          new_array[i] = this->array_[i];
        delete[] array_;
        array_ = new_array;
      }
      array_[idx] = value;
      if (idx >= size_)
        size_++;*/
    }

//------------------------------------------------------------------------------

     T operator()(int i) const {  // Просто возвращает вызванный элемент
        try {
            if (i >= this->size_)
                throw OutOfRange();
            T &element = this->array_[i];
            return element;
        } catch(OutOfRange& e) {
            std::cout << e.what() << std::endl;
        }
    }

//------------------------------------------------------------------------------
  void PushBack(T value) {
    if (size_ != 0)
      this->SetElement(this->idx_last_element_ + 1, value);
    this->SetElement(this->idx_last_element_, value);
  }
//------------------------------------------------------------------------------

    int GetSize() const{
        return size_;
    }

//------------------------------------------------------------------------------

    int GetCapacity() const{
        return capacity_;
    }
//------------------------------------------------------------------------------

  int GetIdxLastElement() const{
    return idx_last_element_;
  }

  private:
    T* array_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
    size_t idx_last_element_ = 0;
};

//------------------------------------------------------------------------------

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v) {
    for (int i = 0; i < v.GetSize(); ++i)
        out << v(i) << " ";

    return out;
}

//-DefaultComparator------------------------------------------------------------

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

//--Heap------------------------------------------------------------------------

template<typename T, typename Comparator = DefaultComparator<T>>  // T - тип данных массива, Comparator - компаратор
class Heap {
  public:

    //------------------------------------------------------------------------------
    /*
     * Для создания кучи есть два возможных варианта, первый - это если мы создаём кучу из массива и вручную добавляем
     * все элементы из него в новый массив(метод Add)
     * Второй вариант, создать кучу из переданного массива
     */
    explicit Heap(Vector<T> array) : array_(array.GetCapacity()) {
      for (int i = 0; i < array.GetSize(); ++i) {
        this->array_.SetElement(i, array(i));
        Siftup(i);
      }
    }

    //------------------------------------------------------------------------------

    Heap(const Heap& copied_heap) {

    }

    //------------------------------------------------------------------------------

    ~Heap() {

    }

    //------------------------------------------------------------------------------

    void Add(T element) {  // Добавляет элемент в кучу
      array_.PushBack(element);
      Siftup(array_.GetIdxLastElement());
    }

    //------------------------------------------------------------------------------

    int ExtractTop() {

    }

    //------------------------------------------------------------------------------
    /*
     * Функция позволяет просмотреть верхний элемент, но не удаляет его из кучи
     */
    int Top() const {

    }

    Vector<T> GetArray() const {
      return array_;
    }

  private:
    Comparator comparator_;
    Vector<T> array_;
    //------------------------------------------------------------------------------

    int GetParentIndex(int index_child) {
      return ((index_child - 1) / 2);
    }

  //------------------------------------------------------------------------------

    int GetLeftChildIndex(int index_parent) {
      return (2 * index_parent + 1);
    }

  //------------------------------------------------------------------------------

    int GetRightChildIndex(int index_parent) {
      return (2 * index_parent + 2);
    }

  //------------------------------------------------------------------------------
    void Siftup(int sifted_element) {
      if (sifted_element == 0)
        return;
      T debug_element = array_(sifted_element);
      int buffer = 0;
      int parent_index = 0;
      while (sifted_element != 0) {
        parent_index = GetParentIndex(sifted_element);
        if (!comparator_(array_(sifted_element), array_(parent_index))) {
          buffer = array_(parent_index);
          array_.SetElement(parent_index, array_(sifted_element));
          array_.SetElement(sifted_element, buffer);
          sifted_element = parent_index;
        } else {
          break;
        }
      }
    }

    //------------------------------------------------------------------------------
    void Hepify() {  // Будем идти от последнего элемента к первому и вызывать SiftDown

    }
    //------------------------------------------------------------------------------

    void SiftDown(int sifted_element) {

    }
};

/*
 * Почему это не работает?
 *
 * template<typename T, typename Comparator>
std::ostream& Heap<T, Comparator>::operator<<(std::ostream& out, const Heap<T, Comparator>& heap) {
    out << heap.array_;
  return out;
}*/

template<typename T, typename Comparator = DefaultComparator<T>>
std::ostream& operator<<(std::ostream& out, const Heap<T, Comparator>& heap) {
  out << heap.GetArray();
  return out;
}

//------------------------------------------------------------------------------
template<typename T, typename Comp = DefaultComparator<T>>
class Solution {
 public:
    void CombiningArray(Heap<T, Comp>& heap, Vector<T> v) {
      for (int i = 0; i < v.GetSize(); ++i) {
        heap.Add(v(i));
      }
    }
 private:
};

void TestFunction() {

  constexpr int count_tests = 2;
  constexpr int count_arrays = 4;
  std::string values[count_arrays] = {
      {"3 10 4 "},
      {"2 8 9 "},
      {"1 50 70"},
      {"100 115 2"}};

  std::string sizes[count_arrays] {
      {"3"},
      {"3"},
      {"3"},
      {"3"}
  };
  Vector<Vector<int>> vecor_of_vectors(count_arrays);
  int solution[3][6] = {{2, 3, 4, 10, 8, 9},
                        {1, 3, 4, 10, 50, 70},
                        {2, 10, 3, 100, 115, 4}};

  for (int i = 0; i < count_arrays; ++i) {
    std::istringstream sizes_stream(sizes[i]);
    std::istringstream values_stream(values[i]);

    sizes_stream.str(sizes[i]);
    values_stream.str(values[i]);
    int s = 0;
    sizes_stream >> s;
    Vector<int> v(s);
    for (int j = 0; j < s; ++j) {
      int val = 0;
      values_stream >> val;
      v.SetElement(j, val);
    }
    vecor_of_vectors.SetElement(i, v);
  }
  for (int i = 0; i < count_arrays; ++i) {
    std::cout << "v[" << i << "]: " << vecor_of_vectors(i) << std::endl;
  }

  for (int i = 1; i < count_arrays; ++i) {
    Heap<int> heap(vecor_of_vectors(0));
    Solution<int> s;
    s.CombiningArray(heap, vecor_of_vectors(i));
    Vector<int> v = heap.GetArray();
    std::cout << "Test " << i << ": " << v;
    bool test_flag = true;
    for (int j = 0; j < 6; ++j) {
      if (solution[i - 1][j] == v(j)) {
        continue;
      }
      test_flag = false;
      break;
    }
    if (test_flag) {
      std::cout << " OK" << std::endl;
    } else {
      std::cout << " WA" << std::endl;
    }
  }
}

int main() {
  /*
  * in       out
  * 3        1 6 10 50 70 90
      * 1
      * 6
      * 2
      * 50 90
      * 3
      * 1 10 70
*/


  return 0;
}
