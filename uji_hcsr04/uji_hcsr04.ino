// === Pengujian Sensor Ultrasonik HC-SR04 ===

// Definisi pin untuk Sensor Ultrasonik sesuai kesepakatan
const int trigPin = 23; // Pin untuk mengirim sinyal suara
const int echoPin = 22; // Pin untuk menerima pantulan suara

// Variabel untuk menyimpan durasi dan jarak
long duration;
int distance;

void setup() {
  // Mulai komunikasi serial untuk menampilkan hasil ke laptop
  Serial.begin(115200);

  // Atur pin Trig sebagai OUTPUT (karena kita mengirim sinyal)
  pinMode(trigPin, OUTPUT);
  // Atur pin Echo sebagai INPUT (karena kita menerima sinyal)
  pinMode(echoPin, INPUT);

  Serial.println("Pengujian Sensor Ultrasonik dimulai...");
}

void loop() {
  // Untuk memulai pengukuran, kita perlu mengirim sebuah pulsa pendek
  // 1. Matikan dulu pin Trig untuk memastikan sinyal bersih
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. Kirim pulsa HIGH selama 10 mikrodetik
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Baca durasi waktu pantulan suara diterima kembali
  // pulseIn() akan mengukur berapa lama pin Echo tetap HIGH
  duration = pulseIn(echoPin, HIGH);

  // 4. Hitung jarak berdasarkan durasi
  // Rumus: Jarak = (Durasi * Kecepatan Suara) / 2
  // Kecepatan suara = 0.034 cm/mikrodetik
  // Dibagi 2 karena durasi adalah waktu bolak-balik (pergi dan pulang)
  distance = duration * 0.034 / 2;

  // 5. Tampilkan hasilnya ke Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Beri jeda setengah detik sebelum pengukuran berikutnya
  delay(500);
}