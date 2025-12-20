#include "marketplace.h"

int main() {
    ListParent LP;
    ListChild LC;
    addressParent currentPlayer = nullptr;

    createListParent(LP);
    createListChild(LC);

    while (true) {

        /* ================= MENU UTAMA ================= */
        if (currentPlayer == nullptr) {
            int pilih;
            menuUtama();
            cin >> pilih;

            if (pilih == 0) {
                break;
            }

            else if (pilih == 1) {
                infotypeParent p;
                cout << "Username: ";
                cin >> p.username;

                if (findParent(LP, p.username) != nullptr) {
                    cout << "Username sudah terdaftar." << endl;
                } else {
                    cout << "Gold awal: ";
                    cin >> p.gold;
                    p.totalIncome = 0;
                    p.totalOutcome = 0;

                    insertParent(LP, createParent(p));
                    cout << "Player berhasil didaftarkan." << endl;
                }
            }

            else if (pilih == 2) {
                string username;
                cout << "Username: ";
                cin >> username;

                if (login(LP, username, currentPlayer)) {
                    cout << "Login berhasil." << endl;
                } else {
                    cout << "Login gagal." << endl;
                }
            }

            else if (pilih == 3) {
                cout << "\n=== MARKET ===" << endl;
                showAllChildWithParent(LP, LC);
            }

            else if (pilih == 4) {
                showStatistikMarket(LP, LC);
            }
        }

        /* ================= MENU PLAYER ================= */
        else {
            int pilihPlayer;
            menuPlayer();
            cin >> pilihPlayer;

            if (pilihPlayer == 1) {
                infoPlayer(currentPlayer);
            }

            else if (pilihPlayer == 2) {
                cout << "\n=== MARKET ===" << endl;
                showAllChildWithParent(LP, LC);
                cout << "Gold kamu: "
                     << currentPlayer->info.gold << endl;
            }

            else if (pilihPlayer == 3) {
                infotypeChild item;
                cout << "Nama Item: ";
                cin >> item.namaItem;
                cout << "Harga: ";
                cin >> item.harga;
                cout << "Apakah Weapon? (1 = ya, 0 = tidak): ";
                cin >> item.isWeapon;

                jualItem(LC, currentPlayer, item);

                cout << "Item berhasil dijual." << endl;
                cout << "Item yang sedang kamu jual:" << endl;
                showChildFromParent(currentPlayer);
            }

            else if (pilihPlayer == 4) {
                string namaItem;
                cout << "Nama item yang dibeli: ";
                cin >> namaItem;

                addressChild C = findChild(LC, namaItem);
                if (C == nullptr) {
                    cout << "Item tidak ditemukan." << endl;
                } else {
                    if (beliItem(LP, LC, currentPlayer, C)) {
                        cout << "Item berhasil dibeli." << endl;
                    } else {
                        cout << "Gagal membeli item." << endl;
                    }
                }
            }

            else if (pilihPlayer == 5) {
                string namaItem;
                cout << "Nama item yang dihapus: ";
                cin >> namaItem;

                addressChild C = findChild(LC, namaItem);
                if (C != nullptr &&
                    findRelasi(currentPlayer, C) != nullptr) {
                    hapusItemSendiri(LC, currentPlayer, C);
                    cout << "Item berhasil dihapus." << endl;
                } else {
                    cout << "Item bukan milikmu atau tidak ditemukan." << endl;
                }
            }

            else if (pilihPlayer == 0) {
                logout(currentPlayer);
                cout << "Logout berhasil." << endl;
            }
        }
    }

    cout << "Terima kasih telah menggunakan marketplace." << endl;
    return 0;
}
