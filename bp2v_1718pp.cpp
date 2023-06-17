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

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const unsigned short fontsize = 15;
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

struct Klan {
    string nev;
    int intelligencia, kitartas, memoria, erdeklodes;
    Klan(string n, int i, int k, int m, int e) : nev(n), intelligencia(i), kitartas(k), memoria(m), erdeklodes(e) {}
};

ostream& operator<< (ostream& ki, const Klan & k) {
    return ki << k.nev << ", INT:" << k.intelligencia << " KIT:" << k.kitartas << " MEM:" << k.memoria
              << " ERD:" << k.erdeklodes;
}

class VizsgApp : public Application {
    TextInput * nev;
    TextBox * intes;
    NumericIN * inte;
    TextBox * kits;
    NumericIN * kit;
    TextBox * mems;
    NumericIN * mem;
    TextBox * erds;
    NumericIN * erd;
    TextBox * klans;
    List * klanl;
    vector<Klan> klanok;
public:
    VizsgApp() : Application(white, 550, 400) {
        gout.load_font(fontfile, fontsize);

        nev = new TextInput(this, 20, 20, 300, 25);
        intes = new TextBox(this, 20, 50, "Intelligencia:");
        inte = new NumericIN(this, 150, 50, 100, 25, 1, 10);
        kits = new TextBox(this, 20, 80, "Kitartás:");
        kit = new NumericIN(this, 150, 80, 100, 25, 1, 10);
        mems = new TextBox(this, 20, 110, "Memória:");
        mem = new NumericIN(this, 150, 110, 100, 25, 1, 10);
        erds = new TextBox(this, 20, 140, "Érdeklődés:");
        erd = new NumericIN(this, 150, 140, 100, 25, 1, 10);
        klans = new TextBox(this, 20, 180, "Klán:");
        klanl = new List(this, 70, 180, 400, 25, 180, vector<string>(1, "üres"), fontfile, fontsize);

        klanok.push_back(Klan("Vajna", 6, 6, 6, 6));

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