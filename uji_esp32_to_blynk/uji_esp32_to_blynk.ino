// === Pengujian Koneksi ESP32 ke Blynk ===

#define BLYNK_TEMPLATE_ID "TMPL6D05MZ_Cd"
#define BLYNK_TEMPLATE_NAME "SeedRon Robot"
#define BLYNK_DEVICE_NAME   "SeedRon V1"
#define BLYNK_AUTH_TOKEN    "bAO9vNDBDMTnrZQJpHouSmT47JnZI_rN"

// Jangan ubah baris ini
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// PENTING: Ganti dengan info WiFi Anda
char ssid[] = "antangin";
char pass[] = "ultraman123";

// Salin Auth Token Anda ke sini juga
char auth[] = BLYNK_AUTH_TOKEN;

void setup() {
  // Mulai komunikasi serial untuk melihat log koneksi
  Serial.begin(115200);
  delay(100);

  Serial.println("Mencoba menghubungkan ke Blynk...");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Koneksi ke Blynk berhasil!");
}

void loop() {
  // Fungsi ini wajib ada untuk menjaga koneksi ke server Blynk
  Blynk.run();
}