/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 15:15:15 by ssukhija          #+#    #+#             */
/*   Updated: 2026/08/18 15:15:15 by ssukhija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"
#include <iostream>

#define RESET "\033[;0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

int main()
{
    // 1. Initialize the non-empty Data structure
    Data myData;
    myData.text = "Serialization Test";
    myData.number = 42;

    std::cout << YELLOW << "--- Original Data ---" << RESET << std::endl;
    std::cout << "Original Pointer Address : " << BLUE << &myData << RESET << std::endl;
    std::cout << "Data.text                : " << myData.text << std::endl;
    std::cout << "Data.number              : " << myData.number << std::endl;

    // 2. Serialize
    std::cout << YELLOW << "\n--- Serializing ---" << RESET << std::endl;
    uintptr_t rawData = Serializer::serialize(&myData);
    std::cout << "Serialized uintptr_t     : " << BLUE << rawData << RESET << std::endl;

    // 3. Deserialize
    std::cout << YELLOW << "\n--- Deserializing ---" << RESET << std::endl;
    Data* recoveredData = Serializer::deserialize(rawData);
    std::cout << "Recovered Pointer Address: " << BLUE << recoveredData << RESET << std::endl;

    // 4. Verify equal comparison
    std::cout << YELLOW << "\n--- Verification ---" << RESET << std::endl;
    if (recoveredData == &myData)
    {
        std::cout << GREEN << "[SUCCESS] The pointers match exactly!" << RESET << std::endl;
        std::cout << "Data address   : " << &myData << std::endl;
        std::cout << "Recovered Data address   : " << recoveredData << std::endl;
        std::cout << "Recovered Data.text      : " << recoveredData->text << std::endl;
        std::cout << "Recovered Data.number    : " << recoveredData->number << std::endl;
    }
    else
    {
        std::cout << RED << "[ERROR] The pointers do not match!" << RESET << std::endl;
    }

    // 5. Corrupt data and verify
    std::cout << YELLOW << "\n--- Verification [Corrupt address by adding 1] ---" << RESET << std::endl;
    rawData = rawData + 1;
    Data* corruptedData = Serializer::deserialize(rawData);
    if (corruptedData == &myData)
    {
        std::cout << RED << "The pointers match! They shouldn't" << RESET << std::endl;
    }
    else
    {
        std::cout << GREEN << "The pointers don't match!" << RESET << std::endl;
        std::cout << "Corrupted Data address  (+1) : " << corruptedData << std::endl;
        std::cout << "Data address   : " << &myData << std::endl;
    }

    return 0;
}