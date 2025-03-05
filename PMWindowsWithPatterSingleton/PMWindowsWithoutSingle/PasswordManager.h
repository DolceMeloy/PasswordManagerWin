#pragma once
#include "Password.h"
#include <map>
#include <string>

class PasswordManager {
private:
    static PasswordManager* instance;
    PasswordManager();
    std::map<std::string, std::map<std::string, Password>> passwords;
    const std::string DEFAULT_FILENAME = "passwords.dat";
    PasswordManager(const PasswordManager&) = delete;
    PasswordManager& operator=(const PasswordManager&) = delete;

public:
    static PasswordManager* getInstance();
    void addPassword(const std::string& website, const std::string& username, const std::string& passwordValue);
    std::string getPassword(const std::string& website, const std::string& username);
    void getPasswordInfo(const std::string& website, const std::string& username);
    void deletePassword(const std::string& website, const std::string& username);
    void showAllWebsites();
    bool saveToFile(const std::string& filename);
    bool saveToFile();
    bool loadFromFile(const std::string& filename);
    bool loadFromFile();
    std::string getDefaultFilename() const;
    ~PasswordManager();

    int getPasswordStrength(const std::string& website, const std::string& username) const;
    std::string getPasswordStrengthDescription(const std::string& website, const std::string& username) const;
    std::string getAllWebsitesString() const; 
};