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

enum Rendezes {AR, ID};

struct Tetelek {
    string nev;
    int ar, id;
    Tetelek(string neve, int ara, int sorrend) : nev(neve), ar(ara), id(sorrend) {}
};

ostream& operator<< (ostream& ki, Tetelek t) {
    return ki << t.nev << ": " << t.ar << " Ft";
}

vector<string> tetelek2string(const vector<Tetelek>& vt) {
    vector<string> v;
    for (const Tetelek& t : vt) {
        stringstream ss;
        ss << t;
        v.push_back(ss.str());
    }
    return v;
}

class BpV8 : public Application {
    Rendezes rend;
    TextInput * nev;
    NumericIN * ar;
    Button * hozzaad;
    Button * vissza;
    Button * modosit;
    Button * torol;
    List * termekek;
    TextBox * egyenleg;
    vector<Tetelek> tetel;
    vector<Tetelek> rtetel;
    TextBox * fajlszoveg;
    TextInput * fajlnev;
    Button * betolt;
    Button * kiment;
    List * rendezo;
    Button * rendezob;
public:
    BpV8() : Application(white, 550, 400) {
        gout.load_font(fontfile, 15);
        rend = ID;

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

        vector<string> tmplist(2);
        tmplist[0] = "Eredeti";
        tmplist[1] = "Ár szerint";
        rendezo = new List(this, _window_width - 120, 20, 100, 25, 100, tmplist, fontfile, 15);
        rendezob = new Button(this, _window_width - 110, 55, 90, 25, "Rendezés", [=](){atrendez();}, fontfile, 15, grey, black);

        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }
    void action(event) override {}
    void egyenlegFrissit() {
        int c = 0;
        for (const Tetelek& t : tetel) {
            c += t.ar;
        }
        stringstream ss;
        ss << "Egyenleg: "<< c << " Ft";
        egyenleg->update(ss.str());
    }
    void arRendez() {
        rtetel = tetel;
        for (size_t i = 0; i < rtetel.size() - 1; i++) {
            for (size_t j = 0; j < rtetel.size() - 1 - i; j++) {
                if (rtetel[j + 1].ar > rtetel[j].ar) {
                    Tetelek tmp = rtetel[j + 1];
                    rtetel[j + 1] = rtetel[j];
                    rtetel[j] = tmp;
                }
            }
        }
    }
    void idRendez() {
        rtetel = tetel;
    }
    void listFrissit() {
        if (rend == ID) {
            idRendez();
        } else if (rend == AR) {
            arRendez();
        }
        termekek->update(tetelek2string(rtetel));
    }
    void atrendez() {
        if (rendezo->getSelected() == 0) {rend = ID;}
        if (rendezo->getSelected() == 1) {rend = AR;}
        if (rendezo->getSelected() != -1) {listFrissit();}
    }
    void ujTetel() {
        if (!nev->getText().empty()) {
            tetel.push_back(Tetelek(nev->getText(), ar->getValue(), tetel.size()));
            listFrissit();
            egyenlegFrissit();
        }
    }
    void torolTetel() {
        if (termekek->getSelected() != -1) {
            tetel.erase(tetel.begin() + rtetel[termekek->getSelected()].id);
            for (size_t i = 0; i < tetel.size(); i++) {
                tetel[i].id = i;
            }
            listFrissit();
            egyenlegFrissit();
        }
    }
    void mindenTorol() {
        tetel.clear();
        listFrissit();
        egyenlegFrissit();
    }
    void modositTetel() {
        if (termekek->getSelected() != -1 and !nev->getText().empty()) {
            tetel[rtetel[termekek->getSelected()].id].nev = nev->getText();
            tetel[rtetel[termekek->getSelected()].id].ar = ar->getValue();
            listFrissit();
            egyenlegFrissit();
        }
    }
    void mentes() {
        if (!fajlnev->getText().empty()) {
            ofstream kifajl(fajlnev->getText());
            for (const Tetelek& t : tetel) {
                kifajl << t << endl;
            }
            kifajl.close();
        }
    }
    void betoltes() {
        if (!fajlnev->getText().empty()) {
            ifstream befajl(fajlnev->getText());
            if (befajl.good()) {
                vector<Tetelek> vt;
                while (befajl.good()) {
                    string tmps, clrs;
                    int tmpi;
                    getline(befajl, tmps, ':') >> ws >> tmpi;
                    vt.push_back(Tetelek(tmps, tmpi, vt.size()));
                    getline(befajl, clrs) >> ws;
                }
                befajl.close();
                tetel = vt;
                listFrissit();
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