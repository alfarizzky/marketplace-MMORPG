#include "marketplace.h"

// Menu Functions (bersama)
void menuUtama() {
    cout << "\n=== MENU UTAMA ===\n";
    cout << "1. Insert Player\n";
    cout << "2. Login\n";
    cout << "3. Show Market\n";
    cout << "4. Menu Statistik\n";
    cout << "5. Cari Player\n";
    cout << "6. Delete Player\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}



void menuPlayer() {
    cout << "\n=== MENU PLAYER ===\n";
    cout << "1. Info Player\n";
    cout << "2. Show Item Milik Player\n";
    cout << "3. Insert Child (Jual Item)\n";
    cout << "4. Insert Relasi\n";
    cout << "5. Delete Relasi\n";
    cout << "6. Delete Child\n";
    cout << "7. Edit Relasi (Pindah Item)\n";
    cout << "8. Cari Child\n";
    cout << "9. Cari Parent dari Child\n";
    cout << "10. Beli Item\n";
    cout << "11. Menu Hitung Relasi\n";
    cout << "0. Logout\n";
    cout << "Pilih: ";
}



void menuStatistikMarket() {
    cout << "\n=== MENU STATISTIK ===\n";
    cout << "1. Player Gold Terbanyak\n";
    cout << "2. Player Pengeluaran Terbesar\n";
    cout << "3. Jumlah Child Tanpa Relasi\n";
    cout << "4. Show Semua Parent\n";
    cout << "5. Show Semua Child\n";
    cout << "6. Show Parent + Child\n";
    cout << "7. Count relation dari setiap element parent\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
}


bool login(ListParent LP, string username, addressParent &currentPlayer) {
    currentPlayer = findParent(LP, username);
    return currentPlayer != nullptr;
}

void logout(addressParent &currentPlayer) {
    currentPlayer = nullptr;
}

// Parent List Functions (rafly)
void createListParent(ListParent &LP) {
    LP.first = nullptr;
}

addressParent createParent(infotypeParent data) {
    addressParent P;
    P = new elmlistParent;
    P->info = data;
    P->relasi = nullptr;
    P->next = nullptr;
    return P;
}

void insertParent(ListParent &LP, addressParent P) {
    if (LP.first == nullptr)
        LP.first = P;
    else {
        addressParent Q = LP.first;
        while (Q->next) Q = Q->next;
        Q->next = P;
    }
}

addressParent findParent(ListParent LP, string username) {
    addressParent P;
    P = LP.first;
    while (P) {
        if (P->info.username == username)
            return P;
        P = P->next;
    }
    return nullptr;
}

void deleteParent(ListParent &LP, ListChild &LC, string username) {
    addressParent prev, curr;

    prev = nullptr;
    curr = LP.first;
    while (curr && curr->info.username != username) {
        prev = curr;
        curr = curr->next;
    }

    if (curr) {
        addressRelasi R;
        R = curr->relasi;
        while (R) {
            addressRelasi tmp;
            tmp = R;

            R = R->next;
            deleteChild(LC, tmp->child);
            delete tmp;
        }

        if (!prev) LP.first = curr->next;
        else prev->next = curr->next;

        delete curr;
    }
}

void showAllParent(ListParent LP) {
    cout << "\n==================== DAFTAR PLAYER ====================\n";
    cout << "Username\tGold\tIncome\tOutcome\n";
    cout << "------------------------------------------------------\n";

    addressParent P;
    P = LP.first;

    if (P == nullptr) {
        cout << "(Tidak ada player)\n";
        return;
    }

    while (P != nullptr) {
        cout << P->info.username << "\t"
             << P->info.gold << "\t"
             << P->info.totalIncome << "\t"
             << P->info.totalOutcome << endl;
        P = P->next;
    }

    cout << "======================================================\n";
}


void infoPlayer(addressParent P) {
    cout << "\nUsername       : " << P->info.username << endl;
    cout << "Gold           : " << P->info.gold << endl;
    cout << "Total Income   : " << P->info.totalIncome << endl;
    cout << "Total Outcome  : " << P->info.totalOutcome << endl;
    cout << "Item Dijual:\n";
    showChildFromParent(P);
}

addressParent playerGoldTerbanyak(ListParent LP) {
    addressParent max;
    addressParent P;

    max = LP.first;
    P = LP.first;

    while (P != nullptr) {
        if (P->info.gold > max->info.gold) {
            max = P;
        }
        P = P->next;
    }

    return max;
}


addressParent playerPengeluaranTerbesar(ListParent LP) {
    addressParent max;
    addressParent P;

    max = LP.first;
    P = LP.first;

    while (P != nullptr) {
        if (P->info.totalOutcome > max->info.totalOutcome) {
            max = P;
        }
        P = P->next;
    }

    return max;
}


void playerTanpaItem(ListParent LP) {
    addressParent P;

    P = LP.first;
    while (P != nullptr) {
        if (P->relasi == nullptr) {
            cout << "- " << P->info.username << endl;
        }
        P = P->next;
    }
}


void cariPlayer(ListParent LP, string username) {
    addressParent P;

    P = findParent(LP, username);
    if (P != nullptr) {
        infoPlayer(P);
    } else {
        cout << "Player tidak ditemukan." << endl;
    }
}


// child List Functions (hafiz)

void createListChild(ListChild &LC) {
    LC.first = nullptr;
}

addressChild createChild(infotypeChild data) {
    addressChild C;

    C = new elmlistChild;
    C->info = data;
    C->next = nullptr;

    return C;
}


void insertChild(ListChild &LC, addressChild C) {
    addressChild Q;

    if (LC.first == nullptr) {
        LC.first = C;
    } else {
        Q = LC.first;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = C;
    }
}


void deleteChild(ListChild &LC, addressChild C) {
    addressChild prev;
    addressChild curr;

    prev = nullptr;
    curr = LC.first;

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


addressChild findChild(ListChild LC, string namaItem) {
    addressChild C;

    C = LC.first;
    while (C != nullptr) {
        if (C->info.namaItem == namaItem) {
            return C;
        }
        C = C->next;
    }
    return nullptr;
}


void showAllChild(ListChild LC) {
    addressChild C;

    cout << "\n====================== DAFTAR ITEM ======================\n";
    cout << "Nama Item\tHarga\tWeapon\n";
    cout << "--------------------------------------------------------\n";

    C = LC.first;
    if (C == nullptr) {
        cout << "(Tidak ada item)\n";
        cout << "========================================================\n";
        return;
    }

    while (C != nullptr) {
        cout << C->info.namaItem << "\t"
             << C->info.harga << "\t"
             << (C->info.isWeapon ? "Yes" : "No") << endl;
        C = C->next;
    }

    cout << "========================================================\n";
}


void editItem(addressChild C, infotypeChild newData) {
    C->info = newData;
}

void cariItem(ListParent LP, ListChild LC, string namaItem) {
    addressChild C;

    C = findChild(LC, namaItem);
    if (C == nullptr) {
        cout << "Item tidak ditemukan." << endl;
        return;
    }

    cout << "Nama Item : " << C->info.namaItem << endl;
    cout << "Harga     : " << C->info.harga << endl;
    cout << "Weapon    : " << (C->info.isWeapon ? "Yes" : "No") << endl;
    cout << "Penjual   : ";
    showParentFromChild(LP, C);
}


// relation Functions (rizki)
addressRelasi createRelasi(addressChild C) {
    addressRelasi R;

    R = new elmRelasi;
    R->child = C;
    R->next = nullptr;

    return R;
}


void insertRelasi(addressParent P, addressChild C) {
    addressRelasi R;
    addressRelasi Q;

    R = createRelasi(C);

    if (P->relasi == nullptr) {
        P->relasi = R;
    } else {
        Q = P->relasi;
        while (Q->next != nullptr) {
            Q = Q->next;
        }
        Q->next = R;
    }
}


void deleteRelasi(addressParent P, addressChild C) {
    addressRelasi prev;
    addressRelasi curr;

    prev = nullptr;
    curr = P->relasi;

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


addressRelasi findRelasi(addressParent P, addressChild C) {
    addressRelasi R;

    R = P->relasi;
    while (R != nullptr) {
        if (R->child == C) {
            return R;
        }
        R = R->next;
    }
    return nullptr;
}


void editRelasi(addressParent P, addressChild oldChild, addressChild newChild) {
    deleteRelasi(P, oldChild);
    insertRelasi(P, newChild);
}

bool pindahKepemilikanItem(addressParent from, addressParent to, addressChild item) {
    if (from == nullptr || to == nullptr) {
        return false;
    }

    if (from == to) {
        return false;
    }

    if (findRelasi(from, item) == nullptr) {
        return false;
    }

    deleteRelasi(from, item);
    insertRelasi(to, item);

    return true;
}

void showChildFromParent(addressParent P) {
    addressRelasi R;

    R = P->relasi;
    if (R == nullptr) {
        cout << "(Tidak ada item)" << endl;
        return;
    }

    while (R != nullptr) {
        cout << "- " << R->child->info.namaItem << endl;
        R = R->next;
    }
}


void showParentFromChild(ListParent LP, addressChild C) {
    addressParent P;

    P = LP.first;
    while (P != nullptr) {
        if (findRelasi(P, C) != nullptr) {
            cout << P->info.username << endl;
            return;
        }
        P = P->next;
    }

    cout << "None" << endl;
}


void showAllParentWithChild(ListParent LP) {
    addressParent P;

    P = LP.first;
    if (P == nullptr) {
        cout << "(Tidak ada player)" << endl;
        return;
    }

    while (P != nullptr) {
        cout << "\nPlayer: " << P->info.username << endl;
        cout << "-----------------------------" << endl;
        showChildFromParent(P);
        P = P->next;
    }
}


void showAllChildWithParent(ListParent LP, ListChild LC) {
    addressChild C;
    addressParent P;
    bool found;

    cout << "\n=========================== MARKET ===========================\n";
    cout << "Item\tHarga\tWeapon\tPenjual\n";
    cout << "-------------------------------------------------------------\n";

    C = LC.first;
    if (C == nullptr) {
        cout << "(Tidak ada item di market)" << endl;
        cout << "=============================================================\n";
        return;
    }

    while (C != nullptr) {
        found = false;
        P = LP.first;

        while (P != nullptr && !found) {
            if (findRelasi(P, C) != nullptr) {
                cout << C->info.namaItem << "\t"
                     << C->info.harga << "\t"
                     << (C->info.isWeapon ? "Yes" : "No") << "\t"
                     << P->info.username << endl;
                found = true;
            }
            P = P->next;
        }

        if (!found) {
            cout << C->info.namaItem << "\t"
                 << C->info.harga << "\t"
                 << (C->info.isWeapon ? "Yes" : "No") << "\t"
                 << "-" << endl;
        }

        C = C->next;
    }

    cout << "=============================================================\n";
}


int countRelasiParent(addressParent P) {
    int count;
    addressRelasi R;

    count = 0;
    R = P->relasi;

    while (R != nullptr) {
        count++;
        R = R->next;
    }

    return count;
}


int countRelasiChild(ListParent LP, addressChild C) {
    int count;
    addressParent P;

    count = 0;
    P = LP.first;

    while (P != nullptr) {
        if (findRelasi(P, C) != nullptr) {
            count++;
        }
        P = P->next;
    }

    return count;
}


int countChildWithoutRelasi(ListChild LC, ListParent LP) {
    int count;
    addressChild C;

    count = 0;
    C = LC.first;

    while (C != nullptr) {
        if (countRelasiChild(LP, C) == 0) {
            count++;
        }
        C = C->next;
    }

    return count;
}


// statistik market functions (bersama)

void showStatistikMarket(ListParent LP, ListChild LC) {
    addressParent g;
    addressParent o;

    cout << "\n==================== RINGKASAN STATISTIK ====================\n";
    cout << "Kategori\t\tPlayer\t\tNilai\n";
    cout << "------------------------------------------------------------\n";

    g = playerGoldTerbanyak(LP);
    if (g != nullptr) {
        cout << "Gold Terbanyak\t\t" << g->info.username << "\t\t" << g->info.gold << endl;
    }

    o = playerPengeluaranTerbesar(LP);
    if (o != nullptr) {
        cout << "Pengeluaran Terbesar\t" << o->info.username << "\t\t" << o->info.totalOutcome << endl;
    }

    cout << "Item Tanpa Relasi\t-\t\t" << countChildWithoutRelasi(LC, LP) << endl;

    cout << "------------------------------------------------------------\n";
    cout << "\nPlayer tanpa item:\n";
    playerTanpaItem(LP);
}


// marketplace functions (bersama)
void jualItem(ListChild &LC, addressParent P, infotypeChild dataItem) {
    addressChild C;

    C = createChild(dataItem);
    insertChild(LC, C);
    insertRelasi(P, C);
}

bool beliItem(ListParent &LP, ListChild &LC, addressParent buyer, addressChild item) {
    addressParent seller;

    seller = LP.first;
    while (seller != nullptr && findRelasi(seller, item) == nullptr) {
        seller = seller->next;
    }

    if (seller == nullptr) {
        return false;
    }

    if (seller == buyer) {
        return false;
    }

    if (buyer->info.gold < item->info.harga) {
        return false;
    }

    buyer->info.gold = buyer->info.gold - item->info.harga;
    buyer->info.totalOutcome = buyer->info.totalOutcome + item->info.harga;

    seller->info.gold = seller->info.gold + item->info.harga;
    seller->info.totalIncome = seller->info.totalIncome + item->info.harga;

    deleteRelasi(seller, item);
    deleteChild(LC, item);

    return true;
}


void hapusItemSendiri(ListChild &LC, addressParent P, addressChild item) {
    deleteRelasi(P, item);
    deleteChild(LC, item);
}
