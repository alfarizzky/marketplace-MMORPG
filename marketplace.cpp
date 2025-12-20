#include "marketplace.h"

// Menu
void menuUtama() {
    cout << "\n=== MARKETPLACE MMORPG ===\n";
    cout << "1. Daftar Player\n";
    cout << "2. Login\n";
    cout << "3. Lihat Market\n";
    cout << "4. Statistik Market\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

void menuPlayer() {
    cout << "\n=== MENU PLAYER ===\n";
    cout << "1. Info Player\n";
    cout << "2. Lihat Market\n";
    cout << "3. Jual Item\n";
    cout << "4. Beli Item\n";
    cout << "5. Hapus Item Sendiri\n";
    cout << "0. Logout\n";
    cout << "Pilih: ";
}
// CREATE LIST
void createListParent(ListParent &LP) {
    LP.first = nullptr;
}

void createListChild(ListChild &LC) {
    LC.first = nullptr;
}

// CREATE NODE
addressParent createParent(infotypeParent data) {
    addressParent P = new elmlistParent;
    P->info = data;
    P->relasi = nullptr;
    P->next = nullptr;
    return P;
}

addressChild createChild(infotypeChild data) {
    addressChild C = new elmlistChild;
    C->info = data;
    C->next = nullptr;
    return C;
}

addressRelasi createRelasi(addressChild C) {
    addressRelasi R = new elmRelasi;
    R->child = C;
    R->next = nullptr;
    return R;
}

// INSERT
void insertParent(ListParent &LP, addressParent P) {
    if (LP.first == nullptr) {
        LP.first = P;
    } else {
        addressParent Q = LP.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = P;
    }
}

void insertChild(ListChild &LC, addressChild C) {
    if (LC.first == nullptr) {
        LC.first = C;
    } else {
        addressChild Q = LC.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
    }
}

void insertRelasi(addressParent P, addressChild C) {
    addressRelasi R = createRelasi(C);
    if (P->relasi == nullptr) {
        P->relasi = R;
    } else {
        addressRelasi Q = P->relasi;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = R;
    }
}

// DELETE
void deleteRelasi(addressParent P, addressChild C) {
    addressRelasi prev = nullptr;
    addressRelasi curr = P->relasi;

    while (curr != nullptr && curr->child != C) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            P->relasi = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
}

void deleteChild(ListChild &LC, addressChild C) {
    addressChild prev = nullptr;
    addressChild curr = LC.first;

    while (curr != nullptr && curr != C) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            LC.first = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
}

void deleteParent(ListParent &LP, ListChild &LC, string username) {
    addressParent prev = nullptr;
    addressParent curr = LP.first;

    while (curr != nullptr && curr->info.username != username) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != nullptr) {
        addressRelasi R = curr->relasi;
        while (R != nullptr) {
            addressRelasi temp = R;
            R = R->next;
            deleteChild(LC, temp->child);
            delete temp;
        }

        if (prev == nullptr) {
            LP.first = curr->next;
        } else {
            prev->next = curr->next;
        }
        delete curr;
    }
}

// FIND
addressParent findParent(ListParent LP, string username) {
    addressParent P = LP.first;
    while (P != nullptr) {
        if (P->info.username == username)
            return P;
        P = P->next;
    }
    return nullptr;
}

addressChild findChild(ListChild LC, string namaItem) {
    addressChild C = LC.first;
    while (C != nullptr) {
        if (C->info.namaItem == namaItem)
            return C;
        C = C->next;
    }
    return nullptr;
}

addressRelasi findRelasi(addressParent P, addressChild C) {
    addressRelasi R = P->relasi;
    while (R != nullptr) {
        if (R->child == C)
            return R;
        R = R->next;
    }
    return nullptr;
}

// SHOW
void showAllParent(ListParent LP) {
    addressParent P = LP.first;
    while (P != nullptr) {
        cout << "Username: " << P->info.username
             << " | Gold: " << P->info.gold << endl;
        P = P->next;
    }
}

void showAllChild(ListChild LC) {
    addressChild C = LC.first;
    while (C != nullptr) {
        cout << "Item: " << C->info.namaItem
             << " | Harga: " << C->info.harga
             << " | Weapon: " << (C->info.isWeapon ? "Yes" : "No") << endl;
        C = C->next;
    }
}

void showChildFromParent(addressParent P) {
    addressRelasi R = P->relasi;
    while (R != nullptr) {
        cout << "- " << R->child->info.namaItem << endl;
        R = R->next;
    }
}

void showAllParentWithChild(ListParent LP) {
    addressParent P = LP.first;
    while (P != nullptr) {
        cout << "Player: " << P->info.username << endl;
        showChildFromParent(P);
        P = P->next;
    }
}

