#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <functional>
using namespace std;

struct player {
    string name;
    int score;
};

struct GreaterComparator {
    template<typename T>
    bool operator()(const T& lhs, const T& rhs) const {
        return lhs > rhs;
    }
};

class kartuves {
protected:
    vector<string> zodziai;
    vector<string> newzodziai;
    string SlaptasZodis;
    string AtspetasZodis;
    int BandymuSkaicius;
    int LikeBandymai;
    vector<char> IsbandytosRaides;
    int hintIndex;
    int points = 0;
    int index = 0;
    int x, n;
    string uzuomina;

public:
    kartuves() {
        ifstream is;
        is.open("wordlist.txt");
        string line;
        while (!is.fail()) {
            is >> line;
            zodziai.push_back(line);
        }
        is.close();
        BandymuSkaicius = 6;
        LikeBandymai = BandymuSkaicius;

    }
    ~kartuves() {}

    void sudetingumas(int n) {
        int temp = 0;
        for (int i = 0; i < zodziai.size(); i++) {
            if (n == 1 && zodziai[i].length() <= 6) {
                temp++;
                newzodziai.push_back(zodziai[i]);
            }
            if (n == 2 && zodziai[i].length() <= 10 && zodziai[i].length() > 6) {
                temp++;
                newzodziai.push_back(zodziai[i]);
            }
            if (n == 3 && zodziai[i].length() <= 20 && zodziai[i].length() > 10) {
                temp++;
                newzodziai.push_back(zodziai[i]);
            }
        }

        srand(time(NULL));
        hintIndex = rand() % temp;
        SlaptasZodis = newzodziai[hintIndex];
        for (int i = 0; i < zodziai.size(); i++) {
            if (SlaptasZodis == zodziai[i]) {
                index = i;
            }
        }
        AtspetasZodis = string(SlaptasZodis.length(), '_');

    }
    void display() {
        cout << "--------" << endl;
        cout << "|      |" << endl;

        if (LikeBandymai < BandymuSkaicius)
            cout << "|      O" << endl;
        else
            cout << "|      " << endl;

        if (LikeBandymai <= BandymuSkaicius - 2)
            cout << "|     /";
        else
            cout << "|      ";

        if (LikeBandymai <= BandymuSkaicius - 3)
            cout << "|";
        else
            cout << " ";

        if (LikeBandymai <= BandymuSkaicius - 4)
            cout << "\\" << endl;
        else
            cout << " " << endl;

        if (LikeBandymai <= BandymuSkaicius - 5)
            cout << "|     /";
        else
            cout << "|      ";

        if (LikeBandymai <= BandymuSkaicius - 6)
            cout << "\\";
        else
            cout << " ";

        cout << endl;
        cout << "|" << endl;
        cout << "|" << endl;
        cout << "================" << endl;
    }
    void rodytiZodi() {
        cout << "ZODIS: " << AtspetasZodis << endl;
    }


    void PabandytosRaides() {
        cout << "Jusu isbandytos raides: ";
        for (int i = 0; i < IsbandytosRaides.size(); i++) {
            cout << IsbandytosRaides[i] << " ";
        }
        cout << endl;
    }
    bool GameOver() {
        return LikeBandymai == 0 || AtspetasZodis == SlaptasZodis;
    }
    void Spelione(char letter) {
        int index;
        if (IsbandytosRaides.empty() || find(IsbandytosRaides.begin(), IsbandytosRaides.end(), letter) == IsbandytosRaides.end()) {
            IsbandytosRaides.push_back(letter);
            index = SlaptasZodis.find(letter);
            if (index != string::npos) {
                points++;
                while (index != string::npos) {
                    AtspetasZodis[index] = letter;
                    index = SlaptasZodis.find(letter, index + 1);
                }
            }
            else {
                LikeBandymai--;
            }
        }
    }
    void taskai() {    
        cout << "JUSU TASKAI: [" << points << "]" << endl << endl;
    }
    void hint() {
        cout << "UZUOMINA: ";
        if (index < 22) {
            uzuomina = "GYVUNAI";
        }
        else if (index > 21 && index < 30) {
            uzuomina = "OOP PROGRAMAVIMAS";
        }
        else if (index > 31 && index <= 41) {
            uzuomina = "LIETUVOS MEDZIAI";
        }
        cout << uzuomina;
        cout << endl;
    }

