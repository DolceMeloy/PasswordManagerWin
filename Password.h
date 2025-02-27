#pragma once
#include <string>

/**
 * Класс для представления пароля и работы с ним
 */
class Password {
private:
    std::string value;          // password value
    int strength;               // password str (1-10)

    /**
     * Оценивает надежность пароля по простым критериям
     * @param pwd Строка пароля для оценки
     * @return Оценка от 1 до 10
     */
    int calculateStrength(const std::string& pwd);

public:
    /**
     * Конструктор класса Password
     * @param passwordValue Строковое значение пароля
     */
    Password(const std::string& passwordValue = "");

    /**
     * Получить значение пароля
     * @return Строка пароля
     */
    std::string getValue() const;

    /**
     * Получить оценку надежности пароля
     * @return Число от 1 до 10
     */
    int getStrength() const;

    /**
     * Проверить, является ли пароль надежным
     * @return true если оценка >= 7, иначе false
     */
    bool isStrong() const;

    /**
     * Получить текстовое описание надежности пароля
     * @return Строка с описанием надежности
     */
    std::string getStrengthDescription() const;
};