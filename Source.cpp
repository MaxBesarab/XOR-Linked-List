#include <iostream>
using namespace std;


struct Wezel {
    int wartosc;
    int xorAdrSasiadow;
};

struct AktualnyWezel {
    Wezel* aktWezel;
    Wezel* poprzednik;
    Wezel* nastepnik;
};

struct Lista {
    Wezel* poczatek;
    Wezel* koniec;
    AktualnyWezel aktWskaznik;
};


//enum komendy {
//    ACTUAL, ADD_BEG, ADD_END, ADD_ACT, NEXT, PREV, DEL_BEG, DEL_END,
//    DEL_VAL, DEL_ACT, PRINT_FORWARD, PRINT_BACKWARD
//};


// ACTUAL
void drukujAktualnyElement(Lista* lista) {
    if (lista->poczatek == NULL)
        cout << "NULL" << endl;
    else
        cout << lista->aktWskaznik.aktWezel->wartosc << endl;
}


Wezel* wyznaczAdresSasiada(Wezel* innySasiad, Wezel* aktWezel) {
    int adres = (int)innySasiad xor aktWezel->xorAdrSasiadow;
    return (Wezel*)adres;
}


// NEXT
void drukujWartoscNastepnika(Lista* lista) {
    if (lista->poczatek == NULL) {
        cout << "NULL" << endl;
        return;

    }
    if (lista->aktWskaznik.aktWezel == lista->koniec) {
        cout << lista->poczatek->wartosc << endl;

        // przestawiamy aktWskaznik na nastepny element
        lista->aktWskaznik.aktWezel = lista->poczatek;
        lista->aktWskaznik.poprzednik = NULL;
        lista->aktWskaznik.nastepnik = wyznaczAdresSasiada(lista->aktWskaznik.poprzednik, lista->aktWskaznik.aktWezel);

    }
    else {
        cout << lista->aktWskaznik.nastepnik->wartosc << endl;

        // przestawiamy aktWskaznik na nastepny element
        lista->aktWskaznik.poprzednik = lista->aktWskaznik.aktWezel;
        lista->aktWskaznik.aktWezel = lista->aktWskaznik.nastepnik;
        lista->aktWskaznik.nastepnik = wyznaczAdresSasiada(lista->aktWskaznik.poprzednik, lista->aktWskaznik.aktWezel);

    }
}


// PREV 
void drukujWartoscPoprzednika(Lista* lista) {
    if (lista->poczatek == NULL) {
        cout << "NULL" << endl;
        return;

    }
    if (lista->aktWskaznik.aktWezel == lista->poczatek) {
        cout << lista->koniec->wartosc << endl;

        // przestawiamy aktWskaznik na poprzedni element
        lista->aktWskaznik.aktWezel = lista->koniec;
        lista->aktWskaznik.nastepnik = NULL;
        lista->aktWskaznik.poprzednik = wyznaczAdresSasiada(lista->aktWskaznik.nastepnik, lista->aktWskaznik.aktWezel);

    }
    else {
        cout << lista->aktWskaznik.poprzednik->wartosc << endl;

        // przestawiamy aktWskaznik na poprzedni element
        lista->aktWskaznik.nastepnik = lista->aktWskaznik.aktWezel;
        lista->aktWskaznik.aktWezel = lista->aktWskaznik.poprzednik;
        lista->aktWskaznik.poprzednik = wyznaczAdresSasiada(lista->aktWskaznik.nastepnik, lista->aktWskaznik.aktWezel);

    }
}


// ADD_BEG N 
void dodajNaPoczatek(Lista* lista, int n) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;
    if (lista->poczatek == NULL) {
        lista->poczatek = lista->koniec = nowyElem;
        lista->poczatek->xorAdrSasiadow = lista->koniec->xorAdrSasiadow = NULL;
        lista->aktWskaznik.aktWezel = lista->poczatek;

    }
    else {

        if (lista->poczatek == lista->koniec) { // lista ma tylko 1 wezel
            lista->koniec->xorAdrSasiadow = NULL xor (int)nowyElem;
            lista->poczatek = nowyElem;
            lista->poczatek->xorAdrSasiadow = (int)lista->koniec xor NULL;

        }
        else {
            lista->poczatek->xorAdrSasiadow = lista->poczatek->xorAdrSasiadow xor (int)nowyElem;
            nowyElem->xorAdrSasiadow = NULL xor (int)lista->poczatek;
            lista->poczatek = nowyElem;

        }

        if (lista->aktWskaznik.poprzednik == NULL)
            lista->aktWskaznik.poprzednik = nowyElem;

    }
}


