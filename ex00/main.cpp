/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 23:13:49 by ssukhija          #+#    #+#             */
/*   Updated: 2026/08/16 23:13:49 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

void testcases() {
    std::cout << "--------TEST CHAR----------" << std::endl;
    ScalarConverter::convert("a");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("Z");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert(" ");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("~");
    std::cout << "--------TEST INT----------" << std::endl;
    ScalarConverter::convert("42");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("-42");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("0");
    std::cout << "--------TEST INT-MAX & INT-MIN----------" << std::endl;
    ScalarConverter::convert("2147483647"); // INT_MAX
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("-2147483648"); // INT_MIN
    std::cout << "--------TEST FLOAT & DOUBLE----------" << std::endl;
    ScalarConverter::convert("4.2f");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("4.2");
    std::cout << "-------TEST INF & NAN-----------" << std::endl;
    ScalarConverter::convert("+inf");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("-inff");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("nan");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("nanf");
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("256");
    std::cout << "-------TEST LARGE NUMBERS-----------" << std::endl;
    ScalarConverter::convert("12345678901234567890");
    std::cout << "--------TEST FLOAT & DOUBLE MAX----------" << std::endl;
    ScalarConverter::convert("3.4028235e+38f"); // float max
    std::cout << "------------------" << std::endl;
    ScalarConverter::convert("1.7976931348623157e+308"); // double max
    }

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        testcases();
        return 0;
    }

    if (argc != 2)
    {
        std::cout << YELLOW << "Usage: ./convert <literal>" << RESET << std::endl;
        return 1;
    }

    ScalarConverter::convert(argv[1]);
    return 0;
}