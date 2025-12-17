#ifndef MONEY_H_
#define MONEY_H_

#include <iostream>

class Money {
 public:
  Money();
  Money(unsigned int rub, short int kop);
  Money(const Money& other);

  unsigned int GetRubles() const;
  short int GetKopeks() const;

  Money AddKopeks(unsigned int additional_kopeks) const;

  // Унарные операции
  Money& operator++();    // Префиксный ++
  Money operator++(int);  // Постфиксный ++
  Money& operator--();    // Префиксный --
  Money operator--(int);  // Постфиксный --

  // Операции приведения типа
  explicit operator unsigned int() const;  // Явное приведение к unsigned int
  operator double() const;                 // Неявное приведение к double

  // Бинарные операции (дружественные)
  friend Money operator+(const Money& m, unsigned int kopeks);
  friend Money operator-(const Money& m, unsigned int kopeks);

  // Перегруженный оператор вывода
  friend std::ostream& operator<<(std::ostream& os, const Money& money);

 private:
  void Normalize();

  unsigned int rubles_;
  short int kopeks_;
};

#endif  // MONEY_H_