#include "pch.h"
#include "MessageDeleteResult.h"

MessageDeleteResult::MessageDeleteResult(Folder folder, vector<string> messageIdsRemoveSucceeded, vector<string> messageIdsRemoveFailed) {
	this->folder = folder;
	this->MessageIdsRemoveSucceeded = messageIdsRemoveSucceeded;
	this->MessageIdsRemoveFailed = messageIdsRemoveFailed;
	this->TotalCount = messageIdsRemoveSucceeded.size() + messageIdsRemoveFailed.size();
	this->SuccessCount = messageIdsRemoveSucceeded.size();
	this->FailedCount = messageIdsRemoveFailed.size();
}

std::ostream& operator<<(std::ostream& os, const MessageDeleteResult& messageDeleteResult)
{
	return os << "Total: " << messageDeleteResult.TotalCount << ". Success: " << messageDeleteResult.SuccessCount << ". Failed: " << messageDeleteResult.FailedCount << ".";
}