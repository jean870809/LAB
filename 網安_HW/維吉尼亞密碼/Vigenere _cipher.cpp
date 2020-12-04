#include <bits/stdc++.h>

using namespace std;
void encode(string input, string key, int keylen); //加密
void decode(string input, string key, int keylen); //解密

int main()
{
    string input;
    char k[999]; //get 使用者輸入的key
    string key;  //整理過後的key
    int mode = 2;
    int input_check = 1;

    cout << "Vigenere Cipher" << endl;

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

        cout << "Please input key: (number(0-25) please use blankspace' 'or '*' or ',' or '.' or ';' to separate)" << endl;
        cin.getline(k, 999); //使用者可混合輸入字母跟數字
        const char *d = "  *,.;"; //分割依據
        char *p;                  //儲存每次分割結果
        p = strtok(k, d);
        while (p)
        {

            for (int j = 0; j < strlen(p); j++)
            {
                if (isdigit(p[j]))
                {
                    key.push_back(atoi(p) + 'A');
                    break;
                }
                else
                {
                    key.push_back(p[j]);
                }
            }
            p = strtok(NULL, d);
        }
        int keylen = key.length();
        for (int i = 0; i < keylen; i++) //刪除key中的重複字元
        {
            for (int j = i + 1; j < keylen; j++)
            {
                if (key[j] == key[i])
                {
                    for (int k = j + 1; k < keylen; k++)
                    {
                        key[k - 1] = key[k];
                    }
                    keylen--; //陣列長度-1
                    j--;      //重複點再次進行查重
                }
            }
        }

        //依據選擇模式選擇做哪種加密
        if (mode == 0)
        {
            encode(input, key, keylen);
        }
        if (mode == 1)
        {
            decode(input, key, keylen);
        }
    }

    return 0;
}
void encode(string input, string key, int keylen) //加密
{
    string output;
    int index = 0, j;
    for (int i = 0; i < input.length(); i++)
    {
        j = index % (keylen);
        if ((input[i] >= 'A' && input[i] <= 'Z') && (key[j] >= 'A' && key[j] <= 'Z')) //如果input[i]是大寫字母&key[i]是大寫字母
        {
            output.push_back(((input[i] - 'A') + (key[j] - 'A')) % 26 + 'A');
            index++;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') && (key[j] >= 'A' && key[j] <= 'Z')) //如果input[i]是小寫字母&key[i]是大寫字母
        {
            output.push_back(((input[i] - 'a') + (key[j] - 'A')) % 26 + 'a');
            index++;
        }
        else if ((input[i] >= 'A' && input[i] <= 'Z') && (key[j] >= 'a' && key[j] <= 'z')) //如果input[i]是大寫字母&key[i]是小寫字母
        {
            output.push_back(((input[i] - 'A') + (key[j] - 'a')) % 26 + 'A');
            index++;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') && (key[j] >= 'a' && key[j] <= 'z')) //如果input[i]是小寫字母&key[i]是小寫字母
        {
            output.push_back(((input[i] - 'a') + (key[j] - 'a')) % 26 + 'a');
            index++;
        }
        else  //如果input[i]是空白則一樣
        {
            output.push_back(input[i]);
        }
        
    }
    cout << "Message encode: " << output << endl;
    cout << "============================" << endl;
}

void decode(string input, string key, int keylen) //解密
{
    string output;
    int index = 0, j;
    for (int i = 0; i < input.length(); i++)
    {
        j = index % (keylen);
        if ((input[i] >= 'A' && input[i] <= 'Z') && (key[j] >= 'A' && key[j] <= 'Z')) //如果input[i]是大寫字母&key[i]是大寫字母
        {
            output.push_back(((input[i] - 'A') + (26 - (key[j] - 'A'))) % 26 + 'A');
            index++;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') && (key[j] >= 'A' && key[j] <= 'Z')) //如果input[i]是小寫字母&key[i]是大寫字母
        {
            output.push_back(((input[i] - 'a') + (26 - (key[j] - 'A'))) % 26 + 'a');
            index++;
        }
        else if ((input[i] >= 'A' && input[i] <= 'Z') && (key[j] >= 'a' && key[j] <= 'z')) //如果input[i]是大寫字母&key[i]是小寫字母
        {
            output.push_back(((input[i] - 'A') + (26 - (key[j] - 'a'))) % 26 + 'A');
            index++;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') && (key[j] >= 'a' && key[j] <= 'z')) //如果input[i]是小寫字母&key[i]是小寫字母
        {
            output.push_back(((input[i] - 'a') + (26 - (key[j] - 'a'))) % 26 + 'a');
            index++;
        }
        else  //如果input[i]是空白則一樣
        {
            output.push_back(input[i]);
        }
        
    }
    cout << "Message decode: " << output << endl;
    cout << "============================" << endl;
}
string delduplicate(string key)
{
    int len = key.length();
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (key[j] == key[i])
            {
                for (int k = j + 1; k < len; k++)
                {
                    key[k - 1] = key[k];
                }
                len--; //陣列長度-1
                j--;   //重複點再次進行查重
            }
        }
    }
    for (int i = 0; i < key.length(); i++)
    {
        cout << key[i];
    }
    return key;
}
