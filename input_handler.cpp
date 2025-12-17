#include "input_handler.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

bool InputHandler::IsAllDigits(const std::string& str) {
  if (str.empty()) {
    return false;
  }
  for (char c : str) {
    if (!std::isdigit(static_cast<unsigned char>(c))) {
      return false;
    }
  }
  return true;
}

std::string InputHandler::CleanString(const std::string& str) {
  std::string result;
  
  // Удаляем пробелы и табуляции
  for (char c : str) {
    if (!std::isspace(static_cast<unsigned char>(c))) {
      result += c;
    }
  }
  
  // Преобразуем в нижний регистр
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  
  return result;
}

bool InputHandler::GetYesNoConfirmation(const std::string& prompt) {
  std::string input;
  
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    
    if (std::cin.eof()) {
      std::cout << "\nВвод прерван. Завершение программы.\n";
      exit(0);
    }
    
    std::string cleaned = CleanString(input);
    
    if (cleaned == "y") {
      return true;
    } else if (cleaned == "n") {
      return false;
    } else {
      std::cout << "Пожалуйста, введите 'y' или 'n'\n";
    }
  }
}

int InputHandler::GetNonNegativeInt(const std::string& prompt) {
  std::string input;
  int value;
  
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    
    if (std::cin.eof()) {
      std::cout << "\nВвод прерван. Завершение программы.\n";
      exit(0);
    }
    
    if (input.empty()) {
      std::cout << "Ошибка! Введите число.\n";
      continue;
    }
    
    if (!IsAllDigits(input)) {
      std::cout << "Ошибка! Введите целое число без символов.\n";
      continue;
    }
    
    std::stringstream ss(input);
    ss >> value;
    
    if (value < 0) {
      std::cout << "Ошибка! Число не может быть отрицательным.\n";
    } else {
      return value;
    }
  }
}

short int InputHandler::GetKopeks(const std::string& prompt) {
  std::string input;
  int value;
  
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    
    if (std::cin.eof()) {
      std::cout << "\nВвод прерван. Завершение программы.\n";
      exit(0);
    }
    
    if (input.empty()) {
      std::cout << "Ошибка! Введите число.\n";
      continue;
    }
    
    if (!IsAllDigits(input)) {
      std::cout << "Ошибка! Введите целое число без символов.\n";
      continue;
    }
    
    std::stringstream ss(input);
    ss >> value;
    
    if (value < 0) {
      std::cout << "Ошибка! Копейки не могут быть отрицательными.\n";
    } else {
      return static_cast<short int>(value);
    }
  }
}