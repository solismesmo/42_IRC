/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: livieira <livieira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:22:04 by livieira          #+#    #+#             */
/*   Updated: 2026/01/13 23:22:06 by livieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HANDLER_CLASS_H
# define COMMAND_HANDLER_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

class Server;
class Command;
class Client;

class CommandHandler
{
private:
	Server *_server;
	std::map<std::string, Command *> _commands;
public:
	CommandHandler(Server *server);
	~CommandHandler();

	void invoke(Client *client, std::string const &message);
};

#endif
