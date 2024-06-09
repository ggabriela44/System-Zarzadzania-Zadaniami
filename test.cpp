#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Klasa zadania
class Zadanie {
public:
    Zadanie(int id, const string& opis)
        : id(id), opis(opis) {}

    int pobierzId() const { return id; }
    string pobierzOpis() const { return opis; }
    void ustawOpis(const string& nowyOpis) { opis = nowyOpis; }

private:
    int id;
    string opis;
};

// Interfejs obserwatora
class Obserwator {
public:
    virtual void aktualizuj() = 0;
};

// Klasa zarządzająca zadaniami (Singleton)
class MenedzerZadan {
public:
    static MenedzerZadan& pobierzInstancje() {
        static MenedzerZadan instancja;
        return instancja;
    }

    void dodajZadanie(const Zadanie& zadanie) {
        zadania.push_back(zadanie);
        powiadomObserwatorow();
    }

    void edytujZadanie(int id, const string& nowyOpis) {
        auto it = find_if(zadania.begin(), zadania.end(), [id](const Zadanie& zadanie) {
            return zadanie.pobierzId() == id;
            });
        if (it != zadania.end()) {
            it->ustawOpis(nowyOpis);
            powiadomObserwatorow();
        }
        else {
            cout << "Zadanie nie znalezione.\n";
        }
    }

    void usunZadanie(int id) {
        zadania.erase(remove_if(zadania.begin(), zadania.end(), [id](const Zadanie& zadanie) {
            return zadanie.pobierzId() == id;
            }), zadania.end());
        powiadomObserwatorow();
    }

    const vector<Zadanie>& pobierzZadania() const {
        return zadania;
    }

    void dodajObserwatora(Obserwator* obserwator) {
        obserwatorzy.push_back(obserwator);
    }

    void powiadomObserwatorow() {
        for (Obserwator* obserwator : obserwatorzy) {
            obserwator->aktualizuj();
        }
    }

private:
    MenedzerZadan() {}
    MenedzerZadan(const MenedzerZadan&) = delete;
    MenedzerZadan& operator=(const MenedzerZadan&) = delete;

    vector<Zadanie> zadania;
    vector<Obserwator*> obserwatorzy;
};

// Klasa obserwatora wypisująca listę zadań
class WypisywaczListyZadan : public Obserwator {
public:
    void aktualizuj() override {
        const vector<Zadanie>& zadania = MenedzerZadan::pobierzInstancje().pobierzZadania();
        cout << "Aktualne zadania:\n";
        for (const Zadanie& zadanie : zadania) {
            cout << "ID: " << zadanie.pobierzId() << ", Opis: " << zadanie.pobierzOpis() << '\n';
        }
        cout << '\n';
    }
};

// Funkcje pomocnicze do interfejsu użytkownika
void wypiszMenu() {
    cout << "1. Dodaj Zadanie\n";
    cout << "2. Edytuj Zadanie\n";
    cout << "3. Usun Zadanie\n";
    cout << "4. Wypisz Zadania\n";
    cout << "5. Wyjdz\n";
}

void dodajZadanie() {
    int id;
    string opis;
    cout << "Podaj ID zadania: ";
    cin >> id;
    cin.ignore();
    cout << "Podaj opis zadania: ";
    getline(cin, opis);

    MenedzerZadan::pobierzInstancje().dodajZadanie(Zadanie(id, opis));
}

void edytujZadanie() {
    int id;
    string opis;
    cout << "Podaj ID zadania do edycji: ";
    cin >> id;
    cin.ignore();
    cout << "Podaj nowy opis zadania: ";
    getline(cin, opis);

    MenedzerZadan::pobierzInstancje().edytujZadanie(id, opis);
}

void usunZadanie() {
    int id;
    cout << "Podaj ID zadania do usunięcia: ";
    cin >> id;

    MenedzerZadan::pobierzInstancje().usunZadanie(id);
}

int main() {
    WypisywaczListyZadan wypisywacz;
    MenedzerZadan::pobierzInstancje().dodajObserwatora(&wypisywacz);

    while (true) {
        wypiszMenu();
        int wybor;
        cin >> wybor;
        switch (wybor) {
        case 1:
            dodajZadanie();
            break;
        case 2:
            edytujZadanie();
            break;
        case 3:
            usunZadanie();
            break;
        case 4:
            MenedzerZadan::pobierzInstancje().powiadomObserwatorow();
            break;
        case 5:
            return 0;
        default:
            cout << "Nieprawidłowy wybór.\n";
        }
    }
}
