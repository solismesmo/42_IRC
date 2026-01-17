#include "Irc.hpp"

KickCommand::KickCommand(Server *server) : Command(server) {}

KickCommand::~KickCommand() {}

void KickCommand::execute(Client *client, std::vector<std::string> arguments)
{
	if (arguments.size() < 2)
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "KICK"));
		return;
	}
	std::string chan_name = arguments[0];
	std::string target = arguments[1];
	std::string reason = "No reason specified.";
	if (arguments.size() >= 3)
	{
		reason = "";
		for (std::vector<std::string>::iterator it = arguments.begin() + 2; it != arguments.end(); it++)
			reason.append(*it + " ");
	}
	if (reason[0] == ':')
		reason = reason.substr(1, reason.size());
	if (reason[reason.size() - 1] == ' ')
		reason = reason.substr(0, reason.size() - 1);

	Channel *chan = this->_server->getChannel(chan_name);
	if (!chan || !chan->isInChannel(client))
	{
		client->reply(ERR_NOTONCHANNEL(client->getNickName(), chan_name));
		return;
	}
	if (chan->getAdmin() != client && !chan->is_oper(client))
	{
		client->reply(ERR_CHANOPRIVSNEEDED(client->getNickName(), chan->getName()));
		return;
	}
	Client *user = this->_server->getClient(target);
	if (!chan || !chan->isInChannel(user))
	{
		client->reply(ERR_USERNOTINCHANNEL(client->getNickName(), user->getNickName(), chan_name));
		return;
	}
	chan->kick(client, user, reason);
}
