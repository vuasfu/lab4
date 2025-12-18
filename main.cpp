#include "money.h"
#include "input_handler.h"
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
#ifdef _WIN32
  system("chcp 65001 > nul");
#endif
  
  try {
    // Ввод начальной суммы
    std::cout << "Введите начальную сумму денег:\n";
    unsigned int rubles = InputHandler::GetNonNegativeInt("Рубли: ");
    short int kopeks = InputHandler::GetKopeks("Копейки: ");
    
    Money money(rubles, kopeks);
    std::cout << "\nСоздана сумма: " << money << "\n";
    
    // Демонстрация унарных операций
    std::cout << "\nДемонстрация унарных операций:\n";
    
    std::cout << "Исходная сумма: " << money << "\n";
    
    // Префиксный ++
    Money m1 = money;
    std::cout << "Префиксный ++: ++m = " << (++m1) << "\n";
    
    // Постфиксный ++
    Money m2 = money;
    std::cout << "Постфиксный ++: m++ = " << (m2++) << " (после операции: " << m2 << ")\n";
    
    // Префиксный --
    Money m3 = money;
    std::cout << "Префиксный --: --m = " << (--m3) << "\n";
    
    // Постфиксный --
    Money m4 = money;
    std::cout << "Постфиксный --: m-- = " << (m4--) << " (после операции: " << m4 << ")\n";
    
    // Демонстрация операций приведения типа
    std::cout << "\nДемонстрация операций приведения типа:\n";
    
    std::cout << "Исходная сумма: " << money << "\n";
    
    // Явное приведение к unsigned int (только рубли)
    unsigned int rubles_only = static_cast<unsigned int>(money);
    std::cout << "Явное приведение к unsigned int (только рубли): " 
              << rubles_only << " руб.\n";
    
    // Неявное приведение к double (копейки в рублях, < 1)
    double kopeks_in_rubles = money;
    std::cout << "Неявное приведение к double (копейки в рублях): " 
              << kopeks_in_rubles << " руб.\n";
    
    // Демонстрация бинарных операций с вводом пользователя
    std::cout << "\nДемонстрация бинарных операций:\n";
    
    std::cout << "Исходная сумма: " << money << "\n";
    
    // Операция + (Money + unsigned int копейки)
    std::cout << "\nВведите количество копеек для сложения: ";
    unsigned int add_kopeks = InputHandler::GetNonNegativeInt("");
    Money sum = money + add_kopeks;
    std::cout << "Бинарная операция +: " << money << " + " << add_kopeks 
              << " коп. = " << sum << "\n";
    
    // Операция - (Money - unsigned int копейки)
    std::cout << "\nВведите количество копеек для вычитания: ";
    unsigned int sub_kopeks = InputHandler::GetNonNegativeInt("");
    try {
      Money diff = money - sub_kopeks;
      std::cout << "Бинарная операция -: " << money << " - " << sub_kopeks 
                << " коп. = " << diff << "\n";
    } catch (const std::exception& e) {
      std::cout << "Ошибка при вычитании: " << e.what() << "\n";
    }
    
    // 1 задание
    std::cout << "\nСложение из 1 задания:\n";
    
    do {
      bool want_to_add = InputHandler::GetYesNoConfirmation(
          "\nХотите добавить копейки к сумме? (y/n): ");
      
      if (want_to_add) {
        unsigned int kopeks_to_add = InputHandler::GetNonNegativeInt(
            "Сколько копеек добавить? ");
        
        Money new_money = money.AddKopeks(kopeks_to_add);
        std::cout << "\nИсходная сумма: " << money << "\n";
        std::cout << "Добавлено копеек: " << kopeks_to_add << "\n";
        std::cout << "Новая сумма: " << new_money << "\n";
        
        money = new_money;
        
        // Показать обновленную сумму с операциями приведения
        std::cout << "Только рубли: " << static_cast<unsigned int>(money) << " руб.\n";
        std::cout << "Копейки в рублях: " << static_cast<double>(money) << " руб.\n";
      } else {
        break;
      }
    } while (true);
    
    std::cout << "\nПрограмма завершена.\n";
    std::cout << "Финальная сумма: " << money << "\n";
    
  } catch (const std::exception& e) {
    std::cerr << "\nОшибка выполнения: " << e.what() << "\n";
    return 1;
  }
  
  return 0;
}