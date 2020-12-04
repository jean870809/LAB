#include <bits/stdc++.h>
#include <vector>

using namespace std;

vector<double> _csv(string s);       //讀取股價
vector<string> _csvstring(string s); //讀取檔名
double fundings(vector<int> num);    //適應函數 //計算趨勢值
void print(int flag);

int N = 10;
double allmoney = 10000000;      //初始資金
vector<string> name;             //股票名
vector<vector<double>> data;     //全部資料
vector<vector<double>> tempdata; //所選資料
vector<vector<string>> answer;   //窮舉的解

int main()
{
    //=================讀取
    ifstream inFile("train_2019_06(2019 Q1).csv", ios::in);
    if (!inFile)
    {
        cout << "開啟檔案失敗！" << endl;
    }
    string line;
    int n = 0;
    while (getline(inFile, line))
    {
        //========================
        if (n == 0)
        {
            name = _csvstring(line);
            n++;
        }
        else
        {
            vector<double> a = _csv(line);
            data.push_back(a);
            n++;
        }
        //========================
    }

    //===========窮取解集合
    int flag = 0;
    while (flag < pow(2, N))
    { //加上空集一共有2^n个集合
        print(flag);
        flag++;
    }
    /*cout << "Subset nums = " << flag << endl;
    for (int i = 0; i < answer.size(); i++)
    {
        for (int j = 0; j < answer[i].size(); j++)
        {
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }*/

    //=============計算所有解的趨勢值
    vector<int> temp(N, 0);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < answer[1].size(); j++)
        {
            if (name[i] == answer[1][j])
            {
                temp[i] = 1;
            }
        }
    }
    for(int i = 0; i < answer[1].size(); i++){
        cout << answer[1][i] << " ";
    }
    cout << endl;

    for(int i =0; i < temp.size(); i++){
        cout << temp[i] << " ";
    }
    cout << endl;

    return 0;
}

void print(int flag) //采用二进制方法输出集合元素
{
    int temp = flag;
    vector<string> b;
    for (int i = 0; i < N; i++)
    {
        if (temp & 1 >= 1)
        {
            b.push_back(name[i]);
        }
        temp >>= 1;
    }
    answer.push_back(b);
}

vector<double> _csv(string s)
{
    vector<double> arr;
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            arr.push_back(atof(token.c_str()));
            i++;
        }
    }

    return arr;
}

vector<string> _csvstring(string s)
{
    vector<string> arr;
    istringstream delim(s);
    string token;
    int i = 0;
    while (getline(delim, token, ','))
    {
        if (i < N)
        {
            arr.push_back(token);
            i++;
        }
    }

    return arr;
}

double fundings(vector<int> num)
{
    int n = 0; //檔數
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == 1)
        {
            n++;
            vector<double> a;
            for (int j = 0; j < data.size(); j++)
            {
                a.push_back(data[j][i]);
            }
            tempdata.push_back(a);
            a.clear();
        }
    }
    int distrimoney = allmoney / n; //各檔分配資金
    vector<int> stock;              //可買股數
    for (int i = 0; i < n; i++)
    {
        stock.push_back(distrimoney / (tempdata[i][0]));
    }
    double remainmoney = 0; //剩餘資金
    for (int i = 0; i < n; i++)
    {
        remainmoney += distrimoney - stock[i] * tempdata[i][0];
    }
    remainmoney += (allmoney - distrimoney * n);
    vector<double> funding; //資金水位

    for (int i = 0; i < tempdata[0].size(); i++) //day
    {
        double temp = 0;
        for (int j = 0; j < n; j++) //幾檔
        {

            temp += stock[j] * tempdata[j][i]; //每日資金水位
        }
        funding.push_back(remainmoney + temp);
    }

    // 趨勢值
    double m;     //每日預期報酬
    double risk;  // 每日風險
    double trend; // 趨勢值
    double temp1 = 0, temp2 = 0;
    for (int i = 0; i < tempdata[0].size(); i++)
    {
        temp1 += (i + 1) * funding[i] - (i + 1) * allmoney;
        temp2 += (i + 1) * (i + 1);
    }
    m = temp1 / temp2;
    double temp = 0;
    for (int i = 0; i < tempdata[0].size(); i++)
    {
        temp += (funding[i] - (m * (i + 1) + allmoney)) * (funding[i] - (m * (i + 1) + allmoney));
    }
    risk = sqrt(temp / (tempdata[0].size()));
    trend = m / risk;

    tempdata.clear();
    stock.clear();
    funding.clear();
    return trend;
}