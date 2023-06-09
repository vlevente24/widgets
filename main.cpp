#include "application.hpp"
#include "list.hpp"

using namespace std;
using namespace genv;

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";

class Switcher : public Application {
    List * l1;
    List * l2;
    vector<string> v1;
    vector<string> v2;
public:
    Switcher() : Application(color(255, 255, 255), 500, 500) {
        v1.push_back("hali");
        v1.push_back("szius");
        v1.push_back("mizu");
        v1.push_back("csumi");

        v2.push_back("Jonapot");
        v2.push_back("Csokolom");
        v2.push_back("Udvozlom");
        v2.push_back("Viszlat");

        l1 = new List(this, 10, 10, 200, 26, 400, v1, fontfile, 15);
        l2 = new List(this, 250, 10, 200, 26, 400, v2, fontfile, 15);

        gout.load_font("/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf", 15);

        for (Widget * ww : _widgets) {
            ww->print(false);
        }
        gout << refresh;
    }
    void action(event ev) override {
        if (ev.type == ev_key and ev.keycode == key_enter) {
            string s2 = l2->getValue();
            if (s2 != "") {
                vector<string> vv2;
                for (string ss : v2) {
                    if (ss != s2) {
                        vv2.push_back(ss);
                    }
                }
                v2 = vv2;
                v1.push_back(s2);
                /*
                */
                delete l1;
                delete l2;
                _widgets.clear();
                l1 = new List(this, 10, 10, 200, 26, 400, v1, fontfile, 15);
                l2 = new List(this, 250, 10, 200, 26, 400, v2, fontfile, 15);
            }
        }
    }
};

int main() {

    Switcher app;
    app.event_loop();

    return 0;
}