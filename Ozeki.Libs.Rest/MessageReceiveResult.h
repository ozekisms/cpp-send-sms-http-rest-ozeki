#pragma once
#include <vector>
#include "Folder.h"
#include "Message.h"

class MessageReceiveResult
{
public:
	Folder folder;
	string Limit;
	vector<Message> Messages;
	int MessageCount;

	MessageReceiveResult(Folder folder, string limit, vector<Message> messages);
};

