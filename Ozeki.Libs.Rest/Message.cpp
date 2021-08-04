#include "pch.h"
#include "Message.h"

Message::Message(void) {
	this->ID = uuidGenerator().uuid();
	this->ValidUntil.addWeek();
	this->IsSubmitReportRequested = true;
	this->IsDeliveryReportRequested = true;
	this->IsViewReportRequested = true;
};

Message::Message(json message) {
	if (message.find("message_id") != message.end()) {
		this->ID = message["message_id"];
	}
	if (message.find("from_connection") != message.end()) {
		this->FromConnection = message["from_connection"];
	}
	if (message.find("from_address") != message.end()) {
		this->FromAddress = message["from_address"];
	}
	if (message.find("from_station") != message.end()) {
		this->FromStation = message["from_station"];
	}
	if (message.find("to_connection") != message.end()) {
		this->ToConnection = message["to_connection"];
	}
	if (message.find("to_address") != message.end()) {
		this->ToAddress = message["to_address"];
	}
	if (message.find("to_station") != message.end()) {
		this->ToStation = message["to_station"];
	}
	if (message.find("text") != message.end()) {
		this->Text = message["text"];
	}
	if (message.find("create_date") != message.end()) {
		this->CreateDate = localdatetime(message["create_date"].get<string>());
	}
	if (message.find("valid_until") != message.end()) {
		this->ValidUntil = localdatetime(message["valid_until"].get<string>());
	}
	if (message.find("time_to_send") != message.end()) {
		this->TimeToSend = localdatetime(message["time_to_send"].get<string>());
	}
	if (message.find("submit_report_requested") != message.end()) {
		this->IsSubmitReportRequested = message["submit_report_requested"].get<bool>();
	}
	if (message.find("delivery_report_requested") != message.end()) {
		this->IsDeliveryReportRequested = message["delivery_report_requested"].get<bool>();
	}
	if (message.find("view_report_requested") != message.end()) {
		this->IsViewReportRequested = message["view_report_requested"].get<bool>();
	}
	if (message.find("tags") != message.end()) {
		json tags = message["tags"];
		if (tags.size() > 0) {
			for (unsigned i = 0; i < tags.size(); i++) {
				this->addTag(tags[i]["name"], tags[i]["value"]);
			}
		}
	}
}


void Message::addTag(string key, string value) {
	this->Tags.push_back(pair<string, string>(key, value));
}

json Message::getTags(void) {
	json tags = json::array();
	for (unsigned i = 0; i < (this->Tags.size()); i++)
	{
		json tag;
		tag[this->Tags[i].first] = this->Tags[i].second;
		tags.push_back(tag);
	}
	return tags;
}

json Message::toJSON(void) {
	json JSON;

	if (this->ID.size() != 0) {
		JSON["message_id"] = this->ID;
	}

	if (this->FromConnection.size() != 0) {
		JSON["from_connection"] = this->FromConnection;
	}

	if (this->FromAddress.size() != 0) {
		JSON["from_address"] = this->FromAddress;
	}

	if (this->FromStation.size() != 0) {
		JSON["from_station"] = this->FromStation;
	}

	if (this->ToConnection.size() != 0) {
		JSON["to_connection"] = this->ToConnection;
	}

	if (this->ToAddress.size() != 0) {
		JSON["to_address"] = this->ToAddress;
	}

	if (this->ToStation.size() != 0) {
		JSON["to_station"] = this->ToStation;
	}

	if (this->Text.size() != 0) {
		JSON["text"] = this->Text;
	}

	JSON["create_date"] = this->CreateDate.toString();
	JSON["valid_until"] = this->ValidUntil.toString();
	JSON["time_to_send"] = this->TimeToSend.toString();

	JSON["submit_report_requested"] = this->IsSubmitReportRequested;
	JSON["submit_delivery_requested"] = this->IsDeliveryReportRequested;
	JSON["submit_view_requested"] = this->IsViewReportRequested;
	
	if (this->Tags.size() != 0) {
		JSON["tags"] = getTags();
	}
	return JSON;
}

std::ostream& operator<<(std::ostream& os, const Message& message)
{
	return os << "->" << message.ToAddress << " '" << message.Text << "'";
}