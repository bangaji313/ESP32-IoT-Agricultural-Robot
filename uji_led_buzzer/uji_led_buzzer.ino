// === Pengujian Sistem Indikator (LED & Buzzer) - VERSI PERBAIKAN ===

// Definisi pin untuk semua indikator
const int pinLedHijau = 2;
const int pinLedKuning = 16;
const int pinLedMerah = 17;
const int pinBuzzer = 15;

void setup() {
  // Mulai komunikasi serial untuk status
  Serial.begin(115200);

  // Atur semua pin indikator sebagai OUTPUT
  pinMode(pinLedHijau, OUTPUT);
  pinMode(pinLedKuning, OUTPUT);
  pinMode(pinLedMerah, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);

  Serial.println("Pengujian Indikator dimulai (Versi Perbaikan Buzzer)...");
}

void loop() {
  // 1. Tes LED Hijau
  Serial.println("Tes LED Hijau...");
  digitalWrite(pinLedHijau, HIGH);
  delay(1000);
  digitalWrite(pinLedHijau, LOW);
  delay(500);

  // 2. Tes LED Kuning
  Serial.println("Tes LED Kuning...");
  digitalWrite(pinLedKuning, HIGH);
  delay(1000);
  digitalWrite(pinLedKuning, LOW);
  delay(500);

  // 3. Tes LED Merah
  Serial.println("Tes LED Merah...");
  digitalWrite(pinLedMerah, HIGH);
  delay(1000);
  digitalWrite(pinLedMerah, LOW);
  delay(500);

  // 4. Tes Buzzer (dengan metode untuk Buzzer Pasif)
  Serial.println("Tes Buzzer...");
  // Gunakan fungsi tone(pin, frekuensi) untuk menghasilkan nada.
  // 440 Hz adalah frekuensi untuk nada A (nada standar).
  tone(pinBuzzer, 750); // Nyalakan buzzer dengan nada 440 Hz
  delay(1000);           // Biarkan berbunyi selama 1 detik
  noTone(pinBuzzer);     // Matikan buzzer
  delay(500);            // Jeda

  Serial.println("Siklus selesai. Mengulang dalam 2 detik...");
  delay(2000);
}