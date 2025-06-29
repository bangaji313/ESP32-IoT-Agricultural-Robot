# Seed-Ron: Prototipe Robot Penanam Benih Otomatis

![Status](https://img.shields.io/badge/status-completed-success) ![Platform](https://img.shields.io/badge/platform-ESP32%20%7C%20Arduino-blue)

Prototipe robot penanam benih otomatis berbasis ESP32 yang dikembangkan untuk tugas besar mata kuliah Pemrograman Robotika IFB-308 di Institut Teknologi Nasional Bandung. Robot ini dirancang untuk membantu proses pertanian dengan kemampuan navigasi, deteksi kondisi tanah, dan penanaman secara mandiri, serta dapat dikontrol dan dipantau dari jarak jauh melalui platform IoT Blynk.

---

### ✨ Fitur Utama

* **Kontrol Manual Jarak Jauh**: Dapat dikendalikan sepenuhnya (maju, mundur, belok) melalui dasbor virtual di platform Blynk.
* **Aksi Tanam Otomatis**: Secara otomatis melakukan siklus penanaman (melubangi, menjatuhkan benih, menutup) saat sensor mendeteksi kelembapan tanah yang ideal.
* **Aksi Tanam Manual**: Mekanisme penanaman juga dapat dipicu secara manual dari dasbor Blynk.
* **Deteksi Halangan**: Dilengkapi sensor ultrasonik untuk mendeteksi dan bereaksi terhadap rintangan di depannya.
* **Monitoring Real-time**: Data dari sensor (jarak dan kelembapan) dikirim dan ditampilkan secara langsung di dasbor Blynk.
* **Indikator Status**: Memberikan umpan balik visual (LED) dan audio (Buzzer) untuk setiap status operasional robot (siaga, bergerak, menanam, ada halangan).
* **Mode Demonstrasi Offline**: Memiliki program alternatif yang berjalan secara otonom tanpa memerlukan koneksi internet, khusus untuk keperluan presentasi.

---

### 👥 Anggota Kelompok F-04

| NRM | Nama | Peran Utama |
| :--- | :--- | :--- |
| 15-2022-065 | **Maulana Seno Aji Yudhantara** | **Ketua Kelompok; Desain Sistem, Fabrikasi & Pemrograman** |
| 15-2022-018 | Sadira Amalina F | Dokumentasi & Penyusunan Laporan |
| 15-2022-059 | Linda Indrawati F. S. | Desain Slide Presentasi & Penyusunan Laporan |
| 15-2022-064 | Muhammad Figo Razzan F | Dukungan Pengujian & Dokumentasi |
| 15-2022-077 | Naizirun De Jesus Da Silva | Instalasi Sistem Kendali & Manajemen Kabel |
| 15-2022-087 | Abhyasa Gunawan Y | Produksi dan Penyuntingan Video Demonstrasi |

---

### 🛠️ Komponen yang Digunakan

| Kategori | Komponen | Jumlah |
| :--- | :--- | :---: |
| **Mikrokontroler** | ESP32 DEVKIT V1 + Expansion Shield | 1 |
| **Sensor** | Sensor Ultrasonik HC-SR04 | 1 |
| | Sensor Kelembapan Tanah YL-69 | 1 |
| **Aktuator** | Motor DC 12V + Gearbox & Roda | 4 |
| | Motor Driver L298N | 1 |
| | Motor Stepper 28BYJ-48 + Driver ULN2003 | 1 |
| **Indikator** | LED 5mm (Merah, Kuning, Hijau) | 3 |
| | Modul Buzzer Pasif | 1 |
| **Catu Daya** | Baterai Li-ion 18650 | 6 |
| | Holder Baterai (2-slot & 4-slot) | Masing-masing 1 |

---

###  Diagram Blok Sistem
![Diagram Blok Sistem](docs\Revisi-DiagramBlokSeedRon.jpg)

### Flowchart Sistem
![Flowchart Algoritma Sistem](docs\FlowchartSistemSeedRon.jpg)

### Bentuk Jadi Robot
![Fisik Robot](docs\FisikRobot.jpg)

---

### 🎥 Video Demonstrasi

Klik pada gambar di bawah untuk menonton video demonstrasi lengkap dari robot Seed-Ron.

[![Video Demonstrasi Seed-Ron](https://img.youtube.com/vi/PZ1vkzNg6BM/0.jpg)](https://www.youtube.com/watch?v=PZ1vkzNg6BM)

---

### 📂 Struktur Repository

Repository ini berisi semua kode yang dikembangkan selama proyek, mulai dari pengujian modular hingga program final.

-   `/uji_[nama_komponen]` : Berisi kode-kode yang digunakan untuk menguji setiap komponen secara terpisah.
-   `/kontrol_gerak` : Kode final Tahap 1 untuk uji coba kontrol gerak via Blynk.
-   `/kontrol_gerak_dan_laporan_sensor` : Kode final Tahap 2 yang mengintegrasikan pembacaan sensor.
-   `/SEEDRON_V1` : Kode final terintegrasi dengan semua fitur online (Blynk).
-   `/SEEDRON-Offline` : Kode final versi demonstrasi yang berjalan secara otonom tanpa internet.
-   `/docs` : Berisi file pendukung seperti diagram blok, gambar, dll.

---

Dibuat untuk memenuhi tugas besar mata kuliah IFB-308 Pemrograman Robotika - Institut Teknologi Nasional Bandung.
Dosen: Milda Gustiana Husada, S.T., M.Eng.