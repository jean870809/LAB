#include <bits/stdc++.h>

using namespace std;
#define MAX_W 275                               //背包限重
#define P_SIZE 8                                //族群規模
#define CHROME_SIZE 100                         //染色體數量
#define p_crossover 0.8                         //交配率
#define p_mutation 0.2                          //突變率
#define EXP_TIME 50                             //實驗次數
#define GEN_TIME 1000                           //迭代次數
int w[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};      //10種物品重量
int p[] = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; //10種物品價值

struct population
{
    int gene[100];
    int weight;
    int profit;
};

population pop[8], temp[8], global_best;
int Gbest_gne;             //最佳解世代
int sumweight(int gene[]); //計算重量
int sumprofit(int gene[]); //計算價值
void initialpop();         //初始化population
void selection();          //選擇 (菁英法)
void crossover();          //交配 (均勻交配)
void mutation();           //突變
void gbgene(int gne);
void fixgene(int i, population p[]);
void printpop(); //print
bool comparegene(population p1, population p2)
{
    if (p1.profit > p2.profit)
    {
        return true;
    }
    return false;
}
int main()
{
    //cout << "=========Initial========" << endl;

    //printpop();
    //srand(time(NULL));
    //srand(114);
    double EXGB_all_profit = 0;     //實驗GB全部的profit加總
    double EXGB_all_generation = 0; //實驗GB全部找到世代加總

    for (int e = 0; e < EXP_TIME; e++) //實驗50次
    {
        cout << "=========Experiment" << e + 1 << "====" << endl;

        initialpop();
        global_best.profit = 0;
        for (int i = 0; i < 1000; i++) //1000代
        {
            //cout << "=========Generation" << i + 1 << "====" << endl;
            selection();
            //cout << "=========Crossover========" << endl;
            crossover();
            //printpop();

            //cout << "=========Mutation========" << endl;
            mutation();
            //printpop();

            gbgene(i);
            //cout << "Generation Global best profit: " << global_best.profit << endl;
        }
        cout << "Global best gene_Generation: " << Gbest_gne << endl;

        cout << "Global best gene: " << endl;

        char c;
        for (int j = 0; j < CHROME_SIZE; j += 10)
        {
            int num = 0;
            for (int k = 0; k < 10; k++)
            {
                if (global_best.gene[j + k] == 1)
                {
                    num++;
                }
            }
            c = 'A' + (j / 10);
            cout << c << ":" << num << " ";
        }
        cout << endl;
        cout << "Global best profit: " << global_best.profit << endl;
        cout << "Global best weight: " << global_best.weight << endl;
        EXGB_all_generation += Gbest_gne;
        EXGB_all_profit += global_best.profit;
    }
    cout << endl;
    cout << fixed << setprecision(5) << "Exp average GB profit" << EXGB_all_profit / EXP_TIME << endl;
    cout << fixed << setprecision(5) << "Exp average GB generation" << EXGB_all_generation / EXP_TIME << endl;
}
void printpop()
{
    char c;
    for (int i = 0; i < P_SIZE; i++)
    {
        cout << "Gene" << i + 1 << ": " << endl;
        for (int j = 0; j < CHROME_SIZE; j += 10)
        {
            int num = 0;
            for (int k = 0; k < 10; k++)
            {
                if (pop[i].gene[j + k] == 1)
                {
                    num++;
                }
            }
            c = 'A' + (j / 10);
            cout << c << ":" << num << " ";
            /*if ((j % 10) == 0)
            {
                cout << endl;
                c = 'A' + (j / 10);
                cout << c << ": ";
            }
            cout << pop[i].gene[j] << " ";*/
        }
        cout << endl;
        cout << "weight: " << pop[i].weight << endl;
        cout << "profit: " << pop[i].profit << endl;
    }
}
int sumweight(int gene[])
{
    int sumw = 0;
    for (int i = 0; i < CHROME_SIZE; i++)
    {
        sumw += gene[i] * w[(i / 10)];
    }
    return sumw;
}
int sumprofit(int gene[])
{
    int sumw = 0;
    for (int i = 0; i < CHROME_SIZE; i++)
    {
        sumw += gene[i] * p[(i / 10)];
    }
    return sumw;
}
void initialpop()
{
    int tempweight = 0;
    bool isPop = false; //確認解是否符合背包限制
    int r = 0;
    for (int i = 0; i < P_SIZE; i++)
    {
        while (!isPop)
        {
            for (int j = 0; j < CHROME_SIZE; j++)
            {
                pop[i].gene[j] = rand() % 2;
            }

            //cout << "Fix" << i + 1 << endl;
            fixgene(i, pop);

            pop[i].weight = sumweight(pop[i].gene);
            pop[i].profit = sumprofit(pop[i].gene);

            isPop = true;
        }
        isPop = false;
    }
}

