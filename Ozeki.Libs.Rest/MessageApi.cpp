#include "pch.h"
#include "MessageApi.h"

string MessageApi::createAuthorizationHeader(string username, string password) {
	string usernamePassword = username + ":" + password;
	string usernamePasswordEncoded = base64::encode(usernamePassword);
	return "Basic " + usernamePasswordEncoded;
}

string MessageApi::createRequestBody(Message message) {
	json result;
	json messages = json::array();
	messages.push_back(message.toJSON());
	result["messages"] = messages;
	return result.dump();
}

string MessageApi::createRequestBody(vector<Message> messages) {
	json result;
	json msgs = json::array();
	for (unsigned i = 0; i < messages.size(); i++) {
		msgs.push_back(messages[i].toJSON());
	}
	result["messages"] = msgs;
	return result.dump();
}

string MessageApi::createRequestBodyManipulate(Folder folder, Message message) {
	json result;
	json messages = json::array();
	messages.push_back(message.ID);
	result["folder"] = getFolder(folder);
	result["message_ids"] = messages;
	return result.dump();
}

string MessageApi::createRequestBodyManipulate(Folder folder,  vector<Message> messages) {
	json result;
	json msgs = json::array();
	for (unsigned i = 0; i < messages.size(); i++) {
		msgs.push_back(messages[i].ID);
	}
	result["folder"] = getFolder(folder);
	result["message_ids"] = msgs;
	return result.dump();
}

char* MessageApi::createUriToSendSms(string url) {
	string action = "?action=sendmsg";
	char* nextToken = NULL;
	char* uri = new char[url.length() + 1];
	strcpy_s(uri, (url.length() + 1), url.c_str());
	char* baseUrl = strtok_s(uri, "?", &nextToken);
	char* actionChar = new char[action.length() + 1];
	strcpy_s(actionChar, (action.length() + 1), action.c_str());
	char* result = new char[url.length() + action.length() + 1];
	strcpy_s(result, (url.length() + action.length() + 1), baseUrl);
	strcat_s(result, (url.length() + action.length() + 1), actionChar);
	return result;
};

char* MessageApi::createUriToDeleteSms(string url) {
	string action = "?action=deletemsg";
	char* nextToken = NULL;
	char* uri = new char[url.length() + 1];
	strcpy_s(uri, (url.length() + 1), url.c_str());
	char* baseUrl = strtok_s(uri, "?", &nextToken);
	char* actionChar = new char[action.length() + 1];
	strcpy_s(actionChar, (action.length() + 1), action.c_str());
	char* result = new char[url.length() + action.length() + 1];
	strcpy_s(result, (url.length() + action.length() + 1), baseUrl);
	strcat_s(result, (url.length() + action.length() + 1), actionChar);
	return result;
};

char* MessageApi::createUriToMarkSms(string url) {
	string action = "?action=markmsg";
	char* nextToken = NULL;
	char* uri = new char[url.length() + 1];
	strcpy_s(uri, (url.length() + 1), url.c_str());
	char* baseUrl = strtok_s(uri, "?", &nextToken);
	char* actionChar = new char[action.length() + 1];
	strcpy_s(actionChar, (action.length() + 1), action.c_str());
	char* result = new char[url.length() + action.length() + 1];
	strcpy_s(result, (url.length() + action.length() + 1), baseUrl);
	strcat_s(result, (url.length() + action.length() + 1), actionChar);
	return result;
};

char* MessageApi::createUriToReceiveSms(string url, Folder folder) {
	string action = "?action=receivemsg&folder=";
	string foldr = getFolder(folder);
	char* nextToken = NULL;
	char* uri = new char[url.length() + 1];
	strcpy_s(uri, (url.length() + 1), url.c_str());
	char* baseUrl = strtok_s(uri, "?", &nextToken);
	char* actionChar = new char[action.length() + 1];
	char* folderChar = new char[foldr.length() + 1];
	strcpy_s(actionChar, (action.length() + 1), action.c_str());
	strcpy_s(folderChar, (foldr.length() + 1), foldr.c_str());
	char* result = new char[url.length() + action.length() + 1];
	strcpy_s(result, (url.length() + action.length() + foldr.length() + 1), baseUrl);
	strcat_s(result, (url.length() + action.length() + foldr.length() + 1), actionChar);
	strcat_s(result, (url.length() + action.length() + foldr.length() + 1 ), folderChar);
	return result;
};

MessageSendResult MessageApi::Send(Message message) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBody(message);
	return getResponse(doRequestPost(createUriToSendSms(_configuration.ApiUrl), authorizationHeader, requestBody)).Results[0];
}

MessageSendResults MessageApi::Send(vector<Message> message) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBody(message);
	return getResponse(doRequestPost(createUriToSendSms(_configuration.ApiUrl), authorizationHeader, requestBody));
}

bool MessageApi::Delete(Folder folder , Message message) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBodyManipulate(folder, message);
	MessageDeleteResult result = getResponseDelete(doRequestPost(createUriToDeleteSms(_configuration.ApiUrl), authorizationHeader, requestBody), { message }, folder);
	if (result.FailedCount == 0 && result.SuccessCount == result.TotalCount) {
		return true;
	}
	else {
		return false;
	}
}

MessageDeleteResult MessageApi::Delete(Folder folder, vector<Message> messages) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBodyManipulate(folder, messages);
	return getResponseDelete(doRequestPost(createUriToDeleteSms(_configuration.ApiUrl), authorizationHeader, requestBody), messages, folder);
}

bool MessageApi::Mark(Folder folder, Message message) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBodyManipulate(folder, message);
	MessageMarkResult result = getResponseMark(doRequestPost(createUriToMarkSms(_configuration.ApiUrl), authorizationHeader, requestBody), { message }, folder);
	if (result.FailedCount == 0 && result.SuccessCount == result.TotalCount) {
		return true;
	}
	else {
		return false;
	}
}

MessageMarkResult MessageApi::Mark(Folder folder, vector<Message> messages) {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	string requestBody = createRequestBodyManipulate(folder, messages);
	return getResponseMark(doRequestPost(createUriToMarkSms(_configuration.ApiUrl), authorizationHeader, requestBody), messages, folder);
}

MessageReceiveResult MessageApi::DownloadIncoming() {
	string authorizationHeader = createAuthorizationHeader(_configuration.Username, _configuration.Password);
	return getResponseReceive(doRequestGet(createUriToReceiveSms(_configuration.ApiUrl, Inbox), authorizationHeader), Inbox);
}