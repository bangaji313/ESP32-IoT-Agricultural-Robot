// === KODE PROGRAM FINAL LENGKAP - SEEDRON V1 ===

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
#include <Stepper.h> // Library baru untuk motor stepper

// Info WiFi Anda
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
int kecepatan = 255;

// Pin Sensor
const int trigPin = 23, echoPin = 22;
const int pinSensorLembap = 34;

// Pin Indikator
const int pinLedHijau = 2, pinLedKuning = 16, pinLedMerah = 17;
const int pinBuzzer = 15;

// Pin Motor Stepper
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 19, 5, 18, 4); // Urutan: IN1, IN3, IN2, IN4

// Variabel Global untuk menyimpan status robot
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
void updateStatusBlynk(String statusTeks) {
  Blynk.virtualWrite(V7, statusTeks);
}

BLYNK_WRITE(V0) { if (param.asInt() == 1) { maju(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V8) { if (param.asInt() == 1) { mundur(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V9) { if (param.asInt() == 1) { belokKiri(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V10) { if (param.asInt() == 1) { belokKanan(); isMoving = true; } else { berhenti(); isMoving = false; } }
BLYNK_WRITE(V11) { if (param.asInt() == 1) { berhenti(); isMoving = false; } }

BLYNK_WRITE(V3) { // Tombol manual stepper
  if (param.asInt() == 1) {
    manualStepperTrigger = true;
  }
}

BLYNK_WRITE(V6) { // Saklar Mute Buzzer
  isBuzzerMuted = param.asInt();
}

// ----------------------------------------------------
// BAGIAN 4: FUNGSI PEMBACAAN SENSOR (Dijalankan Timer)
// ----------------------------------------------------
void bacaSemuaSensor() {
  // Baca Sensor Ultrasonik
  long duration;
  digitalWrite(trigPin, LOW); delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  jarak = duration * 0.034 / 2;
  isObstacle = (jarak < 20 && jarak > 0); // Anggap halangan jika jarak di bawah 20 cm
  Blynk.virtualWrite(V1, jarak);

  // Baca Sensor Kelembapan
  nilaiLembap = analogRead(pinSensorLembap);
  isMoist = (nilaiLembap < 2000);
  Blynk.virtualWrite(V2, isMoist ? 1 : 0);
}


// ----------------------------------------------------
// BAGIAN 5: FUNGSI-FUNGSI AKSI & LOGIKA
// ----------------------------------------------------
void putarStepper() {
  Serial.println("AKSI: Menanam...");
  Blynk.virtualWrite(V4, 1); // Kirim status stepper ON ke Blynk
  updateStatusBlynk("Menanam...");
  myStepper.step(stepsPerRevolution); // Putar satu putaran
  Blynk.virtualWrite(V4, 0); // Kirim status stepper OFF
  manualStepperTrigger = false; // Reset pemicu manual
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
    digitalWrite(pinLedKuning, HIGH); // Kuning solid saat bergerak
    digitalWrite(pinLedHijau, LOW);
    noTone(pinBuzzer);
    updateStatusBlynk("Bergerak...");
  } else { // Kondisi diam / siaga
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

  // Setup pin (motor, sensor, indikator)
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(trigPin, OUTPUT); pinMode(echoPin, INPUT);
  pinMode(pinSensorLembap, INPUT);
  pinMode(pinLedHijau, OUTPUT); pinMode(pinLedKuning, OUTPUT); pinMode(pinLedMerah, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  myStepper.setSpeed(15); // Set kecepatan stepper
  
  // Atur Timer untuk menjalankan fungsi 'bacaSemuaSensor' setiap 250 milidetik
  timer.setInterval(250L, bacaSemuaSensor);
}

void loop() {
  Blynk.run();
  timer.run();
  
  // --- OTAK UTAMA ROBOT ---
  // 1. Logika prioritas: Halangan adalah yang utama
  if (isObstacle) {
    berhenti();
  }

  // 2. Logika Stepper
  if (manualStepperTrigger || isMoist) {
    putarStepper();
  }
  
  // 3. Logika Indikator
  updateIndikator();
}

// ----------------------------------------------------
// BAGIAN 7: FUNGSI-FUNGSI GERAKAN DASAR
// ----------------------------------------------------
void maju() { if (!isObstacle) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); } }
void mundur() { if (!isObstacle) { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); } }
void belokKanan() { if (!isObstacle) { digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); } }
void belokKiri() { if (!isObstacle) { digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); } }
void berhenti() { digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); }