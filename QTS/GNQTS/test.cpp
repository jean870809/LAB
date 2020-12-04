#include <bits/stdc++.h>
using namespace std;

int main()
{
    string input_csv;
    string output_csv;
    for (int y = 2010; y <= 2019; y++)
    {
        for (int m = 1; m <= 12; m++)
        {
            string input_name = "D:/LAB/c++/QTS/DJI_30/M2M/train_";
            string input_format = " Q1).csv";
            stringstream ss_input;
            ss_input << input_name << y << "_" << setw(2) << setfill('0') << m << "(" << y << input_format;
            input_csv = ss_input.str();

            string output_name = "train_result/train_";
            string output_format = " Q1)_result.csv";
            stringstream ss_output;
            ss_output << output_name << y << "_" << setw(2) << setfill('0') << m <<"(" << y << output_format;
            output_csv = ss_output.str();

            cout << input_csv << endl;
            cout << output_csv <<endl;
        }
    }
    return 0;
}