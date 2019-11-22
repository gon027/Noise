#include <iostream>
#include "Noise.h"
using namespace gn;
using namespace std;

int main(){
    Noise noise;

    for(int x = 0; x < 10; x += 1){
        for(int y = 0; y < 10; y += 1){
            for(int z = 0; z < 10; z += 1){
                cout << noise.octaveNoise(x / 100.0L, y / 100.0L, z / 100.0L, 5, 0.5L) * 0.5 + 0.5L << endl;
            }
        }
    }
}