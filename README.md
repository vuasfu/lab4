# lab4
# ФИО: Булгакова Юлия Олеговна

# Описание лабораторной работы
В задании 1 реализовать определение класса (поля, свойства, конструкторы (не менее трех), перегрузку оператора вывода для вывода полей, заданный метод согласно варианту). Протестировать все методы, включая конструкторы, все исходные данные вводятся с клавиатуры, не забывайте проверять данные на корректность.
В задании 2 добавить к реализованному в первом задании классу указанные в варианте перегруженные операции.
В главной функции main показать работу всех функций с дружественным интерфейсом.

# Задание 1

Реализовать класс Money.

Поля:
unsigned int rubles_ - количество рублей
short int kopeks_ - количество копеек

Метод:
Добавление произвольного количества копеек (unsigned int) к объекту типа Money. Результат должен быть типа Money.
Перегрузка оператора вывода:

```cpp

friend std::ostream& operator<<(std::ostream& os, const Money& money) {
  os << money.rubles_ << " руб. ";
  if (money.kopeks_ < 10) {
    os << "0";
  }
  os << money.kopeks_ << " коп.";
  return os;
}
```

1. Получили ссылку на поток вывода и константную ссылку на объект Money
2. Форматировали вывод: рубли + "руб." + дополнение нулем для копеек (если <10) + копейки + "коп."
3. Вернули поток вывода для поддержки цепочки операций

```cpp
Money Money::AddKopeks(unsigned int additional_kopeks) const {
  Money result = *this;
  
  long long total_kopeks = static_cast<long long>(result.kopeks_) + additional_kopeks;
  
  result.rubles_ += static_cast<unsigned int>(total_kopeks / 100);
  result.kopeks_ = static_cast<short int>(total_kopeks % 100);
  
  result.Normalize();
  
  return result;
}
```

1. Создали копию текущего объекта
2. Вычислили общее количество копеек (с учетом возможного переполнения)
3. Распределили копейки между полями rubles_ и kopeks_ (100 копеек = 1 рубль)
4. Нормализовали результат с помощью метода Normalize()
5. Вернули новый объект Money

Конструкторы
Конструктор по умолчанию:
```cpp
Money::Money() : rubles_(0), kopeks_(0) {}
```

Конструктор копирования:
```cpp
Money::Money(const Money& other) 
    : rubles_(other.rubles_), kopeks_(other.kopeks_) {}
```

Конструктор с параметрами:
```cpp
Money::Money(unsigned int rub, short int kop) 
    : rubles_(rub), kopeks_(kop) {
  if (kop < 0) {
    throw std::invalid_argument("Копейки не могут быть отрицательными");
  }
  Normalize();
}
```

1. В каждом конструкторе использован список инициализации для эффективной инициализации полей
2. В конструкторе с параметрами добавлена проверка на отрицательные копейки
3. Выполнена нормализация для корректного представления (копейки < 100)

# Тестирование
<img width="357" height="400" alt="image" src="https://github.com/user-attachments/assets/c62e415c-5bd3-4ce7-845f-9b6586d28bf8" />


# Задание 2

Перегрузить следующие операторы:

Унарные операции:
++ - добавление копейки к объекту типа Money (префиксный и постфиксный)
```cpp
Money& Money::operator++() {  // Префиксный ++
  ++kopeks_;
  Normalize();
  return *this;
}

Money Money::operator++(int) {  // Постфиксный ++
  Money temp = *this;
  ++(*this);
  return temp;
}
```
1. Префиксный ++: увеличиваем копейки, нормализуем результат, возвращаем ссылку на измененный объект
2. Постфиксный ++: сохраняем копию текущего объекта, вызываем префиксную версию, возвращаем копию
-- - вычитание копейки из объекта типа Money (префиксный и постфиксный)
```cpp
Money& Money::operator--() {  // Префиксный --
  if (kopeks_ == 0 && rubles_ == 0) {
    throw std::underflow_error("Нельзя вычесть копейку из нулевой суммы");
  }
  
  --kopeks_;
  if (kopeks_ < 0) {
    if (rubles_ > 0) {
      --rubles_;
      kopeks_ = 99;
    } else {
      kopeks_ = 0;
    }
  }
  return *this;
}

Money Money::operator--(int) {  // Постфиксный --
  Money temp = *this;
  --(*this);
  return temp;
}
```

1. Проверяем, можно ли вычесть копейку (сумма не должна стать отрицательной)
2. Учитываем заем рублей при необходимости (если копеек стало меньше 0)
3. Возвращаем соответствующий объект (ссылка для префиксной, копия для постфиксной)

Операции приведения типа:
unsigned int (явная) – результатом является количество рублей (копейки отбрасываются)

```cpp
explicit operator unsigned int() const {
  return rubles_;
}
```

double (неявная) – результатом являются копейки, переведенные в рубли (результат < 1)

```cpp
operator double() const {
  return static_cast<double>(kopeks_) / 100.0;
}
```

Бинарные операции:
(+ unsigned int) – добавление копеек к денежной сумме

```cpp
Money operator+(const Money& m, unsigned int kopeks) {
  Money result = m;
  result.kopeks_ += kopeks;
  result.Normalize();
  return result;
}
```

(- unsigned int) – вычитание копеек из денежной суммы
```cpp
Money operator-(const Money& m, unsigned int kopeks) {
  Money result = m;
  
  long long total_current_kopeks = static_cast<long long>(result.rubles_) * 100 
                                 + result.kopeks_;
  long long total_result_kopeks = total_current_kopeks - kopeks;
  
  if (total_result_kopeks < 0) {
    throw std::underflow_error("Результат вычитания не может быть отрицательным");
  }
  
  result.rubles_ = static_cast<unsigned int>(total_result_kopeks / 100);
  result.kopeks_ = static_cast<short int>(total_result_kopeks % 100);
  
  return result;
}
```

1. Вычисляем общее количество копеек в исходной сумме
2. Вычитаем указанное количество копеек
3. Проверяем, чтобы результат не стал отрицательным
4. Распределяем результат обратно на рубли и копейки

# Тестирование
<img width="506" height="460" alt="image" src="https://github.com/user-attachments/assets/4a80ff92-225e-4eeb-a8d2-df861cdbca1e" />

<img width="520" height="450" alt="image" src="https://github.com/user-attachments/assets/1316906c-5a7e-461c-b3ca-1b748ba3242f" />








