#ifndef WIDGETS_SCREEN_HPP
#define WIDGETS_SCREEN_HPP

#include "textbox.hpp"

class Screen : public TextBox {
    genv::color _altbckg;
    genv::color _altclr;
public:
    Screen(Application*, int x, int y, int w, int h, std::string text, genv::color altbckg, genv::color altclr);
    void setText(std::string s);
    void print(bool marked) const override;
};


#endif //WIDGETS_SCREEN_HPP
