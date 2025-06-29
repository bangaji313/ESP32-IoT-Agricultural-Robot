// === Pengujian Motor Stepper 28BYJ-48 ===

#include <Stepper.h>

// Jumlah langkah untuk satu putaran penuh pada motor ini adalah 2048
const int stepsPerRevolution = 2048;

// Inisialisasi library Stepper.
// PENTING: Urutan pin untuk library ini adalah IN1, IN3, IN2, IN4.
// Jadi kita masukkan pin kita sesuai urutan tersebut: D19, D5, D18, D4
Stepper myStepper(stepsPerRevolution, 19, 5, 18, 4);

void setup() {
  // Mulai komunikasi serial
  Serial.begin(115200);

  // Atur kecepatan motor stepper (RPM - Rotations Per Minute)
  // Kita set kecepatan rendah agar pergerakan langkahnya terlihat jelas
  myStepper.setSpeed(15);
  
  Serial.println("Pengujian Motor Stepper dimulai...");
}

void loop() {
  // 1. Berputar searah jarum jam
  Serial.println("Berputar searah jarum jam (Clockwise)...");
  // Perintahkan motor untuk bergerak sebanyak satu putaran penuh
  myStepper.step(stepsPerRevolution);
  delay(1000); // Jeda 1 detik

  // 2. Berputar berlawanan arah jarum jam
  Serial.println("Berputar berlawanan arah jarum jam (Counter-Clockwise)...");
  // Gunakan nilai negatif untuk arah sebaliknya
  myStepper.step(-stepsPerRevolution);
  delay(1000); // Jeda 1 detik
}