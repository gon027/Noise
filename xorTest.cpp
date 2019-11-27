#include <iostream>
#include <cstdint>
#include <array>
#include <map>
#include <chrono>
using namespace std;

uint32_t vec[4];
array<uint32_t, 1'000> arr;
map<uint32_t, int> m;
uint32_t seed = 100;

//シード値を格納する名前空間
namespace values{
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
}

//デフォルトのシード値
void defaultSeed(){
    values::x = 815279472;
    values::y = 1396960035;
    values::z = 1881763598;
    values::w = 1082589634;
}

void setSeed(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w){
    values::x = _x;
    values::y = _y;
    values::z = _z;
    values::w = _w;
}

//乱数生成テスト1
uint32_t xorShift(){
    seed ^= seed << 11;
    seed ^= seed >> 7;
    seed ^= seed << 13;
    return seed;
}

//乱数生成テスト2
uint32_t xorShift2(){
    uint32_t t = vec[0];
    uint32_t w = vec[3];

    vec[0] = vec[1];
    vec[1] = vec[2];
    vec[2] = w;

    t ^= t << 11;
    t ^= t >> 13;
    w ^= w >> 19;
    w ^= t;

    vec[3] = w;

    return w;
}

//乱数生成テスト3
uint32_t xorShift3(){
    uint32_t t { values::x ^ ( values::x << 11 ) };

    values::x = values::y;
    values::y = values::z;
    values::z = values::w;
    
    values::w = ( values::w ^ ( values::w >> 13 ) ) ^  ( t ^ ( t << 19 ) );

    return values::w;
}

uint32_t range(uint32_t min, uint32_t max){
    return xorShift3() % (max - min + 1) + min;
}

int main(){
    //配列初期化
    // for(int i = 0; i < 4; i++){
    //     //seed = 1162849171 * (seed ^ ( seed >> 30) );
    //     seed = 756535261 * (seed ^ ( seed >> 30) );
    //     vec[i] = xorShift();
    // }

    // for(int i = 0; i < 4; i++){
    //     cout << vec[i] << endl;
    // }

    auto start = chrono::system_clock::now();

    defaultSeed();
    for(int i = 0; i < arr.size(); ++i){
        arr[i] = range(0, 10);
        m[arr[i]]++;
    }

    for(auto a : m){
        cout << a.first << " " << a.second << endl;
    }

    auto end = chrono::system_clock::now();
    auto diff = end - start;
    auto msec = chrono::duration_cast<std::chrono::microseconds>(diff).count();
    cout << msec << endl;

    return 0;
}