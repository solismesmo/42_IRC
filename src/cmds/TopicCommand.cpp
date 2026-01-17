#include "ft_irc.hpp"

TopicCommand::TopicCommand(Server *server) : Command(server) {}
TopicCommand::~TopicCommand() {}

// TOPIC <channel> [ :<topic> ]
void TopicCommand::execute(Client *client, std::vector<std::string> arguments)
{
    if (arguments.size() < 1 || arguments[0].empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNickName(), "TOPIC"));
        return;
    }

    std::string chanName = arguments[0];
    Channel *channel = _server->getChannel(chanName);
    if (!channel)
    {
        client->reply(ERR_NOSUCHCHANNEL(client->getNickName(), chanName));
        return;
    }

    if (!channel->isInChannel(client))
    {
        client->reply(ERR_NOTONCHANNEL(client->getNickName(), chanName));
        return;
    }

    // Query (TOPIC #chan)
    if (arguments.size() == 1)
    {
        if (channel->getTopic().empty())
            client->reply(RPL_NOTOPIC(client->getNickName(), chanName));
        else
            client->reply(RPL_TOPIC(client->getNickName(), chanName, channel->getTopic()));
        return;
    }

    // Build topic with spaces (TOPIC #chan :hello world)
    std::string topic;
    for (std::vector<std::string>::iterator it = arguments.begin() + 1; it != arguments.end(); ++it)
        topic.append(*it + " ");

    if (!topic.empty() && topic[0] == ':')
        topic = topic.substr(1);

    while (!topic.empty() && (topic[topic.size() - 1] == ' ' || topic[topic.size() - 1] == '\t'))
        topic.erase(topic.size() - 1);

    // If +t: only admin/op can set
    if (channel->isTopicRestricted() && channel->getAdmin() != client && !channel->is_oper(client))
    {
        client->reply(ERR_CHANOPRIVSNEEDED(client->getNickName(), chanName));
        return;
    }

    channel->setTopic(topic);

    // Important: broadcast TOPIC so irssi updates
    channel->broadcast(":" + client->getPrefix() + " TOPIC " + chanName + " :" + topic);
}
