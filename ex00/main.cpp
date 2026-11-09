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

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << YELLOW << "Usage: ./convert <literal>" << RESET << std::endl;
        return 1;
    }

    ScalarConverter::convert(argv[1]);
    return 0;
}