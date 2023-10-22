/*Галкин Сергей Autumn2023 WEB-13*/

/*Ссылка на контест: https://contest.yandex.ru/contest/53768/enter
 *
 * 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив
 * целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите
 * минимальный индекс k минимального элемента массива A, равного
 * или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет,
 * выведите n. n, m ≤ 10000.Требования:  Время работы поиска k для
 * каждого элемента B[i]: O(log(k)).
 *
 * Внимание! В этой задаче для
 * каждого B[i] сначала нужно определить диапазон для бинарного
 * поиска размером порядка k с помощью экспоненциального поиска, а
 * потом уже в нем делать бинарный поиск.
 *
 * Формат входных данных.
 * В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
 *
 * in       out
 * 2 1      1
 * 1 2
 * 2
 *
 * 4 3      1 3 0
 * 2 4 5 7
 * 4 6 1

*/

#include <iostream>
//---CustomPow----------------------------------------------------------------------

int Pow(int base, int degree) {
    if (degree == 0)
        return 1;
    int buff = base;
    for (int i = 1; i < degree; ++i)
        base *= buff;
    return base;
}

//---CustomArray----------------------------------------------------------------------

struct CustomArray {
    int count_of_elements_ = 0;
    int* array_ = nullptr;

    //-------------------------------------------------------------------------

    CustomArray(const CustomArray&) = delete;

    //-------------------------------------------------------------------------

    CustomArray(int count_of_elements) : count_of_elements_(count_of_elements) {
        array_ = new int[count_of_elements_]{0};
        for (int i = 0;  i < count_of_elements_; ++i)
            std::cin >> array_[i];
    }

    //-------------------------------------------------------------------------

    ~CustomArray() {
        delete[] array_;
    }

};

//-------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const CustomArray& array) {
    for (int i = 0; i < array.count_of_elements_; ++i)
        out << array.array_[i] << " ";
    return out;
}

//-----CustomPair--------------------------------------------------------------------

struct CustomPair {
    int a = 0;
    int b = 0;
};

std::ostream& operator<<(std::ostream& out, const CustomPair& pair) {
    out << pair.a << " " << pair.b;
    return out;
}

//-----Solution--------------------------------------------------------------------

class Solution {
 public:
    CustomPair ExponentialSearch(const CustomArray& A, int target_number) {
        CustomPair pair{-1, -1};  // This struct contains the indexes of the interval
        if (A.array_[0] == target_number) {  // What if A[0] - our target?
            return pair = {0, 0};
        }
        int right = 0;
        int left = 0;
        for (int i = 0; i < A.count_of_elements_; ++i) {
            left = Pow(2, i);
            right = Pow(2, i + 1);
            if (A.array_[left] <= target_number && A.array_[right] > target_number) {
                pair = {left, right};
                break;
            }
        }
        return pair;
    }
 private:
};

void TestFunction() {
}

int main() {
    Solution s;
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    CustomArray A(n);  // sort
    CustomArray B(m);
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << s.ExponentialSearch(A, B.array_[0]) << std::endl;
    return 0;
}
