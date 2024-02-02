
#include <TFT_eSPI.h> // Graphics and font library for ILI9341 driver chip
#include <SPI.h>
#define TFT_GREY 0x5AEB // New colour

//==================== Configurações =====================//
#define TEMPERATURAALVO 60.00

//==================== CORES ============================//
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0x073f
#define WHITE   0xFFFF

#define GREETEMP 0x5fe0
#define BLUEUMIDADER 0xFFE0
#define VIOLETUMIDADEA 0xe01f
#define ARDUINOCOLOR 0x07ff

//==================== Variáveis Globais ===============//
float temp = 0;
float hum = 0;
float humAbs = 0;
float pretemp = 0;
float prehum = 0;
float prehumAbs = 0;
float currtemp = 0;
float currhum = 0;
float currhumAbs = 0;
float i = 0;
float j = 0;

double Setpoint, Input, Output;
double Kp = 2, Ki = 5, Kd = 1;


TFT_eSPI tft = TFT_eSPI();


void setup(void) {



  //----------------- Paramentros Inciais (Display) ------------//
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.invertDisplay(0);

  //----------------- Paramentros Inciais (DHT22) ------------//
  Setpoint = TEMPERATURAALVO;


  // -------------- Texto Inicial ----------------------------//
  tft.drawRect(0, 0, 320, 240, ARDUINOCOLOR);
  tft.setTextSize(7);
  tft.setTextColor(ARDUINOCOLOR, BLACK);
  tft.setCursor(50, 30);
  tft.print("DRY");
  tft.setCursor(50, 160);
  tft.print("FILA");
  delay(3000);
  tft.fillScreen(BLACK);

  //-------------- Tela inicial Fixa Display
  // Título
  tft.setTextSize(3);
  tft.setTextColor(YELLOW, BLACK);
  tft.setCursor(60, 5);
  tft.print("FILAMENT DRY");
  tft.setTextSize(2);
  tft.setCursor(95, 30);
  tft.print("thxssio.com");

  //Temperatura
  tft.setTextSize(2);
  tft.setTextColor(GREETEMP, BLACK);
  tft.setCursor(24, 170);
  tft.print("0");
  tft.setCursor(62, 170);
  tft.print("50");
  tft.setTextSize(1);
  tft.setCursor(18, 100);
  tft.print("Temperatura");
  tft.setCursor(45, 110);
  tft.print("ºC");

  //Umidade Relativa
  tft.setTextSize(2);
  tft.setTextColor(BLUEUMIDADER, BLACK);
  tft.setCursor(24 + 110, 170);
  tft.print("0");
  tft.setCursor(58 + 110, 170);
  tft.print("100");
  tft.setTextSize(1);
  tft.setCursor(20 + 110, 100);
  tft.print("Umidade R.");
  tft.setCursor(45 + 110, 110);
  tft.print("R%");

  //Umidade Absoluta
  tft.setTextSize(2);
  tft.setTextColor(VIOLETUMIDADEA, BLACK);
  tft.setCursor(24 + 220, 170);
  tft.print("0");
  tft.setCursor(62 + 220, 170);
  tft.print("80");
  tft.setTextSize(1);
  tft.setCursor(20 + 220, 100);
  tft.print("Umidade A.");
  tft.setCursor(38 + 220, 110);
  tft.print("g/m3");
}

void loop() {
  // ---------------------- Exibe temperatura com elementos gráficos -------------//
  temp = 40; // ( Simulação de valores )
  hum = 10; // ( Simulação de valores )
  humAbs = 40; // ( Simuluação de valores )

  tft.setTextColor(GREETEMP, BLACK);
  tft.setTextSize(2);
  tft.setCursor(27, 125);
  tft.print(temp, 1);
  tft.setTextColor(BLUEUMIDADER, BLACK);
  tft.setTextSize(2);
  tft.setCursor(27 + 110, 125);
  tft.print(hum, 1);
  tft.setTextColor(VIOLETUMIDADEA, BLACK);
  tft.setTextSize(2);
  tft.setCursor(27 + 220, 125);
  tft.print(humAbs, 1);

  tft.setTextSize(1.5);
  tft.setTextColor(GREETEMP, BLACK);
  tft.setCursor(0, 220);
  tft.print("Temp. Alvo:");
  tft.setCursor(68, 220);
  tft.print(TEMPERATURAALVO, 0);
  tft.setCursor(81, 220);
  tft.print("ºC");

  currtemp = temp;
  currhum = hum;
  currhumAbs = humAbs;

  float start_i = map(pretemp, 0, 50, 0, 300);
  float end_j = map(currtemp, 0, 50, 0, 300);

  for (float i = start_i; i <= end_j; i += 0.1)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 50 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 50 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;
    tft.drawLine(x1, y1, x2, y2, GREETEMP);
  }

  for (float i = start_i - 2; i >= end_j; i -= 0.05)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 50 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 50 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;
    tft.drawLine(x1, y1, x2, y2, BLACK);
  }

  start_i = map(prehumAbs, 0, 100, 0, 300);
  end_j = map(currhumAbs, 0, 100, 0, 300);

  for (float i = start_i; i <= end_j; i += 0.1)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 270 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 270 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;

    tft.drawLine(x1, y1, x2, y2, VIOLETUMIDADEA);
  }

  for (float i = start_i - 2; i >= end_j; i -= 0.05)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 270 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 270 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;

    tft.drawLine(x1, y1, x2, y2, BLACK);
  }

  start_i = map(prehum, 0, 100, 0, 300);
  end_j = map(currhum, 0, 100, 0, 300);

  for (float i = start_i; i <= end_j; i += 0.1)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 160 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 160 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;

    tft.drawLine(x1, y1, x2, y2, BLUEUMIDADER);
  }

  for (float i = start_i - 2; i >= end_j; i -= 0.05)
  {
    float adjusted_i = i - 150;
    float angle = (adjusted_i / 57.2958) - 1.57;
    float x1 = 160 + cos(angle) * 40;
    float y1 = 120 + sin(angle) * 40;
    float x2 = 160 + cos(angle) * 50;
    float y2 = 120 + sin(angle) * 50;

    tft.drawLine(x1, y1, x2, y2, BLACK);
  }

  pretemp = currtemp;
  prehum = currhum;
  prehumAbs = currhumAbs;

  delay(10);
}
