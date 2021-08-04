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
    msg.ID = "3587663a-f85a-4332-bb08-8cd58a772d20";

    MessageApi api(configuration);

    auto result = api.Delete(Inbox, msg);

    cout << result << endl;

    return 0;
}