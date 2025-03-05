#pragma once
#include <string>

class Password {
private:
    std::string value;
    int strength;   
    int calculateStrength(const std::string& pwd);

public:
    Password(const std::string& passwordValue = "");
    std::string getValue() const;
    int getStrength() const;
    bool isStrong() const;
    std::string getStrengthDescription() const;
};