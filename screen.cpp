#include "screen.hpp"

using namespace genv;

Screen::Screen(Application *app, int x, int y, int w, int h, std::string text, color altbckg, color altclr) : TextBox(app, x, y, w, h, text),
                                                                                                              _altbckg(altbckg),
                                                                                                              _altclr(altclr) {}

void Screen::setText(std::string s) {
    _text = s;
}

void Screen::print(bool marked) const {
    gout.load_font("/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf", 50);
    gout << _altbckg << move_to(_xpos, _ypos) << box(_width, _height);
    gout << move_to(_xpos + _width - gout.twidth(_text) - 5, _ypos + _height - gout.cdescent() - gout.cascent() - 5) << _altclr << text(_text);
}