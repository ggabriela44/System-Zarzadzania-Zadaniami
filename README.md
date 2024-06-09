### Dokumentacja Systemu Zarządzania Zadaniami "TOo-Da-lOo"

#### Opis projektu

System Zarządzania Zadaniami to aplikacja konsolowa umożliwiająca dodawanie, edytowanie oraz usuwanie zadań. Głównym celem projektu było zrozumienie i praktyczne zastosowanie technik programistycznych, takich jak dziedziczenie, polimorfizm oraz wzorce projektowe. Projekt wykorzystuje wzorce Singleton oraz Observer do zarządzania listą zadań oraz powiadamiania o zmianach w zadaniach. Dodatkowo, użycie biblioteki STL (Standard Template Library) zwiększa czytelność, elastyczność oraz efektywność kodu.

#### Struktura kodu

Kod został podzielony na kilka klas:

- `Zadanie`: Reprezentuje pojedyncze zadanie, przechowując jego identyfikator oraz opis.
- `Obserwator`: Interfejs dla obserwatorów, którzy będą powiadamiani o zmianach w liście zadań.
- `MenedżerZadań`: Klasa zarządzająca zadaniami, zaimplementowana jako Singleton.
- `WypisywaczListyZadań`: Klasa obserwatora, która wypisuje listę zadań na konsolę.

#### Wzorce projektowe

W projekcie zastosowano dwa wzorce projektowe: Singleton oraz Observer.

##### Singleton

Wzorzec Singleton został zastosowany w klasie `MenedżerZadań`, aby zapewnić, że istnieje tylko jedna instancja tej klasy w całym programie. Singleton umożliwia centralne zarządzanie zadaniami i zapewnia, że wszyscy klienci korzystają z tej samej instancji menedżera zadań. Implementacja Singletona polega na zdefiniowaniu prywatnego konstruktora oraz statycznej metody `pobierzInstancje`, która zwraca referencję do jedynej instancji klasy. Dzięki temu mamy pewność, że żaden inny fragment kodu nie utworzy dodatkowej instancji tej klasy, co mogłoby prowadzić do niespójności danych.

```cpp
class MenedżerZadań {
public:
    static MenedżerZadań& pobierzInstancje() {
        static MenedżerZadań instancja;
        return instancja;
    }

private:
    MenedżerZadań() {}
    MenedżerZadań(const MenedżerZadań&) = delete;
    MenedżerZadań& operator=(const MenedżerZadań&) = delete;
};
```

##### Observer

Wzorzec Observer został zastosowany w celu powiadamiania zainteresowanych obiektów (obserwatorów) o zmianach w stanie menedżera zadań. Klasa `Obserwator` definiuje interfejs z metodą `aktualizuj`, którą muszą zaimplementować wszystkie klasy dziedziczące. Klasa `MenedżerZadań` przechowuje listę obserwatorów i zapewnia metody do dodawania obserwatorów oraz powiadamiania ich o zmianach. Za każdym razem, gdy lista zadań jest modyfikowana (dodawanie, edytowanie, usuwanie zadania), menedżer zadań wywołuje metodę `powiadomObserwatorow`, która z kolei wywołuje metodę `aktualizuj` każdego obserwatora.

```cpp
class Obserwator {
public:
    virtual void aktualizuj() = 0;
};

class MenedżerZadań {
public:
    void dodajObserwatora(Obserwator* obserwator) {
        obserwatorzy.push_back(obserwator);
    }

    void powiadomObserwatorow() {
        for (Obserwator* obserwator : obserwatorzy) {
            obserwator->aktualizuj();
        }
    }

private:
    std::vector<Obserwator*> obserwatorzy;
};
```

##### Polimorfizm

Polimorfizm jest realizowany przez wirtualne metody w interfejsie `Obserwator`. Klasa `WypisywaczListyZadań` dziedziczy po `Obserwator` i nadpisuje metodę `aktualizuj`, dzięki czemu może być powiadamiana o zmianach w liście zadań i wypisywać je na konsolę. Mechanizm ten pozwala na elastyczne dodawanie nowych typów obserwatorów bez konieczności modyfikacji kodu menedżera zadań.

```cpp
class WypisywaczListyZadań : public Obserwator {
public:
    void aktualizuj() override {
        const vector<Zadanie>& zadania = MenedżerZadań::pobierzInstancje().pobierzZadania();
        cout << "Aktualne zadania:\n";
        for (const Zadanie& zadanie : zadania) {
            cout << "ID: " << zadanie.pobierzId() << ", Opis: " << zadanie.pobierzOpis() << '\n';
        }
        cout << '\n';
    }
};
```

##### Biblioteka STL

W projekcie intensywnie korzystano z biblioteki STL, w szczególności z kontenera `vector` do przechowywania zadań oraz obserwatorów. Używane są również algorytmy STL, takie jak `find_if` oraz `remove_if`, aby uprościć operacje na wektorach. Dzięki STL kod jest bardziej czytelny i efektywny, co ułatwia zarządzanie dynamicznymi listami obiektów.

```cpp
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class MenedżerZadań {
private:
    vector<Zadanie> zadania;
    vector<Obserwator*> obserwatorzy;
};
```

#### Podsumowanie

System Zarządzania Zadaniami jest przykładem dobrze zaprojektowanej aplikacji wykorzystującej zaawansowane techniki programistyczne, takie jak wzorce projektowe, polimorfizm oraz biblioteka STL. Wzorce Singleton i Observer zapewniają efektywne zarządzanie zadaniami oraz powiadamianie o ich zmianach, co jest kluczowe dla wielu aplikacji. Dzięki temu projektowi użytkownik może zrozumieć i zastosować te techniki w praktycznych scenariuszach programistycznych.
