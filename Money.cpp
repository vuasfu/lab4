#include "Money.h"

Money::Money(unsigned int rubles, short int kopeks) : rubles_(rubles), kopeks_(kopeks) {}

Money Money::AddKopeks(unsigned int amount) const
{
  unsigned int total_kopeks = kopeks_ + amount;
  unsigned int extra_rubles = total_kopeks / 100;
  short int new_kopeks = total_kopeks % 100;
  unsigned int new_rubles = rubles_ + extra_rubles;
  return Money(new_rubles, new_kopeks);
}

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

// Целые рубли
Money::operator unsigned int() const
{
  return rubles_;
}

// Копейки
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