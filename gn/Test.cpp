#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Noise.h"
using namespace std;

int main(){
    FILE* file;
    file = fopen("/Users/kumeitakashi/Desktop/test.csv", "w");

    float a = 0;

    srand((unsigned int)time(NULL));
    gn::Noise noise(rand());

    // noise.debugPrint();

    for(int i = 0; i < 15; ++i){
        for (int j = 0; j < 15; ++j){
            for (int k = 0; k < 15; ++k){
                a = (noise.noise(i / 100.0f, j / 100.0f, k / 100.0f) * 0.5 + 0.5 ) * 255;
                //a = (noise.octaveNoise(i / 100.0f, j / 100.0f, k / 100.0f, 3, 0.25f) * 0.5 + 0.5) * 255;

                // cout << a << endl;

                fprintf(file, "%f\n", a);
            }
        }
    }

    fclose(file);
}