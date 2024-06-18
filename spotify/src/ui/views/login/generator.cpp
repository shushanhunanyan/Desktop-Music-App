#include "generator.h"


std::string Generator::GeneratePassword()
{
    std::vector<char (Generator::*)()> generators = {
        &Generator::GenerateUppercase,
        &Generator::GenerateLowercase,
        &Generator::GenerateSpecialSymbol,
        &Generator::GenerateDigit
    };

    std::srand((std::time(0)));
    std::string password {};

    while (password.length() < password_size) {
        std::random_shuffle(generators.begin(), generators.end());

        for (const auto& function : generators) {
            char tmp = (this->*function)();

            if (password.find(tmp) == std::string::npos) {
                password += tmp;
                break;
            }
        }
    }

    return password;
}


char Generator::GenerateUppercase()
{
    std::srand(std::time(0));
    char min = 'A';
    char max = 'Z';

    return min + (std::rand() % (max - min + 1));
}


char Generator::GenerateLowercase()
{
    std::srand(std::time(0));
    char min = 'a';
    char max = 'z';

    return min + (std::rand() % (max - min + 1));
}


char Generator::GenerateSpecialSymbol()
{
    std::srand(std::time(0));
    char min = '!';
    char max = '/';

    return min + (std::rand() % (max - min + 1));
}


char Generator::GenerateDigit()
{
    std::srand(std::time(0));
    char min = '1';
    char max = '9';

    return min + (std::rand() % (max - min + 1));
}
