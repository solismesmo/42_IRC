/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:16:42 by livieira          #+#    #+#             */
/*   Updated: 2026/01/17 12:22:29 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Irc.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: " << argv[0] << " <port> <password>" << std::endl;
		return (1);
	}
	else if (!containsOnlyDigits(argv[1]))
	{
		std::cout << "Port must be a number" << std::endl;
		return (1);
	}

	Server server = Server(atoi(argv[1]), argv[2]);
	server.listen();
	return (0);
}
