#include "PasswordManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Инициализация статической переменной
PasswordManager* PasswordManager::instance = nullptr;

PasswordManager::PasswordManager() {
    std::cout << "Creating password manager!" << std::endl;
}

PasswordManager* PasswordManager::getInstance() {
    if (instance == nullptr) {
        instance = new PasswordManager();
    }
    return instance;
}

void PasswordManager::addPassword(const std::string& website, const std::string& username,
    const std::string& passwordValue) {
    Password newPassword(passwordValue);
    passwords[website][username] = newPassword;

    std::cout << "Password for " << website << " (" << username << ") added!" << std::endl;
    std::cout << "Strength: " << newPassword.getStrengthDescription() << std::endl;

    if (!newPassword.isStrong()) {
        std::cout << "Tip: this password is not very strong. "
            << "It's better to use a combination of letters, numbers, and special characters." << std::endl;
    }
}

std::string PasswordManager::getPassword(const std::string& website, const std::string& username) {
    if (passwords.find(website) != passwords.end()) {
        if (passwords[website].find(username) != passwords[website].end()) {
            return passwords[website][username].getValue();
        }
    }
    return "Password not found :(";
}

void PasswordManager::getPasswordInfo(const std::string& website, const std::string& username) {
    if (passwords.find(website) != passwords.end()) {
        if (passwords[website].find(username) != passwords[website].end()) {
            Password& pwd = passwords[website][username];
            std::cout << "Password information for " << website << " (" << username << "):" << std::endl;
            std::cout << "  Strength: " << pwd.getStrength() << "/10 - "
                << pwd.getStrengthDescription() << std::endl;
            return;
        }
    }
    std::cout << "Password not found :(" << std::endl;
}

void PasswordManager::deletePassword(const std::string& website, const std::string& username) {
    if (passwords.find(website) != passwords.end()) {
        if (passwords[website].find(username) != passwords[website].end()) {
            passwords[website].erase(username);
            std::cout << "Password for " << website << " (" << username << ") deleted!" << std::endl;
            if (passwords[website].empty()) {
                passwords.erase(website);
            }
            return;
        }
    }
    std::cout << "Cannot delete. Password not found :(" << std::endl;
}

void PasswordManager::showAllWebsites() {
    if (passwords.empty()) {
        std::cout << "No saved passwords!" << std::endl;
        return;
    }

    std::cout << "List of websites:" << std::endl;
    for (const auto& site : passwords) {
        std::cout << "- " << site.first << " (users: " << site.second.size() << ")" << std::endl;
        for (const auto& user : site.second) {
            std::cout << "  * " << user.first << " (strength: "
                << user.second.getStrength() << "/10)" << std::endl;
        }
    }
}

bool PasswordManager::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open file for writing!" << std::endl;
        return false;
    }

    file << passwords.size() << std::endl;
    for (const auto& site : passwords) {
        file << site.first << std::endl;
        file << site.second.size() << std::endl;
        for (const auto& user : site.second) {
            file << user.first << std::endl;
            file << user.second.getValue() << std::endl;
        }
    }

    file.close();
    std::cout << "Data successfully saved to file: " << filename << std::endl;
    return true;
}

bool PasswordManager::saveToFile() {
    return saveToFile(DEFAULT_FILENAME);
}

bool PasswordManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open file for reading!" << std::endl;
        return false;
    }

    try {
        passwords.clear();
        int siteCount;
        file >> siteCount;
        file.ignore();
        for (int i = 0; i < siteCount; i++) {
            std::string website;
            std::getline(file, website);
            int userCount;
            file >> userCount;
            file.ignore();
            for (int j = 0; j < userCount; j++) {
                std::string username, passwordValue;
                std::getline(file, username);
                std::getline(file, passwordValue);
                Password pwd(passwordValue);
                passwords[website][username] = pwd;
            }
        }

        file.close();
        std::cout << "Data successfully loaded from file: " << filename << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cout << "Error reading file: " << e.what() << std::endl;
        file.close();
        return false;
    }
}

bool PasswordManager::loadFromFile() {
    return loadFromFile(DEFAULT_FILENAME);
}

std::string PasswordManager::getDefaultFilename() const {
    return DEFAULT_FILENAME;
}

PasswordManager::~PasswordManager() {
    std::cout << "Destroying password manager!" << std::endl;
}

// Реализация новых методов
int PasswordManager::getPasswordStrength(const std::string& website, const std::string& username) const {
    if (passwords.find(website) != passwords.end() && passwords.at(website).find(username) != passwords.at(website).end()) {
        return passwords.at(website).at(username).getStrength();
    }
    return -1;
}

std::string PasswordManager::getPasswordStrengthDescription(const std::string& website, const std::string& username) const {
    if (passwords.find(website) != passwords.end() && passwords.at(website).find(username) != passwords.at(website).end()) {
        return passwords.at(website).at(username).getStrengthDescription();
    }
    return "Not found";
}

std::string PasswordManager::getAllWebsitesString() const {
    std::ostringstream oss;
    if (passwords.empty()) {
        oss << "No saved passwords!";
    }
    else {
        oss << "List of websites:\n";
        for (const auto& site : passwords) {
            oss << "- " << site.first << " (users: " << site.second.size() << ")\n";
            for (const auto& user : site.second) {
                oss << "  * " << user.first << " (strength: "
                    << user.second.getStrength() << "/10)\n";
            }
        }
    }
    return oss.str();
}