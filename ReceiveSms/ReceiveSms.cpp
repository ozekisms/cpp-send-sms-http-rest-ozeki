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

    MessageApi api(configuration);

    auto result = api.DownloadIncoming();

    cout << result << endl;
    for (Message message : result.Messages) {
        cout << message << endl;
    }

    return 0;
}