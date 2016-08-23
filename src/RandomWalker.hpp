#ifndef RANDOMWALKER_HPP
#define RANDOMWALKER_HPP


#include <random>


class RandomWalker {
public:
    struct Pos {
        float x;
        float y;
    };

    RandomWalker(uint64_t width, uint64_t height);

    void step(void);

    const std::vector<Pos>& getLog(void) const;

private:
    std::default_random_engine _r;

    uint64_t    _width;
    uint64_t    _height;

    Pos     _pos;
    float   _dir;
    float   _spd;

    std::vector<Pos>    _log;
};


#endif // RANDOMWALKER_HPP
