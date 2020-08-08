int claps = 0;
long detectionSpanInitial = 0;
long detectionSpan = 0;
boolean lightState = false;

int sensorPin = 7;
int relayPin = 8;

void setup() {
    pinMode(sensorPin, INPUT);
    pinMode(relayPin, OUTPUT);
}

void loop() {
    int sensorState = digitalRead(sensorPin);

    // sound detected
    if (sensorState == 1) {
        if (claps == 0) {
            detectionSpanInitial = detectionSpan = millis();
            claps++;
        } else if (claps > 0 && millis()-detectionSpan >= 50) {
            detectionSpan = millis();
            claps++;
        }
    }

    if (millis()-detectionSpanInitial >= 1000) {
        if(claps == 2) {
            if (lightState) {
                lightState = false;
                digitalWrite(relayPin, LOW);
            } else {
                lightState = true;
                digitalWrite(relayPin, HIGH);
            }
         }
        claps = 0;
    }
}
