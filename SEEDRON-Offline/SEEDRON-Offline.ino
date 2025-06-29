// === KODE PROGRAM FINAL - VERSI DEMONSTRASI OFFLINE ===

#include <Stepper.h> // Hanya butuh library Stepper

// ----------------------------------------------------
// BAGIAN 1: DEFINISI PIN & OBJEK GLOBAL
// (Sama seperti sebelumnya, tanpa yang berhubungan dengan Blynk)
// ----------------------------------------------------
// Pin motor DC
const int ENA = 33, IN1 = 25, IN2 = 26;
const int ENB = 32, IN3 = 27, IN4 = 14;
int kecepatan = 205; // Kecepatan aman untuk 4 baterai

// Pin Sensor & Indikator
const int trigPin = 23, echoPin = 22;
const int pinSensorLembap = 34;
const int pinLedHijau = 2, pinLedKuning = 16, pinLedMerah = 17;
const int pinBuzzer = 15;

// Konfigurasi Stepper
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 19, 5, 18, 4); // Urutan: IN1, IN3, IN2, IN4

// Variabel Status Global
int jarak = 999;
bool isMoist = false;
bool isObstacle = false;

// ----------------------------------------------------
// BAGIAN 2: FUNGSI-FUNGSI AKSI & LOGIKA DASAR
// ----------------------------------------------------
void bacaSensorJarak() {
  long duration;
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  isObstacle = (jarak < 20 && jarak > 0);
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.println(" cm");
}

void bacaSensorLembap() {
  int nilaiLembap = analogRead(pinSensorLembap);
  isMoist = (nilaiLembap < 2000);
  Serial.print("Tanah Lembap: ");
  Serial.println(isMoist ? "YA" : "TIDAK");
}

void putarStepper() {
  Serial.println("AKSI: Menanam...");
  digitalWrite(pinLedKuning, LOW); // Matikan lampu gerak
  digitalWrite(pinLedHijau, LOW);
  // Lampu penanda khusus saat menanam
  for(int i=0; i<5; i++){
    digitalWrite(pinLedKuning, HIGH);
    delay(100);
    digitalWrite(pinLedKuning, LOW);
    delay(100);
  }
  myStepper.step(stepsPerRevolution);
  Serial.println("AKSI: Selesai menanam.");
}

// Fungsi Gerakan Dasar
void maju() { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void mundur() { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
void berhenti() { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }

// ----------------------------------------------------
// BAGIAN 3: SETUP UTAMA
// ----------------------------------------------------
void setup() {
  Serial.begin(115200);

  // Setup semua pin sebagai OUTPUT atau INPUT
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  pinMode(pinSensorLembap, INPUT);
  pinMode(pinLedHijau, OUTPUT); pinMode(pinLedKuning, OUTPUT); pinMode(pinLedMerah, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  myStepper.setSpeed(15);
  analogWrite(ENA, kecepatan);
  analogWrite(ENB, kecepatan);
  
  Serial.println("Mode Demonstrasi Otomatis Siap.");
  digitalWrite(pinLedHijau, HIGH); // Nyalakan lampu hijau tanda siap
}


// ----------------------------------------------------
// BAGIAN 4: LOOP UTAMA (Skenario Demonstrasi)
// ----------------------------------------------------
void loop() {
  Serial.println("\n=== MEMULAI SIKLUS DEMO BARU ===");
  digitalWrite(pinLedHijau, HIGH); // Status Siap
  digitalWrite(pinLedKuning, LOW);
  digitalWrite(pinLedMerah, LOW);
  noTone(pinBuzzer);
  delay(3000); // Tunggu 3 detik

  // --- Skenario 1: Bergerak maju dan menemukan tanah lembap ---
  Serial.println("DEMO: Bergerak maju mencari lokasi tanam...");
  digitalWrite(pinLedHijau, LOW);
  digitalWrite(pinLedKuning, HIGH); // Lampu kuning tanda bergerak
  maju();
  delay(3000); // Bergerak maju selama 3 detik
  berhenti();
  digitalWrite(pinLedKuning, LOW);
  
  Serial.println("DEMO: Berhenti dan memeriksa tanah...");
  delay(1000);
  bacaSensorLembap();
  if (isMoist) {
    // Jika sensor mendeteksi lembap (misal Anda celupkan ke air), jalankan aksi tanam
    putarStepper();
  } else {
    Serial.println("DEMO: Tanah kering, aksi tanam dilewati.");
  }
  delay(2000);

  // --- Skenario 2: Bergerak maju dan menghindari halangan ---
  Serial.println("DEMO: Melanjutkan pergerakan...");
  digitalWrite(pinLedKuning, HIGH); // Lampu kuning tanda bergerak
  maju();

  // Bergerak maju sambil terus mengecek sensor jarak selama 5 detik
  unsigned long start_time = millis();
  while (millis() - start_time < 5000) {
    bacaSensorJarak();
    if (isObstacle) {
      Serial.println("DEMO: HALANGAN TERDETEKSI! Berhenti!");
      berhenti();
      digitalWrite(pinLedKuning, LOW);
      digitalWrite(pinLedMerah, HIGH); // Lampu merah tanda bahaya
      tone(pinBuzzer, 3000);         // Buzzer berbunyi
      delay(3000);                   // Berhenti dengan alarm selama 3 detik
      noTone(pinBuzzer);
      break; // Keluar dari loop `while`
    }
    delay(100); // Cek sensor setiap 100ms
  }
  
  // Jika selama 5 detik tidak ada halangan, tetap berhenti
  berhenti();
  digitalWrite(pinLedKuning, LOW);

  // Siklus demo selesai, akan berulang dari awal setelah jeda
  Serial.println("=== SIKLUS DEMO SELESAI ===");
  delay(5000);
}