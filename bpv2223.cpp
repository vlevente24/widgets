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
    string nev, egyseg, kategoria;
    int _id, idei, tavalyi;
    double suly;
    Tetel(unsigned int id, string n, string e, string k, int i, int t, double s) : _id(id), nev(n), egyseg(e), kategoria(k), idei(i), tavalyi(t), suly(s) {}
};

ostream& operator<< (ostream& ki, Tetel t) {
    return ki << t.nev << ", " << t.suly << ", " << t.egyseg << ", " << t.kategoria << ", " << t.idei << " Ft, " << t.tavalyi << " Ft";
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
    vector<Tetel> teteleks;

    TextBox * _nevt;
    TextInput * _nev;
    TextInput * _egyseg;
    List * _kat;
    NumericIN * _idei;
    NumericIN * _tavalyi;
    TextInput * _suly;
    Button * _uj;
    Button * _torol;
    Button * _reset;
    List * _tetelek;
    TextBox * _ossz;
    TextBox * _szurt;
    List * _szur;
    TextBox * _rendt;
    List * _rend;
public:
    VizsgApp() : Application(white, 550, 400) {
        gout.load_font(fontfile, fontsize);

        _nevt = new TextBox(this, 20, 20, "Név:");
        _nev = new TextInput(this, 60, 20, 200, 25);
        _egyseg = new TextInput(this, 270, 20, 40, 25);
        vector<string> vtmp = {"élelmiszer","pipere","stb"};
        _kat = new List(this, 330, 20, 150, 25, 100, vtmp, fontfile, fontsize);
        _suly = new TextInput(this, 240, 50, 90, 25);
        _idei = new NumericIN(this, 20, 50, 100, 25, 0, 100000);
        _tavalyi = new NumericIN(this, 130, 50, 100, 25, 0, 100000);
        _uj = new Button(this, 350, 50, 130, 25, "Új/Módosít", [=](){if(!_nev->getText().empty() and !_egyseg->getText().empty() and validSuly() and _kat->getSelected() != -1){ujTetel();frissitTetelek();osszegzes();}}, fontfile, fontsize, grey, black);
        _torol = new Button(this, 350, 80, 60, 25, "Töröl", [=](){if(_tetelek->getSelected() != -1){torolTetel();frissitTetelek();osszegzes();}}, fontfile, fontsize, grey, black);
        _reset = new Button(this, 420, 80, 60, 25, "Reset", [=](){resetTetel();frissitTetelek();osszegzes();}, fontfile, fontsize, grey, black);
        _tetelek = new List(this, 20, 80, 300, 25, 280, vector<string>(0), fontfile, fontsize);
        _ossz = new TextBox(this, 20, 120, "Nincs adat");
        _szurt = new TextBox(this, 250, 154, "Szűrés:");
        vector<string> vtmp2 = {"Nincs"};
        for (string s : vtmp) {vtmp2.push_back(s);}
        _szur = new List(this, 330, 150, 150, 25, 100, vtmp2, fontfile, fontsize, [=](){frissitTetelek();});
        vector<string> vtmp3 = {"Eredeti","ABC","Drágulás"};
        _rendt = new TextBox(this, 250, 184, "Rendezés:");
        _rend = new List(this, 330, 180, 150, 25, 100, vtmp3, fontfile, fontsize, [=](){frissitTetelek();});

        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }
    void action(genv::event) override {}
    bool validSuly() {
        if (!_suly->getText().empty()) {
            stringstream ss;
            ss << _suly->getText();
            double tmp;
            ss >> tmp;
            if (tmp > 0) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    void szures() {
        teteleks.clear();
        if (_szur->getSelected() == -1 or _szur->getValue() == "Nincs") {
            teteleks = tetelek;
        } else {
            for (Tetel t : tetelek) {
                if (t.kategoria == _szur->getValue()) {
                    teteleks.push_back(t);
                }
            }
        }
    }
    void rendezes() {
        if (_rend->getValue() == "ABC") {
            int tetsize = teteleks.size();
            for (int i = 0; i < tetsize - 1; i++) {
                for (int j = 0; j < tetsize - 1 - i; j++) {
                    if (teteleks[j].nev > teteleks[j+1].nev) {
                        Tetel tmpt = teteleks[j+1];
                        teteleks[j+1] = teteleks[j];
                        teteleks[j] = tmpt;
                    }
                }
            }
        } else if (_rend->getValue() == "Drágulás") {
            int tetsize = teteleks.size();
            for (int i = 0; i < tetsize - 1; i++) {
                for (int j = 0; j < tetsize - 1 - i; j++) {
                    if (teteleks[j].idei - teteleks[j].tavalyi > teteleks[j+1].idei - teteleks[j+1].tavalyi) {
                        Tetel tmpt = teteleks[j+1];
                        teteleks[j+1] = teteleks[j];
                        teteleks[j] = tmpt;
                    }
                }
            }
        }
    }
    void ujTetel() {
        stringstream ss;
        ss << _suly->getText();
        double tmp;
        ss >> tmp;
        size_t i = 0;
        while (i < tetelek.size() and tetelek[i].nev != _nev->getText()) {i++;}
        if (i == tetelek.size()) {
            tetelek.push_back(Tetel(tetelek.size(), _nev->getText(), _egyseg->getText(), _kat->getValue(), _idei->getValue(), _tavalyi->getValue(), tmp));
        } else {
            tetelek[i].egyseg = _egyseg->getText();
            tetelek[i].idei = _idei->getValue();
            tetelek[i].tavalyi = _tavalyi->getValue();
            tetelek[i].suly = tmp;
            tetelek[i].kategoria = _kat->getValue();
        }
    }
    void frissitTetelek() {
        szures();
        rendezes();
        _tetelek->update(tetelek2string(teteleks));
    }
    void torolTetel() {
        tetelek.erase(tetelek.begin() + teteleks[_tetelek->getSelected()]._id);
        for (size_t i = 0; i < tetelek.size(); i++) {
            tetelek[i]._id = i;
        }
    }
    void resetTetel() {
        tetelek.clear();
    }
    void osszegzes() {
        if (tetelek.size()) {
            double regi = 0, uj = 0;
            for (Tetel t : tetelek) {
                regi += t.tavalyi * t.suly;
                uj += t.idei * t.suly;
            }
            double valtozas = (uj - regi) / regi * 100;
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