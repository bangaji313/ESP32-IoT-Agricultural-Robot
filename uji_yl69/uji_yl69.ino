// === Pengujian Sensor Kelembapan Tanah YL-69 ===

// Definisi pin untuk Sensor Kelembapan
// Kita menggunakan pin ADC (Analog to Digital Converter). D34 adalah salah satunya.
const int pinSensorLembap = 34;

// Variabel untuk menyimpan nilai dari sensor
int nilaiLembap;

void setup() {
  // Mulai komunikasi serial untuk menampilkan hasil
  Serial.begin(115200);
  
  // Atur pin sensor sebagai INPUT
  pinMode(pinSensorLembap, INPUT);
  
  Serial.println("Pengujian Sensor Kelembapan dimulai...");
  Serial.println("------------------------------------");
}

void loop() {
  // Baca nilai analog dari pin sensor
  // Nilainya akan berkisar antara 0 (sangat basah) hingga 4095 (sangat kering)
  nilaiLembap = analogRead(pinSensorLembap);

  // Tampilkan nilai mentah dari sensor
  Serial.print("Nilai Sensor Mentah: ");
  Serial.println(nilaiLembap);

  // Untuk memudahkan, kita bisa tambahkan logika sederhana
  // Angka '2000' ini hanya contoh, bisa disesuaikan nanti.
  if (nilaiLembap < 2000) {
    Serial.println("Status: Lembap / Basah");
  } else {
    Serial.println("Status: Kering");
  }
  
  Serial.println("------------------------------------");

  // Beri jeda 1 detik sebelum pengukuran berikutnya
  delay(1000);
}