#include <fstream>
#include "application.hpp"
#include "textinput.hpp"
#include "textbox.hpp"
#include "checkbox.hpp"

using namespace genv;
using namespace std;

class FilePrint : public Application {
    TextInput * filename;
    TextInput * text;
    TextBox * tb_f;
    TextBox * tb_t;
    CheckBox * chb1;
public:
    FilePrint() : Application(color(0, 255, 0), 300, 160), filename(new TextInput(this, 10, 30, 200, 26)),
                  text(new TextInput(this, 10, 120, 200, 26)), tb_f(new TextBox(this, 10, 10, 100, 20, "Fájl neve:")),
                  tb_t(new TextBox(this, 10, 100, 100, 20, "Beviteli szöveg:")), chb1(new CheckBox(this, 230, 70, 30)) {
        gout.load_font("/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf", 15);

        for (Widget * ww : _widgets) {
            ww->print(false);
        }
        gout << refresh;
    }
    void print_to_file() {
        ofstream outf(filename->getText());
        outf << text->getText();
        outf.close();
    }
    void rev_print_to_file() {
        ofstream outf(text->getText());
        outf << filename->getText();
        outf.close();
    }
    void action(event ev) override {
        if (ev.type == ev_key) {
            if (ev.keycode == key_enter) {
                print_to_file();
            }
            if (ev.keycode == key_space) {
                if (chb1->getCheck()) {
                    rev_print_to_file();
                }
            }
        }
    }
};

int main() {

    FilePrint app;
    app.event_loop();

    return 0;
}