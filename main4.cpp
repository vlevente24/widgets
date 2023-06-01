#include "application.hpp"
#include "button.hpp"
#include "screen.hpp"

using namespace genv;
using namespace std;

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

enum State {
    ADD, SUB, MUL, DIV, EQ, OTH
};

class Zsamologep : public Application {
    State _state;
    size_t _count;
    Screen * _scr;
    string output;
    int op, op2;
    vector<Button*> _numbtn;
    vector<Button*> _funcbtn;
public:
    Zsamologep() : Application(white,400, 520) {
        gout.open(_window_width, _window_height);
        gout.load_font(fontfile, 15);
        gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);

        output = "";
        op = op2 = _count = 0;
        _scr = new Screen(this, 20, 20, 360, 100, to_string(op), black, white);
        _numbtn.push_back(new Button(this, 110, 410, 80, 80, "0", [=](){
            numeric(0);
            update();
        }, fontfile, 50, grey, black));
        for (int i = 0; i < 9; i++) {
            _numbtn.push_back(new Button(this, 20 + (i % 3) * 90, 140 + (i / 3) * 90, 80, 80, to_string(1 + i), [=](){
                numeric(i + 1);
                update();
            }, fontfile, 50, grey, black));
        }
        _funcbtn.push_back(new Button(this, 290, 140, 80, 80, "C", [=](){
            clear();
            update();
        }, fontfile, 50, grey, black));
        _funcbtn.push_back(new Button(this, 290, 230, 80, 80, "+", [=](){
            operation(ADD);
            update();
        }, fontfile, 50, grey, black));
        _funcbtn.push_back(new Button(this, 290, 320, 80, 80, "-", [=](){
            operation(SUB);
            update();
        }, fontfile, 50, grey, black));
        _funcbtn.push_back(new Button(this, 20, 410, 80, 80, "=", [=](){
            operation(EQ);
            update();
        }, fontfile, 50, grey, black));
        _funcbtn.push_back(new Button(this, 200, 410, 80, 80, "*", [=](){
            operation(MUL);
            update();
        }, fontfile, 50, grey, black));
        _funcbtn.push_back(new Button(this, 290, 410, 80, 80, "/", [=](){
            operation(DIV);
            update();
        }, fontfile, 50, grey, black));

        for (Widget * ww : _widgets) {
            ww->print(false);
        }
        gout << refresh;
    }
    void action(genv::event) {}
    void update() {
        _scr->setText(to_string(op));
    }
    void numeric(int szam) {
        op = op * 10 + szam;
    }
    void operation(State st) {
        _count++;
        if (_count > 1) {
            switch (_state) {
                case ADD:
                    op2 += op;
                    op = 0;
                    break;
                case SUB:
                    op2 -= op;
                    op = 0;
                    break;
                case MUL:
                    op2 *= op;
                    op = 0;
                    break;
                case DIV:
                    op2 /= op;
                    op = 0;
                    break;
            }
        } else if (_count == 1) {
            op2 = op;
            op = 0;
        }
        if (st == EQ) {
            op = op2;
            op2 = 0;
            _count = 0;
        }
        _state = st;
    }
    void clear() {
        op = 0;
        op2 = 0;
        _count = 0;
    }
};

int main() {
    Zsamologep zs;
    zs.event_loop();
    return 0;
}

//őswidget, ősalkalmazás, statikus szöveg, szövegbemenet, list, számbeállító, gomb, checkbox