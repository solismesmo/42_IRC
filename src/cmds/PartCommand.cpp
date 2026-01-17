#include "Irc.hpp"

PartCommand::PartCommand(Server *server) : Command(server) {}

PartCommand::~PartCommand() {}

void PartCommand::execute(Client *client, std::vector<std::string> arguments) {

	if (arguments.empty())
	{
		client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "PART"));
		return;
	}

	std::string name = arguments[0];
	std::string reason = "";

	if (arguments.size() >= 2)
		for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); it++)
			reason.append(*it + " ");
	if (reason[0] == ':')
		reason = reason.substr(1, reason.size());
	if (reason[reason.size() - 1] == ' ')
		reason = reason.substr(0, reason.size() - 1);
	Channel *channel = _server->getChannel(name);
	if (!channel)
	{
		client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), name));
		return;
	}
	std::vector<Channel *> chans = client->getUserChans();
	std::vector<Channel *>:: iterator it = chans.begin();

	Channel *chan;
	while (it != chans.end())
	{
		chan = it.operator*();
		if (chan->getName() == name)
			break ;
		++it;
	}
	if (it == chans.end())
	{
		client->write(ERR_NOTONCHANNEL(client->getNickName(), name));
	 	return;
	}

	client->leave(chan, 0, reason);
}
