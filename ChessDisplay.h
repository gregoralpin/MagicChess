#include <Arduino.h>
#include <LiquidCrystal.h>

class ChessDisplay : public LiquidCrystal 
{
  public:
    using LiquidCrystal::LiquidCrystal;
    
    void display_message_at(String message, int column, int row);
    void print_top_left(String message);
    void print_top_right(String message);
    void print_middle(String message);
    void clear_middle();
    void print_bottom(String message);
    void clear_bottom();
};
