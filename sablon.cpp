#include "application.hpp"
#include "numericin.hpp"
#include "textinput.hpp"
#include "textbox.hpp"
#include "list.hpp"
#include "button.hpp"
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
using namespace genv;

// Érdemes a TextBox -oknál 20 magassággal számolni.

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const unsigned short fontsize = 15;
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

class VizsgApp : public Application {
    TextBox * hello;
public:
    VizsgApp() : Application(white, 550, 400) {
        gout.load_font(fontfile, fontsize);

        hello = new TextBox(this, 20, 20, "Hello, én vagyok a sablon!");

        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }
    void action(genv::event) override {}
};

int main() {
    VizsgApp myapp;
    myapp.event_loop();
    return 0;
}