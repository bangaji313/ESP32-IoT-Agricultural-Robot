// === KODE PROGRAM FINAL - TAHAP 2: KONTROL GERAK + LAPORAN SENSOR ===

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
// BAGIAN 2: DEFINISI PIN & OBJEK GLOBAL
// ----------------------------------------------------
// Objek Timer Blynk
BlynkTimer timer;

// Pin untuk motor DC (dari Tahap 1)
const int ENA = 33;
const int IN1 = 25;
const int IN2 = 26;
const int ENB = 32;
const int IN3 = 27;
const int IN4 = 14;
int kecepatan = 170;

// Pin untuk Sensor Ultrasonik
const int trigPin = 23;
const int echoPin = 22;

// Pin untuk Sensor Kelembapan
const int pinSensorLembap = 34;


// ----------------------------------------------------
// BAGIAN 3: FUNGSI PEMBACAAN DAN PENGIRIMAN DATA
// ----------------------------------------------------
// Fungsi ini akan dijalankan oleh Timer setiap 1 detik
void kirimDataSensor() {
  // --- Membaca Sensor Ultrasonik ---
  long duration;
  int jarak;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  
  // Mengirim nilai 'jarak' ke widget yang terhubung ke Virtual Pin 1
  Blynk.virtualWrite(V1, jarak); 

  // --- Membaca Sensor Kelembapan ---
  int nilaiLembap = analogRead(pinSensorLembap);
  
  // Mengirim status (0 atau 1) ke widget LED yang terhubung ke Virtual Pin 2
  if (nilaiLembap < 2000) { // Anggap nilai di bawah 2000 itu lembap
    Blynk.virtualWrite(V2, 1); // Kirim 1 (membuat LED di Blynk ON)
  } else {
    Blynk.virtualWrite(V2, 0); // Kirim 0 (membuat LED di Blynk OFF)
  }
  
  // Mencetak ke Serial Monitor untuk debugging kita
  Serial.print("Jarak: ");
  Serial.print(jarak);
  Serial.print(" cm | Nilai Lembap: ");
  Serial.println(nilaiLembap);
}


// ----------------------------------------------------
// BAGIAN 4: FUNGSI KONTROL BLYNK (DARI TAHAP 1)
// ----------------------------------------------------
BLYNK_WRITE(V0) { if (param.asInt() == 1) { maju(); } else { berhenti(); } }
BLYNK_WRITE(V8) { if (param.asInt() == 1) { mundur(); } else { berhenti(); } }
BLYNK_WRITE(V9) { if (param.asInt() == 1) { belokKiri(); } else { berhenti(); } }
BLYNK_WRITE(V10) { if (param.asInt() == 1) { belokKanan(); } else { berhenti(); } }
BLYNK_WRITE(V11) { if (param.asInt() == 1) { berhenti(); } }


// ----------------------------------------------------
// BAGIAN 5: SETUP UTAMA
// ----------------------------------------------------
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  // Setup pin motor sebagai OUTPUT
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Setup pin sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pinSensorLembap, INPUT);
  
  analogWrite(ENA, kecepatan);
  analogWrite(ENB, kecepatan);

  // Atur Timer untuk menjalankan fungsi 'kirimDataSensor' setiap 1 detik (1000 milidetik)
  timer.setInterval(1000L, kirimDataSensor);
}


// ----------------------------------------------------
// BAGIAN 6: LOOP UTAMA
// ----------------------------------------------------
void loop() {
  Blynk.run(); // Menjaga koneksi ke Blynk
  timer.run(); // Menjalankan timer
}


// ----------------------------------------------------
// BAGIAN 7: FUNGSI-FUNGSI GERAKAN (DARI TAHAP 1)
// ----------------------------------------------------
void maju() { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void mundur() { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
void belokKanan() { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
void belokKiri() { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void berhenti() { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }