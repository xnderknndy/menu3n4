// MENU 3

/*
 * tampilkanTabelBuku: menampilkan array buku dalam bentuk tabel.
 * Dipakai oleh menu 3, 5, 7, dan hasil sorting menu 8.
 */
void tampilkanTabelBuku(const Buku daftar[], int jumlah)
{
    int  i;
    char teksHarga[PANJANG_RUPIAH];

    cetakGaris('=', LEBAR_TABEL_BUKU);
    printf("| %-3s | %-6s | %-35s | %-18s | %16s |\n",
           "No", "Kode", "Nama Buku", "Jenis Buku", "Harga");
    cetakGaris('-', LEBAR_TABEL_BUKU);
    for (i = 0; i < jumlah; i++) {
        formatRupiah(daftar[i].harga, teksHarga);
        printf("| %-3d | %-6s | %-35s | %-18s | %16s |\n", i + 1,
               daftar[i].kode, daftar[i].nama, daftar[i].jenis, teksHarga);
    }
    cetakGaris('=', LEBAR_TABEL_BUKU);
}

/* MENU 3 - menuViewBuku: menampilkan seluruh data buku yang tersedia. */
void menuViewBuku(const DaftarBuku *db)
{
    cetakJudul("MENU 3 - DATA BUKU");
    if (db->jumlah == 0) {
        printf("Belum ada data buku.\n");
        return;
    }
    tampilkanTabelBuku(db->data, db->jumlah);
}


// MENU 4

/*
 * tampilkanTabelHistory: menampilkan seluruh histori transaksi dalam
 * bentuk tabel, beserta total buku terjual dan total pendapatan.
 */
void tampilkanTabelHistory(const DaftarHistory *dh)
{
    int    i;
    int    totalTerjual = 0;
    double totalPendapatan = 0;
    char   teksTotal[PANJANG_RUPIAH];

    cetakGaris('=', LEBAR_TABEL_HISTORY);
    printf("| %-3s | %-10s | %-14s | %20s |\n",
           "No", "Kode Buku", "Jumlah Terjual", "Total Harga");
    cetakGaris('-', LEBAR_TABEL_HISTORY);
    for (i = 0; i < dh->jumlah; i++) {
        formatRupiah(dh->data[i].totalHarga, teksTotal);
        printf("| %-3d | %-10s | %14d | %20s |\n", i + 1,
               dh->data[i].kodeBuku, dh->data[i].jumlahTerjual, teksTotal);
        totalTerjual    += dh->data[i].jumlahTerjual;
        totalPendapatan += dh->data[i].totalHarga;
    }
    cetakGaris('=', LEBAR_TABEL_HISTORY);
    formatRupiah(totalPendapatan, teksTotal);
    printf("Total buku terjual      : %d eksemplar\n", totalTerjual);
    printf("Total seluruh penjualan : %s\n", teksTotal);
}

/*
 * bacaInteger: meminta input bilangan bulat dalam rentang [min, maks].
 * Input diulang sampai valid (bukan huruf, bukan desimal, dalam rentang).
 */
int bacaInteger(const char *label, int min, int maks)
{
    char  buffer[PANJANG_BARIS];
    char *sisa;
    long  nilai;

    while (1) {
        printf("%s", label);
        bacaBaris(buffer, sizeof(buffer));
        nilai = strtol(buffer, &sisa, 10);

        if (strlen(buffer) == 0 || *sisa != '\0') {
            printf("  [!] Input harus berupa angka bulat.\n");
        } else if (nilai < min || nilai > maks) {
            printf("  [!] Input harus antara %d dan %d.\n", min, maks);
        } else {
            return (int)nilai;
        }
    }
}

/*
 * MENU 4 - menuDeleteHistory: menampilkan daftar histori, meminta index
 * (validasi 1 s.d. jumlah data), lalu menghapus histori pada index itu
 * dengan menggeser data setelahnya satu posisi ke kiri.
 */
void menuDeleteHistory(DaftarHistory *dh)
{
    int nomor, i;

    cetakJudul("MENU 4 - DELETE HISTORY");
    if (dh->jumlah == 0) {
        printf("Belum ada data history yang bisa dihapus.\n");
        return;
    }
    tampilkanTabelHistory(dh);

    nomor = bacaInteger("\nMasukkan index history yang akan dihapus: ",
                        1, dh->jumlah);

    /* index input mulai dari 1, index array mulai dari 0 */
    for (i = nomor - 1; i < dh->jumlah - 1; i++) {
        dh->data[i] = dh->data[i + 1];
    }
    dh->jumlah--;

    printf("Data Successfully delete..\n");
}