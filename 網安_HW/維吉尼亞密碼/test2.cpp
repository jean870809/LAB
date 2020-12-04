#include <bits/stdc++.h>

using namespace std;

int main()
{
    string input = "Hello World";
    string key;
    cin >> key;

    for (int i = 0; i < input.length(); i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;
    int temp = 0;
    for (int i = 0; i < input.length(); i++)
    {

        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
        {
            int j = temp % (key.length());
            cout << key[j] << " ";
            temp++;
        }
        else
        {
            cout << " "
                 << " ";
        }
    }
    cout << endl;
    temp = 0;
    for (int i = 0; i < input.length(); i++)
    {

        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
        {
            int j = temp % (key.length());
            cout << key[j]-'A' << " ";
            temp++;
        }
        else
        {
            cout << " "
                 << " ";
        }
    }
    cout << endl;
    return 0;
}