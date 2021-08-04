#pragma once
#define CURL_STATICLIB
#include "../Ozeki.Libs.Rest/curl/curl.h"
#ifdef _DEBUG
#pragma comment (lib, "../Ozeki.Libs.Rest/curl/libcurl_a_debug.lib")
#else
#pragma comment (lib, "../Ozeki.Libs.Rest/curl/libcurl_a.lib")
#endif
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "Crypt32.lib")
#include "cppcodec\base64_default_rfc4648.hpp"
#include "Configuration.h"
#include "MessageSendResult.h"
#include "MessageSendResults.h"
#include "MessageMarkResult.h"
#include "MessageDeleteResult.h"
#include "MessageReceiveResult.h"
#include "Message.h"
#include "Folder.h"
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
using base64 = cppcodec::base64_rfc4648;

class MessageApi {
public:

	Configuration _configuration;

	MessageApi(Configuration configuration) {
		_configuration = configuration;
	};

	MessageSendResult Send(Message message);

	MessageSendResults Send(vector<Message> messages);

	bool Delete(Folder folder, Message message);

	MessageDeleteResult Delete(Folder folder, vector<Message> messages);

	bool Mark(Folder folder, Message message);

	MessageMarkResult Mark(Folder folder, vector<Message> messages);

	MessageReceiveResult DownloadIncoming();

private:

	string createAuthorizationHeader(string username, string password);

	string createRequestBody(Message message);

	string createRequestBody(vector<Message> messages);

	string createRequestBodyManipulate(Folder folder, Message message);

	string createRequestBodyManipulate(Folder folder, vector<Message> messages);

	char* createUriToSendSms(string url);

	char* createUriToDeleteSms(string url);

	char* createUriToMarkSms(string url);

	char* createUriToReceiveSms(string url, Folder folder);

	MessageSendResults getResponse(string response) {
		json resp = json::parse(response);
		json data = resp["data"];
		json messages = data["messages"];
		vector<MessageSendResult> results;
		if (messages.size() > 0) {
			for (unsigned i = 0; i < messages.size(); i++) {
				Message message = Message(messages[i]);
				results.push_back(MessageSendResult(message, Success, resp["response_msg"].get<string>()));
			}
		}
		return MessageSendResults(data["total_count"].get<int>(), data["success_count"].get<int>(), data["failed_count"].get<int>(), results);
	};

	MessageDeleteResult getResponseDelete(string response, vector<Message> messages, Folder folder) {
		json resp = json::parse(response);
		vector<string> msgs;
		for (unsigned i = 0; i < messages.size(); i++) {
			msgs.push_back(messages[i].ID);
		}
		if (resp["response_code"] == "SUCCESS") {
			vector<string> failed;
			vector<string> succeeded;
			json ids = resp["data"]["message_ids"];
			for (unsigned i = 0; i < msgs.size(); i++) {
				bool success = false;
				for (unsigned j = 0; j < ids.size(); j++) {
					if (msgs[i] == ids[j]) {
						success = true;
					}
				}
				if (success) {
					succeeded.push_back(msgs[i]);
				}
				else {
					failed.push_back(msgs[i]);
				}
			}
			return MessageDeleteResult(folder, succeeded, failed);
		}
		else {
			return MessageDeleteResult(folder, {}, msgs);
		}
	};

	MessageMarkResult getResponseMark(string response, vector<Message> messages, Folder folder) {
		json resp = json::parse(response);
		vector<string> msgs;
		for (unsigned i = 0; i < messages.size(); i++) {
			msgs.push_back(messages[i].ID);
		}
		if (resp["response_code"] == "SUCCESS") {
			vector<string> failed;
			vector<string> succeeded;
			json ids = resp["data"]["message_ids"];
			for (unsigned i = 0; i < msgs.size(); i++) {
				bool success = false;
				for (unsigned j = 0; j < ids.size(); j++) {
					if (msgs[i] == ids[j]) {
						success = true;
					}
				}
				if (success) {
					succeeded.push_back(msgs[i]);
				}
				else {
					failed.push_back(msgs[i]);
				}
			}
			return MessageMarkResult(folder, succeeded, failed);
		}
		else {
			return MessageMarkResult(folder, {}, msgs);
		}
	};

	MessageReceiveResult getResponseReceive(string response, Folder folder) {
		json data = json::parse(response)["data"];
		string limit = data["limit"];
		json messages = data["data"];
		vector<Message> msgs;
		if (messages.size() > 0) {
			for (unsigned i = 0; i < messages.size(); i++) {
				Message msg = Message(messages[i]);
				msgs.push_back(msg);
			}
			this->Delete(folder, msgs);
		}
		return MessageReceiveResult(folder, limit, msgs);
	}

	string getFolder(Folder folder) {
		if (folder == Inbox) {
			return "inbox";
		}
		else if (folder == Outbox) {
			return "outbox";
		}
		else if (folder == Sent) {
			return "sent";
		}
		else if (folder == NotSent) {
			return "notsent";
		}
		else if (folder == Deleted) {
			return "deleted";
		}
		else {
			return "";
		}
	}

	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}

	string doRequestPost(char* url, string authorizationHeader, string requestBody) {
		CURL* curl;
		CURLcode res;
		string readBuffer;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if (curl) {
			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Accept: application/json");
			headers = curl_slist_append(headers, "Content-Type: application/json");
			headers = curl_slist_append(headers, ("Authorization: " + authorizationHeader).c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			return readBuffer;
		}
		return "";
	}

	string doRequestGet(char* url, string authorizationHeader) {
		CURL* curl;
		CURLcode res;
		string readBuffer;

		curl_global_init(CURL_GLOBAL_ALL);

		curl = curl_easy_init();
		if (curl) {
			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Accept: application/json");
			headers = curl_slist_append(headers, "Content-Type: application/json");
			headers = curl_slist_append(headers, ("Authorization: " + authorizationHeader).c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl_global_cleanup();
			return readBuffer;
		}
		return "";
	};
};