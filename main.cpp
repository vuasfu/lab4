#include "Money.h"

#include <iostream>
#include <limits>
#include <locale>

unsigned int ReadUnsignedInt(const std::string& prompt)
{
  unsigned int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;

    if (!std::cin.fail()) {
      return value;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Ошибка ввода. Введите положительное целое число.\n";
  }
}

short int ReadKopeks(const std::string& prompt)
{
  int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;

    if (!std::cin.fail() && value >= 0 && value < 100) {
      return static_cast<short int>(value);
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cerr << "Ошибка ввода. Копейки должны быть от 0 до 99.\n";
  }
}

void PrintMoney(const Money& money)
{
  unsigned int rubles = static_cast<unsigned int>(money);
  double fractional = static_cast<double>(money);

  short int kopeks = static_cast<short int>(fractional * 100);

  std::cout << "Текущая сумма: "
            << rubles << " руб. "
            << kopeks << " коп.\n";
}

int main()
{
  try {
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    std::cin.imbue(std::locale());
    std::cerr.imbue(std::locale());
  } catch (...) {
  }

  unsigned int rubles = ReadUnsignedInt("Введите количество рублей: ");
  short int kopeks = ReadKopeks("Введите количество копеек (0-99): ");

  Money money(rubles, kopeks);

  while (true) {
    std::cout << "\nМеню:\n";
    std::cout << "1. ++ (префикс)\n";
    std::cout << "2. -- (префикс)\n";
    std::cout << "3. t++ (постфикс)\n";
    std::cout << "4. t-- (постфикс)\n";
    std::cout << "5. Добавить копейки (+)\n";
    std::cout << "6. Вычесть копейки (-)\n";
    std::cout << "7. Показать сумму\n";
    std::cout << "8. Показать результаты приведения типов\n";
    std::cout << "0. Выход\n";

    unsigned int choice = ReadUnsignedInt("Выберите пункт: ");

    if (choice == 0) {
      break;
    }

    switch (choice) {
      case 1: {
        // Префиксный ++ - возвращает ссылку на измененный объект
        std::cout << "До операции: ";
        PrintMoney(money);
        
        Money& result = ++money;
        
        std::cout << "После ++money: ";
        PrintMoney(money);
        std::cout << "Результат операции (ссылка на тот же объект): ";
        PrintMoney(result);
        break;
      }

      case 2: {
        // Префиксный -- - возвращает ссылку на измененный объект
        std::cout << "До операции: ";
        PrintMoney(money);
        
        Money& result = --money;
        
        std::cout << "После --money: ";
        PrintMoney(money);
        std::cout << "Результат операции (ссылка на тот же объект): ";
        PrintMoney(result);
        break;
      }

      case 3: {
        // Постфиксный ++ - возвращает СТАРОЕ значение
        std::cout << "До операции: ";
        PrintMoney(money);
        
        Money old_value = money++;
        
        std::cout << "После money++: ";
        PrintMoney(money);
        std::cout << "Результат операции (старое значение): ";
        PrintMoney(old_value);
        break;
      }

      case 4: {
        // Постфиксный -- - возвращает СТАРОЕ значение
        std::cout << "До операции: ";
        PrintMoney(money);
        
        Money old_value = money--;
        
        std::cout << "После money--: ";
        PrintMoney(money);
        std::cout << "Результат операции (старое значение): ";
        PrintMoney(old_value);
        break;
      }

      case 5: {
        unsigned int amount =
            ReadUnsignedInt("Введите количество копеек для добавления: ");
        money = money + amount;
        PrintMoney(money);
        break;
      }

      case 6: {
        unsigned int amount =
            ReadUnsignedInt("Введите количество копеек для вычитания: ");
        money = money - amount;
        PrintMoney(money);
        break;
      }

      case 7:
        PrintMoney(money);
        break;

      case 8: {
        // Демонстрация операций приведения типов
        std::cout << "\n=== Операции приведения типов ===\n";
        
        // Явное приведение к unsigned int (целые рубли, копейки отбрасываются)
        unsigned int rubles_only = static_cast<unsigned int>(money);
        std::cout << "Явное приведение к unsigned int: "
                  << rubles_only << " руб. (копейки отброшены)\n";
        
        // Неявное приведение к double (копейки как дробная часть рубля, < 1)
        double kopeks_as_rubles = static_cast<double>(money);
        std::cout << "Неявное приведение к double: "
                  << kopeks_as_rubles << " руб. (только дробная часть)\n";
        
        // Проверка, что результат < 1
        std::cout << "Проверка: " << kopeks_as_rubles << " < 1? "
                  << (kopeks_as_rubles < 1.0 ? "Да" : "Нет") << "\n";
        break;
      }

      default:
        std::cerr << "Неверный пункт меню.\n";
        break;
    }
  }

  return 0;

}
