#include <RotaryEncoder.h>
#include <LiquidCrystal.h>
#include <GFButton.h>
#include "CountdownTimer.h"
#define LCD_COLUMNS 20
#define LCD_ROWS 4

#include "MoveManager.h"



/***** CONTROL MODULE STATE *****/
enum ControlModuleState {
  WAITING_PIECE_SELECTION,
  WAITING_DESTINATION_SELECTION
};

enum ControlModulePlayerState {
  WAITING_LEFT,
  WAITING_RIGHT
};

/***** CONTROL VAR DECLARATION *****/
RotaryEncoder *column_encoder = nullptr;
RotaryEncoder *row_encoder = nullptr;
LiquidCrystal *lcd = nullptr;
GFButton *selectBtn = nullptr;
CountdownTimer *TimerLeft = nullptr;
CountdownTimer *TimerRight = nullptr;
enum ControlModuleState state = WAITING_PIECE_SELECTION;
enum ControlModulePlayerState playerState = WAITING_LEFT;
long previousSeconds;

int selected_piece_position = -1;
int selected_destination_position = -1;
int col_pos = 0;
int row_pos = 0;
/***** CONTROL VAR INSTANTIATION *****/
void init_control(){
  previousSeconds = millis();

  column_encoder = new RotaryEncoder(20, 21);
  row_encoder = new RotaryEncoder(2,3);

  selectBtn = new GFButton(6);
  selectBtn->setPressHandler(selectPressed);

  lcd = new LiquidCrystal(8, 9, 10, 11, 12, 13);// LiquidCrystal(rs,en,d4,d5,d6,d7)
  lcd->begin(LCD_COLUMNS, LCD_ROWS);

  TimerLeft = new CountdownTimer(60 * 3);
  TimerRight = new CountdownTimer(60 * 3);
}

/***** CONTROL LCD FUNCTIONS *****/
void display_message_at(LiquidCrystal *lcd, String message, int column, int row){
  lcd->setCursor(column, row);
  lcd->print(message);
}

void lcd_print_top_left(LiquidCrystal *lcd, String message){
  if(lcd == nullptr){
    return; 
  }

  if(message.length() > 7){
    Serial.println("Message too big to be written at position");
    return;
  }

  display_message_at(lcd, message, 0, 0);
}

void lcd_print_top_right(LiquidCrystal *lcd, String message){
  if(lcd == nullptr){
    return; 
  }

  if(message.length() > 7){
    Serial.println("Message too big to be written at position");
    return;
  }
  
  display_message_at(lcd, message, LCD_COLUMNS - message.length(), 0);
}

void lcd_print_middle(LiquidCrystal *lcd, String message){
  if(lcd == nullptr){
    return; 
  }

  if(message.length() > 20){
    Serial.println("Message too big to be written at position");
    return;
  }

  display_message_at(lcd, message, 0, 2);
}

void lcd_print_bottom(LiquidCrystal *lcd, String message){
  if(lcd == nullptr){
    return; 
  }

  if(message.length() > 20){
    Serial.println("Message too big to be written at position");
    return;
  }

  display_message_at(lcd, message, 0, 3);
}

/***** CONTROL ENCODER FUNCTIONS *****/
void colEncoderInterrupt(){
  column_encoder->tick();
}

void rowEncoderInterrupt(){
  row_encoder->tick();
}

String translateIntToColumn(int encoderPos){
  
  int pos = (10000000 + encoderPos) % 8;

  char translation = 65 + pos;
  return String(translation);
}

String translateIntToRow(int encoderPos){
  return String(((10000000 + encoderPos) % 8) + 1);
}

/***** CONTROL BUTTON FUNCTIONS *****/
void selectPressed(){
  Serial.println("Shit was pressed");
}

/***** CONTROL FLOW AUX FUNCTIONS *****/
void changePlayer(){
  if(playerState == WAITING_LEFT){
    display_message_at(lcd, " ", 6, 0);
    display_message_at(lcd, ">", 13, 0);
    TimerLeft->Pause();
    TimerRight->Resume();
    playerState = WAITING_RIGHT;
  }
  else{
    display_message_at(lcd, " ", 13, 0);
    display_message_at(lcd, "<", 6, 0);
    TimerLeft->Resume();
    TimerRight->Pause();
    playerState = WAITING_LEFT;
  }
}
/***** MAIN FUNCTIONS *****/
void setup() {
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(20), colEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), colEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), rowEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rowEncoderInterrupt, CHANGE);

  init_control();

  lcd_print_top_left(lcd, TimerLeft->GetRemainingTime());
  lcd_print_top_right(lcd, TimerRight->GetRemainingTime());
  display_message_at(lcd, "<", 6, 0);

  state = WAITING_PIECE_SELECTION;

  TimerLeft->Start();
  TimerRight->Start();
  TimerRight->Pause();
}

void loop() {
  //Serial.println("Loop is runnning 1");

  selectBtn->process();

  if(selectBtn->wasPressed()){
    Serial.println("TESTESTE");
  }

  if(state == WAITING_PIECE_SELECTION)
  {
     lcd_print_middle(lcd, "Selecione uma peca:");
     if(selectBtn->wasPressed()){
       selected_piece_position = row_pos * 8 + col_pos;
       Serial.println("Selected piece at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_piece_position));
       state = WAITING_DESTINATION_SELECTION;
     }
  }
  else if (state == WAITING_DESTINATION_SELECTION){
    lcd_print_middle(lcd, "Selecione o destino:");
    if(selectBtn->wasPressed()){
       selected_destination_position = row_pos * 8 + col_pos;
       Serial.println("Selected destination at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_destination_position));
       MoveManager* moveManager = MoveManager::GetMoveManagerInstance();
       int* validMoves = moveManager->validMovements(selected_piece_position);
       
       bool destinationValid = false;
       for(int i = 0; i < 64; i++){
        if (validMoves[i] == selected_destination_position){
          destinationValid = true;
          break;
        }
       }

       if (destinationValid){
        Serial.println("Good move!");
        changePlayer();
       }
       else{
        Serial.println("Bad move...");
       }
       state = WAITING_PIECE_SELECTION;
     }
  }

  if(millis() - previousSeconds > 1000){
    lcd_print_top_left(lcd, String(TimerLeft->GetRemainingTime()));
    lcd_print_top_right(lcd, String(TimerRight->GetRemainingTime()));

    previousSeconds = millis();
  }

  col_pos = column_encoder->getPosition();
  row_pos = row_encoder->getPosition();
  
  
  //Serial.println(translateIntToColumn(col_pos) + "," + translateIntToRow(row_pos));
  lcd_print_bottom(lcd, translateIntToColumn(col_pos) + translateIntToRow(row_pos));

  //Serial.println(ClockA->GetRemainingTime());

}
