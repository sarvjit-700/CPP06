/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 23:56:15 by ssukhija          #+#    #+#             */
/*   Updated: 2026/08/19 23:56:15 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>

#define RESET "\033[;0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

Base* generate(void)
{
    int random;
    
    random = rand() % 3;

    if (random == 0)
    {
        std::cout << BLUE << "Generated: A" << RESET << std::endl;
        return new A;
    }
    else if (random == 1)
    {
        std::cout << BLUE << "Generated: B" << RESET << std::endl;
        return new B;
    }
    else
    {
        std::cout << BLUE << "Generated: C" << RESET << std::endl;
        return new C;
    }
}

void identify(Base* p)
{
    std::cout << "Pointer Identify  : ";
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << RED << "Unknown Type" << RESET << std::endl;
}

void identify(Base &p)
{
    std::cout << "Reference Identify : ";
    try
    {
        (void) dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (const std::exception &e) {}

    try
    {
        (void) dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (const std::exception &e) {}

    try
    {
        (void) dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (const std::exception &e) {}
    std::cout << RED << "Unknown Type" << RESET << std::endl;
}

int main()
{
    int i;
    Base* obj;

    i = 0;
    srand(time(NULL));

    std::cout << YELLOW << "--- Testing Identification ---" << RESET << std::endl;
    while (i < 5)
    {
        std::cout << GREEN << "\nTest " << (i + 1) << ":" << RESET << std::endl;

        obj = generate();
        identify(obj);
        identify(*obj);
        delete obj;
        i++;
    }
    return 0;
}