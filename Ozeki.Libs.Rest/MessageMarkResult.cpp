#include "pch.h"
#include "MessageMarkResult.h"

MessageMarkResult::MessageMarkResult(Folder folder, vector<string> messageIdsMarkSucceeded, vector<string> messageIdsMarkFailed) {
	this->folder = folder;
	this->MessageIdsMarkSucceeded = messageIdsMarkSucceeded;
	this->MessageIdsMarkFailed = messageIdsMarkFailed;
	this->TotalCount = messageIdsMarkSucceeded.size() + messageIdsMarkFailed.size();
	this->SuccessCount = messageIdsMarkSucceeded.size();
	this->FailedCount = messageIdsMarkFailed.size();
}

std::ostream& operator<<(std::ostream& os, const MessageMarkResult& messageMarkResult)
{
	return os << "Total: " << messageMarkResult.TotalCount << ". Success: " << messageMarkResult.SuccessCount << ". Failed: " << messageMarkResult.FailedCount << ".";
}