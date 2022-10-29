
#include <WiFi.h>
#include <FirebaseESP32.h>


#define FIREBASE_HOST "minidata-8543a.firebaseio.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "sVXQrYDBOUZhcsUOdpQkbDPrj1eYZyub7kf1fGzW"
#define WIFI_SSID "NO>>>BODY"
#define WIFI_PASSWORD "aa9b8822y1zz"


//Define FirebaseESP32 data object
FirebaseData firebaseData;

FirebaseJson json;

//void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");


String path = "/Environmental Check";
String s="Hey";
int i=500;
delay(1000);
  if (Firebase.setString(firebaseData, path + "/Humdity", s))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }

    if (Firebase.setInt(firebaseData, path + "/Humidity", i))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("ETag: " + firebaseData.ETag());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
    delay(5000);
}

void loop()
{FirebaseJson updateData;
FirebaseJson json;

for(int json=0;json<100;json++){
updateData.set("data1", json); 
delay(1000); 

if (Firebase.updateNode(firebaseData, "/Environmental Check/Humidity", updateData)) {

  Serial.println(firebaseData.dataPath());

  Serial.println(firebaseData.dataType());

  Serial.println(firebaseData.jsonString()); 

} else {
  Serial.println(firebaseData.errorReason());
}
}
    delay(5000);

}