    int get_LikeBandymai() {
        return LikeBandymai;
    }
    string get_SlaptasZodis() {
        return SlaptasZodis;
    }
    int zaisti_single() {
        cout << "Pasirinkite zaidimo sudetinguma: " << endl << "1) Lengvas" << endl << "2) Vidutinis" << endl << "3) Sunkus" << endl << "Jusu pasirinkimas: ";
        int n;
        cin >> n;
        sudetingumas(n);
        system("cls");
        LikeBandymai = 6;
        while (!GameOver()) {
            cout << "Kartuves" << endl;
            taskai();
            display();
            rodytiZodi();
            PabandytosRaides();
            hint();
            cout << "IRASYKITE RAIDE: ";
            char letter;
            cin >> letter;
            Spelione(letter);
            hint();
            system("cls");
        }
        if (get_LikeBandymai() == 0) {
            cout << "=====================[JUS PRALAIMEJOTE!]=====================" << endl << "ZODIS BUVO: " << get_SlaptasZodis() << endl;

        }
        else {
            cout << "=====================[JUS LAIMEJOTE!]========================" << endl;
        }
        ofstream os;
        os.open("osuser.txt", ofstream::app);
        os << points << " ";
        return n;
    }

};

class multiplayer :public kartuves
{

public:
    multiplayer() {}
    void multi() {
        cout << "Pasirinkite zaidima: " << endl << "1) Singleplayer" << endl << "2) Multiplayer" << endl << "Jusu pasirinkimas: ";
        int x;
        cin >> x;
        system("cls");
        if (x == 1) {
            zaisti_single();
        }
        if (x == 2) {
            temp();
            zaisti_multi();
        }
        if (x != 1 && x != 2) {
            cout << "Ivedete bloga pasirinkima!";
        }
    }
    void temp() {
        cout << "Iveskite zodi, kuri norite kad speliotu jusu priesininkas: ";
        cin >> SlaptasZodis;
        system("cls");
        cout << "Iveskite uzuomina: ";
        getline(cin >> ws, uzuomina);
        AtspetasZodis = string(SlaptasZodis.length(), '_');
    }
    void hint() {
        cout << "UZUOMINA: " << uzuomina << endl;
    }
    void zaisti_multi() {
        while (!GameOver()) {
            cout << "Kartuves" << endl;
            taskai();
            display();
            rodytiZodi();
            PabandytosRaides();
            hint();
            cout << "IRASYKITE RAIDE: ";
            char letter;
            cin >> letter;
            Spelione(letter);
            system("cls");

        }
        if (get_LikeBandymai() == 0) {
            cout << "=====================[JUS PRALAIMEJOTE!]=====================" << endl << "ZODIS BUVO: " << get_SlaptasZodis() << endl;

        }
        else {

            cout << "=====================[JUS LAIMEJOTE!]========================" << endl;
        }

        ofstream os;
        os.open("osuser.txt", ofstream::app);
        os << points << " ";
    }

};
class highscores {
private:
    string get_vardas;
    int get_balai;
    vector <player> play;
    player temp;
    vector <pair<string, int>> vect;
    map <string, int, GreaterComparator> balai;
    int points = 0;
public:
    highscores() {}
    ~highscores() {}
    void out_to_file(string vardas) {
        ofstream os;
        os.open("osuser.txt", ofstream::app);
        os << vardas << " ";
        os.close();

    }
    void user() {
        ifstream is;
        string line;
        is.open("osuser.txt");
        int value;
        while (getline(is, line)) {
            istringstream iss(line);
            string str, str2;
            while (iss >> str >> value) {
                balai[str] += value;
            }
        }
        is.close();
    }
    void leaderboard() {
        vector<pair<string, int>> sortedBalai(balai.begin(), balai.end());

        sort(sortedBalai.begin(), sortedBalai.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
         });

        int i = 1;
        for (const auto& pair : sortedBalai) {
            std::cout << std::setw(25) << std::left << i;
            std::cout << std::setw(27) << std::left << pair.first;
            std::cout << std::setw(25) << std::left << pair.second << std::endl;
            i++;
        }
    }
    void print_leaderboard() {
        cout << endl << "======================LEADERBOARD'AS=========================" << endl;
        cout << "=============================================================" << endl;
        cout << setw(25) << left << "RANKAS";
        cout << setw(25) << left << "VARDAS";
        cout << setw(25) << left << "TASKAI" << endl;
        cout << "=============================================================" << endl;

        
    }

};
int main() {
    highscores hs;
    kartuves kartuves;
    multiplayer ch;
    //hs.leaderboard();
    string vardas, slaptazodis;
    cout << "Iveskite savo varda, kuri veliau naudosite prisijungimui: ";
    cin >> vardas;

    hs.out_to_file(vardas);

    ch.multi();

    hs.user();
    hs.print_leaderboard();
    hs.leaderboard();
   
    return 0;

}
