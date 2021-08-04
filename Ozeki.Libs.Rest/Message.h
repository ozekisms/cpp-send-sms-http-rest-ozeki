#pragma once
#include "localdatetime.h"
#include <string>
#include <vector>
#include "uuid.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

class Message
{
public:
	string ID;
	string FromConnection;
	string FromAddress;
	string FromStation;
	string ToConnection;
	string ToAddress;
	string ToStation;
	string Text;
	localdatetime CreateDate = localdatetime();
	localdatetime ValidUntil = localdatetime();
	localdatetime TimeToSend = localdatetime();
	bool IsSubmitReportRequested;
	bool IsDeliveryReportRequested;
	bool IsViewReportRequested;
	vector<pair<string, string>> Tags;

	Message(void);

	Message(json message);

	void addTag(string key, string value);

	json getTags(void);

	json toJSON(void);
};

