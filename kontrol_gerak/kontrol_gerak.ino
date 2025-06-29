// === KODE PROGRAM FINAL - TAHAP 1: KONTROL GERAK ===

// ----------------------------------------------------
// BAGIAN 1: KREDENSIAL & LIBRARY
// ----------------------------------------------------
#define BLYNK_TEMPLATE_ID   "TMPL6D05MZ_Cd"
#define BLYNK_TEMPLATE_NAME "SeedRon Robot"
#define BLYNK_DEVICE_NAME   "SeedRon V1"
#define BLYNK_AUTH_TOKEN    "bAO9vNDBDMTnrZQJpHouSmT47JnZI_rN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Info WiFi Anda
char ssid[] = "antangin";
char pass[] = "ultraman123";
char auth[] = BLYNK_AUTH_TOKEN;

// ----------------------------------------------------
// BAGIAN 2: DEFINISI PIN & VARIABEL MOTOR
// (Disalin dari kode uji motor)
// ----------------------------------------------------
// Definisi pin untuk motor kiri (Channel A di L298N)
const int ENA = 33;
const int IN1 = 25;
const int IN2 = 26;

// Definisi pin untuk motor kanan (Channel B di L298N)
const int ENB = 32;
const int IN3 = 27;
const int IN4 = 14;

// Variabel untuk kecepatan motor (0-255)
// Ingat, kita pakai 4 baterai, jadi set kecepatan jangan terlalu tinggi
int kecepatan = 255;


// ----------------------------------------------------
// BAGIAN 3: FUNGSI KONTROL BLYNK (JEMBATAN KONTROL)
// Ini adalah bagian baru yang paling penting
// ----------------------------------------------------

BLYNK_WRITE(V0) { // Fungsi untuk tombol Maju
  Serial.println("--- Perintah MAJU (V0) diterima dari Blynk! ---"); // <-- TAMBAHKAN INI
  int pinValue = param.asInt();
  if (pinValue == 1) { maju(); } else { berhenti(); }
}

BLYNK_WRITE(V8) { // Fungsi untuk tombol Mundur
  Serial.println("--- Perintah MUNDUR (V8) diterima dari Blynk! ---"); // <-- TAMBAHKAN INI
  int pinValue = param.asInt();
  if (pinValue == 1) { mundur(); } else { berhenti(); }
}

BLYNK_WRITE(V9) { // Fungsi untuk tombol Kiri
  Serial.println("--- Perintah KIRI (V9) diterima dari Blynk! ---"); // <-- TAMBAHKAN INI
  int pinValue = param.asInt();
  if (pinValue == 1) { belokKiri(); } else { berhenti(); }
}

BLYNK_WRITE(V10) { // Fungsi untuk tombol Kanan
  Serial.println("--- Perintah KANAN (V10) diterima dari Blynk! ---"); // <-- TAMBAHKAN INI
  int pinValue = param.asInt();
  if (pinValue == 1) { belokKanan(); } else { berhenti(); }
}

BLYNK_WRITE(V11) { // Fungsi untuk tombol Stop
  Serial.println("--- Perintah STOP (V11) diterima dari Blynk! ---"); // <-- TAMBAHKAN INI
  berhenti();
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // Atur semua pin motor sebagai OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Set kecepatan awal motor
  analogWrite(ENA, kecepatan);
  analogWrite(ENB, kecepatan);
}

void loop() {
  // Hanya jalankan Blynk.run() di loop utama
  Blynk.run();
}

// ----------------------------------------------------
// BAGIAN 4: FUNGSI-FUNGSI GERAKAN
// (Disalin dari kode uji motor)
// ----------------------------------------------------
void maju() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKanan() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}