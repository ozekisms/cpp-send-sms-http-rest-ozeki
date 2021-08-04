#include "pch.h"
#include "MessageReceiveResult.h"

MessageReceiveResult::MessageReceiveResult(Folder folder, string limit, vector<Message> messages) {
	this->folder = folder;
	this->Limit = limit;
	this->Messages = messages;
	this->MessageCount = messages.size();
}

std::ostream& operator<<(std::ostream& os, const MessageReceiveResult& messageReceiveResult)
{
	return os << "Message count: " << messageReceiveResult.MessageCount << ".";
}