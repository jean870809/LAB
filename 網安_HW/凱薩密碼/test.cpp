#include <bits/stdc++.h>

using namespace std;

int main(){
    char c = 'Y';
    int key = 2;
    c = ((c-'A')+key)%26 + 'A';
    

    cout << c;

    c = ((c-'A')+(26-key))%26 + 'A';
    cout << c;
    return 0;
}