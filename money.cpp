#include "money.h"
#include <stdexcept>

Money::Money() : rubles_(0), kopeks_(0) {}

Money::Money(unsigned int rub, short int kop) : rubles_(rub), kopeks_(kop) {
  if (kop < 0) {
    throw std::invalid_argument("Копейки не могут быть отрицательными");
  }
  Normalize();
}

Money::Money(const Money& other) 
    : rubles_(other.rubles_), kopeks_(other.kopeks_) {}

unsigned int Money::GetRubles() const {
  return rubles_;
}

short int Money::GetKopeks() const {
  return kopeks_;
}

Money Money::AddKopeks(unsigned int additional_kopeks) const {
  Money result = *this;
  
  long long total_kopeks = static_cast<long long>(result.kopeks_) + additional_kopeks;
  
  result.rubles_ += static_cast<unsigned int>(total_kopeks / 100);
  result.kopeks_ = static_cast<short int>(total_kopeks % 100);
  
  result.Normalize();
  
  return result;
}

Money& Money::operator++() {
  ++kopeks_;
  Normalize();
  return *this;
}

Money Money::operator++(int) {
  Money temp = *this;
  ++(*this);
  return temp;
}

Money& Money::operator--() {
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

Money Money::operator--(int) {
  Money temp = *this;
  --(*this);
  return temp;
}

Money::operator unsigned int() const {
  return rubles_;
}

Money::operator double() const {
  return static_cast<double>(kopeks_) / 100.0;
}

Money operator+(const Money& m, unsigned int kopeks) {
  Money result = m;
  result.kopeks_ += kopeks;
  result.Normalize();
  return result;
}

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

std::ostream& operator<<(std::ostream& os, const Money& money) {
  os << money.rubles_ << " руб. ";
  if (money.kopeks_ < 10) {
    os << "0";
  }
  os << money.kopeks_ << " коп.";
  return os;
}

void Money::Normalize() {
  if (kopeks_ >= 100) {
    rubles_ += kopeks_ / 100;
    kopeks_ %= 100;
  }
  if (kopeks_ < 0 && rubles_ > 0) {
    --rubles_;
    kopeks_ += 100;
  }
}