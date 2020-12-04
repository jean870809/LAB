#include <bits/stdc++.h>

using namespace std;
void encode(string input, int key); //加密
void decode(string input, int key); //解密
int main()
{
    string input;
    int key, mode = 2;
    int input_check = 1;

    cout << "Caesar Cipher" << endl;

    while (mode != -1)
    {
        while (1)
        {
            cout << "choose mode(Encode:0 ,Decode:1,Exit:-1)" << endl; //設定模式 加密:0 解密:1 離開:-1
            cin >> mode;
            if (mode != 0 && mode != 1 && mode != -1)
            {
                cout << "Error. Please enter again." << endl;
            }
            else
            {
                break;
            }
        }
        cout << endl;
        if (mode == -1) //mode = -1 離開程式
        {
            cout << "Exit" << endl;
            break;
        }
        if (mode == 0) //mode = 0 加密
        {
            cout << "============================" << endl;
            cout << "Encode: " << endl;
        }
        if (mode == 1) //mode = 1 解密
        {
            cout << "============================" << endl;
            cout << "Decode: " << endl;
        }
        cout << "Please input Message: " << endl;
        input = "\n"; //因為有cin跟getline 所以要先清除緩存
        getline(cin, input);
        getline(cin, input);

        while (1) //檢查key是否在0-25內 否則重新輸入
        {
            cout << "Please input key(0-25): " << endl;
            cin >> key;
            if (key >= 0 && key <= 25)
            {
                break;
            }
            else
            {
                cout << "Error!  Please enter again." << endl;
            }
        }

        if (mode == 0)
        {
            encode(input, key);
        }
        if (mode == 1)
        {
            decode(input, key);
        }
    }

    return 0;
}
void encode(string input, int key) //加密
{
    string output;
    for (int i = 0; i < input.length(); i++)
    {
        if ((input[i] >= 'A' && input[i] <= 'Z'))
        {
            output.push_back(((input[i] - 'A') + key) % 26 + 'A');
        }
        else if ((input[i] >= 'a' && input[i] <= 'z'))
        {
            output.push_back(((input[i] - 'a') + key) % 26 + 'a');
        }

        else if (input[i] == ' ')
        {
            output.push_back(input[i]);
        }
        else
        {
            cout << "Error!" << endl;
            break;
        }
    }
    cout << "Message encode: " << output << endl;
    cout << "============================" << endl;
}

void decode(string input, int key) //解密
{
    string output;
    for (int i = 0; i < input.length(); i++)
    {
        if ((input[i] >= 'A' && input[i] <= 'Z'))
        {
            output.push_back(((input[i] - 'A') + (26 - key)) % 26 + 'A');
        }
        else if ((input[i] >= 'a' && input[i] <= 'z'))
        {
            output.push_back(((input[i] - 'a') + (26 - key)) % 26 + 'a');
        }

        else if (input[i] == ' ')
        {
            output.push_back(input[i]);
        }
        else
        {
            cout << "Error!" << endl;
            break;
        }
    }
    cout << "Message decode: " << output << endl;
    cout << "============================" << endl;
}
