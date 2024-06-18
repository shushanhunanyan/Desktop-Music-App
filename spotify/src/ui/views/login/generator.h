#ifndef GENERATOR_H
#define GENERATOR_H


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>


class Generator
{
public:
    Generator() = default;
    ~Generator() = default;

    std::string GeneratePassword();
private:
    char GenerateUppercase();
    char GenerateLowercase();
    char GenerateSpecialSymbol();
    char GenerateDigit();

private:
    const size_t password_size = 12;
};

#endif // GENERATOR_H
