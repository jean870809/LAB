#include <bits/stdc++.h>

#include <fcntl.h> //print ф.ψ
using namespace std;

string bell_state[4] = {"+00+11", "+00-11", "+01+10", "+01-10"}; //phi+,phi-,psi+,psi-
vector<string> output;
vector<string> swap_output;
vector<string> output2;

void output_print(vector<string> output, int length);
void output_bellstate(vector<string> output, int length);
void csv_output_bellstate(vector<string> output);
void expand(string s, int i);
string output_csv = "bellstate_.csv";
int main()
{
    int input;
    int swap_state[4];
    cin >> input;
    output_csv.insert(10, to_string(input));
    cout << "--------------------------------------------" << input << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < 4; i++)
    {
        swap_state[i] = int(input / pow(10, 3 - i));
        input -= pow(10, 3 - i) * swap_state[i];
        //cout << swap_state[i] << endl;
    }

    //=======================================
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
            swap_output.push_back(temp);

            temp.clear();
        }
    }
    output_print(output, 25);
    //---------------------
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 1; j < output[i].size(); j += 5)
        {
            swap_output[i][j] = output[i][j + swap_state[0] - 1];
            swap_output[i][j + 1] = output[i][j + swap_state[1] - 1];
            swap_output[i][j + 2] = output[i][j + swap_state[2] - 1];
            swap_output[i][j + 3] = output[i][j + swap_state[3] - 1];
        }
    }
    output_print(swap_output, 25);

    //---------------------用bell state測量 ф+(H).ф-(h).ψ+(S).ψ-(s)
    /*
    00 = ф+ + ф- (H+h)
    01 = ψ+ + ψ- (S+s)
    10 = ψ+ - ψ- (S-s)
    11 = ф+ - ф- (H-h)
    */
    string temp2;
    for (int i = 0; i < swap_output.size(); i++)
    {
        for (int j = 0; j < swap_output[i].size(); j++)
        {
            if ((j % 5) == 0) //+ or -
            {
                temp2.push_back(swap_output[i][j]);
            }
            if ((j % 5) == 1 || (j % 5) == 3)
            {
                if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '0')
                {
                    temp2.append("(+H+h)");
                }
                else if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '1')
                {
                    temp2.append("(+S+s)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '0')
                {
                    temp2.append("(+S-s)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '1')
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
    //output_print(output2, 20);
    output_bellstate(output2, 45);
    //csv_output_bellstate(output2);
    return 0;
}
void expand(string s, int i)
{
    string tmp;
    string epd;  //expand
    string fepd; //final_expand
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
    //cout << fepd << endl;

    if (fepd[1] == 'S')
    {
        string substr1 = fepd.substr(0, 6);
        string substr2 = fepd.substr(6, 6);
        fepd.clear();
        fepd = fepd + substr2 + substr1;
    }
    //cout << fepd << endl;
    output2[i] = fepd;
}
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
void output_bellstate(vector<string> output, int length)
{
    //----------------output---------------
    _setmode(_fileno(stdout), _O_U16TEXT);

    wcout << L"-----------------------------------------------------------------------------------------------------------" << endl;
    wcout << L"           ";
    wcout << left << setw(length) << setfill(L' ') << L" \u0444+";
    wcout << left << setw(length) << setfill(L' ') << L" \u0444-";
    wcout << left << setw(length) << setfill(L' ') << L" \u03C8+";
    wcout << left << setw(length) << setfill(L' ') << L" \u03C8-";
    wcout << endl;
    for (int i = 0; i < output.size(); i++)
    {
        if (i == 0)
        {
            wcout << left << setw(2) << setfill(L' ') << L" \u0444+";
        }
        else if (i == 4)
        {
            wcout << left << setw(2) << setfill(L' ') << L" \u0444-";
        }
        else if (i == 8)
        {
            wcout << left << setw(2) << setfill(L' ') << L" \u03C8+";
        }
        else if (i == 12)
        {
            wcout << left << setw(2) << setfill(L' ') << L" \u03C8-";
        }
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
void csv_output_bellstate(vector<string> output)
{
    ofstream myFile;
    myFile.open(output_csv);
    myFile << ",ф+,ф-,ψ+,ψ-" << endl;
    for (int i = 0; i < output.size(); i++)
    {
        if (i == 0)
        {
            myFile << "ф+,";
        }
        else if (i == 4)
        {
            myFile << "ф-,";
        }
        else if (i == 8)
        {
            myFile << "ψ+,";
        }
        else if (i == 12)
        {
            myFile << "ψ-,";
        }
        for (int j = 0; j < output[i].size(); j++)
        {
            if (output[i][j] == 'H')
            {
                myFile << "ф+";
            }
            else if (output[i][j] == 'h')
            {
                myFile << "ф-";
            }
            else if (output[i][j] == 'S')
            {
                myFile << "ψ+";
            }
            else if (output[i][j] == 's')
            {
                myFile << "ψ-";
            }
            else
            {
                myFile << output[i][j];
            }
        }
        if ((i % 4) == 3)
        {
            myFile << endl;
        }
        else
        {
            myFile << ",";
        }
    }
}
