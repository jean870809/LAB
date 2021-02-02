#include <bits/stdc++.h>

#include <fcntl.h> //print ф.ψ
using namespace std;

string bell_state[4] = {"+00+11", "+00-11", "+01+10", "+01-10"}; //phi+,phi-,psi+,psi-
vector<string> output;
vector<string> output2;

void output_print(vector<string> output, int length)
{
    //----------------output---------------
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
    cout << "           ";
    for (int i = 0; i < 4; i++)
    {
        cout << left << setw(length) << setfill(' ') << bell_state[i];
    }
    cout << endl;
    for (int i = 0; i < output.size(); i++)
    {
        if ((i % 4) == 0)
        {
            cout << left << setw(11) << setfill(' ') << bell_state[int(i / 4)];
        }
        cout << left << setw(length) << setfill(' ') << output[i];
        if ((i % 4) == 3)
        {
            cout << endl;
        }
    }
    cout << "-----------------------------------------------------------------------------------------------------------" << endl;
}

void output_bellstate(vector<string> output, int length);
void expand(string s, int i);
int main()
{
    cout << "--------------------------------------------1423-----------------------------------------------------------" << endl;

    //=======================
    string temp;
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            if ((bell_state[i][0] == '+' && bell_state[j][0] == '+') || (bell_state[i][0] == '-' && bell_state[j][0] == '-'))
            {
                temp.push_back('+');
            }
            else
            {
                temp.push_back('-');
            }
            temp.append(bell_state[i], 1, 2);
            temp.append(bell_state[j], 1, 2);

            if ((bell_state[i][0] == '+' && bell_state[j][3] == '+') || (bell_state[i][0] == '-' && bell_state[j][3] == '-'))
            {
                temp.push_back('+');
            }
            else
            {
                temp.push_back('-');
            }
            temp.append(bell_state[i], 1, 2);
            temp.append(bell_state[j], 4, 2);

            if ((bell_state[i][3] == '+' && bell_state[j][0] == '+') || (bell_state[i][3] == '-' && bell_state[j][0] == '-'))
            {
                temp.push_back('+');
            }
            else
            {
                temp.push_back('-');
            }
            temp.append(bell_state[i], 4, 2);
            temp.append(bell_state[j], 1, 2);

            if ((bell_state[i][3] == '+' && bell_state[j][3] == '+') || (bell_state[i][3] == '-' && bell_state[j][3] == '-'))
            {
                temp.push_back('+');
            }
            else
            {
                temp.push_back('-');
            }
            temp.append(bell_state[i], 4, 2);
            temp.append(bell_state[j], 4, 2);
            output.push_back(temp);
            temp.clear();
        }
    }
    //output_print(output, 25);
    //---------------------1234->1324->1423
    char sw; //swap
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 2; j < output[i].size(); j += 5) //1324
        {
            sw = output[i][j];
            output[i][j] = output[i][j + 1];
            output[i][j + 1] = sw;
        }
        for (int j = 2; j < output[i].size(); j += 5) //1423
        {
            sw = output[i][j];
            output[i][j] = output[i][j + 2];
            output[i][j + 2] = sw;
        }
    }
    output_print(output, 25);
    //---------------------用bellstate測量 ф+(H).ф-(h).ψ+(S).ψ-(s)
    /*
    00 = ф+ + ф- (H+h)
    01 = ψ+ + ψ- (S+s)
    10 = ψ+ - ψ- (S-s)
    11 = ф+ - ф- (H-h)
    */
    string temp2;
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 0; j < output[i].size(); j++)
        {
            if ((j % 5) == 0) //+ or -
            {
                temp2.push_back(output[i][j]);
            }
            if ((j % 5) == 1 || (j % 5) == 3)
            {
                if (output[i][j] == '0' && output[i][j + 1] == '0')
                {
                    temp2.append("(+H+h)");
                }
                else if (output[i][j] == '0' && output[i][j + 1] == '1')
                {
                    temp2.append("(+S+s)");
                }
                else if (output[i][j] == '1' && output[i][j + 1] == '0')
                {
                    temp2.append("(+S-s)");
                }
                else if (output[i][j] == '1' && output[i][j + 1] == '1')
                {
                    temp2.append("(+H-h)");
                }
            }
        }
        //cout << temp2 << endl;
        output2.push_back(temp2);
        temp2.clear();
    }
    //output_print(output2, 60);

    for (int i = 0; i < output2.size(); i++)
    {
        expand(output2[i], i);
    }
    output_print(output2, 20);
    output_bellstate(output2, 20);
    return 0;
}
void expand(string s, int i)
{
    string tmp;
    string epd;
    string fepd;
    char sign;
    for (int i = 0; i < s.size(); i += 13)
    {

        sign = s[i];

        if ((s[i + 2] == '+' && s[i + 8] == '+') || (s[i + 2] == '-' && s[i + 8] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.push_back(s[i + 3]);
        tmp.push_back(s[i + 9]);
        if ((s[i + 2] == '+' && s[i + 10] == '+') || (s[i + 2] == '-' && s[i + 10] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.push_back(s[i + 3]);
        tmp.push_back(s[i + 11]);
        if ((s[i + 4] == '+' && s[i + 8] == '+') || (s[i + 4] == '-' && s[i + 8] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.push_back(s[i + 5]);
        tmp.push_back(s[i + 9]);
        if ((s[i + 4] == '+' && s[i + 10] == '+') || (s[i + 4] == '-' && s[i + 10] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.push_back(s[i + 5]);
        tmp.push_back(s[i + 11]);

        if (sign == '-')
        {
            for (int i = 0; i < tmp.size(); i++)
            {
                if (tmp[i] == '+')
                {
                    tmp[i] = '-';
                }
                else if (tmp[i] == '-')
                {
                    tmp[i] = '+';
                }
            }
        }
        epd += tmp;
        tmp.clear();
    }
    int subpos;
    char sign2;
    for (int i = 0; i < epd.size() / 2; i += 3)
    {
        sign = epd[i];
        subpos = epd.find(epd.substr(i + 1, 2), i + 3);
        sign2 = epd[subpos - 1];
        if (sign == sign2)
        {
            fepd += sign;
            fepd.append(epd, i + 1, 2);
        }
    }
    output2[i] = fepd;
}

void output_bellstate(vector<string> output, int length)
{
    //----------------output---------------
    _setmode(_fileno(stdout), _O_U16TEXT);

    wcout << L"-----------------------------------------------------------------------------------------------------------" << endl;
    //wcout << L"           ";
    /*for (int i = 0; i < 4; i++)
    {
        cout << left << setw(length) << setfill(' ') << bell_state[i];
    }
    cout << endl;*/
    for (int i = 0; i < output.size(); i++)
    {
        /*if ((i % 4) == 0)
        {
            cout << left << setw(11) << setfill(' ') << bell_state[int(i / 4)];
        }*/
        //cout << left << setw(length) << setfill(' ') << output[i];
        for (int j = 0; j < output[i].size(); j++)
        {
            if (output[i][j] == 'H')
            {
                wcout << L" \u0444+";
            }
            else if (output[i][j] == 'h')
            {
                wcout << L" \u0444-";
            }
            else if (output[i][j] == 'S')
            {
                wcout << L" \u03C8+";
            }
            else if (output[i][j] == 's')
            {
                wcout << L" \u03C8-";
            }
            else
            {
                wstring widesign;

                widesign += wchar_t(output[i][j]);
                const wchar_t *result = widesign.c_str();

                wcout << "   " << result;
            }
        }
        wcout << L"     ";
        if ((i % 4) == 3)
        {
            wcout << endl;
        }
    }
    wcout << L"-----------------------------------------------------------------------------------------------------------" << endl;
}
