#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

#define N 30 //選幾檔計算

void _csvprice(string s); //讀取股價
void _csvname(string s);  //讀取公司名
struct stock
{
    string name;          //公司名
    vector<double> price; //股價
};
stock dji[N];
string input_csv = "train_2019_06(2019 Q1).csv";
string output_csv = "funding_" + input_csv;
int main()
{
    //=================讀取
    ifstream inFile(input_csv, ios::in);
    if (!inFile)
    {
        cout << "FAIL！" << endl;
    }
    string line;
    int n = 0;
    while (getline(inFile, line))
    {
        if (n == 0)
        {
            _csvname(line);
            //name.push_back(a);
            n++;
        }
        else
        {
            _csvprice(line);
            //data.push_back(a);
            n++;
        }
    }
    //===============
    //=============== 計算
    double allmoney = 10000000;     //初始資金
    int distrimoney = allmoney / N; //各檔分配資金
    vector<int> stock;              //可買股數
    for (int i = 0; i < N; i++)
    {
        stock.push_back(distrimoney / (dji[i].price[0]));
    }
    double remainmoney = 0; //剩餘資金
    for (int i = 0; i < N; i++)
    {
        remainmoney += distrimoney - stock[i] * (dji[i].price[0]);
    }
    remainmoney += (allmoney - distrimoney * N);
    vector<double> funding;        //資金水位
    int day = dji[0].price.size(); //天數

    for (int i = 0; i < day; i++) //day
    {
        double temp = 0;
        for (int j = 0; j < N; j++) //幾檔
        {

            temp += stock[j] * dji[j].price[i];
        }
        funding.push_back(remainmoney + temp);
    }

    //===== 算2次趨勢線係數 a、b  Y = ax^2+bx+c
    MatrixXd Y(day, 1); //Y[y-c]
    for (int i = 0; i < day; i++)
    {
        Y(i, 0) = funding[i] - allmoney;
    }

    MatrixXd A(day, 2); //A[x^2,x]
    for (int i = 0; i < day; i++)
    {
        A(i, 0) = (i + 1) * (i + 1);
        A(i, 1) = i + 1;
    }
    MatrixXd AT(2, day); //Transpose A
    AT = A.transpose().eval();

    MatrixXd theta(2, 1);
    theta = (((AT * A).inverse()) * AT * Y).eval();

    //二次回歸方程式 Y=ax^2+bx+c
    double a = theta(0, 0);
    double b = theta(1, 0);

    cout << fixed << setprecision(20) << a << endl;
    cout << fixed << setprecision(20) << b << endl;
    cout << "f(x) = " << a << "x*x + " << b << "x + " << allmoney << endl;

    //==============write
    ofstream myFile;
    myFile.open(output_csv);

    for (int i = 0; i < funding.size(); i++)
    {
        myFile << fixed << setprecision(10) << funding[i] << endl;
    }
    myFile << fixed << setprecision(10) << "Y = " << a << "x*x + " << b << "x + " << allmoney << endl;
    myFile << fixed << setprecision(10) << "a = " << a << endl;
    myFile << fixed << setprecision(10) << "b = " << b << endl;

    return 0;
}
void _csvprice(string s)
{
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            dji[i].price.push_back(atof(token.c_str()));
            i++;
        }
    }
}

void _csvname(string s)
{
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            dji[i].name = token;
            i++;
        }
    }
}
