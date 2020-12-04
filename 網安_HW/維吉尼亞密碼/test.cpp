#include <bits/stdc++.h>

using namespace std;

int main()
{
    //char s[] = "Hello    Nice, to meet  ,* you";
    char s[100];
    //char k[100];
    string k;
    //cin >> s;
    cin.getline(s,100);
    int i = 0;
    while (s[i] !='\0')
    {
        cout << s[i];
        i++;
    }
    cout << endl;
    /*
    ** 用 空格，星號，逗號進行分割 
    ** 無論多少個，都會被當作一個key
    */
    const char *d = "  *,.;"; //分割依據
    char *p;                //儲存每次分割結果
    p = strtok(s, d);
    
    while (p)
    {
        
        for (int j = 0; j < strlen(p); j++)
        {
            if(isdigit(p[j])){
                k.push_back(atoi(p)-1+'A');
                break;
            }else
            {
                k.push_back(p[j]);
                
            }
        }
        p = strtok(NULL, d);
    }
    for (int i = 0; i< k.length(); i++)
    {
        cout << k[i] ;
    }
    
    
    return 0;
}
