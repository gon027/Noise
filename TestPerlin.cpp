#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include "Noise.h"
using namespace gn;
using namespace std;
/*
random_device rnd{};

uint32_t p[512];

//乱数の配列をランダムに生成
void makeArray(uint32_t seed){
    mt19937 mt(rnd());
    uniform_int_distribution<uint32_t> r(0, 255);

    for(int i = 0; i < 512; ++i){
        p[i] = r(mt);
    }
}

void printPerlin(){
    for(int i = 1; i < 512; ++i){
        printf("%3d ", p[i]);
        if(i % 16 == 0){
            cout << endl;
        }
    }
    cout << endl;
}

//フェード関数(6t^5 – 15t^4 + 10t^3)
inline double fade(double t){
    return t * t * t * (t * (t * 6 - 15) + 10);
}

//線形補完関数
inline double lerp(double t, double a, double b){
    return a + t * (b - a);
}

//勾配ベクトル
inline double grad(int hash, double x, double y, double z){
    // 15 == 0b1111
    int h = hash & 15;
    double u = h < 8 ? x : y;
    double v = h < 4 ? y : ( h == 12 || h == 14 ) ? x : z;

    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

//3次元ノイズ
double noise(double x, double y, double z){
    // [0 - 255]の領域にする
    int X = (int)floor( x ) & 255;
    int Y = (int)floor( y ) & 255;
    int Z = (int)floor( z ) & 255;

    x -= floor( x );
    y -= floor( y );
    z -= floor( z );

    double u = fade( x );
    double v = fade( y );
    double w = fade( z );

    //ハッシュを求める
    int A  = p[ X     ] + Y;
    int AA = p[ A     ] + Z;
    int AB = p[ A + 1 ] + Z;
    int B  = p[ X + 1 ] + Y;
    int BA = p[ B     ] + Z;
    int BB = p[ B + 1 ] + Z;

    int AAA = p[ AA     ];
    int AAB = p[ AB     ];
    int ABA = p[ BA     ];
    int ABB = p[ BB     ];
    int BAA = p[ AA + 1 ];
    int BAB = p[ AB + 1 ]; 
    int BBA = p[ BA + 1 ];
    int BBB = p[ BB + 1 ];

    // 8頂点から勾配ベクトルを求める
    double a = grad( AAA, x + 0, y + 0, z + 0 );
    double b = grad( ABA, x - 1, y + 0, z + 0 );
    double c = grad( AAB, x + 0, y - 1, z + 0 );
    double d = grad( ABB, x - 1, y - 1, z + 0 );
    double e = grad( BAA, x + 0, y + 0, z - 1 );
    double f = grad( BBA, x - 1, y + 0, z - 1 );
    double g = grad( BAB, x + 0, y - 1, z - 1 );
    double h = grad( BBB, x - 1, y - 1, z - 1 );

    //横方向の補間を計算
    double x1 = lerp( u, a, b );
    double x2 = lerp( u, c, d );
    double x3 = lerp( u, e, f );
    double x4 = lerp( u, g, h );

    //縦方向の補間を計算
    double y1 = lerp( v, x1, x2 );
    double y2 = lerp( v, x3, x4 );

    return lerp( w, y1, y2 );
}

//オクターブノイズ
double octaveNoise(double x, double y, double z, int octaves = 5, double persistence = 0.5L){
    double total { 0 };
    double frequency { 1 };
    double amplitude { 1 };
    double maxValue { 0 };
    
    for (int i = 0; i < octaves; ++i){
        total += noise(x * frequency, y * frequency, z * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maxValue;
}
*/


int main(){
    // makeArray(855);
    // //printPerlin();

    // for(int x = 0; x < 10; x += 1){
    //     for(int y = 0; y < 10; y += 1){
    //         for(int z = 0; z < 10; z += 1){
    //             cout << ( 0.5L * octaveNoise(x / 100.0L, y / 100.0L, z / 100.0L) + 0.5L ) << endl;
    //         }
    //     }
    // }

    Noise noise;

    for(int x = 0; x < 10; x += 1){
        for(int y = 0; y < 10; y += 1){
            for(int z = 0; z < 10; z += 1){
                cout << noise.octaveNoise(x / 100.0L, y / 100.0L, z / 100.0L, 5, 0.5L) * 0.5 + 0.5L << endl;
            }
        }
    }
}