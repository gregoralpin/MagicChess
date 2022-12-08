#pragma once

class LEDControl{
  private:
    
  public:
 
    LEDControl();
    /// <summary>
    /// Set led on (true) or off (false)
    /// </summary>
    void TurnLedOnOff(ledPos, bool onoff, int color);
    void TurnLedsOn(int *ledList, int color);
    void TurnEverythingOff();
}
