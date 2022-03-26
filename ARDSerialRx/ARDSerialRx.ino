#include <string.h>
#include  <Scheduler.h>

int i_Byte = 0;
char buffer[100];
int i=0;
int led = LED_BUILTIN;
int pin = 22;
int period = 1000;
int read_val = 0;

void setup()
{
    Serial.begin(9600);           // start serial for output
    Serial.println("USB Started...");
    Serial3.begin(9600);           // start serial for output

    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);

    pinMode(pin, INPUT_PULLUP);
    
    Scheduler.startLoop(led_loop);
    Scheduler.startLoop(read_loop);
}

void loop()
{
    delay(100);
    while(Serial3.available() > 0)
        buffer[i] = Serial3.read();
    
    Serial3.flush();
}

void led_loop()
{
    delay(period);
    digitalWrite(led, HIGH);
    delay(period);
    digitalWrite(led, LOW);
}

void read_loop()
{
    delay(10*period);
    read_val=digitalRead(pin);
    if (read_val==HIGH)
    {
        Serial3.println("HIGH");
    }
    else
    {
        Serial3.println("LOW");
    }    
}
