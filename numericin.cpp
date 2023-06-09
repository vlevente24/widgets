#include "numericin.hpp"
#include <sstream>
#include <cmath>
#include <iostream>

using namespace genv;
using namespace std;

NumericIN::NumericIN(Application * app, int x, int y, int w, int h, int min, int max) : Widget(app, x, y, w, h),
                    _min(min), _max(max), _value(min), _cursor_wait(0), _cursor_state(false) {
    _cursor_pos = val2str().length();
}

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
    gout << move_to(_xpos + 5, _ypos + 5) << color(0, 0, 0) << text(str.str());
    if (marked and _cursor_state) {
        gout << move_to(_xpos + 5 + gout.twidth(str.str().substr(0, _cursor_pos)), _ypos + 4) << color(0, 0, 0) << line(0, gout.cascent() + gout.cdescent() + 1);
    }
}

void NumericIN::handle(event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (ev.pos_x >= _xpos + _width - 1 - (_height * 0.6 - 2) and ev.pos_x < _xpos + _width - 1) {
                _cursor_wait = 0;
                _cursor_state = false;
                gin.timer(_cursor_wait);
                if (ev.pos_y >= _ypos + 1 and ev.pos_y <= _ypos + _height / 2) {
                    _value = _value >= _max ? _value : _value + 1;
                }
                else if (ev.pos_y > _ypos + _height / 2 and ev.pos_y < _ypos + _height - 1) {
                    _value = _value <= _min ? _value : _value - 1;
                }
            }
            else if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width - 1 - (_height * 0.6 - 2)) {
                if (_cursor_wait == 0) {
                    _cursor_wait = 600;
                    _cursor_state = true;
                    _cursor_pos = val2str().length();
                    gin.timer(_cursor_wait);
                }
            }
        }
    }
    if (ev.type == ev_key) {
        if (ev.keycode == key_up) {
            _value = _value >= _max ? _value : _value + 1;
            _cursor_wait = 0;
            _cursor_state = false;
            gin.timer(_cursor_wait);
        }
        if (ev.keycode == key_down) {
            _value = _value <= _min ? _value : _value - 1;
            _cursor_wait = 0;
            _cursor_state = false;
            gin.timer(_cursor_wait);
        }
        if (ev.keycode == key_pgup) {
            _value = _value + 10 > _max ? _value : _value + 10;
            _cursor_wait = 0;
            _cursor_state = false;
            gin.timer(_cursor_wait);
        }
        if (ev.keycode == key_pgdn) {
            _value = _value - 10 < _min ? _value : _value - 10;
            _cursor_wait = 0;
            _cursor_state = false;
            gin.timer(_cursor_wait);
        }
        if (ev.keycode == key_left and _cursor_wait > 0 and _cursor_pos >= 1) {
            if (_value >= 0) {
                _cursor_pos -= 1;
                _cursor_state = true;
                gin.timer(0);
                gin.timer(600);
            }
            else if (_cursor_pos >= 2) {
                _cursor_pos -= 1;
                _cursor_state = true;
                gin.timer(0);
                gin.timer(600);
            }
        }
        if (ev.keycode == key_right and _cursor_wait > 0 and _cursor_pos + 1 <= val2str().length()) {
            _cursor_pos += 1;
            _cursor_state = true;
            gin.timer(0);
            gin.timer(600);
        }
        if (ev.keycode == '-' and _cursor_wait > 0 and _value != 0) {
            if (_value * -1 >=_min and _value * -1 <= _max) {
                if (_value < 0) {
                    _cursor_pos -= 1;
                } else {
                    _cursor_pos += 1;
                }
                _value *= -1;
                _cursor_state = true;
                gin.timer(0);
                gin.timer(600);
            }
        }
        if (ev.keycode == '0' and _cursor_wait > 0) {
            cursorIncrease(0);
        }
        if (ev.keycode == '1' and _cursor_wait > 0) {
            cursorIncrease(1);
        }
        if (ev.keycode == '2' and _cursor_wait > 0) {
            cursorIncrease(2);
        }
        if (ev.keycode == '3' and _cursor_wait > 0) {
            cursorIncrease(3);
        }
        if (ev.keycode == '4' and _cursor_wait > 0) {
            cursorIncrease(4);
        }
        if (ev.keycode == '5' and _cursor_wait > 0) {
            cursorIncrease(5);
        }
        if (ev.keycode == '6' and _cursor_wait > 0) {
            cursorIncrease(6);
        }
        if (ev.keycode == '7' and _cursor_wait > 0) {
            cursorIncrease(7);
        }
        if (ev.keycode == '8' and _cursor_wait > 0) {
            cursorIncrease(8);
        }
        if (ev.keycode == '9' and _cursor_wait > 0) {
            cursorIncrease(9);
        }
        if (ev.keycode == key_backspace and  _cursor_wait > 0) {
            cursorDecrease();
        }
    }
    if (ev.type == ev_timer) {
        _cursor_state = !_cursor_state;
    }
}

void NumericIN::reset() {
    _cursor_wait = 0;
    _cursor_state = false;
    gin.timer(_cursor_wait);
}

string NumericIN::val2str() {
    stringstream ss;
    ss << _value;
    return ss.str();
}

void NumericIN::cursorIncrease(int n) {
    int crs = _cursor_pos, abs = _value, l, tmp;
    stringstream ss;
    if (_value < 0) {
        abs *= -1;
        crs -= 1;
    }
    ss << abs;
    l = ss.str().length();
    tmp = pow(10, l-crs);
    abs = ((abs / tmp) * 10 + n) * tmp + abs % tmp;
    if (_value < 0) {
        abs *= -1;
    }
    if (abs >= _min and abs <= _max) {
        if (_value != 0 or abs / 10) {
            _cursor_pos += 1;
        }
        _value = abs;
        _cursor_state = true;
        gin.timer(0);
        gin.timer(600);
    }
}

void NumericIN::cursorDecrease() {
    int crs = _cursor_pos, abs = _value, l, tmp;
    stringstream ss;
    if (_value < 0) {
        abs *= -1;
        crs -= 1;
    }
    if (crs > 0 and _value != 0) {
        ss << abs;
        l = ss.str().length();
        tmp = pow(10, l-crs);
        abs = ((abs / tmp) / 10) * tmp + abs % tmp;
        if (_value < 0) {
            abs *= -1;
        }
        if (abs >= _min and abs <= _max) {
            if (abs or _value < 0) {
                _cursor_pos -= 1;
            }
            _value = abs;
            _cursor_state = true;
            gin.timer(0);
            gin.timer(600);
        }
    }
}

int NumericIN::getValue() const {
    return _value;
}