void showAllChildWithParent(ListParent LP, ListChild LC) {
    addressChild C = LC.first;
    while (C != nullptr) {
        cout << "Item: " << C->info.namaItem << " | Seller: ";
        showParentFromChild(LP, C);
        C = C->next;
    }
}

void showParentFromChild(ListParent LP, addressChild C) {
    addressParent P = LP.first;
    while (P != nullptr) {
        if (findRelasi(P, C) != nullptr) {
            cout << P->info.username << endl;
            return;
        }
        P = P->next;
    }
    cout << "None" << endl;
}

// COUNT
int countRelasiParent(addressParent P) {
    int count = 0;
    addressRelasi R = P->relasi;
    while (R != nullptr) {
        count++;
        R = R->next;
    }
    return count;
}

int countRelasiChild(ListParent LP, addressChild C) {
    int count = 0;
    addressParent P = LP.first;
    while (P != nullptr) {
        if (findRelasi(P, C) != nullptr)
            count++;
        P = P->next;
    }
    return count;
}

int countChildWithoutRelasi(ListChild LC, ListParent LP) {
    int count = 0;
    addressChild C = LC.first;
    while (C != nullptr) {
        if (countRelasiChild(LP, C) == 0)
            count++;
        C = C->next;
    }
    return count;
}

//  EDIT RELASI
void editRelasi(addressParent P, addressChild oldChild, addressChild newChild) {
    deleteRelasi(P, oldChild);
    insertRelasi(P, newChild);
}

//  MARKETPLACE FEATURE
bool login(ListParent LP, string username, addressParent &currentPlayer) {
    currentPlayer = findParent(LP, username);
    return (currentPlayer != nullptr);
}

void logout(addressParent &currentPlayer) {
    currentPlayer = nullptr;
}

void infoPlayer(addressParent P) {
    cout << "Username: " << P->info.username << endl;
    cout << "Gold: " << P->info.gold << endl;
    cout << "Total Income: " << P->info.totalIncome << endl;
    cout << "Total Outcome: " << P->info.totalOutcome << endl;
    cout << "Item Dijual:" << endl;
    showChildFromParent(P);
}

void jualItem(ListChild &LC, addressParent P, infotypeChild dataItem) {
    addressChild C = createChild(dataItem);
    insertChild(LC, C);
    insertRelasi(P, C);
}

bool beliItem(ListParent &LP, ListChild &LC, addressParent buyer, addressChild item) {
    addressParent seller = LP.first;
    while (seller != nullptr && findRelasi(seller, item) == nullptr) {
        seller = seller->next;
    }

    if (seller == nullptr || seller == buyer)
        return false;

    if (buyer->info.gold < item->info.harga)
        return false;

    buyer->info.gold -= item->info.harga;
    buyer->info.totalOutcome += item->info.harga;

    seller->info.gold += item->info.harga;
    seller->info.totalIncome += item->info.harga;

    deleteRelasi(seller, item);
    deleteChild(LC, item);

    return true;
}

void hapusItemSendiri(ListChild &LC, addressParent P, addressChild item) {
    deleteRelasi(P, item);
    deleteChild(LC, item);
}

void editItem(addressChild C, infotypeChild newData) {
    C->info = newData;
}

void cariPlayer(ListParent LP, string username) {
    addressParent P = findParent(LP, username);
    if (P != nullptr) {
        infoPlayer(P);
    } else {
        cout << "Player tidak ditemukan." << endl;
    }
}

void cariItem(ListParent LP, ListChild LC, string namaItem) {
    addressChild C = findChild(LC, namaItem);
    if (C != nullptr) {
        cout << "Item: " << C->info.namaItem << endl;
        showParentFromChild(LP, C);
    } else {
        cout << "Item tidak ditemukan." << endl;
    }
}

addressParent playerGoldTerbanyak(ListParent LP) {
    addressParent max = LP.first;
    addressParent P = LP.first;
    while (P != nullptr) {
        if (P->info.gold > max->info.gold)
            max = P;
        P = P->next;
    }
    return max;
}

addressParent playerPengeluaranTerbesar(ListParent LP) {
    addressParent max = LP.first;
    addressParent P = LP.first;
    while (P != nullptr) {
        if (P->info.totalOutcome > max->info.totalOutcome)
            max = P;
        P = P->next;
    }
    return max;
}

void playerTanpaItem(ListParent LP) {
    addressParent P = LP.first;
    while (P != nullptr) {
        if (P->relasi == nullptr)
            cout << P->info.username << endl;
        P = P->next;
    }
}
