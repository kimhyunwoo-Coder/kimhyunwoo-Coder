#include <iostream>
#include <stdexcept>
#include <algorithm>  // std::sort

template <typename T>
class SimpleVector {
private:
    T* array;  // 데이터를 저장할 배열
    size_t current_size;  // 현재 원소의 개수
    size_t current_capacity;  // 배열의 용량

public:
    // 기본 생성자: 크기가 10인 배열을 생성
    SimpleVector() : current_size(0), current_capacity(10) {
        array = new T[current_capacity];  // 크기가 10인 배열 생성
    }

    // 숫자를 하나 받는 생성자: 해당 숫자 크기의 배열을 생성
    explicit SimpleVector(size_t capacity) : current_size(0), current_capacity(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0.");
        }
        array = new T[current_capacity];  // 지정된 크기의 배열 생성
    }

    // 복사 생성자
    SimpleVector(const SimpleVector& other)
        : current_size(other.current_size), current_capacity(other.current_capacity) {
        array = new T[current_capacity];  // 새로운 배열 할당
        std::copy(other.array, other.array + current_size, array);  // 기존 배열의 값 복사
    }

    // 소멸자: 할당된 배열 메모리 해제
    ~SimpleVector() {
        delete[] array;
    }

    // push_back: 원소를 맨 뒤에 추가
    void push_back(const T& value) {
        if (current_size >= current_capacity) {
            // 크기가 꽉 찼으면 배열 크기를 5만큼 늘리고 복사
            resize(current_capacity + 5);
        }
        array[current_size++] = value;  // 배열 끝에 원소 추가
    }

    // pop_back: 벡터의 마지막 원소를 제거
    void pop_back() {
        if (current_size == 0) {
            return;  // 원소가 없으면 아무 동작도 하지 않음
        }
        --current_size;  // 마지막 원소 제거
    }

    // size: 현재 원소의 개수 반환
    size_t size() const {
        return current_size;
    }

    // capacity: 현재 배열의 크기(용량) 반환
    size_t capacity() const {
        return current_capacity;
    }

    // resize: 배열의 크기를 변경
    void resize(size_t new_capacity) {
        if (new_capacity <= current_capacity) {
            return;  // 새로운 크기가 기존 크기보다 작으면 아무 동작도 하지 않음
        }

        // 새로운 크기만큼 배열 재할당
        T* new_array = new T[new_capacity];
        std::copy(array, array + current_size, new_array);  // 기존 원소들을 새로운 배열로 복사

        delete[] array;  // 기존 배열 메모리 해제
        array = new_array;  // 새로운 배열로 포인터 변경
        current_capacity = new_capacity;  // 새 용량으로 업데이트
    }

    // sortData: 내부 데이터를 정렬
    void sortData() {
        std::sort(array, array + current_size);  // STL sort 함수 사용하여 정렬
    }

    // 인덱스 접근 연산자
    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];  // 배열 원소를 반환
    }

    // const 인덱스 접근 연산자 (읽기 전용)
    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];  // 배열 원소를 반환
    }
};

int main() {
    SimpleVector<int> vec;  // 크기 10인 벡터 생성

    vec.push_back(30);
    vec.push_back(10);
    vec.push_back(20);

    std::cout << "Size: " << vec.size() << std::endl;  // Size: 3
    std::cout << "Capacity: " << vec.capacity() << std::endl;  // Capacity: 10

    vec.push_back(40);  // 원소 추가
    vec.push_back(50);  // 원소 추가
    std::cout << "Size after adding more: " << vec.size() << std::endl;  // Size after adding more: 5
    std::cout << "Capacity after expansion: " << vec.capacity() << std::endl;  // Capacity after expansion: 15

    vec.sortData();  // 데이터 정렬

    // 정렬된 벡터 출력
    std::cout << "Sorted Data: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";  // 인덱스를 이용해 값 출력
    }
    std::cout << std::endl;

    return 0;
}