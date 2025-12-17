#ifndef INPUT_HANDLER_H_
#define INPUT_HANDLER_H_

#include <string>

class InputHandler {
 public:
  static int GetNonNegativeInt(const std::string& prompt);
  static short int GetKopeks(const std::string& prompt);
  static bool GetYesNoConfirmation(const std::string& prompt);
  
 private:
  // Проверяет, что строка состоит только из цифр
  static bool IsAllDigits(const std::string& str);
  // Очищает строку от пробелов и приводит к нижнему регистру
  static std::string CleanString(const std::string& str);
};

#endif  // INPUT_HANDLER_H_