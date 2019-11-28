#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <cstdint>
#include <array>

namespace gn{
    using uint = std::uint_fast32_t;

    class XorShift{
    private:
        uint seed;
        uint seeds[4];

    public:
        /*
        * デフォルトのシード値を設定
        */
        XorShift();

        /*
        * 引数に入れた値をシード値として設定
        */
        XorShift(uint _seed);

        /*
        * 
        */
        ~XorShift() = default;

        /*
        * シード値を設定
        */
        void setSeedValue(uint _seed);

        /*
        * 乱数を取得する
        */
        uint getRand();

        /*
        * [ _min, _max ]の範囲の乱数をint型で取得
        * _min : 範囲の最小値
        * _max : 範囲の最大値
        */
        int getRandomRangeInt(int _min, int _max);

        /*
        * [ _min, _max ]の範囲の乱数をfloat型で取得
        * _min : 範囲の最小値
        * _max : 範囲の最大値
        */
        float getRandomRangeFloat(float _min, float _max);
    };
}

#endif // XORSHIFT_H