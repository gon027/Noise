#include "Noise.h"

namespace gn{
    
    Noise::Noise()
        : rad()
        , mt(rad())
        , randomRange(0, 255)
    {
        makeArray();
    }

    void Noise::makeArray() noexcept{
        for(int i = 0; i < 512; ++i){
            p[i] = randomRange(mt);
        }
    }

    double Noise::noise(double _x, double _y, double _z) noexcept{
        _x = (double)_x; 
        _y = (double)_y; 
        _z = (double)_z;

        int X = (int)floor( _x ) & 255;
        int Y = (int)floor( _y ) & 255;
        int Z = (int)floor( _z ) & 255;

        _x -= floor( _x );
        _y -= floor( _y );
        _z -= floor( _z );
    
        double u = fade( _x );
        double v = fade( _y );
        double w = fade( _z );

        // ハッシュを求める
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
        double a = grad( AAA, _x + 0, _y + 0, _z + 0 );
        double b = grad( ABA, _x - 1, _y + 0, _z + 0 );
        double c = grad( AAB, _x + 0, _y - 1, _z + 0 );
        double d = grad( ABB, _x - 1, _y - 1, _z + 0 );
        double e = grad( BAA, _x + 0, _y + 0, _z - 1 );
        double f = grad( BBA, _x - 1, _y + 0, _z - 1 );
        double g = grad( BAB, _x + 0, _y - 1, _z - 1 );
        double h = grad( BBB, _x - 1, _y - 1, _z - 1 );

        // 横方向の補間を計算
        double x1 = lerp( u, a, b );
        double x2 = lerp( u, c, d );
        double x3 = lerp( u, e, f );
        double x4 = lerp( u, g, h );

        // 縦方向の補間を計算
        double y1 = lerp( v, x1, x2 );
        double y2 = lerp( v, x3, x4 );

        return lerp( w, y1, y2 );
    }

    double Noise::octaveNoise(double _x, double _y, double _z, int _octaves = 5, double _persistence = 0.5L){
        double total { 0 };
        double frequency { 1 };
        double amplitude { 1 };
        double maxValue { 0 };

        for(int i = 0; i < _octaves; ++i){
            total += noise( _x * frequncy, _y * frequncy, _y * frequncy );
            maxValue += amplitude;
            amlitude *= presistence;
            frequency *= 2;
        }

        return total / maxValue;
    }
}