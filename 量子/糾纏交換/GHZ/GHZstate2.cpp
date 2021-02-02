#include <bits/stdc++.h>

#include <fcntl.h> //print ф.ψ
using namespace std;

string bell_state[4] = {"+00+11", "+00-11", "+01+10", "+01-10"}; //phi+,phi-,psi+,psi-
vector<string> output;
vector<string> swap_output;
vector<string> output2;
vector<string> expand_output;

void output_print();
void expand(string s);
void csv_output_ghzstate();
void csv_output_ghzstate_table();

string output_csv = "GHZ_state_.csv";
string outputtable__csv = "GHZ_state_table2_.csv";

int main()
{
    int input;
    int swap_state[6];
    cin >> input;
    output_csv.insert(10, to_string(input));
    outputtable__csv.insert(16, to_string(input));

    cout << "--------------------------------------------" << input << "-----------------------------------------------------------" << endl;

    for (int i = 0; i < 6; i++)
    {
        swap_state[i] = int(input / pow(10, 5 - i));
        input -= pow(10, 5 - i) * swap_state[i];
    }

    //=======================================
    string temp;
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if ((bell_state[i][0] == '+' && bell_state[j][0] == '+' && bell_state[k][0] == '+') || (bell_state[i][0] == '-' && bell_state[j][0] == '-' && bell_state[k][0] == '+') || (bell_state[i][0] == '+' && bell_state[j][0] == '-' && bell_state[k][0] == '-') || (bell_state[i][0] == '-' && bell_state[j][0] == '+' && bell_state[k][0] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 1, 2);
                temp.append(bell_state[j], 1, 2);
                temp.append(bell_state[k], 1, 2);

                if ((bell_state[i][0] == '+' && bell_state[j][0] == '+' && bell_state[k][3] == '+') || (bell_state[i][0] == '-' && bell_state[j][0] == '-' && bell_state[k][3] == '+') || (bell_state[i][0] == '+' && bell_state[j][0] == '-' && bell_state[k][3] == '-') || (bell_state[i][0] == '-' && bell_state[j][0] == '+' && bell_state[k][3] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 1, 2);
                temp.append(bell_state[j], 1, 2);
                temp.append(bell_state[k], 4, 2);

                if ((bell_state[i][0] == '+' && bell_state[j][3] == '+' && bell_state[k][0] == '+') || (bell_state[i][0] == '-' && bell_state[j][3] == '-' && bell_state[k][0] == '+') || (bell_state[i][0] == '+' && bell_state[j][3] == '-' && bell_state[k][0] == '-') || (bell_state[i][0] == '-' && bell_state[j][3] == '+' && bell_state[k][0] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 1, 2);
                temp.append(bell_state[j], 4, 2);
                temp.append(bell_state[k], 1, 2);

                if ((bell_state[i][0] == '+' && bell_state[j][3] == '+' && bell_state[k][3] == '+') || (bell_state[i][0] == '-' && bell_state[j][3] == '-' && bell_state[k][3] == '+') || (bell_state[i][0] == '+' && bell_state[j][3] == '-' && bell_state[k][3] == '-') || (bell_state[i][0] == '-' && bell_state[j][3] == '+' && bell_state[k][3] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 1, 2);
                temp.append(bell_state[j], 4, 2);
                temp.append(bell_state[k], 4, 2);

                if ((bell_state[i][3] == '+' && bell_state[j][0] == '+' && bell_state[k][0] == '+') || (bell_state[i][3] == '-' && bell_state[j][0] == '-' && bell_state[k][0] == '+') || (bell_state[i][3] == '+' && bell_state[j][0] == '-' && bell_state[k][0] == '-') || (bell_state[i][3] == '-' && bell_state[j][0] == '+' && bell_state[k][0] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 4, 2);
                temp.append(bell_state[j], 1, 2);
                temp.append(bell_state[k], 1, 2);

                if ((bell_state[i][3] == '+' && bell_state[j][0] == '+' && bell_state[k][3] == '+') || (bell_state[i][3] == '-' && bell_state[j][0] == '-' && bell_state[k][3] == '+') || (bell_state[i][3] == '+' && bell_state[j][0] == '-' && bell_state[k][3] == '-') || (bell_state[i][3] == '-' && bell_state[j][0] == '+' && bell_state[k][3] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 4, 2);
                temp.append(bell_state[j], 1, 2);
                temp.append(bell_state[k], 4, 2);

                if ((bell_state[i][3] == '+' && bell_state[j][3] == '+' && bell_state[k][0] == '+') || (bell_state[i][3] == '-' && bell_state[j][3] == '-' && bell_state[k][0] == '+') || (bell_state[i][3] == '+' && bell_state[j][3] == '-' && bell_state[k][0] == '-') || (bell_state[i][3] == '-' && bell_state[j][3] == '+' && bell_state[k][0] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 4, 2);
                temp.append(bell_state[j], 4, 2);
                temp.append(bell_state[k], 1, 2);

                if ((bell_state[i][3] == '+' && bell_state[j][3] == '+' && bell_state[k][3] == '+') || (bell_state[i][3] == '-' && bell_state[j][3] == '-' && bell_state[k][3] == '+') || (bell_state[i][3] == '+' && bell_state[j][3] == '-' && bell_state[k][3] == '-') || (bell_state[i][3] == '-' && bell_state[j][3] == '+' && bell_state[k][3] == '-'))
                {
                    temp.push_back('+');
                }
                else
                {
                    temp.push_back('-');
                }
                temp.append(bell_state[i], 4, 2);
                temp.append(bell_state[j], 4, 2);
                temp.append(bell_state[k], 4, 2);

                //cout << bell_state[i] << " * " << bell_state[j] << " * " << bell_state[k] << " = " << temp << endl;
                output.push_back(temp);
                swap_output.push_back(temp);
                temp.clear();
            }
        }
    }
    //output_print();
    //----------------------------swap
    for (int i = 0; i < output.size(); i++)
    {
        for (int j = 1; j < output[i].size(); j += 7)
        {
            swap_output[i][j] = output[i][j + swap_state[0] - 1];
            swap_output[i][j + 1] = output[i][j + swap_state[1] - 1];
            swap_output[i][j + 2] = output[i][j + swap_state[2] - 1];
            swap_output[i][j + 3] = output[i][j + swap_state[3] - 1];
            swap_output[i][j + 4] = output[i][j + swap_state[4] - 1];
            swap_output[i][j + 5] = output[i][j + swap_state[5] - 1];
        }
    }
    //output_print();

    //---------------------用GHZ state測量 G1,G2,G3,G4,G5,G6,G7,G8
    /*
    000 = + G1 + G2
    001 = + G3 + G4
    010 = + G5 + G6
    011 = + G7 + G8
    100 = + G7 - G8
    101 = + G5 - G6
    110 = + G3 - G4
    111 = + G1 - G2
    */
    string temp2;
    for (int i = 0; i < swap_output.size(); i++)
    {
        for (int j = 0; j < swap_output[i].size(); j++)
        {
            if ((j % 7) == 0) //+ or -
            {
                temp2.push_back(swap_output[i][j]);
            }
            if ((j % 7) == 1 || (j % 7) == 4)
            {
                if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '0' && swap_output[i][j + 2] == '0')
                {
                    temp2.append("(+G1+G2)");
                }
                else if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '0' && swap_output[i][j + 2] == '1')
                {
                    temp2.append("(+G3+G4)");
                }
                else if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '1' && swap_output[i][j + 2] == '0')
                {
                    temp2.append("(+G5+G6)");
                }
                else if (swap_output[i][j] == '0' && swap_output[i][j + 1] == '1' && swap_output[i][j + 2] == '1')
                {
                    temp2.append("(+G7+G8)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '0' && swap_output[i][j + 2] == '0')
                {
                    temp2.append("(+G7-G8)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '0' && swap_output[i][j + 2] == '1')
                {
                    temp2.append("(+G5-G6)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '1' && swap_output[i][j + 2] == '0')
                {
                    temp2.append("(+G3-G4)");
                }
                else if (swap_output[i][j] == '1' && swap_output[i][j + 1] == '1' && swap_output[i][j + 2] == '1')
                {
                    temp2.append("(+G1-G2)");
                }
            }
        }
        output2.push_back(temp2);
        temp2.clear();
    }
    //output_print();

    for (int i = 0; i < output2.size(); i++)
    {
        expand(output2[i]);
    }
    //output_print();
    //csv_output_ghzstate();
    csv_output_ghzstate_table();
    return 0;
}
void output_print()
{
    //----------------output---------------
    int w = 0;
    for (int i = 0; i < 4; i++)
    {

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                cout << "--------------------------------------------------------" << endl;
                cout << bell_state[i] << " * " << bell_state[j] << " * " << bell_state[k] << endl;
                cout << " = " << output[w] << endl;
                cout << " = " << swap_output[w] << endl;
                cout << " = " << output2[w] << endl;
                cout << " = " << expand_output[w] << endl;
                cout << "--------------------------------------------------------" << endl;

                w++;
            }
        }
    }
}
void expand(string s)
{
    string tmp;
    string epd;  //expand
    string fepd; //final_expand
    char sign;
    for (int i = 0; i < s.size(); i += 17)
    {

        sign = s[i];

        if ((s[i + 2] == '+' && s[i + 10] == '+') || (s[i + 2] == '-' && s[i + 10] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.append(s, i + 3, 2);
        tmp.append(s, i + 11, 2);
        if ((s[i + 2] == '+' && s[i + 13] == '+') || (s[i + 2] == '-' && s[i + 13] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.append(s, i + 3, 2);
        tmp.append(s, i + 14, 2);
        if ((s[i + 5] == '+' && s[i + 10] == '+') || (s[i + 5] == '-' && s[i + 10] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.append(s, i + 6, 2);
        tmp.append(s, i + 11, 2);
        if ((s[i + 5] == '+' && s[i + 13] == '+') || (s[i + 5] == '-' && s[i + 13] == '-'))
        {
            tmp.push_back('+');
        }
        else
        {
            tmp.push_back('-');
        }
        tmp.append(s, i + 6, 2);
        tmp.append(s, i + 14, 2);

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
    //cout << epd << endl;

    int subpos;
    char sign2;
    for (int i = 0; i < epd.size() / 2; i += 5)
    {
        sign = epd[i];
        subpos = epd.find(epd.substr(i + 1, 4), i + 5);
        sign2 = epd[subpos - 1];
        if (sign == sign2)
        {
            fepd += sign;
            fepd.append(epd, i + 1, 4);
        }
    }
    //cout << fepd << endl;
    expand_output.push_back(fepd);
}
void csv_output_ghzstate()
{
    ofstream myFile;
    myFile.open(output_csv);
    int w = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                switch (i)
                {
                case 0:
                    myFile << "ф+";
                    break;
                case 1:
                    myFile << "ф-";
                    break;
                case 2:
                    myFile << "ψ+";
                    break;
                case 3:
                    myFile << "ψ-";
                    break;
                default:
                    break;
                }
                myFile << "⊗";
                switch (j)
                {
                case 0:
                    myFile << "ф+";
                    break;
                case 1:
                    myFile << "ф-";
                    break;
                case 2:
                    myFile << "ψ+";
                    break;
                case 3:
                    myFile << "ψ-";
                    break;
                default:
                    break;
                }
                myFile << "⊗";
                switch (k)
                {
                case 0:
                    myFile << "ф+";
                    break;
                case 1:
                    myFile << "ф-";
                    break;
                case 2:
                    myFile << "ψ+";
                    break;
                case 3:
                    myFile << "ψ-";
                    break;
                default:
                    break;
                }
                myFile << ",\'" << expand_output[w] << endl;

                w++;
            }
        }
    }
}
void csv_output_ghzstate_table()
{
    ofstream myFile;
    myFile.open(outputtable__csv);
    //myFile << ",ф+,ф-,ψ+,ψ-" << endl;
    for (int i = 0; i < expand_output.size(); i += expand_output.size() / 4)
    {
        myFile << ",ф+,ф-,ψ+,ψ-" << endl;

        for (int j = 0; j < expand_output.size() / 4; j++)
        {
            if ((j % 4) == 0)
            {
                switch (i)
                {
                case 0:
                    myFile << "ф+";
                    break;
                case 16:
                    myFile << "ф-";
                    break;
                case 32:
                    myFile << "ψ+";
                    break;
                case 48:
                    myFile << "ψ-";
                    break;
                default:
                    break;
                }
            }
            switch (j)
            {
            case 0:
                myFile << "ф+,";
                break;
            case 4:
                myFile << "ф-,";
                break;
            case 8:
                myFile << "ψ+,";
                break;
            case 12:
                myFile << "ψ-,";
                break;
            default:
                break;
            }
            myFile << "\'" << expand_output[i + j];
            if ((j % 4) == 3)
            {
                myFile << endl;
            }
            else
            {
                myFile << ",";
            }
        }
        myFile << endl;
    }
}