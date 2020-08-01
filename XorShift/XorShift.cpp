#include "XorShift.h"

namespace gn {
    XorShift::XorShift() {
        seeds[0] = 815'279'472;
        seeds[1] = 1'396'960'035;
        seeds[2] = 1'881'763'598;
        seeds[3] = 1'082'589'634;
    }

    XorShift::XorShift(uint _seed)
        : seed()
    {
        this->setSeedValue(_seed);
    }

    void XorShift::setSeedValue(uint _seed){
        if (_seed == 0){
            seed = 1'022'659'036;
        }
        else{
            seed = _seed;
        }

        seeds[0] = seed ^ (seed << 11);
        seeds[1] = (seed >> 9) ^ (seeds[0] >> 7);
        seeds[2] = (seed << 3) ^ (seeds[1] >> 5);
        seeds[3] = (seed >> 17) ^ (seeds[2] << 13);
    }

    uint XorShift::getRand(){
        uint t{seeds[0] ^ seeds[0] << 11};

        seeds[0] = seeds[1];
        seeds[1] = seeds[2];
        seeds[2] = seeds[3];
        seeds[3] = (seeds[3] ^ (seeds[3] >> 13)) ^ (t ^ (t << 19));

        return seeds[3];
    }

    int XorShift::getRandomRangeInt(int _min, int _max){
        return getRand() % (_max - _min + 1) + _min;
    }

    float XorShift::getRandomRangeFloat(float _min, float _max){
        return (float)(getRand() % 0xFFFF) / 0xFFFF * (_max - _min + 1.0f) + _min;
    }
}
