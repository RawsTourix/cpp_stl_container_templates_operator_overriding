# Перегрузка операторов `+` и `+=` для контейнеров STL

Данный проект демонстрирует, как с помощью шаблонов перегрузить операторы `+` и `+=` для стандартных контейнеров C++: `vector`, `list`, `deque`, `map` и `set`.

## Перегрузка операторов

Перегрузка операторов позволяет определить поведение операторов для пользовательских типов данных. В этом проекте перегружаются операторы `+` и `+=` для объединения контейнеров одного типа.

- `operator+` создает новый контейнер, содержащий элементы обоих входных контейнеров.
- `operator+=` добавляет элементы правого контейнера к левому.

## Шаблоны для контейнеров

1. **Последовательные контейнеры (`vector`, `list`, `deque`, `set`**)

   Для этих контейнеров используются шаблоны с одним типовым параметром (`typename T`):

   ```cpp
   template <template <typename> class Container, typename T>
   Container<T> operator+(const Container<T>& a, const Container<T>& b) {
       Container<T> result(a);
       result.insert(b.begin(), b.end());
       return result;
   }

   template <template <typename> class Container, typename T>
   Container<T>& operator+=(Container<T>& a, const Container<T>& b) {
       a.insert(b.begin(), b.end());
       return a;
   }
   ```

   В данном проекте `set` используется как последовательный контейнер.

2. **Ассоциативные контейне `map`**

   Для этого контейнера используются шаблоны с двумя параметрами (`typename K, typename V`):

   ```cpp
   template <template <typename, typename> class Container, typename K, typename V>
   Container<K, V> operator+(const Container<K, V>& a, const Container<K, V>& b) {
       Container<K, V> result(a);
       result.insert(b.begin(), b.end());
       return result;
   }

   template <template <typename, typename> class Container, typename K, typename V>
   Container<K, V>& operator+=(Container<K, V>& a, const Container<K, V>& b) {
       a.insert(b.begin(), b.end());
       return a;
   }
   ```

## Особенности реализации

### `map`

- Для `map` требуется отдельная перегрузка, потому что этот контейнер использует пары `std::pair<const K, V>`. Простая перегрузка для контейнеров с одним параметро`<typename T>` здесь не подходит.

- Для вывода `map` необходим отдельный шаблон, так как элементы этого контейнера представлены парами ключ-значение. При итерации по `map` мы распаковываем каждую пару и выводим её элементы по отдельности:

  ```cpp
  template <template <typename, typename> class Container, typename K, typename V>
  void print(const Container<K, V>& container) {
      for (const auto& [key, value] : container) {
          std::cout << "{" << key << ": " << value << "} ";
      }
      std::cout << std::endl;
  }
  ```

- **Почему`set`работает с общей перегрузкой, а `map` — нет?**

  Разница связана с типом элементов, которые хранят эти контейнеры:

  1. `set<T>` хранит значения типа `T`. Итераторы возвращают простой элемент.
  2. `map<K, V>` хранит пары `std::pair<const K, V>`. Итераторы возвращают эту пару.

  Вызов `result.insert(a.end(), b.begin(), b.end());` в `set` работает корректно. `set` игнорирует переданный итератор позиции `result.end()`, так как все элементы автоматически вставляются в отсортированном порядке. Для `map` же требуется отдельная перегрузка, так как добаление итератора позиции вызовет ошибку.

### `set`

- **Перегрузка операторов**: Несмотря на то что `set` тоже является ассоциативным контейнером, он требует перегрузки с одним параметром (`typename T`), потому что элементы `set` не представлены парами, в отличие от `map`.

- **Функция вывода**: Для `set` не требуется отдельная функция вывода — он совместим с общей функцией, используемой для последовательных контейнеров:

  ```cpp
  template <template <typename> class Container, typename T>
  void print(const std::string& message, const Container<T>& container) {
      std::cout << message;
      for (const auto& elem : container)
          std::cout << elem << " ";
      std::cout << std::endl;
  }
  ```

## Запуск кода

1. Клонируйте репозиторий:

   ```bash
   git clone https://github.com/RawsTourix/cpp_stl_container_templates_operator_overriding.git
   ```

2. Перейдите в папку с проектом и скомпилируйте код:

   ```bash
   cd cpp_stl_container_templates_operator_overriding
   g++ main.cpp -o main -std=c++20
   ```

3. Запустите программу:

   ```bash
   ./main
   ```

Код протестирован и корректно работает для `vector`, `list`, `deque`, `map` и `set`.