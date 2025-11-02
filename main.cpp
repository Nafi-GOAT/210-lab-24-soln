#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int main_menu();
void add_goat(list<Goat> &trip, string names[], string colors[]);
void delete_goat(list<Goat> &trip);
void display_trip(const list<Goat> &trip);
int select_goat (const list<Goat> &trip);

void sort_goats(list<Goat> &trip);
void find_oldest_goat(const list<Goat> &trip);
void count_color(const list<Goat> &trip);
void remove_old_goats(list<Goat> &trip);
void shuffle_goats(list<Goat> &trip);
void reverse_goats(list<Goat> &trip);
void clear_goats(list<Goat> &trip);

int main() {
    srand(time(0));
    bool again = true;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (i < SZ_NAMES && fin >> names[i]) i++;
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (i < SZ_COLORS && fin1 >> colors[i]) i++;
    fin1.close();


    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        int age = rand() % MAX_AGE;  // defined in Goat.h
        string name = names[rand() % SZ_NAMES];
        string color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(Goat(name, age, color));
    }
    
    while (again) {
        int choice = main_menu();
        cout << endl;

        switch (choice) {
            case 1: add_goat(trip, names, colors); break;
            case 2: delete_goat(trip); break;
            case 3: display_trip(trip); break;
            case 4: sort_goats(trip); break;
            case 5: find_oldest_goat(trip); break;
            case 6: count_color(trip); break;
            case 7: remove_old_goats(trip); break;
            case 8: shuffle_goats(trip); break;
            case 9: reverse_goats(trip); break;
            case 10: clear_goats(trip); break;
            case 11: again = false; break;
        }

        cout << endl;
    }

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats by name\n";
    cout << "[5] Find oldest goat\n";
    cout << "[6] Count goats by color\n";
    cout << "[7] Remove goats older than a certain age\n";
    cout << "[8] Shuffle goats\n";
    cout << "[9] Reverse order of goats\n";
    cout << "[10] Clear all goats\n";
    cout << "[11] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 11) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
        if (trip.empty()) {
        cout << "No goats to delete.\n";
        return;
    }
    int n = select_goat(trip);
    auto it = trip.begin();
    advance(it, n - 1);
    cout << "Deleting goat: ";
    it->display();
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string names[], string colors[]) {
    int age = rand() % MAX_AGE;
    string nm = names[rand() % SZ_NAMES];
    string cl = colors[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(const list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats to show.\n";
        return;
    }
    int i = 1;
    for (const Goat &g : trip) {
        cout << "[" << setw(2) << i++ << "] ";
        g.display();
    }
}


int select_goat(const list<Goat> &trip) {
    display_trip(trip);
    cout << "Select goat #: ";
    int n;
    cin >> n;
    while (n < 1 || n > trip.size()) {
        cout << "Invalid choice. Try again: ";
        cin >> n;
    }
    return n;
}
 
void sort_goats(list<Goat> &trip) {
    trip.sort([](const Goat &a, const Goat &b) {
        return a.get_name() < b.get_name();
    });
    cout << "Goats sorted by name.\n";
}

void find_oldest_goat(const list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats.\n";
        return;
    }
    auto oldest = max_element(trip.begin(), trip.end(),
        [](const Goat &a, const Goat &b) {
            return a.get_age() < b.get_age();
        });
    cout << "Oldest goat: ";
    oldest->display();
}
  
void count_color(const list<Goat> &trip) {
    string color;
    cout << "Enter color to count: ";
    cin >> color;
    int count = count_if(trip.begin(), trip.end(),
        [&](const Goat &g) { return g.get_color() == color; });
    cout << "There are " << count << " goats with color " << color << ".\n";
}

void remove_old_goats(list<Goat> &trip) {
    int age;
    cout << "Remove goats older than what age? ";
    cin >> age;
    trip.remove_if([&](const Goat &g) { return g.get_age() > age; });
    cout << "Remaining goats: " << trip.size() << endl;
}

void shuffle_goats(list<Goat> &trip) {
    vector<Goat> v(trip.begin(), trip.end());
    random_device rd;
    mt19937 g(rd());
    shuffle(v.begin(), v.end(), g);
    trip.assign(v.begin(), v.end());
    cout << "Goats shuffled.\n";
}

void reverse_goats(list<Goat> &trip) {
    trip.reverse();
    cout << "Goats reversed.\n";
}

void clear_goats(list<Goat> &trip) {
    trip.clear();
    cout << "All goats cleared.\n";
}