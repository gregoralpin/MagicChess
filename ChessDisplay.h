#include <Arduino.h>
#include <LiquidCrystal.h>

class ChessDisplay : public LiquidCrystal 
{
  public:
    using LiquidCrystal::LiquidCrystal;
    
    void display_message_at(String message, int column, int row);
    void lcd_print_top_left(String message);
    void lcd_print_top_right(String message);
    void lcd_print_middle(String message);
    void lcd_print_bottom(String message);
};