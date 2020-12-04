#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <math.h>
using namespace std;
vector<double> _csv(string s);
int main()
{

    vector<vector<double>> data;

    //=================讀取
    ifstream inFile("train_2019_06(2019 Q1).csv", ios::in);
    if (!inFile)
    {
        cout << "開啟檔案失敗！" << endl;
    }
    string line;
    while (getline(inFile, line))
    {
        //========================
        vector<double> a = _csv(line);
        data.push_back(a);
        //========================
    }

    //=============== 計算
    double allmoney = 10000000;     //初始資金
    int n = data[0].size();         //檔數
    int distrimoney = allmoney / n; //各檔分配資金
    vector<int> stock;              //可買股數
    for (int i = 0; i < n; i++)
    {
        stock.push_back(distrimoney / (data[1][i]));
    }
    double remainmoney = 0; //剩餘資金
    for (int i = 0; i < n; i++)
    {
        remainmoney += distrimoney - stock[i] * data[1][i];
    }
    remainmoney += (allmoney - distrimoney * n);
    vector<double> funding; //資金水位

    for (int i = 1; i < data.size(); i++) //day
    {
        double temp = 0;
        for (int j = 0; j < n; j++) //幾檔
        {

            temp += stock[j] * data[i][j];
        }
        funding.push_back(remainmoney + temp);
    }

    // 趨勢值
    double m;     //每日預期報酬
    double risk;  // 每日風險
    double trend; // 趨勢值
    double temp1 = 0, temp2 = 0;
    for (int i = 1; i < data.size(); i++)
    {
        temp1 += i * funding[i - 1] - i * allmoney;
        temp2 += i * i;
    }
    m = temp1 / temp2;
    double temp = 0;
    for (int i = 1; i < data.size(); i++)
    {
        temp += (funding[i - 1] - (m * i + allmoney)) * (funding[i - 1] - (m * i + allmoney));
    }
    risk = sqrt(temp / (data.size() - 1));
    trend = m / risk;
    //==============write
    ofstream myFile;
    myFile.open("30funding.csv");

    for (int i = 0; i < funding.size(); i++)
    {
        myFile << fixed << setprecision(10) << funding[i] << endl;
    }
    myFile << fixed << setprecision(10) << "Y = " << m << "X + " << allmoney << endl;
    myFile << fixed << setprecision(10) << "m = " << m << endl;
    myFile << fixed << setprecision(10) << "daily risk = " << risk << endl;
    myFile << fixed << setprecision(10) << "trend = " << trend << endl;

    return 0;
}

vector<double> _csv(string s)
{
    vector<double> arr;
    istringstream delim(s);
    string token;
    while (getline(delim, token, ','))
    {
        arr.push_back(atof(token.c_str()));
    }
    return arr;
}
