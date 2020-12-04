#include <bits/stdc++.h>

using namespace std;

#define dim 1
#define upper 100
#define lower -100
#define population 5

float w = 0.5;
float c1 = 1;
float c2 = 1.2;

float particle[population][dim];
float particleV[population][dim] = {0};
float fitness[population] = {0};
float gbest, gbest_p[dim];
float pbest[population] = {0}, pbest_p[population][dim];
void initial();
void fit();
void move();
int main()
{
    initial();
    for (int i = 0; i < 350; i++)
    {
        cout << "====iteration" << i + 2 << "=====" << endl;
        fit();
        move();
    }
}
void initial()
{
    int length = upper - lower;
    for (int i = 0; i < population; i++)
    {
        for (int j = 0; j < dim; j++)
        {
            particle[i][j] = ((float)rand() / RAND_MAX) * length + lower;
            cout << particle[i][j] << ",";
        }
        pbest[i] = 10000;
        cout << endl;
    }
    gbest = 10000;
}
void fit()
{
    cout << "fitness" << endl;

    for (int i = 0; i < population; i++)
    {
        fitness[i] = 0;
        for (int j = 0; j < dim; j++)
        {
            fitness[i] += fabs(particle[i][j]);
        }
        cout << fitness[i] << endl;
        if (fitness[i] < pbest[i])
        {
            pbest[i] = fitness[i];
            for (int j = 0; j < dim; j++)
            {
                pbest_p[i][j] = particle[i][j];
            }
            cout << "===pbest===" << i << ":";
            cout << fitness[i] << endl;
        }
        if (pbest[i] < gbest)
        {
            gbest = pbest[i];
            cout << "===gbest===" << gbest << endl;
            for (int j = 0; j < dim; j++)
            {
                gbest_p[j] = pbest_p[i][j];
            }
        }
    }
}
void move()
{
    float r1 = 0, r2 = 0;
    for (int i = 0; i < population; i++)
    {
        cout << "pop: " << i << ": ";
        for (int j = 0; j < dim; j++)
        {
            r1 = rand() / RAND_MAX;
            r2 = rand() / RAND_MAX;

            particleV[i][j] = w * particleV[i][j] + c1 * (pbest_p[i][j] - particle[i][j]) + c2 * (gbest_p[j] - particle[i][j]);
            cout << particleV[i][j] << "; ";
            particle[i][j] = particle[i][j] + particleV[i][j];
            cout << particle[i][j] << ",";
        }
        cout << endl;
    }
}