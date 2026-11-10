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

    // 6. Modify data via recovered pointer (proves it points to the exact same memory)
    std::cout << YELLOW << "\n--- Verification [Modify via Recovered Pointer] ---" << RESET << std::endl;
    recoveredData->text = "Modified through recoveredData!";
    recoveredData->number = 999;
    std::cout << "Original myData.text     : " << myData.text << std::endl;
    std::cout << "Original myData.number   : " << myData.number << std::endl;

    // 7. Heap-allocated Data test
    std::cout << YELLOW << "\n--- Verification [Heap Allocation] ---" << RESET << std::endl;
    Data* heapData = new Data;
    heapData->text = "Heap Data";
    heapData->number = -42;

    uintptr_t rawHeap = Serializer::serialize(heapData);
    Data* recoveredHeap = Serializer::deserialize(rawHeap);

    if (recoveredHeap == heapData)
    {
        std::cout << GREEN << "[SUCCESS] Heap pointers match! (" << recoveredHeap << ")" << RESET << std::endl;
        std::cout << "Recovered Heap text      : " << recoveredHeap->text << std::endl;
        std::cout << "Recovered Heap number    : " << recoveredHeap->number << std::endl;
    }
    delete heapData;

    // 8. NULL pointer test
    std::cout << YELLOW << "\n--- Verification [NULL Pointer] ---" << RESET << std::endl;
    Data* nullPtr = NULL;
    uintptr_t rawNull = Serializer::serialize(nullPtr);
    Data* recoveredNull = Serializer::deserialize(rawNull);
    std::cout << "Serialized NULL          : " << rawNull << std::endl;
    std::cout << "Recovered NULL pointer   : " << recoveredNull << std::endl;
    if (recoveredNull == NULL)
        std::cout << GREEN << "[SUCCESS] NULL pointer preserved!" << RESET << std::endl;
    
    return 0;
}