#include "noise/Noise.h"
#include <iostream>
using namespace std;

int main(){
    gn::Noise n;

    double a[10][10] = {0};

    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            a[i][j] = n.noise(i * 0.25, j * 0.5, 0.0f);
        }
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}