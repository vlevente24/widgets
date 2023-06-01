#include <sstream>
#include <iostream>
#include "application.hpp"
#include "list.hpp"
#include "button.hpp"
#include "textinput.hpp"

using namespace std;
using namespace genv;

const string fontfile = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color black(0, 0, 0);
const color white(255, 255, 255);
const color grey(200,200,200);

struct Car {
    Car(string brand, string stype, unsigned int id) : _brand(brand), _stype(stype), _id(id) {}
    string _brand, _stype;
    unsigned int _id;
    bool bennevan(string s) {
        return _brand.find(s) < _brand.length();
    }
};

ostream & operator<<(ostream & out, const Car & c) {
    return out << c._brand << ", " << c._stype;
}

struct Rent {
    Rent(Car c, string s) : car(c), customer(s) {}
    Car car;
    string customer;
};

ostream & operator<<(ostream & out, const Rent & r) {
    return out << r.car << ": " << r.customer;
}

template <typename T>
vector<string> tostring(vector<T> v) {
    vector<string> vs;
    for (T t : v) {
        stringstream ss;
        ss << t;
        vs.push_back(ss.str());
    }
    return vs;
}

class AutoBerles : public Application {
    List * carList;
    List * customerList;
    List * rentList;
    Button * rentCarBtn;
    Button * backCarBtn;
    vector<Car> cars;
    vector<Car> fcars;
    vector<Rent> rented;
    vector<string> customers;
    TextInput * szures;
public:
    AutoBerles() : Application(genv::color(0, 0, 0), 700, 400) {
        gout.open(_window_width, _window_height);
        gout.load_font("/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf", 15);
        gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
        cars.push_back(Car("Ferrari", "305", cars.size()));
        cars.push_back(Car("Tesla", "Model X", cars.size()));
        cars.push_back(Car("Trabant", "2", cars.size()));
        carList = new List(this, 10, 10, 200, 26, 300, tostring(cars));
        customers.push_back("Kis Miska");
        customers.push_back("Kukor Ica");
        customers.push_back("Vicc Elek");
        customerList = new List(this, 230, 10, 200, 26, 300, customers);
        rentList = new List(this, 450, 10, 200, 26, 300, vector<string>());
        rentCarBtn = new Button(this, 200, 350, 60, 30, "Rent", [=](){rent(); update();}, fontfile, 15, grey, black);
        backCarBtn = new Button(this, 300, 350, 60, 30, "Back", [=](){back(); update();}, fontfile, 15, grey, black);
        szures = new TextInput(this, 10, 350, 150, 30);
        fcars = cars;
        for (Widget * ww : _widgets) {ww->print(false);}
        gout << refresh;
    }

    void rent() {
        int icar = carList->getSelected();
        int icstmr = customerList->getSelected();
        if (icar != -1 and icstmr != -1) {
            rented.push_back(Rent(fcars[icar], customers[icstmr]));
            fcars.erase(fcars.begin() + icar);
            cars.erase(cars.begin() + fcars[icar]._id);
            for (size_t i = 0; i < cars.size(); i++) {
                cars[i]._id = i;
            }
            filter();
        }
    }
    void update() {
        carList->update(tostring(fcars));
        customerList->update(customers);
        rentList->update(tostring(rented));
    }
    void back() {
        int irented = rentList->getSelected();
        if (irented != -1) {
            fcars.push_back(rented[irented].car);
            cars.push_back(rented[irented].car);
            rented.erase(rented.begin() + irented);
            for (size_t i = 0; i < cars.size(); i++) {
                cars[i]._id = i;
            }
            filter();
        }
    }
    void filter () {
        string ss = szures->getText();
        vector<Car> vc;
        for (Car cr : cars) {
            if (cr.bennevan(ss)) {
                vc.push_back(cr);
            }
        }
        if (vc.size() != fcars.size()) {
            fcars = vc;
            carList->update(tostring(fcars));
        }
    }
    void action(genv::event ev) override {
        if (ev.type == ev_key) {
            filter();
        }
    }
};

int main() {
    AutoBerles autok;
    autok.event_loop();
    return 0;
}

// szövegbeviteli mező -> autómárka, baloldalt csak azokat jeleníti meg, amikre rászűrtünk