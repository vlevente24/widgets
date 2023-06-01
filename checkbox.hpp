#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "widgets.hpp"

class CheckBox : public Widget {
    bool _checked;
public:
    CheckBox(Application*, int x, int y, int size);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    bool getCheck() const;
};

#endif