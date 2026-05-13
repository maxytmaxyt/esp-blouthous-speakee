#include <Arduino.h>

// PIN-WAHL: Nimm GPIO 34 (oft als D34 beschriftet)
const int BUTTON_PIN = 34; 

void setup() {
    Serial.begin(115200);
    // Der ESP32 ADC ist manchmal etwas ungenau, wir stellen ihn stabil ein
    analogReadResolution(12); // 0 - 4095
    
    Serial.println("======================================");
    Serial.println("   BUTTON-PAD ANALYSE-MODUS AKTIV     ");
    Serial.println("======================================");
    Serial.println("Drücke jetzt nacheinander alle Buttons...");
}

void loop() {
    int rawValue = analogRead(BUTTON_PIN);

    // Filter: Nur Werte anzeigen, wenn sich wirklich was tut.
    // Falls dein Monitor ohne Tastendruck durchrast, ändere 4000 auf 100 oder 4090.
    if (rawValue < 4000 && rawValue > 50) { 
        Serial.print("Gefundener Wert: ");
        Serial.print(rawValue);
        Serial.println("  <--- Diesen Wert für diesen Button notieren!");
        
        delay(400); // Pause, damit der Monitor nicht mit dem gleichen Wert flutet
    }
}
