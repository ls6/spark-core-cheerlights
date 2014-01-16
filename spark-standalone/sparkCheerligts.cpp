TCPClient client;
String responseLine;
String colorName;
unsigned long nextPoll = 0;

void setup() {
    Serial.begin(57600);
    
    delay(2000);
    connectToCheerlights();
}

void connectToCheerlights() {
    Serial.println("connecting to cheerlights...");
    
    if (client.connect("api.thingspeak.com", 80)){
        Serial.println("connected...");
        client.println("GET /channels/1417/field/1/last.txt HTTP/1.0");
        client.println();
    } else {
        Serial.println("connection failed");
    }
    
    responseLine = "";
    colorName = "";
}

void readColor() {
    Serial.println("entering readColor");
    
    while (client.available()) {
        char ch = client.read();
        colorName += ch;
    };
    
    client.stop();
    
    colorName.trim();
    Serial.println(colorName);

    if (colorName == "purple") {
        switchColor(49);
    } else if (colorName == "red") {
        switchColor(50);
    } else if (colorName == "green") {
        switchColor(51);
    } else if (colorName == "blue") {
        switchColor(52);
    } else if (colorName == "cyan") {
        switchColor(53);
    } else if (colorName == "white") {
        switchColor(54);
    } else if (colorName == "warmwhite") {
        switchColor(55);
    } else if (colorName == "magenta") {
        switchColor(56);
    } else if (colorName == "yellow") {
        switchColor(57);
    } else if (colorName == "orange") {
        switchColor(97);
    } else if (colorName == "pink") {
        switchColor(98);
    } else if (colorName == "oldlace") {
        switchColor(55);
    } else {
        RGB.control(false);
        Serial.println("didn't find the color");
        Serial.println(colorName);
        Serial.println(colorName.length());
    };
}

void switchColor (int color) {
    
    switch (color) {
        case 49:
            RGB.control(true);
            RGB.color(128,0,128);
            break;
        case 50:
            RGB.control(true);
            RGB.color(255,0,0);
            break;
        case 51:
            RGB.control(true);
            RGB.color(0,255,0);
            break;
        case 52:
            RGB.control(true);
            RGB.color(0,0,255);
            break;
        case 53:
            RGB.control(true);
            RGB.color(0,255,255);
            break;
        case 54:
            RGB.control(true);
            RGB.color(255,255,255);
            break;
        case 55:
            RGB.control(true);
            RGB.color(253,245,230);
            break;
        case 56:
            RGB.control(true);
            RGB.color(255,0,255);
            break;
        case 57:
            RGB.control(true);
            RGB.color(255,255,0);    
            break;
        case 97:
            RGB.control(true);
            RGB.color(255,165,0);
            break;
        case 98:
            RGB.control(true);
            RGB.color(255,192,203);
            break;
        default:
            RGB.control(false);
    };
}

void loop() {
    if (nextPoll <= millis()) {
        nextPoll = millis()+60000;
        connectToCheerlights();
    };
    
    if (client.available()) {
        char ch = client.read();
        responseLine += ch;
        Serial.print(ch);
        //if end of line found
        if (ch == 10) {
            Serial.println(responseLine.length());
            if (responseLine.length() == 2) {
                readColor();
            };
            responseLine = "";
        };
    };

    if (Serial.available() > 0) {
        char cmd = Serial.read();
        Serial.print("got: ");
        Serial.println(cmd);
        switchColor(cmd);
    };
}
