#pragma once
#include <FastLED.h>

class LEDControl{
  private:
    int NumLeds;
    CRGB *leds;
    int lastHouseLedLitIndex;

    int ConvertRowAndPosToTabIndex(int row, int col);
    int ConvertRowAndColToLedPos(int row, int col);
    int ConvertTabIndexToLedPos(int tabIndex);


  public:
    
    LEDControl(int numLeds);

    // Basic functions.

    void TurnLedOff(int ledPos);
    void TurnLedOn(int ledPos, CRGB color);
    void TurnEverythingOff();
    
    // Useful functions


    /// <summary>
    /// Funcao usada para mostrar a casa selecionada. Automaticamente apaga
    /// a casa selecionada anterior.
    /// </summary> 
    void ShowHouseSelection(int row, int col);

    /// <summary>
    /// Funcao usada para mostrar onde o jogador pode mover a peça.
    /// Acende os leds das casas do tabuleiro que são válidas para mover uma peça.
    /// Recebe uma lista de 0..63 posições indicando quais casas são válidas:
    /// -1 é casa invalida, qlqr coisa diferente quer dizer que casa é valida (e deve ter seu led aceso).
    /// </summary> 
    void ShowPossibleMoves(int *validMoves);
};
