#pragma once
#include <string>

/**
 * ����� ��� ������������� ������ � ������ � ���
 */
class Password {
private:
    std::string value;          // password value
    int strength;               // password str (1-10)

    /**
     * ��������� ���������� ������ �� ������� ���������
     * @param pwd ������ ������ ��� ������
     * @return ������ �� 1 �� 10
     */
    int calculateStrength(const std::string& pwd);

public:
    /**
     * ����������� ������ Password
     * @param passwordValue ��������� �������� ������
     */
    Password(const std::string& passwordValue = "");

    /**
     * �������� �������� ������
     * @return ������ ������
     */
    std::string getValue() const;

    /**
     * �������� ������ ���������� ������
     * @return ����� �� 1 �� 10
     */
    int getStrength() const;

    /**
     * ���������, �������� �� ������ ��������
     * @return true ���� ������ >= 7, ����� false
     */
    bool isStrong() const;

    /**
     * �������� ��������� �������� ���������� ������
     * @return ������ � ��������� ����������
     */
    std::string getStrengthDescription() const;
};