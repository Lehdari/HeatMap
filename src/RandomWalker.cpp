#include "RandomWalker.hpp"

#include <ctime>


#define RF (_r() % 10000) / 9999.0f
#define PI 3.14159265359


RandomWalker::RandomWalker(uint64_t width, uint64_t height) :
    _r      (time(NULL)),
    _width  (width),
    _height (height),
    _pos    {RF*_width, RF*_height},
    _dir    (RF*2*PI),
    _spd    (1.0f + RF*3.0f)
{
    _log.push_back(_pos);
}

void RandomWalker::step(void) {
    _pos.x += _spd*cosf(_dir);
    _pos.y += _spd*sinf(_dir);

    if (_pos.x >= _width) {
        _pos.x = (float)_width-0.1f;
        _dir += PI;
    }
    if (_pos.x < 0.0f) {
        _pos.x = 0.1f;
        _dir += PI;
    }
    if (_pos.y >= _height) {
        _pos.y = (float)_height-0.1f;
        _dir += PI;
    }
    if (_pos.y < 0.0f) {
        _pos.y = 0.1f;
        _dir += PI;
    }

    _log.push_back(_pos);

    _dir += 0.1f - RF*0.2f;
    if (_dir < 0.0f) _dir += 2*PI;
    if (_dir > 2*PI) _dir -= 2*PI;

    _spd += 0.1f - RF*0.2f;
    if (_spd < 1.0f) _spd = 1.0f;
    if (_spd > 5.0f) _spd = 5.0f;
}

const std::vector<RandomWalker::Pos>& RandomWalker::getLog(void) const {
    return _log;
}
