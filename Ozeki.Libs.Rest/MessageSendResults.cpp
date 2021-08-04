#include "pch.h"
#include "MessageSendResults.h"

MessageSendResults::MessageSendResults(int totalCount, int successCount, int failedCount, vector<MessageSendResult> results) {
	this->TotalCount = totalCount;
	this->SuccessCount = successCount;
	this->FailedCount = failedCount;
	this->Results = results;
}

std::ostream& operator<<(std::ostream& os, const MessageSendResults& messageSendResults)
{
	return os << "Total: " << messageSendResults.TotalCount << ". Success: " << messageSendResults.SuccessCount << ". Failed: " << messageSendResults.FailedCount << ".";
}