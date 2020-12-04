#include <bits/stdc++.h>

using namespace std;

int MIN = 16777216; //256*256*256

int gene[4][9];
int tmp[4][9];
double pro[4];                     //輪盤法 各基因的機率
int global_best_gene[1][10];       //全域最佳解基因 & fitness &在第幾代找到
void initial();                    //產生初始解
void fitness();                    //計算適應值
int f(int num);                    //適應值函數
void selection();                  //選擇 (輪盤法)
void crossover();                  //交配 (單點交配&固定分割點 0123|4567)
void mutation();                   //突變
void print_fitness(int gene[][9]); //印出適應值
void gbgene(int gne);              //全域最好的基因

int main()
{
    cout << "=====Initial=====" << endl;
    initial();
    global_best_gene[0][8] = MIN;
    for (int i = 0; i < 30; i++)
    {
        cout << "================" << i + 1 << endl;
        cout << "=====Fitness=====" << endl;
        fitness();
        cout << "=====Selection===" << endl;
        selection();
        cout << "=====Crossover===" << endl;
        crossover();
        cout << "=====Mutation====" << endl;
        mutation();
        gbgene(i);
    }
    cout << endl;
    cout << "Global best gene_Generation: " << global_best_gene[0][9] + 1 << endl;
    cout << "Global best gene: ";
    for (int j = 0; j < 9; j++)
    {
        if (j == 8)
        {
            cout << " fitness: " << global_best_gene[0][j];
        }
        else
        {
            cout << global_best_gene[0][j];
        }
    }
    cout << endl;
    return 0;
}
void initial()
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gene[i][j] = rand() % 2;
        }
    }
}
void fitness()
{
    for (int i = 0; i < 4; i++)
    {
        int temp = 0;
        for (int j = 0; j < 8; j++)
        {
            temp += gene[i][j] * pow(2, 7 - j);
        }
        gene[i][8] = f(temp);
    }
    print_fitness(gene);
}
int f(int num)
{
    return (num - 3) * (num - 5) * (num + 2);
}
void selection() //適應值為0該怎麼處理?
{
    double totalsum = 0;   //所有適應值的和
    double partialSum = 0; //目前加總的機率
    int selone_index = 0;
    int seltwo_index = 0;

    double r_one = (double)rand() / RAND_MAX;
    double r_two;
    for (int i = 0; i < 4; i++)
    {
        if (gene[i][8] == 0)
        {
            totalsum += ((double)1 / 1);
        }
        else 
        {
            totalsum += ((double)1 / abs(gene[i][8]));
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (gene[i][8] == 0)
        {
            pro[i] = ((double)1 / 1) / totalsum;
        }
        else 
        {
            pro[i] = ((double)1 / abs(gene[i][8])) / totalsum;
        }
        
        //cout << pro[i] << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        partialSum += pro[i];
        if (r_one <= partialSum)
        {
            selone_index = i;
            break;
        }
    }
    //cout << selone_index << endl;
    seltwo_index = selone_index;
    while (selone_index == seltwo_index)
    {
        r_two = (double)rand() / RAND_MAX;
        //cout << r_two;
        partialSum = 0;

        for (int i = 0; i < 4; i++)
        {
            partialSum += pro[i];
            if (r_two <= partialSum)
            {
                seltwo_index = i;
                //cout << seltwo_index << endl;

                break;
            }
        }
    }
    //cout << selone_index << " " << seltwo_index << endl;
    for (int j = 0; j < 9; j++)
    {
        tmp[0][j] = gene[selone_index][j];
        tmp[1][j] = gene[seltwo_index][j];
    }
    for (int i = 0; i < 2; i++)
    {
        cout << "gene: ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
            {
                cout << " fitness: " << tmp[i][j];
            }
            else
            {
                cout << tmp[i][j];
            }
        }
        cout << endl;
    }
}
void crossover()
{
    //int cut = rand() % 8;
    //cout << cut << endl;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (j < 4)
            {
                tmp[2][j] = tmp[0][j];
                tmp[3][j] = tmp[1][j];
            }
            else
            {
                tmp[2][j] = tmp[1][j];
                tmp[3][j] = tmp[0][j];
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            gene[i][j] = tmp[i][j];
        }
    }
    fitness();
}
void mutation()
{
    for (int i = 2; i < 4; i++)
    {
        int j = rand() % 8;
        gene[i][j] = !gene[i][j];
    }
    fitness();
}
void print_fitness(int gene[][9])
{
    for (int i = 0; i < sizeof(gene); i++)
    {
        cout << "gene: ";
        for (int j = 0; j < 9; j++)
        {
            if (j == 8)
            {
                cout << " fitness: " << gene[i][j];
            }
            else
            {
                cout << gene[i][j];
            }
        }
        cout << endl;
    }
}
void gbgene(int gne)
{
    int min = MIN;
    int min_index;

    for (int i = 0; i < 4; i++)
    {
        if (min > gene[i][8])
        {
            min = gene[i][8];
            min_index = i;
        }
    }

    if (global_best_gene[0][8] > min)
    {
        global_best_gene[0][9] = gne;
        for (int j = 0; j < 9; j++)
        {
            global_best_gene[0][j] = gene[min_index][j];
        }
    }
}
