#include <iostream>
#include <stdexcept>
#include <algorithm>  // std::sort

template <typename T>
class SimpleVector {
private:
    T* array;  // �����͸� ������ �迭
    size_t current_size;  // ���� ������ ����
    size_t current_capacity;  // �迭�� �뷮

public:
    // �⺻ ������: ũ�Ⱑ 10�� �迭�� ����
    SimpleVector() : current_size(0), current_capacity(10) {
        array = new T[current_capacity];  // ũ�Ⱑ 10�� �迭 ����
    }

    // ���ڸ� �ϳ� �޴� ������: �ش� ���� ũ���� �迭�� ����
    explicit SimpleVector(size_t capacity) : current_size(0), current_capacity(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0.");
        }
        array = new T[current_capacity];  // ������ ũ���� �迭 ����
    }

    // ���� ������
    SimpleVector(const SimpleVector& other)
        : current_size(other.current_size), current_capacity(other.current_capacity) {
        array = new T[current_capacity];  // ���ο� �迭 �Ҵ�
        std::copy(other.array, other.array + current_size, array);  // ���� �迭�� �� ����
    }

    // �Ҹ���: �Ҵ�� �迭 �޸� ����
    ~SimpleVector() {
        delete[] array;
    }

    // push_back: ���Ҹ� �� �ڿ� �߰�
    void push_back(const T& value) {
        if (current_size >= current_capacity) {
            // ũ�Ⱑ �� á���� �迭 ũ�⸦ 5��ŭ �ø��� ����
            resize(current_capacity + 5);
        }
        array[current_size++] = value;  // �迭 ���� ���� �߰�
    }

    // pop_back: ������ ������ ���Ҹ� ����
    void pop_back() {
        if (current_size == 0) {
            return;  // ���Ұ� ������ �ƹ� ���۵� ���� ����
        }
        --current_size;  // ������ ���� ����
    }

    // size: ���� ������ ���� ��ȯ
    size_t size() const {
        return current_size;
    }

    // capacity: ���� �迭�� ũ��(�뷮) ��ȯ
    size_t capacity() const {
        return current_capacity;
    }

    // resize: �迭�� ũ�⸦ ����
    void resize(size_t new_capacity) {
        if (new_capacity <= current_capacity) {
            return;  // ���ο� ũ�Ⱑ ���� ũ�⺸�� ������ �ƹ� ���۵� ���� ����
        }

        // ���ο� ũ�⸸ŭ �迭 ���Ҵ�
        T* new_array = new T[new_capacity];
        std::copy(array, array + current_size, new_array);  // ���� ���ҵ��� ���ο� �迭�� ����

        delete[] array;  // ���� �迭 �޸� ����
        array = new_array;  // ���ο� �迭�� ������ ����
        current_capacity = new_capacity;  // �� �뷮���� ������Ʈ
    }

    // sortData: ���� �����͸� ����
    void sortData() {
        std::sort(array, array + current_size);  // STL sort �Լ� ����Ͽ� ����
    }

    // �ε��� ���� ������
    T& operator[](size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];  // �迭 ���Ҹ� ��ȯ
    }

    // const �ε��� ���� ������ (�б� ����)
    const T& operator[](size_t index) const {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        return array[index];  // �迭 ���Ҹ� ��ȯ
    }
};

int main() {
    SimpleVector<int> vec;  // ũ�� 10�� ���� ����

    vec.push_back(30);
    vec.push_back(10);
    vec.push_back(20);

    std::cout << "Size: " << vec.size() << std::endl;  // Size: 3
    std::cout << "Capacity: " << vec.capacity() << std::endl;  // Capacity: 10

    vec.push_back(40);  // ���� �߰�
    vec.push_back(50);  // ���� �߰�
    std::cout << "Size after adding more: " << vec.size() << std::endl;  // Size after adding more: 5
    std::cout << "Capacity after expansion: " << vec.capacity() << std::endl;  // Capacity after expansion: 15

    vec.sortData();  // ������ ����

    // ���ĵ� ���� ���
    std::cout << "Sorted Data: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";  // �ε����� �̿��� �� ���
    }
    std::cout << std::endl;

    return 0;
}