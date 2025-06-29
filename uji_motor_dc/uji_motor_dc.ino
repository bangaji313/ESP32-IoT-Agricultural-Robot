// === Pengujian Motor DC untuk Robot SeedRon ===

// Definisi pin untuk motor kiri (Channel A di L298N)
const int ENA = 33; // Enable A - Mengatur kecepatan motor kiri
const int IN1 = 25;
const int IN2 = 26;

// Definisi pin untuk motor kanan (Channel B di L298N)
const int ENB = 32; // Enable B - Mengatur kecepatan motor kanan
const int IN3 = 27;
const int IN4 = 14;

// Variabel untuk kecepatan motor (0-255)
int kecepatan = 200; // Kita set kecepatan sedang untuk pengujian

void setup() {
  // Mulai komunikasi serial untuk menampilkan status
  Serial.begin(115200);

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

  Serial.println("Pengujian motor dimulai...");
}

void loop() {
  // 1. Bergerak Maju
  Serial.println("Maju...");
  maju();
  delay(2000); // Jalan maju selama 2 detik

  // 2. Berhenti
  Serial.println("Berhenti...");
  berhenti();
  delay(1000); // Berhenti selama 1 detik

  // 3. Bergerak Mundur
  Serial.println("Mundur...");
  mundur();
  delay(2000); // Jalan mundur selama 2 detik

  // 4. Berhenti
  Serial.println("Berhenti...");
  berhenti();
  delay(1000); // Berhenti selama 1 detik

  // 5. Belok Kanan (Pivot Turn)
  Serial.println("Belok Kanan...");
  belokKanan();
  delay(1000); // Belok selama 1 detik

  // 6. Belok Kiri (Pivot Turn)
  Serial.println("Belok Kiri...");
  belokKiri();
  delay(1000); // Belok selama 1 detik
  
  // 7. Berhenti
  Serial.println("Berhenti...");
  berhenti();
  delay(2000); // Berhenti selama 2 detik sebelum siklus berulang
}

// === Kumpulan Fungsi Gerakan ===

void maju() {
  // Kiri Maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Kanan Maju
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void mundur() {
  // Kiri Mundur
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Kanan Mundur
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKanan() {
  // Kiri Maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Kanan Mundur (untuk berputar di tempat)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void belokKiri() {
  // Kiri Mundur
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Kanan Maju
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void berhenti() {
  // Matikan kedua sisi motor
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}