#include "application.hpp"
#include "numericin.hpp"
#include "textinput.hpp"
#include "textbox.hpp"
#include "list.hpp"
#include "button.hpp"
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

// Érdemes a TextBox -oknál 20 magassággal számolni.

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const unsigned short fontsize = 15;
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

struct Tetel {
    string nev, egyseg;
    unsigned int idei, tavalyi;
    Tetel(string n, string e, unsigned int i, unsigned int t) : nev(n), egyseg(e), idei(i), tavalyi(t) {}
};

ostream& operator<< (ostream& ki, Tetel t) {
    return ki << t.nev << ", " << t.egyseg << ", " << t.idei << " Ft, " << t.tavalyi << " Ft";
}

vector<string> tetelek2string(const vector<Tetel>& vt) {
    vector<string> vs;
    for (Tetel t : vt) {
        stringstream ss;
        ss << t;
        vs.push_back(ss.str());
    }
    return vs;
}

class VizsgApp : public Application {
    vector<Tetel> tetelek;

    TextBox * _nevt;
    TextInput * _nev;
    TextInput * _egyseg;
    NumericIN * _idei;
    NumericIN * _tavalyi;
    Button * _uj;
    Button * _torol;
    Button * _reset;
    List * _tetelek;
    TextBox * _ossz;
public:
    VizsgApp() : Application(white, 550, 400) {
        gout.load_font(fontfile, fontsize);

        _nevt = new TextBox(this, 20, 20, "Név:");
        _nev = new TextInput(this, 60, 20, 200, 25);
        _egyseg = new TextInput(this, 270, 20, 40, 25);
        _idei = new NumericIN(this, 20, 50, 100, 25, 0, 100000);
        _tavalyi = new NumericIN(this, 130, 50, 100, 25, 0, 100000);
        _uj = new Button(this, 250, 50, 90, 25, "Új/Módosít", [=](){if(!_nev->getText().empty() and !_egyseg->getText().empty()){ujTetel();frissitTetelek();osszegzes();}}, fontfile, fontsize, grey, black);
        _torol = new Button(this, 350, 50, 60, 25, "Töröl", [=](){if(_tetelek->getSelected() != -1){torolTetel();frissitTetelek();osszegzes();}}, fontfile, fontsize, grey, black);
        _reset = new Button(this, 420, 50, 60, 25, "Reset", [=](){resetTetel();frissitTetelek();osszegzes();}, fontfile, fontsize, grey, black);
        _tetelek = new List(this, 20, 80, 300, 25, 280, vector<string>(0), fontfile, fontsize);
        _ossz = new TextBox(this, 20, 120, "Nincs adat");

        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }
    void action(genv::event) override {}
    void ujTetel() {
        size_t i = 0;
        while (i < tetelek.size() and tetelek[i].nev != _nev->getText()) {i++;}
        if (i == tetelek.size()) {
            tetelek.push_back(Tetel(_nev->getText(), _egyseg->getText(), _idei->getValue(), _tavalyi->getValue()));
        } else {
            tetelek[i].egyseg = _egyseg->getText();
            tetelek[i].idei = _idei->getValue();
            tetelek[i].tavalyi = _tavalyi->getValue();
        }
    }
    void frissitTetelek() {
        _tetelek->update(tetelek2string(tetelek));
    }
    void torolTetel() {
        tetelek.erase(tetelek.begin() + _tetelek->getSelected());
    }
    void resetTetel() {
        tetelek.clear();
    }
    void osszegzes() {
        if (tetelek.size()) {
            int regi = 0, uj = 0;
            for (Tetel t : tetelek) {
                regi += t.tavalyi;
                uj += t.idei;
            }
            double valtozas = (uj - regi) * 100.0 / regi;
            stringstream ss;
            ss << "Összesen: " << valtozas << "%";
            _ossz->update(ss.str());
        } else {
            _ossz->update("Nincs adat");
        }
    }

};

int main() {
    VizsgApp myapp;
    myapp.event_loop();
    return 0;
}