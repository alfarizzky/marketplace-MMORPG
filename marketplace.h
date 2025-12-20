#ifndef MARKETPLACE_H_INCLUDED
#define MARKETPLACE_H_INCLUDED

#include <iostream>

using namespace std;


// CHILD (ITEM)
struct Item {
    string namaItem;
    int harga;
    bool isWeapon;
};

typedef Item infotypeChild;
typedef struct elmlistChild *addressChild;

struct elmlistChild {
    infotypeChild info;
    addressChild next;
};

// RELASI
typedef struct elmRelasi *addressRelasi;

struct elmRelasi {
    addressChild child;
    addressRelasi next;
};

// PARENT (PLAYER)
struct Player {
    string username;
    int gold;
    int totalIncome;
    int totalOutcome;
};

typedef Player infotypeParent;
typedef struct elmlistParent *addressParent;

struct elmlistParent {
    infotypeParent info;
    addressRelasi relasi;
    addressParent next;
};

// ---------- LIST ----------
struct ListParent {
    addressParent first;
};

struct ListChild {
    addressChild first;
};

// Menu
void menuPlayer();
void menuUtama();

// CREATE LIST
void createListParent(ListParent &LP);
void createListChild(ListChild &LC);

// CREATE NODE
addressParent createParent(infotypeParent data);
addressChild createChild(infotypeChild data);
addressRelasi createRelasi(addressChild C);

// INSERT
void insertParent(ListParent &LP, addressParent P);
void insertChild(ListChild &LC, addressChild C);
void insertRelasi(addressParent P, addressChild C);

// DELETE
void deleteParent(ListParent &LP, ListChild &LC, string username);
void deleteChild(ListChild &LC, addressChild C);
void deleteRelasi(addressParent P, addressChild C);

// FIND
addressParent findParent(ListParent LP, string username);
addressChild findChild(ListChild LC, string namaItem);
addressRelasi findRelasi(addressParent P, addressChild C);

// SHOW / DISPLAY
void showAllParent(ListParent LP);
void showAllChild(ListChild LC);
void showChildFromParent(addressParent P);
void showAllParentWithChild(ListParent LP);
void showAllChildWithParent(ListParent LP, ListChild LC);
void showParentFromChild(ListParent LP, addressChild C);
void showStatistikMarket(ListParent LP, ListChild LC);

// COUNT / STATISTIK
int countRelasiParent(addressParent P);
int countRelasiChild(ListParent LP, addressChild C);
int countChildWithoutRelasi(ListChild LC, ListParent LP);


// mengganti child dari parent tertentu
void editRelasi(addressParent P, addressChild oldChild, addressChild newChild);

// LOGIN
bool login(ListParent LP, string username, addressParent &currentPlayer);
void logout(addressParent &currentPlayer);

// MENU PLAYER
void infoPlayer(addressParent P);
void jualItem(ListChild &LC, addressParent P, infotypeChild dataItem);
bool beliItem(ListParent &LP, ListChild &LC, addressParent buyer, addressChild item);
void hapusItemSendiri(ListChild &LC, addressParent P, addressChild item);
void editItem(addressChild C, infotypeChild newData);

// SEARCH
void cariPlayer(ListParent LP, string username);
void cariItem(ListParent LP, ListChild LC, string namaItem);

// STATISTIK MARKET
addressParent playerGoldTerbanyak(ListParent LP);
addressParent playerPengeluaranTerbesar(ListParent LP);
void playerTanpaItem(ListParent LP);



#endif // MARKETPLACE_H_INCLUDED
