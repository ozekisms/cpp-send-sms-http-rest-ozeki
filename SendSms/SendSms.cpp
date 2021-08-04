#include <iostream>
#include <string>
#include "Ozeki.Libs.Rest.h"

using namespace std;

int main()
{
    //Function to create unique identifier for each messages
    srand((unsigned)time(0));
	
	Configuration configuration;
	configuration.Username = "http_user";
	configuration.Password = "qwe123";
	configuration.ApiUrl = "http://127.0.0.1:9509/api";

	Message msg;
	msg.ToAddress = "+36201111111";
	msg.Text = "Hello world!";

	MessageApi api(configuration);

	auto result = api.Send(msg);

	cout << result << endl;

	return 0;
}
