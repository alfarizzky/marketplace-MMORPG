#include "marketplace.h"

int main() {
    ListParent LP;
    ListChild LC;
    addressParent currentPlayer = nullptr;
    bool keluar = false;

    createListParent(LP);
    createListChild(LC);

    while (!keluar) {

        /* ================= MENU UTAMA ================= */
        if (currentPlayer == nullptr) {
            int pilih;
            menuUtama();
            cin >> pilih;

            if (pilih == 0) {
                keluar = true;
            }

            else if (pilih == 1) { // Insert Parent
                infotypeParent p;
                cout << "Username: ";
                cin >> p.username;
                cout << "Gold awal: ";
                cin >> p.gold;
                p.totalIncome = 0;
                p.totalOutcome = 0;

                insertParent(LP, createParent(p));
                cout << "Player ditambahkan.\n";
            }

            else if (pilih == 2) { // Login
                string user;
                cout << "Username: ";
                cin >> user;
                if (login(LP, user, currentPlayer))
                    cout << "Login berhasil.\n";
                else
                    cout << "Login gagal.\n";
            }

            else if (pilih == 3) { // Show Market
                showAllChildWithParent(LP, LC);
            }

            else if (pilih == 4) { // Statistik
                int s;
                do {
                    menuStatistikMarket();
                    cin >> s;

                    if (s == 1) {
                        addressParent p = playerGoldTerbanyak(LP);
                        if (p) cout << p->info.username << " : " << p->info.gold << endl;
                    }
                    else if (s == 2) {
                        addressParent p = playerPengeluaranTerbesar(LP);
                        if (p) cout << p->info.username << " : " << p->info.totalOutcome << endl;
                    }
                    else if (s == 3) {
                        cout << "Child tanpa relasi: "
                             << countChildWithoutRelasi(LC, LP) << endl;
                    }
                    else if (s == 4) {
                        showAllParent(LP);
                    }
                    else if (s == 5) {
                        showAllChild(LC);
                    }
                    else if (s == 6) {
                        showAllParentWithChild(LP);
                    }

                } while (s != 0);
            }

            else if (pilih == 5) { // Find Parent
                string user;
                cout << "Username: ";
                cin >> user;
                cariPlayer(LP, user);
            }

            else if (pilih == 6) { // Delete Parent
                string user;
                cout << "Username yang dihapus: ";
                cin >> user;
                deleteParent(LP, LC, user);
                cout << "Delete parent selesai.\n";
            }
        }

        /* ================= MENU PLAYER ================= */
        else {
            int pilih;
            menuPlayer();
            cin >> pilih;

            if (pilih == 0) {
                logout(currentPlayer);
            }

            else if (pilih == 1) {
                infoPlayer(currentPlayer);
            }

            else if (pilih == 2) {
                showChildFromParent(currentPlayer);
            }

            else if (pilih == 3) { // Insert Child
                infotypeChild c;
                cout << "Nama item: ";
                cin >> c.namaItem;
                cout << "Harga: ";
                cin >> c.harga;
                cout << "Weapon (1/0): ";
                cin >> c.isWeapon;
                insertChild(LC, createChild(c));
                cout << "Child ditambahkan.\n";
            }

            else if (pilih == 4) { // Insert Relasi
                string item;
                cout << "Nama item: ";
                cin >> item;
                addressChild C = findChild(LC, item);
                if (C) insertRelasi(currentPlayer, C);
            }

            else if (pilih == 5) { // Delete Relasi
                string item;
                cout << "Nama item: ";
                cin >> item;
                addressChild C = findChild(LC, item);
                if (C) deleteRelasi(currentPlayer, C);
            }

            else if (pilih == 6) { // Delete Child
                string item;
                cout << "Nama item: ";
                cin >> item;
                addressChild C = findChild(LC, item);
                if (C && countRelasiChild(LP, C) == 0) {
                    deleteChild(LC, C);
                    cout << "Child dihapus.\n";
                } else {
                    cout << "Hapus relasi dulu.\n";
                }
            }

            else if (pilih == 7) { // Edit Relasi
                string item, target;
                cout << "Nama item: ";
                cin >> item;
                cout << "Pindah ke player: ";
                cin >> target;

                addressChild C = findChild(LC, item);
                addressParent T = findParent(LP, target);
                if (C && T) pindahKepemilikanItem(currentPlayer, T, C);
            }

            else if (pilih == 8) {
                string item;
                cout << "Nama item: ";
                cin >> item;
                cariItem(LP, LC, item);
            }

            else if (pilih == 9) {
                string item;
                cout << "Nama item: ";
                cin >> item;
                addressChild C = findChild(LC, item);
                if (C) showParentFromChild(LP, C);
            }

            else if (pilih == 10) { // Beli Item
                string item;
                cout << "Nama item: ";
                cin >> item;
                addressChild C = findChild(LC, item);
                if (C) beliItem(LP, LC, currentPlayer, C);
            }

            else if (pilih == 11) { // Menu Hitung
                int h;
                do {
                    cout << "\n=== MENU HITUNG RELASI ===\n";
                    cout << "1. Hitung relasi player ini\n";
                    cout << "2. Hitung relasi child tertentu\n";
                    cout << "0. Kembali\n";
                    cout << "Pilih: ";
                    cin >> h;

                    if (h == 1)
                        cout << countRelasiParent(currentPlayer) << endl;
                    else if (h == 2) {
                        string item;
                        cout << "Nama item: ";
                        cin >> item;
                        addressChild C = findChild(LC, item);
                        if (C) cout << countRelasiChild(LP, C) << endl;
                    }
                } while (h != 0);
            }
        }
    }

    cout << "Program selesai.\n";
    return 0;
}
