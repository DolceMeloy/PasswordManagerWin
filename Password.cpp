#include "Password.h"
#include <algorithm>

int Password::calculateStrength(const std::string& pwd) {
    int score = 0;

    // Длина пароля (до 5 баллов)
    score += std::min(5, static_cast<int>(pwd.length() / 2));

    // Наличие цифр (1 балл)
    if (pwd.find_first_of("0123456789") != std::string::npos)
        score += 1;

    // Наличие специальных символов (2 балла)
    if (pwd.find_first_of("!@#$%^&*()_+-=[]{}|;:,.<>?/") != std::string::npos)
        score += 2;

    // Наличие заглавных букв (1 балл)
    if (pwd.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
        score += 1;

    // Наличие строчных букв (1 балл)
    if (pwd.find_first_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos)
        score += 1;

    // Ограничение максимального балла до 10
    return std::min(10, score);
}

// Конструктор класса Password
Password::Password(const std::string& passwordValue) {
    value = passwordValue;
    strength = calculateStrength(passwordValue);
}

// Получить значение пароля
std::string Password::getValue() const {
    return value;
}

// Получить силу пароля
int Password::getStrength() const {
    return strength;
}

// Проверка, является ли пароль сильным (7 и более баллов)
bool Password::isStrong() const {
    return strength >= 7;
}

// Получить описание силы пароля
std::string Password::getStrengthDescription() const {
    if (strength <= 3)
        return "Very Weaknes :(";
    else if (strength <= 5)
        return "Weaknes :/";
    else if (strength <= 7)
        return "Awersome :|";
    else if (strength <= 9)
        return "Good! :)";
    else
        return "Very Good! :D";
}
