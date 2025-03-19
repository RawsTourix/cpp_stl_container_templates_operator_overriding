#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>

using namespace std;

// Переопределение операторов + и += для всех типов контейнеров с простым типом данных
template <template <typename...> class Container, typename T>
Container<T> operator+(const Container<T>& a, const Container<T>& b) {
    Container<T> result(a);
    result.insert(result.end(), b.begin(), b.end());
    return result;
}

template <template <typename...> class Container, typename T>
Container<T>& operator+=(Container<T>& a, const Container<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

// Переопределение операторов + и += для map
template <typename K, typename V>
map<K, V> operator+(const map<K, V>& a, const map<K, V>& b) {
    map<K, V> result(a);
    result.insert(b.begin(), b.end());
    return result;
}

template <typename K, typename V>
    map<K, V>& operator+=(map<K, V>& a, const map<K, V>& b) {
    a.insert(b.begin(), b.end());
    return a;
}

// Переопределение операторов + и += для set
template <typename T>
set<T> operator+(const set<T>& a, const set<T>& b) {
    set<T> result(a);
    result.insert(b.begin(), b.end());
    return result;
}

template <typename T>
set<T>& operator+=(set<T>& a, const set<T>& b) {
    a.insert(b.begin(), b.end());
    return a;
}

// Вывод элементов контейнера с простым типом данных (для set тоже работает)
template <template <typename...> class Container, typename T>
void print(const string& message, const Container<T>& container) {
    cout << message;
    for (const auto& elem : container)
        cout << elem << " ";
    cout << endl;
}

// Вывод элементов контейнера map
template <typename K, typename V>
void print(const string& message, const map<K, V>& container) {
    cout << message;
    for (const auto& [key, value] : container) {
        cout << "{" << key << ": " << value << "} ";
    }
    cout << endl;
}

// Пример работы переопределения
// для vector
void vector_example() {
    vector<int> v1 { 1, 2, 3 };
    vector<int> v2 { 4, 5, 6 };
    vector<int> v3 { 7, 8, 9 };
    
    vector<int> v = v1 + v2;
    v += v3;
    
    print("vector<int>:\t\t", v);
}

// для list
void list_example() {
    list<float> l1 { 1.1, 2.2, 3.3 };
    list<float> l2 { 4.4, 5.5, 6.6 };
    list<float> l3 { 7.7, 8.8, 9.9 };
    
    list<float> l = l1 + l2;
    l += l3;
    
    print("list<float>:\t\t", l);
}

// для deque
void deque_example() {
    deque<char> d1 { 'a', 'b', 'c' };
    deque<char> d2 { 'd', 'e', 'f' };
    deque<char> d3 { 'g', 'h', 'i' };
    
    deque<char> d = d1 + d2;
    d += d3;
    
    print("deque<char>:\t\t", d);
}

// для map
void map_example() {
    map<int, string> m1 { {1, "first"} };
    map<int, string> m2 { {2, "second"} };
    map<int, string> m3 { {3, "third"} };
    
    map<int, string> m = m1 + m2;
    m += m3;
    
    print("map<int, string>:\t", m);
}

// для set
void set_example() {
    set<bool> s1 { true, false };
    set<bool> s2 { false, true };
    set<bool> s3 { true, false };
    
    set<bool> s = s1 + s2;
    s += s3;
    
    print("set<bool>:\t\t", s);
}

int main() {
    vector_example();
    list_example();
    deque_example();
    map_example();
    set_example();
    
    return 0;
}