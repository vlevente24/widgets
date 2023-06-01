#include "checkbox.hpp"

using namespace genv;

CheckBox::CheckBox(Application * app, int x, int y, int size) : Widget(app, x, y, size, size), _checked(false) {}

void CheckBox::print(bool b) const {
    gout << color(134, 134, 134) << move_to(_xpos, _ypos) << box(_width, _height);
    if (_checked) {
        gout << color(255, 255, 255) << move_to(_xpos + _width / 4, _ypos + _height / 4) << line_to(_xpos + _width * 3 / 4, _ypos + _height * 3 / 4) << move_to(_xpos + _width * 3 / 4, _ypos + _height / 4) << line_to(_xpos + _width / 4, _ypos + _height * 3 / 4);
        //gout << color(255, 255, 255) << move_to(_xpos + 3, _ypos + _height / 2) << line_to(_xpos + _width * 2 / 5, _ypos + _height - 3) << line_to(_xpos + _width - 3, _ypos + 3);
    }
    else {
        gout << move_to(_xpos + 2, _ypos + 2) << color(255, 255, 255) << box(_width - 4, _height - 4);
    }
}

void CheckBox::handle(event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            _checked = !_checked;
        }
    }
    /*
    if (ev.type == ev_key) {
        if (ev.keycode == key_space) {
            _checked = !_checked;
        }
    }
    */
}

void CheckBox::reset() {}

bool CheckBox::getCheck() const {
    return _checked;
}