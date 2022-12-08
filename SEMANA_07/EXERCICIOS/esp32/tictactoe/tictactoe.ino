#include <WiFi.h>
#include <HTTPClient.h>
#include <String.h>

#define LEDX 21
#define LEDTIE 47
#define LEDO 48

#define ssid "WIFI_SSID"
#define password "WIFI_PASSWORD"

String serverURL = "SERVER_URL";

void initWiFi(char* _ssid, char* _password) {
  WiFi.begin(_ssid, _password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.print("Connected to Wi-Fi Network ");
  Serial.println(_ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}


String getWinner() {
  String winnerStatus = "0";

  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;

    String serverPath = serverURL + "/winner";
    
    http.begin(serverPath.c_str());
    
    int httpResponseCode = http.GET();
    
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
      winnerStatus = payload;
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }

  return winnerStatus;
}

void setup() {
  Serial.begin(115200);

  pinMode(LEDX, OUTPUT);
  pinMode(LEDO, OUTPUT);
  pinMode(LEDTIE, OUTPUT);

  WiFi.mode(WIFI_STA);
  initWiFi(ssid, password);

}

void loop() {
  String winner = getWinner();

  if (winner == "0") {
      digitalWrite(LEDX, LOW);
      digitalWrite(LEDO, LOW);
      digitalWrite(LEDTIE, LOW);
  } else if (winner == "1"){
      digitalWrite(LEDX, HIGH);
  } else if (winner == "2"){
      digitalWrite(LEDO, HIGH);
  } else if (winner == "3") {
      digitalWrite(LEDTIE, HIGH);
  }

  delay(1000);
}