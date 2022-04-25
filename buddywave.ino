int WAVE_PIN = D5;
int PAT_PIN = D8;
const char *EVENT_HOST = "Deakin_RIOT_SIT210_Photon_Buddy";
const char *EVENT_REC  = "Deakin_RIOT_SIT210_Argon_Buddy";

SYSTEM_THREAD(ENABLED);

int current_signal = 0;
void my_handler(const char *event, const char *data);
void blink_led(int pin, int times, int delay);

void publish(const char *data) 
{
    Particle.publish(EVENT_HOST, data);
}

void setup() {
    // receiver setup
    pinMode(WAVE_PIN, OUTPUT);
    pinMode(PAT_PIN, OUTPUT);
    
    Particle.subscribe(EVENT_HOST, my_handler);
}

void loop() {
    if (current_signal % 2 ==0) { publish("wave"); }
    else {publish("pat");}
    current_signal++;
    delay(1000);
}

void my_handler(const char *event, const char *data)
{
    if (strcmp(data, "wave") == 0)    
    {
        blink_led(WAVE_PIN, 3, 1000);
    }
    else if (strcmp(data,"pat") == 0)
    {
        blink_led(PAT_PIN, 5, 1000);
    }
    
    Particle.publish(EVENT_REC, String::format("Received event: %s",data));
}

void blink_led(int pin, int times, int delay_val)
{
    for (int i =0;i<times;++i)
    {
        digitalWrite(pin,HIGH);
        delay(delay_val);
        digitalWrite(pin,LOW);
        delay(delay_val);
    }
}

