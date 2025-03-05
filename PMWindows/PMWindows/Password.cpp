#include "Password.h"
#include <algorithm>

int Password::calculateStrength(const std::string& pwd) {
    int score = 0;

    score += std::min(5, static_cast<int>(pwd.length() / 2));

    if (pwd.find_first_of("0123456789") != std::string::npos)
        score += 1;

    if (pwd.find_first_of("!@#$%^&*()_+-=[]{}|;:,.<>?/") != std::string::npos)
        score += 2;

    if (pwd.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != std::string::npos)
        score += 1;

    if (pwd.find_first_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos)
        score += 1;

    return std::min(10, score);
}

Password::Password(const std::string& passwordValue) {
    value = passwordValue;
    strength = calculateStrength(passwordValue);
}

std::string Password::getValue() const {
    return value;
}

int Password::getStrength() const {
    return strength;
}

bool Password::isStrong() const {
    return strength >= 7;
}

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
