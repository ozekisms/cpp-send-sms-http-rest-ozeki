#pragma once
#include <vector>
#include "MessageSendResult.h"

class MessageSendResults
{
public:
	int TotalCount;
	int SuccessCount;
	int FailedCount;
	vector<MessageSendResult> Results;

	MessageSendResults(int totalCount, int successCount, int failedCount, vector<MessageSendResult> results);
};

