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

struct OutOfRange : public std::exception {
    const char * what () const throw () {
        return "Out of range";
    }
};

//--Vector------------------------------------------------------------------------
template<typename T>
class Vector {
  public:
    Vector(size_t size) {
        size_ = size;
        capacity_ = 2 * size_;
        array_ = new T[capacity_]{T()};
    }

    Vector(size_t size, const T& default_value) {
        size_ = size;
        capacity_ = 2 * size_;
        array_ = new T[capacity_];
        for (int i = 0; i < capacity_; ++i)
            array_[i] = default_value;
    }

    Vector(const Vector& copied_vector) {
        this->size_ = copied_vector.size_;
        this->capacity_ = copied_vector.capacity_;
        this->array_ = new T[this->capacity_];
        for (int i = 0; i < copied_vector.size_; ++i)
            this->array_[i] = copied_vector.array_[i];
    }
    ~Vector() {
        delete[] array_;
    }


    T& operator()(int i) {
        try {
            if (i >= this->size_)
                throw OutOfRange();
            T &element = this->array_[i];
            return element;
        } catch(OutOfRange& e) {
            std::cout << e.what() << std::endl;
        }
    }

    T& operator()(int i) const {
        try {
            if (i >= this->size_)
                throw OutOfRange();
            T &element = this->array_[i];
            return element;
        } catch(OutOfRange& e) {
            std::cout << e.what() << std::endl;
        }
    }

    int GetSize() const{
        return size_;
    }

    int GetCapacity() const{
        return capacity_;
    }

  private:
    T* array_ = nullptr;
    size_t capacity_ = 0;
    size_t size_ = 0;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& v) {
    for (int i = 0; i < v.GetSize(); ++i)
        out << v(i) << " ";

    return out;
}
//--Heap------------------------------------------------------------------------
class Heap {
  public:

    //------------------------------------------------------------------------------

    Heap() {

    }

    //------------------------------------------------------------------------------

    Heap(const Heap& copied_heap) {

    }

    //------------------------------------------------------------------------------

    ~Heap() {

    }

    //------------------------------------------------------------------------------

    void Add(int element) {

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
  private:
    //------------------------------------------------------------------------------

    void Siftup() {

    }

    //------------------------------------------------------------------------------

    void SiftDown() {

    }
};
//------------------------------------------------------------------------------
class Solution {
 public:
 private:
};

void TestFunction() {
}

int main() {
    Vector<int> v(5);
    v(1) = 1;
    std::cout << v << std::endl;
    /*int argument_one = 0;
    int argument_two = 0;
    std::cin >> argument_one >> argument_two;
    std::cout << "Repo" << std::endl;*/
    return 0;
}