// ADD_END N
void dodajNaKoniec(Lista* lista, int n) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;

    if (lista->koniec == NULL) {
        lista->poczatek = lista->koniec = nowyElem;
        lista->poczatek->xorAdrSasiadow = lista->koniec->xorAdrSasiadow = NULL;
        lista->aktWskaznik.aktWezel = lista->poczatek;

    }
    else {
        if (lista->koniec == lista->poczatek) { //lista ma 1 wezel
            lista->poczatek->xorAdrSasiadow = NULL xor (int)nowyElem;
            lista->koniec = nowyElem;
            lista->koniec->xorAdrSasiadow = (int)lista->poczatek xor NULL;

        }
        else {
            lista->koniec->xorAdrSasiadow = lista->koniec->xorAdrSasiadow xor (int)nowyElem;
            nowyElem->xorAdrSasiadow = NULL xor (int)lista->koniec;
            lista->koniec = nowyElem;

        }

        if (lista->aktWskaznik.nastepnik == NULL)
            lista->aktWskaznik.nastepnik = nowyElem;

    }
}


// ADD_ACT N
void dodajPoprzednikAktualnego(Lista* lista, int n) {
    Wezel* nowyElem = new Wezel;
    nowyElem->wartosc = n;
    nowyElem->xorAdrSasiadow = (int)lista->aktWskaznik.aktWezel xor (int)lista->aktWskaznik.poprzednik;

    // zmieniamy xorAdrSasiadow w aktWezel i jego poprzedniku,
    // bo bedziemy miedzy nimi wstawiac nowyElem
    if (lista->aktWskaznik.poprzednik == NULL) { //poczatek listy
        lista->aktWskaznik.aktWezel->xorAdrSasiadow = (int)lista->aktWskaznik.nastepnik xor (int)nowyElem;
        lista->poczatek = nowyElem;

    }
    else {
        Wezel* poprzednikPoprzednika = wyznaczAdresSasiada(lista->aktWskaznik.aktWezel, lista->aktWskaznik.poprzednik);
        lista->aktWskaznik.poprzednik->xorAdrSasiadow = (int)poprzednikPoprzednika xor (int)nowyElem;
        lista->aktWskaznik.aktWezel->xorAdrSasiadow = (int)lista->aktWskaznik.nastepnik xor (int)nowyElem;

        lista->aktWskaznik.poprzednik = nowyElem;

    }
}


// DEL_BEG
void usunPierwszyElement(Lista* lista) {
    Wezel* doUsuniecia = lista->poczatek;

    if (lista->poczatek == NULL)
        return;
    else if (lista->poczatek == lista->koniec) { // mamy tylko 1 element
        lista->poczatek = lista->koniec = NULL;
        lista->aktWskaznik.aktWezel = NULL;
        lista->aktWskaznik.nastepnik = NULL;
        lista->aktWskaznik.poprzednik = NULL;
        delete doUsuniecia;

    }
    else {
        Wezel* nowyPoczatek = wyznaczAdresSasiada(NULL, lista->poczatek);

        // musimy zaktualizowac xorAdrSasiadow w nowym poczatku 
        // (lewy sasiad staje sie NULL)
        Wezel* nastepnikNowegoPoczatku = wyznaczAdresSasiada(lista->poczatek, nowyPoczatek);
        nowyPoczatek->xorAdrSasiadow = NULL xor (int)nastepnikNowegoPoczatku;

        lista->poczatek = nowyPoczatek;
        if (doUsuniecia == lista->aktWskaznik.aktWezel) {
            lista->aktWskaznik.aktWezel = lista->koniec;
            lista->aktWskaznik.nastepnik = NULL;
            lista->aktWskaznik.poprzednik = wyznaczAdresSasiada(NULL, lista->aktWskaznik.aktWezel);

        }
        delete doUsuniecia;

    }
}


