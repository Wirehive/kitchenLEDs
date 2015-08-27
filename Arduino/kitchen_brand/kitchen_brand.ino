#include <Adafruit_NeoPixel.h>

#define PIN 2
#define PIXELS 450
#define WAIT 10
#define PHASE_LENGTH 180.

#define COLOR_0_R 255
#define COLOR_0_G 161
#define COLOR_0_B 27

#define COLOR_1_R 0
#define COLOR_1_G 130
#define COLOR_1_B 100

#define COLOR_2_R 206
#define COLOR_2_G 15
#define COLOR_2_B 105

#define COLOR_3_R 0
#define COLOR_3_G 195
#define COLOR_3_B 131

const float delta[4][3] = {
    {(COLOR_1_R-COLOR_0_R)/PHASE_LENGTH, (COLOR_1_G-COLOR_0_G)/PHASE_LENGTH, (COLOR_1_B-COLOR_0_B)/PHASE_LENGTH},
    {(COLOR_2_R-COLOR_1_R)/PHASE_LENGTH, (COLOR_2_G-COLOR_1_G)/PHASE_LENGTH, (COLOR_2_B-COLOR_1_B)/PHASE_LENGTH},
    {(COLOR_3_R-COLOR_2_R)/PHASE_LENGTH, (COLOR_3_G-COLOR_2_G)/PHASE_LENGTH, (COLOR_3_B-COLOR_2_B)/PHASE_LENGTH},
    {(COLOR_0_R-COLOR_3_R)/PHASE_LENGTH, (COLOR_0_G-COLOR_3_G)/PHASE_LENGTH, (COLOR_0_B-COLOR_3_B)/PHASE_LENGTH}
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(
    PIXELS,
    PIN,
    NEO_GRB + NEO_KHZ800
);

uint16_t scroll;
uint8_t phase;
float next_color[] = {(float)COLOR_0_R, (float)COLOR_0_G, (float)COLOR_0_B};

void setup() {
    Serial.begin(115200);
    strip.begin();
    for(uint16_t p = 0; p < PIXELS; p++) {
      strip.setPixelColor(p, strip.Color(next_color[0], next_color[1], next_color[2]));
    }
}

void loop() {
    Serial.println("Hi");
    for(uint8_t i = 0; i < PHASE_LENGTH; i++) {
        next_color[0] += delta[phase][0];
        next_color[1] += delta[phase][1];
        next_color[2] += delta[phase][2];
        //Better in a ring buffer but libraries!
        for(uint16_t p = 0; p < PIXELS - 1; p++) {
            strip.setPixelColor(p, strip.getPixelColor(p + 1));
        }
        strip.setPixelColor(PIXELS -1, strip.Color(next_color[0], next_color[1], next_color[2]));
        strip.show();
        ++scroll %= PIXELS;
        delay(WAIT);
    }
    ++phase %= sizeof(delta) / sizeof(*delta);
}
