#pragma once
#include "Message.h"
#include "DeliveryStatus.h"
#include <string>

class MessageSendResult
{
public:
	Message message;
	DeliveryStatus status;
	string statusMessage;

	MessageSendResult(Message message, DeliveryStatus status, string statusMessage);
};