// DEL_END
void usunOstatniElement(Lista* lista) {
    Wezel* doUsuniecia = lista->koniec;

    if (lista->koniec == NULL)
        return;
    else if (lista->poczatek == lista->koniec) { // mamy tylko 1 element
        lista->poczatek = lista->koniec = NULL;
        lista->aktWskaznik.aktWezel = NULL;
        lista->aktWskaznik.nastepnik = NULL;
        lista->aktWskaznik.poprzednik = NULL;
        delete doUsuniecia;

    }
    else {
        Wezel* nowyKoniec = wyznaczAdresSasiada(NULL, lista->koniec);

        // musimy zaktualizowac xorAdrSasiadow w nowym koncu 
        // (prawy sasiad staje sie NULL)
        Wezel* poprzednikNowegoKonca = wyznaczAdresSasiada(lista->koniec, nowyKoniec);
        nowyKoniec->xorAdrSasiadow = NULL xor (int)poprzednikNowegoKonca;

        lista->koniec = nowyKoniec;
        if (doUsuniecia == lista->aktWskaznik.aktWezel) {
            lista->aktWskaznik.aktWezel = nowyKoniec;
            lista->aktWskaznik.nastepnik = NULL;
            lista->aktWskaznik.poprzednik = wyznaczAdresSasiada(NULL, lista->aktWskaznik.aktWezel);

        }
        delete doUsuniecia;

    }
}


void usunWezel(Lista* lista, Wezel* poprzednik, Wezel* usuwanyWezel) {
    if (usuwanyWezel == lista->poczatek)
        usunPierwszyElement(lista);
    else if (usuwanyWezel == lista->koniec)
        usunOstatniElement(lista);
    else {
        if (lista->aktWskaznik.aktWezel == usuwanyWezel) {
            // przestawiamy ACTUAL na poprzedni wezel
            lista->aktWskaznik.nastepnik = lista->aktWskaznik.aktWezel;
            lista->aktWskaznik.aktWezel = poprzednik;
            lista->aktWskaznik.poprzednik = wyznaczAdresSasiada(lista->aktWskaznik.nastepnik, lista->aktWskaznik.aktWezel);

        }
        //musimy zaktualizowac xorAdrSasiadow w sasiednich wezlach
        Wezel* nastepnik = wyznaczAdresSasiada(poprzednik, usuwanyWezel);
        Wezel* nastepnikNastepnika = wyznaczAdresSasiada(usuwanyWezel, nastepnik);
        nastepnik->xorAdrSasiadow = (int)nastepnikNastepnika xor (int)poprzednik;

        Wezel* poprzednikPoprzednika = wyznaczAdresSasiada(usuwanyWezel, poprzednik);
        poprzednik->xorAdrSasiadow = (int)poprzednikPoprzednika xor (int)nastepnik;

        delete usuwanyWezel;

    }
}


// DEL_VAL N
void usunWezlyZDanejLiczba(Lista* lista, int n) {
    if (lista->poczatek == NULL)
        return;
    else {
        Wezel* doSprawdzenia;
        doSprawdzenia = lista->poczatek;
        Wezel* poprzedni = NULL;
        if (lista->poczatek == lista->koniec) {
            if (doSprawdzenia->wartosc == n)
                usunWezel(lista, poprzedni, doSprawdzenia);
            return;

        }
        else {
            Wezel* nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);
            while (doSprawdzenia != lista->koniec) {
                if (doSprawdzenia->wartosc == n) {
                    usunWezel(lista, poprzedni, doSprawdzenia);
                    doSprawdzenia = nastepny;
                    nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);
                    // poprzedni zostaje poprzednim

                }
                else {
                    poprzedni = doSprawdzenia;
                    doSprawdzenia = nastepny;
                    nastepny = wyznaczAdresSasiada(poprzedni, doSprawdzenia);

                }

            }
            if (lista->koniec->wartosc == n)
                usunOstatniElement(lista);
            return;

        }

    }
}


