#ifndef NOISE_H
#define NOISE_H

#include <array>
#include <random>
#include <cstdint>
#include "XorShift.h"

namespace gn{

    class Noise{
    public:
        Noise();
        Noise(const uint32_t _seed);
        ~Noise() = default;

        void setSeed(const uint32_t _seed) noexcept;

        /*
        * [ -0.5, 0.5]の範囲でノイズを生成する
        */
        double noise(double _x, double y_, double _z) noexcept;

        /*
        * オクターブノイズを生成する
        */
        double octaveNoise(double _x, double _y, double _z, int _octaves, double _persistence);

    private:
        gn::XorShift xorShift;
        uint32_t seed;
        std::array<int, 512> p {{}};

        void makeArray() noexcept;

        //フェード関数(6t^5 ? 15t^4 + 10t^3)
        double fade(double t) noexcept;

        //線形補完関数
        double lerp(double t, double a, double b) noexcept;

        //勾配ベクトル
        double grad(int hash, double x, double y, double z) noexcept;
    };
}

#endif //NOISE_H