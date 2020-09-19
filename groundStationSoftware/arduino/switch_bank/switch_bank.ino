// declaring switch inputs
#define SWITCH1 2
#define SWITCH2 3
#define SWITCH3 4
#define SWITCH4 5
#define SWITCH5 6
#define SWITCH6 7
#define SWITCH7 8
#define SWITCH8 9
#define SWITCH9 10

// Switch class
class Switch {
    const static unsigned long debounceDelay = 50;

public:
    Switch(int pin, unsigned char eventNbr) : pin(pin), eventNbr(eventNbr) {}
    Switch(){}

    int getPin() {return pin;}

    void update(unsigned long currentTime) {
        
        currentState = digitalRead(pin);

        if (currentState != oldState) {
            lastDebounceTime = millis();
            
            if ((currentTime - lastDebounceTime) > debounceDelay) {
                if (currentState == HIGH) {
                    Serial.write(eventNbr);
                }
                oldState = currentState;
            };
        };

    }
private:
    int pin; // pin number
    int currentState = 0;
    int oldState = 0;
    unsigned char eventNbr; // char to send if pressed
    unsigned long lastDebounceTime = 0;
};

// Sin number for each switch
int switchPins[9] = {SWITCH1, SWITCH2, SWITCH3, SWITCH4, SWITCH5, SWITCH6, SWITCH7, SWITCH8, SWITCH9};

// list of switch
Switch Switches[9];

void setup() {

    // create switches
    for(int i = 0; i < 9; i++) {
        Switches[i] = Switch(switchPins[i], (unsigned char)i);
        pinMode(Switches[i].getPin(), INPUT);
    }

    // begin serial communication
    Serial.begin(9600);
}

void loop() {   
    unsigned long currentTime = millis();

    //update each switches
    for (int i=0; i<9; i++) {
        Switches[i].update(currentTime);
    }
}
