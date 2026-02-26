#ifndef MONEY_H_
#define MONEY_H_

class Money {
 public:
  Money(unsigned int rubles, short int kopeks);
  Money AddKopeks(unsigned int amount) const;

  Money& operator++();       // префикс ++t
  Money operator++(int);     // постфикс t++
  Money& operator--();       // префикс --t
  Money operator--(int);     // постфикс t--

  // Приведение типов
  explicit operator unsigned int() const;
  operator double() const;

  // Бинарные операции с копейками
  Money operator+(unsigned int amount) const;
  Money operator-(unsigned int amount) const;

 private:
  unsigned int rubles_;
  short int kopeks_;
};

#endif  