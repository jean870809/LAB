#include <bits/stdc++.h>

using namespace std;
vector<double> _csv(string s);       //讀取股價
vector<string> _csvstring(string s); //讀取檔名
double fundings(vector<int> num);

vector<vector<string>> name;       //股票名
vector<vector<double>> data;       //全部資料
vector<vector<double>> tempdata;   //所選資料
vector<vector<int>> rank_solution; //解集合

double allmoney = 10000000; //初始資金
int N = 30;                 //選幾檔計算

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
            vector<string> b = _csvstring(line);
            name.push_back(b);
            n++;
        }
        else
        {
            vector<double> c = _csv(line);
            data.push_back(c);
            n++;
        }
        //========================
    }
    int length = data[0].size(); //有幾檔

    //==========rank
    for (int i = 0; i < length; i++)
    {
        vector<int> temp(length, 0);
        for (int j = 0; j < length; j++)
        {
            if (i == j)
            {
                temp[j] = 1;
            }
        }
        rank_solution.push_back(temp);
        temp.clear();
    }
    /*for (int i = 0; i < rank_solution.size(); i++)
    {
        for (int j = 0; j < rank_solution[0].size(); j++)
        {
            cout << rank_solution[i][j] << " ";
        }
        cout << endl;
    }
    vector<double> trend;
    for (int i = 0; i < rank_solution.size(); i++)
    {
        trend.push_back(fundings(rank_solution[i]));
    }*/

    //sort(trend.begin(), trend.end());
    vector<int> temp_sol;
    string temp_name;
    for (int i = 0; i < length; i++)
    {
        for (int j = i + 1; j < length; j++)
        {
            if (fundings(rank_solution[i]) < fundings(rank_solution[j]))
            {
                temp_sol = rank_solution[i];
                rank_solution[i] = rank_solution[j];
                rank_solution[j] = temp_sol;

                temp_name = name[0][i];
                name[0][i] = name[0][j];
                name[0][j] = temp_name;
            }
        }
    }

    ofstream File;
    File.open("rank.csv");
    for (int i = 0; i < length; i++)
    {
        File << "Rank" << i + 1 << "," << name[0][i];
        File << fixed << setprecision(10) << ",趨勢值," << fundings(rank_solution[i]) << endl;
    }

    cout << endl;
    return 0;
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
    if (n == 0)
    {
        return 0;
    }
    else
    {
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
        double m = 0;     //每日預期報酬
        double risk = 0;  // 每日風險
        double trend = 0; // 趨勢值
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
        if (m < 0)
        {
            trend = m * risk;
        }
        else
        {
            trend = m / risk;
        }

        tempdata.clear();
        stock.clear();
        funding.clear();
        return trend;
    }
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