// DEL_ACT
void usunAktualnyElement(Lista* lista) {
    if (lista->poczatek == NULL)
        return;
    else
        usunWezel(lista, lista->aktWskaznik.poprzednik, lista->aktWskaznik.aktWezel);
}


void drukujOdPoczatku(Lista* lista) {
    if (lista->poczatek == NULL)
        cout << "NULL" << endl;
    else if (lista->poczatek == lista->koniec)
        cout << lista->poczatek->wartosc << endl;
    else {
        Wezel* poprzedni = NULL;
        Wezel* drukowany = lista->poczatek;
        Wezel* nastepny = wyznaczAdresSasiada(poprzedni, drukowany);
        while (drukowany != lista->koniec) {
            cout << drukowany->wartosc << " ";
            poprzedni = drukowany;
            drukowany = nastepny;
            nastepny = wyznaczAdresSasiada(poprzedni, drukowany);

        }
        cout << lista->koniec->wartosc << endl;

    }
}


void drukujOdKonca(Lista* lista) {
    if (lista->koniec == NULL)
        cout << "NULL" << endl;
    else if (lista->poczatek == lista->koniec)
        cout << lista->koniec->wartosc << endl;
    else {
        Wezel* poprzedni = NULL;
        Wezel* drukowany = lista->koniec;
        Wezel* nastepny = wyznaczAdresSasiada(poprzedni, drukowany);
        while (drukowany != lista->poczatek) {
            cout << drukowany->wartosc << " ";
            poprzedni = drukowany;
            drukowany = nastepny;
            nastepny = wyznaczAdresSasiada(poprzedni, drukowany);

        }
        cout << lista->poczatek->wartosc << endl;

    }
}


bool porownajString(char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] == s2[i]) {
            i++;

        }
        else
            return false;

    }
    return true;
}


void wyznaczKomende(char* komenda, Lista* lista) {
    int n;

    if (porownajString(komenda, "ACTUAL")) {
        drukujAktualnyElement(lista);

    }
    else if (porownajString(komenda, "NEXT")) {
        drukujWartoscNastepnika(lista);

    }
    else if (porownajString(komenda, "PREV")) {
        drukujWartoscPoprzednika(lista);

    }
    else if (porownajString(komenda, "ADD_BEG")) {
        cin >> n;
        dodajNaPoczatek(lista, n);

    }
    else if (porownajString(komenda, "ADD_END")) {
        cin >> n;
        dodajNaKoniec(lista, n);

    }
    else if (porownajString(komenda, "ADD_ACT")) {
        cin >> n;
        dodajPoprzednikAktualnego(lista, n);

    }
    else if (porownajString(komenda, "DEL_BEG")) {
        usunPierwszyElement(lista);

    }
    else if (porownajString(komenda, "DEL_END")) {
        usunOstatniElement(lista);

    }
    else if (porownajString(komenda, "DEL_VAL")) {
        cin >> n;
        usunWezlyZDanejLiczba(lista, n);

    }
    else if (porownajString(komenda, "DEL_ACT")) {
        usunAktualnyElement(lista);

    }
    else if (porownajString(komenda, "PRINT_FORWARD")) {
        drukujOdPoczatku(lista);

    }
    else {
        drukujOdKonca(lista);

    }
}


void wyczyscListe(Lista* lista) {
    while (lista->poczatek != lista->koniec)
        usunPierwszyElement(lista);
    usunPierwszyElement(lista);
}


int main()
{
    char komenda[15];
    Lista lista;
    lista.poczatek = lista.koniec = NULL;
    lista.aktWskaznik.aktWezel = lista.poczatek;
    lista.aktWskaznik.nastepnik = lista.aktWskaznik.poprzednik = NULL;

    while (cin >> komenda) {
        wyznaczKomende(komenda, &lista);

    }

    if (lista.poczatek != NULL)
        wyczyscListe(&lista);

    return 0;
}