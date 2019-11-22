#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>
#include <cstdint>

namespace gn{

    class Noise{
    private:
        std::random_device rad;
        std::mt19937 mt;
        std::uniform_int_distribution<uint32_t> randomRange;
        
        std::array<uint32_t, 256> per {{}};
        std::array<uint32_t, 512> p {{}};

        void setSeed(const uint32_t _seed) noexcept;
        void makeArray() noexcept;

        //フェード関数(6t^5 – 15t^4 + 10t^3)
        inline double fade(double t) noexcept{
            return t * t * t * (t * (t * 6 - 15) + 10);
        }

        //線形補完関数
        inline double lerp(double t, double a, double b) noexcept{
            return a + t * (b - a);
        }

        //勾配ベクトル
        inline double grad(int hash, double x, double y, double z) noexcept{
            // 15 == 0b1111
            int h = hash & 15;
            double u = h < 8 ? x : y;
            double v = h < 4 ? y : (h == 12 || h == 14) ? x : z;

            return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
        }

    public:
        Noise();
        Noise(const uint32_t _seed);
        ~Noise() = default;

        uint32_t seed;

        //ノイズ
        double noise(double _x, double y_, double _z) noexcept;

        //オクターブノイズ
        double octaveNoise(double _x, double _y, double _z, int _octaves, double _persistence);
    };
}

#endif //NOISE_H