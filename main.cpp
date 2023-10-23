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
#include <sstream>
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

    CustomArray(const CustomArray& new_array) {
        this->count_of_elements_ = new_array.count_of_elements_;
        this->array_ = new int[this->count_of_elements_]{0};
        for (int i = 0; i < count_of_elements_; ++i)
            this->array_[i] = new_array.array_[i];
    }

    //-------------------------------------------------------------------------

    CustomArray(int count_of_elements, std::istream& in = std::cin) : count_of_elements_(count_of_elements) {
        array_ = new int[count_of_elements_]{0};
        for (int i = 0;  i < count_of_elements_; ++i)
             in >> array_[i];
    }

    //-------------------------------------------------------------------------

    CustomArray(std::istream& in_num, std::istream& in = std::cin) {
        in_num >> count_of_elements_;
        array_ = new int[count_of_elements_]{0};
        for (int i = 0;  i < count_of_elements_; ++i)
            in >> array_[i];
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

/*
 * В общем виде может быть три случая
 * 1) Искомый элемент выходит за рамки предложенного отсортированного массива:
 * B[i] = 10; A = {1 2 3 4 5}.
 * 2) Есть элемент равный искомому B[i] = 4; A = {1 2 3 4 5}.
 * 3) Есть элемент больше искомого, но нет равных B[i] = 4; A = {1 2 3 5 7}.
 */

class Solution {
 public:

    /*
     * Если первое число и есть искомый элемент вернется пара со значением {0, 0}.
     * Если же искомый элемент выходит за рамки массива в котором он ищется
     * вернется пара со значениями {-1, -1}.
     */
    CustomPair ExponentialSearch(const CustomArray& A, int target_number) {
        CustomPair pair{-1, -1};  // This struct contains the indexes of the interval
        if (A.array_[0] >= target_number) {  // What if A[0] - our target?
            return pair = {0, 0};
        }
        if (A.array_[1] >= target_number) {  // What if A[1] - our target or immediately more A[1] ?
            return pair = {1, 1};
        }
        int right = 0;
        int left = 0;
        int i = -1;  // -1 For correct loop work below
        do {
            i++;
            left = Pow(2, i);
            right = Pow(2, i + 1);
            if (right > (A.count_of_elements_ - 1)) {
                right = A.count_of_elements_ - 1;
            }
            if (A.array_[left] <= target_number && A.array_[right] > target_number) {
                pair = {left, right};
                break;
            }
        } while (Pow(2, i + 1) < A.count_of_elements_);

        return pair;
    }

    /*
     * На вход подаётся отсортированный массив, диапазон отсортированного массива
     * в котором будет выполнен поиск и искомое число.
     */

    int BinarySearch(const CustomArray& A, const CustomPair& range, int target_number) {
        int left = range.a;
        int right = range.b;
        int mid = (right + left)/2;
        bool detect = false;
        while (left < right) {
            mid = (right + left)/2;
            if (A.array_[mid] == target_number) {
                detect = true;
                break;
            } else if (A.array_[mid] < target_number) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (detect) {
            return mid;
        }

        return right;  //  target_number гарантированно есть или большее число
    }
//-------------------------------------------------------------------------

    CustomArray Matching(const CustomArray& A, const CustomArray& B) {
        CustomArray resualt(B);
        CustomPair buffer_pair{0, 0};
        for (int i = 0; i < B.count_of_elements_; ++i) {
            buffer_pair = ExponentialSearch(A, B.array_[i]);
            if (buffer_pair.a < 0 || buffer_pair.b < 0) {
                resualt.array_[i] = A.count_of_elements_;
                continue;
            } else if(buffer_pair.a == 0 || buffer_pair.b == 0) {
                resualt.array_[i] = 0;
                continue;
            } else {
                resualt.array_[i] = BinarySearch(A, buffer_pair, B.array_[i]);
            }
        }
        return resualt;
    }

 private:
};

void TestFunctionFirst() {
    Solution s;
    std::istringstream in_a("1 4 5 7 8 9 10 11 12 13");
    std::istringstream in_b("11 12 1");
    CustomArray A{10, in_a};  // sort
    CustomArray B{3, in_b};  // sort
    std::cout << A << std::endl;
    std::cout << B << std::endl;
    std::cout << s.Matching(A, B) << std::endl;
}

int main() {
    Solution s;
    int n = 0;
    int m = 0;
    std::cin >> n >> m;
    CustomArray A{n, std::cin};  // sort
    CustomArray B{m, std::cin};

    std::cout << s.Matching(A, B);
    return 0;
}