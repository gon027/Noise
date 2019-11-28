#include "Noise.h"

namespace gn{
    
    Noise::Noise()
        // : rad()
        // , mt(rad())
        // , randomRange(0, 255)
        : xorShift()
    {
        makeArray();
    }

    Noise::Noise(const uint32_t _seed)
        // : rad()
        // , mt(_seed)
        // , randomRange(0, 255)
        : xorShift( _seed )
    {
        setSeed(_seed);
        makeArray();
    }

    void Noise::setSeed(const uint32_t _seed) noexcept{
        this->seed = _seed;
    }

    void Noise::makeArray() noexcept{
        for(int i = 0; i < 512; ++i){
            p[i] = /*randomRange(mt);*/ xorShift.getRandomRangeInt(0, 255);
        }
    }

    double Noise::noise(double _x, double _y, double _z) noexcept{
        _x = (double)_x; 
        _y = (double)_y; 
        _z = (double)_z;

        int X { (int)floor( _x ) & 255 };
        int Y { (int)floor( _y ) & 255 };
        int Z { (int)floor( _z ) & 255 };

        _x -= floor( _x );
        _y -= floor( _y );
        _z -= floor( _z );
    
        double u { fade( _x ) };
        double v { fade( _y ) };
        double w { fade( _z ) };

        // ハッシュを求める
        int A  { static_cast<int>( p[ X     ] + Y ) };
        int AA { static_cast<int>( p[ A     ] + Z ) };
        int AB { static_cast<int>( p[ A + 1 ] + Z ) };
        int B  { static_cast<int>( p[ X + 1 ] + Y ) };
        int BA { static_cast<int>( p[ B     ] + Z ) };
        int BB { static_cast<int>( p[ B + 1 ] + Z ) };

        int AAA { static_cast<int>( p[ AA     ] ) };
        int AAB { static_cast<int>( p[ AB     ] ) };
        int ABA { static_cast<int>( p[ BA     ] ) };
        int ABB { static_cast<int>( p[ BB     ] ) };
        int BAA { static_cast<int>( p[ AA + 1 ] ) };
        int BAB { static_cast<int>( p[ AB + 1 ] ) }; 
        int BBA { static_cast<int>( p[ BA + 1 ] ) };
        int BBB { static_cast<int>( p[ BB + 1 ] ) };

        // 8頂点から勾配ベクトルを求める
        double a { grad( AAA, _x + 0, _y + 0, _z + 0 ) };
        double b { grad( ABA, _x - 1, _y + 0, _z + 0 ) };
        double c { grad( AAB, _x + 0, _y - 1, _z + 0 ) };
        double d { grad( ABB, _x - 1, _y - 1, _z + 0 ) };
        double e { grad( BAA, _x + 0, _y + 0, _z - 1 ) };
        double f { grad( BBA, _x - 1, _y + 0, _z - 1 ) };
        double g { grad( BAB, _x + 0, _y - 1, _z - 1 ) };
        double h { grad( BBB, _x - 1, _y - 1, _z - 1 ) };

        // 横方向の補間を計算
        double x1 { lerp( u, a, b ) };
        double x2 { lerp( u, c, d ) };
        double x3 { lerp( u, e, f ) };
        double x4 { lerp( u, g, h ) };

        // 縦方向の補間を計算
        double y1 { lerp( v, x1, x2 ) };
        double y2 { lerp( v, x3, x4 ) };

        return lerp( w, y1, y2 );
    }

    double Noise::octaveNoise(double _x, double _y, double _z, int _octaves = 5, double _persistence = 0.5L){
        double total { 0 };
        double frequency { 1 };
        double amplitude { 1 };
        double maxValue { 0 };

        for(int i = 0; i < _octaves; ++i){
            total += noise( _x * frequency, _y * frequency, _z * frequency);
            maxValue += amplitude;
			amplitude *= _persistence;
            frequency *= 2;
        }

        return total / maxValue;
    }
}

// #include <iostream>
// using namespace std;

// int main(){
//     gn::Noise n;

//     cout << n.noise(0.1, 0.43, 0.1) << endl;
// }