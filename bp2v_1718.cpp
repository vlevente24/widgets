#include "application.hpp"
#include "textinput.hpp"
#include "textbox.hpp"
#include "button.hpp"
#include "list.hpp"
#include "numericin.hpp"
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
using namespace genv;

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

struct Tetelek {
    string nev;
    int ar;
    Tetelek(string neve, int ara) : nev(neve), ar(ara) {}
};

ostream& operator<< (ostream& ki, Tetelek t) {
    return ki << t.nev << ": " << t.ar << " Ft";
}

vector<string> tetelek2string(vector<Tetelek> vt) {
    vector<string> v;
    for (Tetelek t : vt) {
        stringstream ss;
        ss << t;
        v.push_back(ss.str());
    }
    return v;
}

class BpV8 : public Application {
    TextInput * nev;
    NumericIN * ar;
    Button * hozzaad;
    Button * vissza;
    Button * modosit;
    Button * torol;
    List * termekek;
    TextBox * egyenleg;
    vector<Tetelek> tetel;
    TextBox * fajlszoveg;
    TextInput * fajlnev;
    Button * betolt;
    Button * kiment;
public:
    BpV8() : Application(white, 500, 400) {
        gout.load_font(fontfile, 15);

        nev = new TextInput(this, 20, 20, 300, 25);
        ar = new NumericIN(this, 20, 55, 150, 25, -10000, 10000);
        hozzaad = new Button(this, 190, 55, 100, 25, "Hozzáad", [=](){ujTetel();}, fontfile, 15, grey, black);
        modosit = new Button(this, 300, 55, 100, 25, "Módosít", [=](){modositTetel();}, fontfile, 15, grey, black);
        egyenleg = new TextBox(this, 20, 90, 200, 20, "Egyenleg: 0 Ft");
        termekek = new List(this, 20, 110, 300, 25, 250, vector<string>(), fontfile, 15);
        vissza = new Button(this, 30, 160, 100, 25, "Vissza", [=](){torolTetel();}, fontfile, 15, grey, black);
        torol = new Button(this, 150, 160, 100, 25, "Törlés", [=](){mindenTorol();}, fontfile, 15, grey, black);

        fajlszoveg = new TextBox(this, _window_width - 220, _window_height - 100, 100, 20, "Fájl neve:");
        fajlnev = new TextInput(this, _window_width - 220, _window_height - 80, 200, 25);
        betolt = new Button(this, _window_width - 110, _window_height - 45, 90, 25, "Betölt", [=](){betoltes();}, fontfile, 15, grey, black);
        kiment = new Button(this, _window_width - 210, _window_height - 45, 90, 25, "Mentés", [=](){mentes();}, fontfile, 15, grey, black);

        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }
    void action(event) override {}
    void egyenlegFrissit() {
        int c = 0;
        for (Tetelek t : tetel) {
            c += t.ar;
        }
        stringstream ss;
        ss << "Egyenleg: "<< c << " Ft";
        egyenleg->update(ss.str());
    }
    void ujTetel() {
        if (nev->getText() != "") {
            tetel.push_back(Tetelek(nev->getText(), ar->getValue()));
            termekek->update(tetelek2string(tetel));
            egyenlegFrissit();
        }
    }
    void torolTetel() {
        if (termekek->getSelected() != -1) {
            tetel.erase(tetel.begin() + termekek->getSelected());
            termekek->update(tetelek2string(tetel));
            egyenlegFrissit();
        }
    }
    void mindenTorol() {
        tetel.clear();
        termekek->update(tetelek2string(tetel));
        egyenlegFrissit();
    }
    void modositTetel() {
        if (termekek->getSelected() != -1 and nev->getText() != "") {
            tetel[termekek->getSelected()].nev = nev->getText();
            tetel[termekek->getSelected()].ar = ar->getValue();
            termekek->update(tetelek2string(tetel));
            egyenlegFrissit();
        }
    }
    void mentes() {
        if (fajlnev->getText() != "") {
            ofstream kifajl(fajlnev->getText());
            for (Tetelek t : tetel) {
                kifajl << t << endl;
            }
            kifajl.close();
        }
    }
    void betoltes() {
        if (fajlnev->getText() != "") {
            ifstream befajl(fajlnev->getText());
            if (befajl.good()) {
                vector<Tetelek> vt;
                while (befajl.good()) {
                    string tmps, clrs;
                    int tmpi;
                    getline(befajl, tmps, ':') >> ws >> tmpi;
                    vt.push_back(Tetelek(tmps, tmpi));
                    getline(befajl, clrs) >> ws;
                }
                befajl.close();
                tetel = vt;
                termekek->update(tetelek2string(tetel));
                egyenlegFrissit();
            }
            else {
                gout.message("NOT VALID FILENAME");
            }
        }
    }
};

int main() {
    BpV8 app;
    app.event_loop();
    return 0;
}