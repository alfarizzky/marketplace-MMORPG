#ifndef MARKETPLACE_H_INCLUDED
#define MARKETPLACE_H_INCLUDED

#include <iostream>

using namespace std;

// struct & typedef section

// Child (hafiz)
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

// Relation (rizki)
typedef struct elmRelasi *addressRelasi;

struct elmRelasi {
    addressChild child;
    addressRelasi next;
};

// Parent (rafly)
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

// List Definitions
struct ListParent {
    addressParent first;
};

struct ListChild {
    addressChild first;
};

// Menu Functions (bersama)
void menuUtama();
void menuPlayer();
void menuStatistikMarket();


// List Parent Functions (rafly)

// create list parent
void createListParent(ListParent &LP);

// create & insert parent
addressParent createParent(infotypeParent data);
void insertParent(ListParent &LP, addressParent P);

// delete parent
void deleteParent(ListParent &LP, ListChild &LC, string username);

// find parent
addressParent findParent(ListParent LP, string username);

// show & info parent
void showAllParent(ListParent LP);
void infoPlayer(addressParent P);

// statistik parent
addressParent playerGoldTerbanyak(ListParent LP);
addressParent playerPengeluaranTerbesar(ListParent LP);
void playerTanpaItem(ListParent LP);

// search parent
void cariPlayer(ListParent LP, string username);


// List Child Functions (hafiz)

// create list child
void createListChild(ListChild &LC);

// create & insert child
addressChild createChild(infotypeChild data);
void insertChild(ListChild &LC, addressChild C);

// delete child
void deleteChild(ListChild &LC, addressChild C);

// find child
addressChild findChild(ListChild LC, string namaItem);

// show child
void showAllChild(ListChild LC);

// edit child
void editItem(addressChild C, infotypeChild newData);

// search child
void cariItem(ListParent LP, ListChild LC, string namaItem);


// Relation Functions (rizki)

// create relasi
addressRelasi createRelasi(addressChild C);

// insert & delete relasi
void insertRelasi(addressParent P, addressChild C);
void deleteRelasi(addressParent P, addressChild C);

// find relasi
addressRelasi findRelasi(addressParent P, addressChild C);

// edit relasi (Tipe A)
void editRelasi(addressParent P,
                addressChild oldChild,
                addressChild newChild);

// pindah kepemilikan (edit relasi)
bool pindahKepemilikanItem(addressParent from, addressParent to, addressChild item);

// show relasi
void showChildFromParent(addressParent P);
void showParentFromChild(ListParent LP, addressChild C);
void showAllParentWithChild(ListParent LP);
void showAllChildWithParent(ListParent LP, ListChild LC);

// count relasi
int countRelasiParent(addressParent P);
int countRelasiChild(ListParent LP, addressChild C);
int countChildWithoutRelasi(ListChild LC, ListParent LP);

// marketplace feature (bersama)

// login system
bool login(ListParent LP, string username, addressParent &currentPlayer);
void logout(addressParent &currentPlayer);

// marketplace feature
void jualItem(ListChild &LC, addressParent P, infotypeChild dataItem);
bool beliItem(ListParent &LP, ListChild &LC,
              addressParent buyer, addressChild item);
void hapusItemSendiri(ListChild &LC, addressParent P, addressChild item);

// statistik gabungan
void showStatistikMarket(ListParent LP, ListChild LC);


#endif // MARKETPLACE_H_INCLUDED
