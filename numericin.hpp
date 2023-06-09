#ifndef NUMERICIN_HPP_INCLUDE
#define NUMERICIN_HPP_INCLUDE

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"

class NumericIN : public Widget {
    int _min, _max;
    int _value;
    int _cursor_pos, _cursor_wait;
    bool _cursor_state;
    std::string val2str();
    void cursorIncrease(int n);
    void cursorDecrease();
public:
    NumericIN(Application*, int x, int y, int w, int h, int min, int max);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    int getValue() const;
};

#endif