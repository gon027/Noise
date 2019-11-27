#include <iostream>
#include <cstdint>
#include <array>
#include <map>
#include <ctime>
#include <chrono>
#include <random>
using namespace std;

array<int, 1000000> a;
map<int, int> m;

int main(){
    random_device dev;
    mt19937 mt { dev() };
    uniform_int_distribution<> ui(1, 6);

    auto start = chrono::system_clock::now();

    for(int i = 0; i < a.size(); i++){
        a[i] = ui(mt);
        m[a[i]]++;
    }

    for(auto e : m){
        cout << e.first << " " << e.second << endl;
    }

    auto end = chrono::system_clock::now();
    auto diff = end - start;
    auto msec = chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    cout << msec << "ミリ秒" << endl;
}