#pragma once
#include "Folder.h"
#include <vector>

class MessageMarkResult
{
public:
	Folder folder;
	vector<string> MessageIdsMarkSucceeded;
	vector<string> MessageIdsMarkFailed;
	int TotalCount;
	int SuccessCount;
	int FailedCount;

	MessageMarkResult(Folder folder, vector<string> messageIdsMarkSucceeded, vector<string> messageIdsMarkFailed);
};

