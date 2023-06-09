#ifndef LIST_HPP_INCLUDE
#define LIST_HPP_INCLUDE

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <string>

class List : public Widget {
    std::vector<std::string> _sv;
    std::vector<genv::canvas*> _v;
    std::string _value;
    const std::string _fontfile;
    const unsigned short _fontsize;
    int _y_down_max, _y_down, _index, _shift, _valuei;
    void print_btn(bool) const;
    void print_box() const;
    int calc_index(int);
public:
    List(Application*, int x, int y, int w, int h, int max_y_down, std::vector<std::string> items, std::string fontfile, unsigned short fontsize);
    ~List();
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    bool is_selected(int, int) override;
    std::string getValue() const;
    int getSelected() const;
    void update(std::vector<std::string> items);
};

#endif