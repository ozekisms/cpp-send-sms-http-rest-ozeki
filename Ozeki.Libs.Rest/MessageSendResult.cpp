#include "pch.h"
#include "MessageSendResult.h"

MessageSendResult::MessageSendResult(Message message, DeliveryStatus status, string statusMessage) {
	this->message = message;
	this->status = status;
	this->statusMessage = statusMessage;
}

std::ostream& operator<<(std::ostream& os, const DeliveryStatus& status)
{
	switch (status)
	{
	case Success:
		return os << "Success";
	case Failed:
		return os << "Failed";
	default:
		return os << "";
	}
}

std::ostream& operator<<(std::ostream& os, const MessageSendResult& messageSendResult)
{
	return os << messageSendResult.status << ", ->" << messageSendResult.message.ToAddress << " '" << messageSendResult.message.Text << "'";
}