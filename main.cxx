#include <iostream>
#include <map>

int factorial(int n) {

    
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

template <typename T, size_t ChunkSize = 10>
class CustomAllocator {
public:
    using value_type = T;

    CustomAllocator() : current_size_(0), total_size_(0), data_(nullptr) 
    {
        ;;
    }

    template <typename U>
    struct rebind 
    {
        typedef CustomAllocator<U, ChunkSize> other;
    };

    T* allocate(std::size_t n) 
    {
        if (n > ChunkSize) 
        {
            throw std::bad_alloc();
        }

        if (current_size_ + n > total_size_) 
        {
            reserve(total_size_ + ChunkSize);
        }

        T* ptr = data_ + current_size_;
        current_size_ += n;
        return ptr;
    }

    void deallocate(T* p, std::size_t n) noexcept 
    {
        ;;
    }

    void reserve(std::size_t new_size) {
        if (new_size <= total_size_)
        {
            return;
        }

        T* new_data = static_cast<T*>(::operator new(new_size * sizeof(T)));

        if (data_) 
        {
            for (size_t i = 0; i < current_size_; ++i) 
            {
                new (new_data + i) T(std::move(data_[i]));
                data_[i].~T();
            }
            ::operator delete(data_);
        }

        data_ = new_data;
        total_size_ = new_size;
    }

    std::size_t current_size_;
    std::size_t total_size_;
    T* data_;
};

// template <typename T, size_t ChunkSize = 10>
// struct MyAllocator {
//     using value_type = T;
    
//     MyAllocator() = default;
    
//     template <typename U>
//     MyAllocator(const MyAllocator<U>&) {}
    
//     T* allocate(std::size_t n) {
//         return static_cast<T*>(::operator new(n * sizeof(T)));
//     }
    
//     void deallocate(T* _p, std::size_t _n) {
//         ::operator delete(_p);
//     }
// };

// template <typename T, typename Allocator = std::allocator<T>>
// class Container {
// private:
//     struct Node {
//         T data;
//         Node* next;
//         Node(const T& value) : data(value), next(nullptr) {}
//     };

//     Node* head; // Указатель на голову списка
//     Node* tail; // Указатель на хвост списка
//     Allocator allocator; // Аллокатор для управления памятью узлов списка
    
// public:
//     // Конструктор контейнера
//     Container() : head(nullptr), tail(nullptr) {}
    
//     // Добавление нового элемента в контейнер
//     void add(const T& value) {
//         auto newNode = allocator.allocate(1);
//         allocator.construct(newNode, value);
        
//         if (tail) {
//             tail->next = newNode;
//             tail = newNode;
//         } else {
//             head = tail = newNode;
//         }
//     }
    
//     // Обход контейнера в одном направлении с помощью функции
//     template <typename Function>
//     void traverse(Function func) {
//         for (Node* current = head; current != nullptr; current = current->next) {
//             func(current->data);
//         }
//     }

// };

int main() {
    // Обычный std::map
    std::map<int, int> usual_map_integers; 
    for (int i = 0; i < 10; ++i) {
        usual_map_integers.emplace(i, factorial(i));
    }

    for (const auto& pair : usual_map_integers) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << std::endl;
    // std::map с кастомным аллокатором
    using custom_map = std::map<int, int, std::less<>, CustomAllocator<std::pair<const int, int>>>;
    custom_map custom_map_integers; 
    for (int i = 0; i < 10; ++i) {
        custom_map_integers.emplace(i, factorial(i));
    }

    for (const auto& pair : custom_map_integers) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << std::endl;
    // Контейнер
    // Container<int> integer_container;

    // // Добавляем элементы в контейнер
    // integer_container.add(1);
    // integer_container.add(2);
    // integer_container.add(3);
    // integer_container.add(4);
    // integer_container.add(5);
    // integer_container.add(6);
    // integer_container.add(7);
    // integer_container.add(8);
    // integer_container.add(9);
    // integer_container.add(10);

    // // Обходим контейнер и выводим элементы
    // integer_container.traverse([](int value) {
    //     std::cout << value << " ";
    // });

    return 0;
}