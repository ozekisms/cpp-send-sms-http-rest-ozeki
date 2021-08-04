#pragma once
#include "Folder.h"
#include <vector>

class MessageDeleteResult
{
public:
	Folder folder;
	vector<string> MessageIdsRemoveSucceeded;
	vector<string> MessageIdsRemoveFailed;
	int TotalCount;
	int SuccessCount;
	int FailedCount;

	MessageDeleteResult(Folder folder, vector<string> messageIdsRemoveSucceeded, vector<string> messageIdsRemoveFailed);
};