// === KODE PROGRAM FINAL LENGKAP - VERSI PERBAIKAN MOTOR ===

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
#include <Stepper.h>

char ssid[] = "antangin";
char pass[] = "ultraman123";
char auth[] = BLYNK_AUTH_TOKEN;

// ----------------------------------------------------
// BAGIAN 2: DEFINISI PIN & OBJEK GLOBAL
// ----------------------------------------------------
BlynkTimer timer;

// Pin motor DC
const int ENA = 33, IN1 = 25, IN2 = 26;
const int ENB = 32, IN3 = 27, IN4 = 14;
int kecepatan = 255; // Atur atur biar ga terlalu panas

// Pin Sensor & Indikator
const int trigPin = 23, echoPin = 22;
const int pinSensorLembap = 34;
const int pinLedHijau = 2, pinLedKuning = 16, pinLedMerah = 17;
const int pinBuzzer = 15;

// Konfigurasi Stepper
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 19, 5, 18, 4);

// Variabel Status Global
int jarak = 999;
int nilaiLembap = 4095;
bool isMoist = false;
bool isObstacle = false;
bool manualStepperTrigger = false;
bool isBuzzerMuted = false;
bool isMoving = false;


// ----------------------------------------------------
// BAGIAN 3: FUNGSI-FUNGSI BLYNK
// ----------------------------------------------------
void updateStatusBlynk(String statusTeks) { Blynk.virtualWrite(V7, statusTeks); }

// Fungsi Kontrol Gerak dari Blynk
BLYNK_WRITE(V0) { if (param.asInt() == 1) { maju(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V8) { if (param.asInt() == 1) { mundur(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V9) { if (param.asInt() == 1) { belokKiri(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V10) { if (param.asInt() == 1) { belokKanan(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V11) { if (param.asInt() == 1) { berhenti(); isMoving = false; } }

// Fungsi Kontrol Lainnya dari Blynk
BLYNK_WRITE(V3) { if (param.asInt() == 1) { manualStepperTrigger = true; } }
BLYNK_WRITE(V6) { isBuzzerMuted = param.asInt(); }


// ----------------------------------------------------
// BAGIAN 4: FUNGSI PEMBACAAN SENSOR (Dijalankan Timer)
// ----------------------------------------------------
void bacaSemuaSensor() {
  long duration;
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  isObstacle = (jarak < 20 && jarak > 0);
  Blynk.virtualWrite(V1, jarak);
  nilaiLembap = analogRead(pinSensorLembap);
  isMoist = (nilaiLembap < 2000);
  Blynk.virtualWrite(V2, isMoist ? 1 : 0);
}


// ----------------------------------------------------
// BAGIAN 5: FUNGSI-FUNGSI AKSI & LOGIKA
// ----------------------------------------------------
void putarStepper() {
  Serial.println("AKSI: Menanam...");
  Blynk.virtualWrite(V4, 1);
  updateStatusBlynk("Menanam...");
  myStepper.step(stepsPerRevolution);
  Blynk.virtualWrite(V4, 0);
  manualStepperTrigger = false;
  Serial.println("AKSI: Selesai menanam.");
}

void updateIndikator() {
  if (isObstacle) {
    digitalWrite(pinLedMerah, HIGH);
    digitalWrite(pinLedKuning, LOW);
    digitalWrite(pinLedHijau, LOW);
    if (!isBuzzerMuted) { tone(pinBuzzer, 3000); }
    updateStatusBlynk("HALANGAN!");
  } else if (isMoving) {
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedKuning, HIGH);
    digitalWrite(pinLedHijau, LOW);
    noTone(pinBuzzer);
    updateStatusBlynk("Bergerak...");
  } else {
    digitalWrite(pinLedMerah, LOW);
    digitalWrite(pinLedKuning, LOW);
    digitalWrite(pinLedHijau, HIGH);
    noTone(pinBuzzer);
    updateStatusBlynk("Siap");
  }
}

// ----------------------------------------------------
// BAGIAN 6: SETUP & LOOP UTAMA
// ----------------------------------------------------
void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  pinMode(pinSensorLembap, INPUT);
  pinMode(pinLedHijau, OUTPUT); pinMode(pinLedKuning, OUTPUT); pinMode(pinLedMerah, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  
  myStepper.setSpeed(15);
  analogWrite(ENA, kecepatan);
  analogWrite(ENB, kecepatan);

  timer.setInterval(250L, bacaSemuaSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  
  // --- OTAK UTAMA ROBOT ---
  // Logika Halangan dinonaktifkan sementara untuk tes, tapi tetap ada di sini
  // if (isObstacle) {
  //   berhenti();
  // }
  
  if (manualStepperTrigger || isMoist) {
    putarStepper();
  }
  
  updateIndikator();
}

// ----------------------------------------------------
// BAGIAN 7: FUNGSI-FUNGSI GERAKAN DASAR
// (Sama seperti kode Tahap 1, direct tanpa syarat)
// ----------------------------------------------------
void maju() { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void mundur() { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
void belokKanan() { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); }
void belokKiri() { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); }
void berhenti() { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }