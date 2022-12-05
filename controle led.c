#include "FastLED.h"  // Fastled library to control the LEDs

// How many leds are connected?
#define NUM_LEDS 84

#define DATA_PIN 2

CRGB leds[NUM_LEDS];

bool movimento = false;

unsigned long agora = 0;

int selePassado=0;

bool finalMovimento=false;

bool pecaSelecionada = false;


void setup() {
  // put your setup code here, to run once:
  LEDS.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // Init of the Fastled library
  FastLED.setBrightness(90);

  Serial.begin(9600);
}

bool verMov(int* mov, int posX, int posY, int n)
{
	int pos = (posX * 8) + posY;
	bool valida = false;

	for (int i = 0; i < n; i++) {
		if (pos == mov[i]) {
			valida = true;

		}

	}
	return valida;
}

void movInval(int posX,int posY,bool valida) {

  if (!valida) {

    int p = numLed(posX, posY);
    for (int i = 0; i < 6; i++) {
      leds[p] = CRGB::Red;
      agora = millis()
    while(millis() < agora + 200) {
        // Pausa de 0.2 segundos. Nada a fazer
        }
      FastLED.show();
      
      leds[p] = CRGB::Black;
      agora = millis()
    while(millis() < agora + 200) {
        // Pausa de 0.2 segundos. Nada a fazer
        }
      FastLED.show();
    }
    
  }
}

void movVal(int* mov, int n) {
  for (int i = 0; i < n; i++){
    int p = posConversor(mov[i]);
    leds[p] = CRGB::Green;
    FastLED.show();
  }

}

int posConversor(int tab) {
  //logica para converter a posicao recebida pela logica do tabuleiro para a pos da led
  int x, y, p;

  x = tab / 8;
  y = tab % 8;

  p = numLedGrande(x, y);

  return p;

}

void apagaLedEspecífica(int posLed)
{
    leds[posLed] = CRGB::Black;
}

void apagaTudo() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    
  }
  FastLED.show();
}
void quadEscolido(int posY, int posX) {
  int p = numLed(posX, posY);
    leds[p] = CRGB::Green;
    agora = millis()
    while(millis() < agora + 500) {
        // Pausa de 0.5 segundos. Nada a fazer
        }
    FastLED.show();

    
    leds[p] = CRGB::Black;
    agora = millis()
    while(millis() < agora + 500) {
        // Pausa de 0.5 segundos. Nada a fazer
        }
    FastLED.show();
  
}

int numLedGrande(int x, int y) {
  int p;
  if (x % 2 > 0) {
    p = 12 + x * 6 - (y);

  } else {
    p =
      y + x * 11;
  }
  return p;
}

void loop() {

  FastLED.show();





  
  bool movimento = false;

  if (finalMovimento) {
	  apagaTudo;
  }

  else{
  if pecaSelecionada{
	  if (verMov) {

		  quadEscolido(x, y, true);

}
	else
	{
		  movInval(x,y)
	}
	  
	  movVal(teste,4);
  }

  else
  {
	  int seleAtual = numLedGrande(x,y);
	  if (selePassado != seleAtual)
	  {
		  if (selePassado != 0) {
			  apagaLedEspecífica(selePassado);
		  }
		  selePassado = seleAtual;
	  }
  }
  }


  delay(100);
}

