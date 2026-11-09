/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 11:35:10 by ssukhija          #+#    #+#             */
/*   Updated: 2026/08/16 11:35:10 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &copy) 
{ 
    (void)copy;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &copy) 
{
    (void)copy; 
    return *this;
}

ScalarConverter::~ScalarConverter() {}

static bool isChar(const std::string &s)
{
    if (s.length() == 1 && !isdigit(s[0]) && isprint(s[0]))
    {
        return true;
    }
    return false;
}

static bool isInt(const std::string &s)
{
    size_t i;

    i = 0;
    if (s[i] == '-' || s[i] == '+')
        i++;
    if (i == s.length())
        return false;
    while (i < s.length())
    {
        if (!isdigit(s[i]))
            return false;
        i++;
    }
    return true;
}

static bool isFloat(const std::string &s)
{
    size_t  i;
    bool    hasDot;
    bool    hasDigit;

    if (s == "-inff" || s == "+inff" || s == "nanf")
        return true;

    if (s.empty() || s[s.length() - 1] != 'f' )
        return false;

    i = 0;
    if (s[i] == '-' || s[i] == '+')
        i++;
    
    if (i == s.length() -1)
        return false;
    
    hasDot = false;
    hasDigit = false;
    while (i < s.length() - 1)
    {
        if (s[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (isdigit(s[i]))
            hasDigit = true;
        else
            return false;
        i++; 
    }
    return hasDigit && hasDot;
}

static bool isDouble(const std::string &s)
{
    size_t  i;
    bool    hasDot;
    bool    hasDigit;

    if (s == "-inf" || s == "+inf" || s =="nan")
        return true;
    
    i = 0;
    if (s[i] == '-' || s[i] == '+')
        i++;

    if (i == s.length())
        return false;

    hasDot = false;
    hasDigit = false;
    while (i < s.length())
    {
        if (s[i] == '.')
        {
            if (hasDot)
                return false;
            hasDot = true;
        }
        else if (isdigit(s[i]))
            hasDigit = true;
        else
            return false;
        i++;
    }
    return hasDigit && hasDot;
}

static void printResults(char c, int i, float f, double d, const std::string &input)
{
    double  val;
    bool    isPseudo;

    if (input.length() == 1 && !isdigit(input[0]) && isprint(input[0]))
        val = static_cast<double>(input[0]);
    else
        val = std::strtod(input.c_str(), NULL);

    if (input == "nan" || input == "nanf" || input == "+inf" 
        || input == "+inff" || input == "-inf" || input == "-inff")
        isPseudo = true;
    else
        isPseudo = false;

    std::cout << "char: ";
    if (isPseudo || val < std::numeric_limits<char>::min() || val > std::numeric_limits<char>::max())
        std::cout << "impossible" << std::endl;
    else if (!isprint(c))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << c << "'" << std::endl;

    std::cout << "int: ";
    if (isPseudo || val < std::numeric_limits<int>::min() || val > std::numeric_limits<int>::max())
        std::cout << "impossible" << std::endl;
    else
        std::cout << i << std::endl;

    std::cout << "float: ";
    if (isPseudo)
    {
        if (input == "nan" || input == "nanf")
            std::cout << "nanf" << std::endl;
        else if (input[0] == '+')
            std::cout << "+inff" << std::endl;
        else
            std::cout << "-inff" << std::endl;
    }
    else
    {
        std::cout << f;
        if (f - static_cast<int>(f) == 0.0f)
            std::cout << ".0";
        std::cout << "f" << std::endl;
    }

    std::cout << "double: ";
    if (isPseudo)
    {
        if (input == "nan" || input == "nanf")
            std::cout << "nan" << std::endl;
        else if (input[0] == '+')
            std::cout << "+inf" << std::endl;
        else
            std::cout << "-inf" << std::endl;
    }
    else
    {
        std::cout << d;
        if (d - static_cast<int>(d) == 0.0)
            std::cout << ".0";
        std::cout << std::endl;
    }
}

void ScalarConverter::convert(const std::string &input)
{
    char    c;
    long    l;
    int     i;
    float   f;
    double  d;

    if (isChar(input))
    {
        c = input[0];
        printResults(c, static_cast<int>(c), static_cast<float>(c), static_cast<double>(c), input);
    }
    else if (isInt(input))
    {
        l = std::strtol(input.c_str(), NULL, 10);
        i = static_cast<int>(l);
        printResults(static_cast<int>(i), i, static_cast<float>(i), static_cast<double>(i), input);
    }
    else if (isFloat(input))
    {
        f = static_cast<float>(std::strtod(input.c_str(), NULL));
        printResults(static_cast<char>(f), static_cast<int>(f), f, static_cast<double>(f), input);
    }
    else if (isDouble(input))
    {
        d = std::strtod(input.c_str(), NULL);
        printResults(static_cast<char>(d), static_cast<int>(d), static_cast<float>(d), d, input);
    }
    else
    {
        std::cout << RED << "Error: The provided string is not a valid char, int, float, or double literal." << RESET << std::endl;
    }
}



