#include <WiFi.h>
#include <WebServer.h>

#define RED_LED 25
#define BLUE_LED 26
#define GREEN_LED 27
#define WHITE_LED 33

const char* ssid = "ESP32_LED";
const char* password = "12345678";

WebServer server(80);

bool redState = false;
bool blueState = false;
bool greenState = false;
bool whiteState = false;

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>UR.SURENDRA</title>

<style>
body {
  background: #0759e8;
  color: white;
  font-family: Arial;
  text-align: center;
  margin: 0;
  padding-top: 30px;
}

h1 {
  font-size: 30px;
  margin: 5px;
}

h2 {
  font-size: 21px;
  margin: 5px;
}

h3 {
  font-size: 18px;
  margin-top: 5px;
  margin-bottom: 45px;
}

.row {
  width: 90%;
  margin: 0 auto 35px auto;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.label {
  font-size: 21px;
  font-weight: bold;
}

.red {
  color: #ff7777;
}

.blue {
  color: #55eaff;
}

.green {
  color: #55ff88;
}

.white {
  color: white;
}

.switch {
  position: relative;
  display: inline-block;
  width: 62px;
  height: 34px;
}

.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  left: 0;
  right: 0;
  top: 0;
  bottom: 0;
  background-color: white;
  border-radius: 34px;
  cursor: pointer;
}

.slider:before {
  content: "";
  position: absolute;
  width: 26px;
  height: 26px;
  left: 4px;
  bottom: 4px;
  background-color: #cccccc;
  border-radius: 50%;
  transition: 0.2s;
}

input:checked + .slider {
  background-color: #222222;
}

input:checked + .slider:before {
  transform: translateX(28px);
  background-color: #00ff66;
}
</style>
</head>

<body>

<h1>UR.SURENDRA</h1>
<h2>ESP32 PROJECT</h2>
<h3>LED CONTROLLERS</h3>

<div class="row">
<span class="label red">Red LED ON/OFF :</span>
<label class="switch">
<input type="checkbox" id="red" onchange="changeLED('red', this.checked)">
<span class="slider"></span>
</label>
</div>

<div class="row">
<span class="label blue">Blue LED ON/OFF :</span>
<label class="switch">
<input type="checkbox" id="blue" onchange="changeLED('blue', this.checked)">
<span class="slider"></span>
</label>
</div>

<div class="row">
<span class="label green">Green LED ON/OFF :</span>
<label class="switch">
<input type="checkbox" id="green" onchange="changeLED('green', this.checked)">
<span class="slider"></span>
</label>
</div>

<div class="row">
<span class="label white">White LED ON/OFF :</span>
<label class="switch">
<input type="checkbox" id="white" onchange="changeLED('white', this.checked)">
<span class="slider"></span>
</label>
</div>

<script>
function changeLED(color, state) {
  var value = state ? "on" : "off";

  fetch("/" + color + "?state=" + value)
  .then(function(response) {
    return response.text();
  })
  .then(function(data) {
    console.log(data);
  })
  .catch(function(error) {
    console.log(error);
  });
}
</script>

</body>
</html>
)rawliteral";

  return html;
}

void handleRoot() {
  server.send(200, "text/html", makePage());
}

void handleRed() {
  if (server.hasArg("state")) {
    redState = (server.arg("state") == "on");
  }

  digitalWrite(RED_LED, redState ? HIGH : LOW);

  server.send(200, "text/plain", redState ? "RED ON" : "RED OFF");
}

void handleBlue() {
  if (server.hasArg("state")) {
    blueState = (server.arg("state") == "on");
  }

  digitalWrite(BLUE_LED, blueState ? HIGH : LOW);

  server.send(200, "text/plain", blueState ? "BLUE ON" : "BLUE OFF");
}

void handleGreen() {
  if (server.hasArg("state")) {
    greenState = (server.arg("state") == "on");
  }

  digitalWrite(GREEN_LED, greenState ? HIGH : LOW);

  server.send(200, "text/plain", greenState ? "GREEN ON" : "GREEN OFF");
}

void handleWhite() {
  if (server.hasArg("state")) {
    whiteState = (server.arg("state") == "on");
  }

  digitalWrite(WHITE_LED, whiteState ? HIGH : LOW);

  server.send(200, "text/plain", whiteState ? "WHITE ON" : "WHITE OFF");
}

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);

  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(WHITE_LED, LOW);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/red", handleRed);
  server.on("/blue", handleBlue);
  server.on("/green", handleGreen);
  server.on("/white", handleWhite);

  server.begin();
}

void loop() {
  server.handleClient();
}