void selection()
{
    //cout << "=========Sorting========" << endl;
    sort(pop, pop + P_SIZE, comparegene);
    //printpop();
    for (int i = 0; i < 4; i++)
    {
        temp[i] = pop[i];
    }
}
void crossover()
{
    //int cut1 = rand() % 100; //切割點1
    //int cut2 = rand() % 100; //切割點2
    int mask[CHROME_SIZE];
    for (int i = 0; i < CHROME_SIZE; i++)
    {
        mask[i] = rand() % 2;
    }

    int choose1, choose2; //選誰交配
    for (int i = 4; i < P_SIZE; i += 2)
    {

        choose1 = rand() % 4;
        choose2 = rand() % 4;
        while (choose1 == choose2)
        {
            choose2 = rand() % 4;
        }
        //cout << "Choose: " << choose1 << " " << choose2 << endl;
        for (int j = 0; j < CHROME_SIZE; j++)
        {
            /*if (j < cut1 || j > cut2)
            {
                temp[i].gene[j] = temp[choose1].gene[j];
                temp[i + 1].gene[j] = temp[choose2].gene[j];
            }
            else
            {
                temp[i].gene[j] = temp[choose2].gene[j];
                temp[i + 1].gene[j] = temp[choose1].gene[j];
            }*/

            if (mask[j] == 0)
            {
                temp[i].gene[j] = temp[choose1].gene[j];
                temp[i + 1].gene[j] = temp[choose2].gene[j];
            }
            else
            {
                temp[i].gene[j] = temp[choose2].gene[j];
                temp[i + 1].gene[j] = temp[choose1].gene[j];
            }
        }
        temp[i].weight = sumweight(temp[i].gene);
        temp[i].profit = sumprofit(temp[i].gene);
        temp[i + 1].weight = sumweight(temp[i + 1].gene);
        temp[i + 1].profit = sumprofit(temp[i + 1].gene);
    }

    for (int i = 4; i < P_SIZE; i++)
    {

        //cout << "Fix" << i + 1 << endl;
        fixgene(i, temp);

        pop[i] = temp[i];
    }
}
void mutation()
{
    for (int i = 4; i < P_SIZE; i++)
    {
        double r_mp = (double)rand() / RAND_MAX;
        if (r_mp < p_mutation)
        {
            int mutnum = rand() % 100;
            for (int j = 0; j < mutnum; j++)
            {
                int mutpos = rand() % 100;
                pop[i].gene[mutpos] = 1 - pop[i].gene[mutpos];
            }

            fixgene(i, pop);

            //pop[i].weight = sumweight(pop[i].gene);
            //pop[i].profit = sumprofit(pop[i].gene);
        }
    }
}
void fixgene(int i, population p[])
{
    int j = CHROME_SIZE;
    //cout << "Fix" << i + 1 << endl;
    while (sumweight(p[i].gene) > MAX_W && (j >= 0))
    {
        if (p[i].gene[j] == 1)
        {
            //cout << "Fixing" << j << endl;
            p[i].gene[j] = 0;
            //cout << sumweight(pop[i].gene) << endl;
        }

        j--;
    }
    j = 0;
    while (sumweight(p[i].gene) < MAX_W && (j < CHROME_SIZE))
    {

        if (p[i].gene[j] == 0)
        {
            //cout << "Fixing" << j << endl;
            if ((sumweight(p[i].gene) + w[(j / 10)]) <= 275)
            {
                p[i].gene[j] = 1;
            }
            //cout << sumweight(pop[i].gene) << endl;
        }
        j++;
    }
    p[i].weight = sumweight(p[i].gene);
    p[i].profit = sumprofit(p[i].gene);
}
void gbgene(int gne)
{
    sort(pop, pop + P_SIZE, comparegene);
    if (pop[0].profit > global_best.profit)
    {
        global_best = pop[0];
        Gbest_gne = gne;
    }
}
