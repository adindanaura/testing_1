// stok.c - Modul 2: Manajemen stok dan isi ulang bahan
// Materi: struct, pointer, function
// Compile: gcc stok.c -o stok
// Jalankan: ./stok   (di Windows: stok.exe)

#include <stdio.h>
#include <string.h>

#define JUMLAH_BAHAN 4
#define BATAS_MENIPIS 100   // di bawah angka ini stok dianggap menipis

// "Kartu data" untuk satu bahan
struct Bahan {
    char nama[30];
    int stok;
    char satuan[10];
};

// Mencetak semua bahan beserta stoknya
void tampilStok(struct Bahan daftar[], int n) {
    printf("\n=== STOK BAHAN ===\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %-15s : %5d %s", i + 1, daftar[i].nama, daftar[i].stok, daftar[i].satuan);
        if (daftar[i].stok < BATAS_MENIPIS) {
            printf("  <-- menipis!");
        }
        printf("\n");
    }
}

// Mencari bahan berdasarkan nama.
// Mengembalikan POINTER ke bahan yang ditemukan, atau NULL kalau tidak ada.
struct Bahan *cariBahan(struct Bahan daftar[], int n, const char *nama) {
    for (int i = 0; i < n; i++) {
        if (strcmp(daftar[i].nama, nama) == 0) {
            return &daftar[i];   // & = alamat dari elemen array
        }
    }
    return NULL;
}

// Menambah stok. Pakai pointer supaya yang berubah adalah data ASLI, bukan salinan.
void isiUlang(struct Bahan *b, int jumlah) {
    if (jumlah <= 0) {
        printf("Jumlah isi ulang harus lebih dari 0.\n");
        return;
    }
    b->stok += jumlah;   // b->stok artinya "stok milik struct yang ditunjuk b"
    printf("Isi ulang %s +%d %s. Stok sekarang: %d\n", b->nama, jumlah, b->satuan, b->stok);
}

// Mengurangi stok (dipakai saat bahan digunakan).
// Mengembalikan 1 kalau berhasil, 0 kalau gagal (stok tidak cukup).
int kurangiStok(struct Bahan *b, int jumlah) {
    if (jumlah <= 0) {
        return 0;
    }
    if (b->stok < jumlah) {
        printf("Stok %s tidak cukup (sisa %d %s, butuh %d).\n", b->nama, b->stok, b->satuan, jumlah);
        return 0;
    }
    b->stok -= jumlah;
    return 1;
}

int main() {
    // Data awal
    struct Bahan daftar[JUMLAH_BAHAN] = {
        {"Biji Kopi", 500, "gram"},
        {"Susu",      800, "ml"},
        {"Gula",      300, "gram"},
        {"Es Batu",    60, "gram"}
    };

    tampilStok(daftar, JUMLAH_BAHAN);

    // Coba isi ulang
    struct Bahan *b = cariBahan(daftar, JUMLAH_BAHAN, "Es Batu");
    if (b != NULL) {
        isiUlang(b, 200);
    }

    // Coba pakai bahan (berhasil)
    b = cariBahan(daftar, JUMLAH_BAHAN, "Biji Kopi");
    if (b != NULL && kurangiStok(b, 18)) {
        printf("Biji Kopi terpakai 18 gram.\n");
    }

    // Coba pakai bahan (gagal karena kebanyakan)
    b = cariBahan(daftar, JUMLAH_BAHAN, "Gula");
    if (b != NULL) {
        kurangiStok(b, 1000);
    }

    // Coba cari bahan yang tidak ada
    b = cariBahan(daftar, JUMLAH_BAHAN, "Sirup");
    if (b == NULL) {
        printf("Bahan 'Sirup' tidak ditemukan.\n");
    }

    tampilStok(daftar, JUMLAH_BAHAN);
    return 0;
}