#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h> 

#define FIREBASE_HOST "tubesiot-a2e9c.firebaseio.com"
#define FIREBASE_AUTH "yRHiYAel2aSBXYar4xbCLAb5jnuAbypndTsma9kr"
#define WIFI_SSID "rexus"
#define WIFI_PASSWORD "Abi180798"

#define buzzer D7

Servo myservo;
int servoPin = D5;

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  pinMode(buzzer, OUTPUT);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  myservo.write(0);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}


void loop() {
  if (Firebase.getInt("makan") == 1){
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
    }else{
      Serial.println(Firebase.getInt("makan"));
      myservo.write(45);
      delay(100);
      Firebase.setInt("makan", 0);
      myservo.write(0);
    }
  }

  
  if (Firebase.getInt("isi") <= 7 ){
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
    }else{
      Serial.println(Firebase.getInt("isi"));
      digitalWrite(buzzer, LOW);
      Serial.println("Masih Ada");
    }
  }else{
    if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());
      return;
    }else{
      Serial.println(Firebase.getInt("isi"));
      Serial.println("Silahkan isi kembali");
      digitalWrite(buzzer, HIGH);
    }
  }
}
