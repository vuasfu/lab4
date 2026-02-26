# lab4
# ФИО: Булгакова Юлия Олеговна

# Постановка задач

В задании 1 реализовать определение класса (поля, свойства, конструкторы (не менее трех),
перегрузку оператора вывода для вывода полей, заданный метод согласно варианту).
Протестировать все методы, включая конструкторы, все исходные данные вводятся с клавиатуры, не
забывайте проверять данные на корректность.
В задании 2 добавить к реализованному в первом задании классу указанные в варианте
перегруженные операции.
В главной функции main показать работу всех функций с дружественным интерфейсом.

# Задание 1

Реализовать класс Money с конструктором и методом AddKopeks.

1. Определить класс с полями rubles_ (рубли) и kopeks_ (копейки).
2. Реализовать конструктор с параметрами.
3. Реализовать метод AddKopeks для добавления произвольного количества копеек.

Реализация

```cpp
class Money {
 public:
  Money(unsigned int rubles, short int kopeks);
  Money AddKopeks(unsigned int amount) const;

 private:
  unsigned int rubles_;
  short int kopeks_;
};
```

# Задание 2

Добавить к классу Money перегруженные операторы.

1. Реализовать префиксные и постфиксные операторы ++ и --.
2. Реализовать операторы приведения к unsigned int (явный) и double (неявный).
3. Реализовать бинарные операторы + и - с беззнаковым целым числом (копейки).

Реализация

```cpp
class Money {
 public:
  // ... конструктор и AddKopeks ...

  // Унарные операторы
  Money& operator++();       // префикс ++t
  Money operator++(int);     // постфикс t++
  Money& operator--();       // префикс --t
  Money operator--(int);     // постфикс t--

  // Приведение типов
  explicit operator unsigned int() const;  // явное приведение к unsigned int
  operator double() const;                 // неявное приведение к double

  // Бинарные операции с копейками
  Money operator+(unsigned int amount) const;
  Money operator-(unsigned int amount) const;

 private:
  unsigned int rubles_;
  short int kopeks_;
};
```
```cpp
// Префиксный ++t
Money& Money::operator++()
{
  kopeks_ += 1;
  if (kopeks_ >= 100) {
    rubles_ += kopeks_ / 100;
    kopeks_ = kopeks_ % 100;
  }
  return *this;
}

// Постфиксный t++
Money Money::operator++(int)
{
  Money temp = *this;
  ++(*this);
  return temp;
}

// Префиксный --t
Money& Money::operator--()
{
  if (kopeks_ > 0) {
    kopeks_ -= 1;
  } else if (rubles_ > 0) {
    rubles_ -= 1;
    kopeks_ = 99;
  } else {
    kopeks_ = 0;
  }
  return *this;
}

// Постфиксный t--
Money Money::operator--(int)
{
  Money temp = *this;
  --(*this);            
  return temp;
}

// Приведение к unsigned int (целые рубли)
Money::operator unsigned int() const
{
  return rubles_;
}

// Приведение к double (копейки как дробная часть рубля)
Money::operator double() const
{
  return static_cast<double>(kopeks_) / 100.0;
}

// Бинарный оператор + с копейками
Money Money::operator+(unsigned int amount) const
{
  unsigned int total_kopeks = kopeks_ + amount;
  unsigned int extra_rubles = total_kopeks / 100;
  short int new_kopeks = total_kopeks % 100;
  unsigned int new_rubles = rubles_ + extra_rubles;
  return Money(new_rubles, new_kopeks);
}

// Бинарный оператор - с копейками
Money Money::operator-(unsigned int amount) const
{
  unsigned int total_kopeks = rubles_ * 100 + kopeks_;
  if (amount >= total_kopeks) {
    return Money(0, 0);
  }
  unsigned int remaining = total_kopeks - amount;
  unsigned int new_rubles = remaining / 100;
  short int new_kopeks = remaining % 100;
  return Money(new_rubles, new_kopeks);
}
```

# Тестирование

<img width="386" height="482" alt="image" src="https://github.com/user-attachments/assets/0d03fbbc-7d72-4f72-ac28-c931bd8cd736" />
<img width="523" height="522" alt="image" src="https://github.com/user-attachments/assets/b1b33f4f-ed0e-4142-b48e-92e12e289693" />
<img width="386" height="482" alt="image" src="https://github.com/user-attachments/assets/b5f21ed2-6bd6-46ab-be00-4e3f53978877" />
<img width="461" height="512" alt="image" src="https://github.com/user-attachments/assets/7558c8f9-8be8-446a-bab2-fdfc2e3a682a" />




