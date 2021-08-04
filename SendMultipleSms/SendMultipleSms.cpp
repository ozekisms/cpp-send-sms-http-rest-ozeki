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

    Message msg1;
    msg1.ToAddress = "+36201111111";
    msg1.Text = "Hello world 1";

    Message msg2;
    msg2.ToAddress = "+36202222222";
    msg2.Text = "Hello world 2";

    Message msg3;
    msg3.ToAddress = "+36203333333";
    msg3.Text = "Hello world 3";

    MessageApi api(configuration);

    auto result = api.Send({ msg1, msg2, msg3 });

    cout << result << endl;

    return 0;
}