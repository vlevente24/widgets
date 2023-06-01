#ifndef NUMERICIN_HPP_INCLUDE
#define NUMERICIN_HPP_INCLUDE

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"

class NumericIN : public Widget {
    int _min, _max;
    int _value;
public:
    NumericIN(Application*, int, int, int, int, int, int);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
};

#endif