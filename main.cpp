#include "marketplace.h"

int main() {
    ListParent LP;
    ListChild LC;
    addressParent currentPlayer;
    bool keluar;
    int pilih;
    int pilihPlayer;
    int ps;

    createListParent(LP);
    createListChild(LC);

    currentPlayer = nullptr;
    keluar = false;

    while (keluar == false) {

        /* ================= MENU UTAMA ================= */
        if (currentPlayer == nullptr) {

            menuUtama();
            cin >> pilih;

            if (pilih == 0) {
                keluar = true;
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

                if (login(LP, username, currentPlayer) == true) {
                    cout << "Login berhasil." << endl;
                } else {
                    cout << "Login gagal." << endl;
                }
            }

            else if (pilih == 3) {
                showAllChildWithParent(LP, LC);
            }

            else if (pilih == 4) {
                ps = -1;
                while (ps != 0) {
                    menuStatistikMarket();
                    cin >> ps;

                    if (ps == 1) {
                        showStatistikMarket(LP, LC);
                    }
                    else if (ps == 2) {
                        showAllParent(LP);
                    }
                    else if (ps == 3) {
                        showAllChild(LC);
                    }
                    else if (ps == 4) {
                        showAllParentWithChild(LP);
                    }
                    else if (ps == 0) {
                        /* kembali ke menu utama */
                    }
                    else {
                        cout << "Pilihan tidak valid." << endl;
                    }
                }
            }

            else if (pilih == 5) {
                string user;
                cout << "Username player: ";
                cin >> user;
                cariPlayer(LP, user);
            }

            else {
                cout << "Pilihan menu tidak valid." << endl;
            }
        }

        /* ================= MENU PLAYER ================= */
        else {

            menuPlayer();
            cin >> pilihPlayer;

            if (pilihPlayer == 1) {
                infoPlayer(currentPlayer);
            }

            else if (pilihPlayer == 2) {
                showAllChildWithParent(LP, LC);
                cout << "Gold kamu: " << currentPlayer->info.gold << endl;
            }

            else if (pilihPlayer == 3) {
                infotypeChild item;
                cout << "Nama Item: ";
                cin >> item.namaItem;
                cout << "Harga: ";
                cin >> item.harga;
                cout << "Weapon (1=ya, 0=tidak): ";
                cin >> item.isWeapon;

                jualItem(LC, currentPlayer, item);
                cout << "Item berhasil dijual." << endl;
            }

            else if (pilihPlayer == 4) {
                string namaItem;
                cout << "Nama item: ";
                cin >> namaItem;

                addressChild C;
                C = findChild(LC, namaItem);

                if (C != nullptr && beliItem(LP, LC, currentPlayer, C) == true) {
                    cout << "Item berhasil dibeli." << endl;
                } else {
                    cout << "Gagal membeli item." << endl;
                }
            }

            else if (pilihPlayer == 5) {
                string namaItem;
                cout << "Nama item: ";
                cin >> namaItem;

                addressChild C;
                C = findChild(LC, namaItem);

                if (C != nullptr && findRelasi(currentPlayer, C) != nullptr) {
                    hapusItemSendiri(LC, currentPlayer, C);
                    cout << "Item berhasil dihapus." << endl;
                } else {
                    cout << "Item bukan milikmu atau tidak ditemukan." << endl;
                }
            }

            else if (pilihPlayer == 6) {
                string item;
                string target;

                cout << "Nama item: ";
                cin >> item;
                cout << "Pindah ke player: ";
                cin >> target;

                addressChild C;
                addressParent T;

                C = findChild(LC, item);
                T = findParent(LP, target);

                if (C != nullptr && T != nullptr &&
                    pindahKepemilikanItem(currentPlayer, T, C) == true) {
                    cout << "Item berhasil dipindahkan." << endl;
                } else {
                    cout << "Gagal memindahkan item." << endl;
                }
            }

            else if (pilihPlayer == 7) {
                string user;
                cout << "Username player: ";
                cin >> user;
                cariPlayer(LP, user);
            }

            else if (pilihPlayer == 8) {
                string item;
                cout << "Nama item: ";
                cin >> item;
                cariItem(LP, LC, item);
            }

            else if (pilihPlayer == 9) {
                string item;
                infotypeChild newData;

                cout << "Nama item: ";
                cin >> item;

                addressChild C;
                C = findChild(LC, item);

                if (C != nullptr && findRelasi(currentPlayer, C) != nullptr) {
                    cout << "Nama baru: ";
                    cin >> newData.namaItem;
                    cout << "Harga baru: ";
                    cin >> newData.harga;
                    cout << "Weapon (1=ya, 0=tidak): ";
                    cin >> newData.isWeapon;

                    editItem(C, newData);
                    cout << "Item berhasil diedit." << endl;
                } else {
                    cout << "Item bukan milikmu atau tidak ditemukan." << endl;
                }
            }

            else if (pilihPlayer == 0) {
                logout(currentPlayer);
                cout << "Logout berhasil." << endl;
            }

            else {
                cout << "Pilihan menu tidak valid." << endl;
            }
        }
    }

    cout << "Terima kasih telah menggunakan marketplace." << endl;
    return 0;
}
