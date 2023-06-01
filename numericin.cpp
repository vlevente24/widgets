#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "numericin.hpp"
#include <sstream>

using namespace genv;
using namespace std;

NumericIN::NumericIN(Application * app, int x, int y, int w, int h, int min, int max) : Widget(app, x, y, w, h), _min(min), _max(max), _value(min) {}

void NumericIN::print(bool marked) const {
    gout << (marked ? color(20, 131, 218) : color(134, 134, 134));
    gout << move_to(_xpos, _ypos) << box(_width, _height) << move_to(_xpos + 2, _ypos + 2) << color(255, 255, 255) << box(_width - 4, _height - 4);
    int button_w = (_height * 0.6 - 2), button_h = (_height - 2);
    gout << move_to(_xpos + _width - 1 - button_w, _ypos + 1) << color(110, 110, 110) << box(button_w, button_h) << move_to(_xpos + _width - button_w, _ypos + 2) << color(240, 240, 240) << box(button_w - 2, button_h - 2);
    gout << move_to(_xpos + _width - 1 - button_w, _ypos + _height / 2) << color(60, 60, 60) << line_to(_xpos + _width - 1, _ypos + _height / 2);
    gout << color(60, 60, 60) << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h / 6) << line_to(_xpos + _width - 1 - button_w * 0.3, _ypos + 1 + button_h * 2 / 6) << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h / 6) << line_to(_xpos + _width - 1 - button_w * 0.7, _ypos + 1 + button_h * 2 / 6);
    gout << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 5 / 6) << line_to(_xpos + _width - 1 - button_w * 0.3, _ypos + 1 + button_h * 4 / 6) << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 5 / 6) << line_to(_xpos + _width - 1 - button_w * 0.7, _ypos + 1 + button_h * 4 / 6);
    stringstream str;
    str << _value;
    gout << move_to(_xpos + 2 + 3, _ypos + 2 + 3) << color(0, 0, 0) << text(str.str());
}

void NumericIN::handle(event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (ev.pos_x >= _xpos + _width - 1 - (_height * 0.6 - 2) and ev.pos_x < _xpos + _width - 1) {
                if (ev.pos_y >= _ypos + 1 and ev.pos_y <= _ypos + _height / 2) {
                    _value = _value >= _max ? _value : _value + 1;
                }
                else if (ev.pos_y > _ypos + _height / 2 and ev.pos_y < _ypos + _height - 1) {
                    _value = _value <= _min ? _value : _value - 1;
                }
            }
        }
    }
    if (ev.type == ev_key) {
        if (ev.keycode == key_up) {
            _value = _value >= _max ? _value : _value + 1;
        }
        if (ev.keycode == key_down) {
            _value = _value <= _min ? _value : _value - 1;
        }
        if (ev.keycode == key_pgup) {
            _value = _value + 10 > _max ? _value : _value + 10;
        }
        if (ev.keycode == key_pgdn) {
            _value = _value - 10 < _min ? _value : _value - 10;
        }
    }
}

void NumericIN::reset() {}