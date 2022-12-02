#include <RotaryEncoder.h>
#include "ChessDisplay.h"
#include <GFButton.h>
#include "CountdownTimer.h"
#include "MoveManager.h"

/***** CONTROL STATES *****/

enum GameState {
  GAME_START,
  WAITING_PIECE_SELECTION,
  WAITING_DESTINATION_SELECTION,
  GAME_END
};

enum PlayerState {
  WAITING_LEFT_PLAYER,
  WAITING_RIGHT_PLAYER
};

/**************************/

/***** CONTROL VAR DECLARATION *****/

enum GameState gameState;
enum PlayerState playerState;

RotaryEncoder *row_encoder = nullptr;
RotaryEncoder *column_encoder = nullptr;
ChessDisplay *lcd = nullptr;
GFButton *selectBtn = nullptr;
CountdownTimer *TimerLeft = nullptr;
CountdownTimer *TimerRight = nullptr;

long previousSeconds;
int selected_piece_position;
int selected_destination_position;
int col_pos;
int row_pos;

/***********************************/

/***** CONTROL VAR INSTANTIATION *****/

void init_control(){
  gameState = GAME_START;
  playerState = WAITING_LEFT_PLAYER;

  row_encoder = new RotaryEncoder(2,3);
  column_encoder = new RotaryEncoder(20, 21);
  lcd = new ChessDisplay(8, 9, 10, 11, 12, 13);// LiquidCrystal(rs,en,d4,d5,d6,d7);
  lcd->begin(20, 4);
  selectBtn = new GFButton(6);
  TimerLeft = new CountdownTimer(60 * 3);
  TimerRight = new CountdownTimer(60 * 3);
  
  previousSeconds = millis();
  selected_destination_position = 0; // [0..64]
  selected_destination_position = 0; // [0..64]
  col_pos = 0; // [0..8]
  row_pos = 0; // [0..8]
}

/************************************/

/***** ENCODER FUNCTIONS *****/

void colEncoderInterrupt(){
  column_encoder->tick();
}

void rowEncoderInterrupt(){
  row_encoder->tick();
}

/****************************/

/***** MISC AUX FUNCTIONS *****/

/// <summary>
/// Transforms encoderPos (ie. int) value to a int in interval [0..7]
/// </summary>
int encoder_pos_to_game_pos(int encoderPos){
  return ((10000000 + encoderPos) % 8);
}

/// <summary>
/// Transforms int in interval [0..7] to a char in [A..H]
/// </summary>
String game_pos_to_row_pos(int game_pos){
  char translation = 65 + game_pos;
  return String(translation);
}

/// <summary>
/// Transforms int in interval [0..7] to int in [1..8]
/// </summary>
String game_pos_to_column_pos(int game_pos){
  return String(game_pos + 1);
}

void changePlayerTurn(){
  if(playerState == WAITING_LEFT_PLAYER){
    lcd->show_right_turn_indicator();
    TimerLeft->Pause();
    TimerRight->Resume();
    playerState = WAITING_RIGHT_PLAYER;
  }
  else{
    lcd->show_left_turn_indicator();
    TimerLeft->Resume();
    TimerRight->Pause();
    playerState = WAITING_LEFT_PLAYER;
  }
}

/*****************************/

/***** MAIN FUNCTIONS *****/

void setup() {
  Serial.begin(9600);

  // Enoder Attach Interrupts.
  attachInterrupt(digitalPinToInterrupt(20), colEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(21), colEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(2), rowEncoderInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), rowEncoderInterrupt, CHANGE);

  // Vars initialization.
  init_control();
}

void loop() {

  // Update lcd values on every iteration while game is runnnig.
  if (gameState != GAME_END || gameState != GAME_START){
    
    // Get row and pos position
    row_pos = encoder_pos_to_game_pos(row_encoder->getPosition());
    col_pos = encoder_pos_to_game_pos(column_encoder->getPosition());

    // Print encoder values.
    lcd->print_bottom(game_pos_to_row_pos(row_pos) + game_pos_to_column_pos(col_pos));
    
    // Print updated timer values.
    if(millis() - previousSeconds > 1000){
      lcd->print_top_left(String(TimerLeft->GetRemainingTime()));
      lcd->print_top_right(String(TimerRight->GetRemainingTime()));

      previousSeconds = millis();
    }
  }

  switch (gameState)
  {
    case GAME_START:
      lcd->print_top_left(TimerLeft->GetRemainingTime());
      lcd->print_top_right(TimerRight->GetRemainingTime());
      lcd->show_left_turn_indicator();

      TimerLeft->Start();
      TimerRight->Start();
      TimerRight->Pause();

      playerState = WAITING_LEFT_PLAYER;
      gameState = WAITING_PIECE_SELECTION;
      break;

    case WAITING_PIECE_SELECTION:
      lcd->show_select_piece_message();

      if(selectBtn->wasPressed()){
        selected_piece_position = row_pos * 8 + col_pos;
        Serial.println("Selected piece at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_piece_position));
        gameState = WAITING_DESTINATION_SELECTION;
      }
      break;

    case WAITING_DESTINATION_SELECTION:
      lcd->show_select_destination_message();
      
      if(selectBtn->wasPressed()){
        selected_destination_position = row_pos * 8 + col_pos;
        Serial.println("Selected destination at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_destination_position));
        
        MoveManager* moveManager = MoveManager::GetMoveManagerInstance(); // this line should be outside of loop
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
          changePlayerTurn();
        }
        else{
          Serial.println("Bad move...");
        }
        
        gameState = WAITING_PIECE_SELECTION;
      }
      break;

    case GAME_END:
      lcd->clear();
      lcd->print_middle("Game over");
      lcd->print_bottom("Player ? has won!");
      break;

    default:
      break;
  }

  // if(selectBtn->wasPressed()){
  //   Serial.println("TESTESTE");
  // }

  // if(state == WAITING_PIECE_SELECTION)
  // {
  //    lcd_print_middle(lcd, "Selecione uma peca:");
  //    if(selectBtn->wasPressed()){
  //      selected_piece_position = row_pos * 8 + col_pos;
  //      Serial.println("Selected piece at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_piece_position));
  //      state = WAITING_DESTINATION_SELECTION;
  //    }
  // }
  // else if (state == WAITING_DESTINATION_SELECTION){
  //   lcd_print_middle(lcd, "Selecione o destino:");
  //   if(selectBtn->wasPressed()){
  //      selected_destination_position = row_pos * 8 + col_pos;
  //      Serial.println("Selected destination at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_destination_position));
  //      MoveManager* moveManager = MoveManager::GetMoveManagerInstance();
  //      int* validMoves = moveManager->validMovements(selected_piece_position);
       
  //      bool destinationValid = false;
  //      for(int i = 0; i < 64; i++){
  //       if (validMoves[i] == selected_destination_position){
  //         destinationValid = true;
  //         break;
  //       }
  //      }

  //      if (destinationValid){
  //       Serial.println("Good move!");
  //       changePlayer();
  //      }
  //      else{
  //       Serial.println("Bad move...");
  //      }
  //      state = WAITING_PIECE_SELECTION;
  //    }
  // }

  // if(millis() - previousSeconds > 1000){
  //   lcd_print_top_left(lcd, String(TimerLeft->GetRemainingTime()));
  //   lcd_print_top_right(lcd, String(TimerRight->GetRemainingTime()));

  //   previousSeconds = millis();
  // }

  // col_pos = column_encoder->getPosition();
  // row_pos = row_encoder->getPosition();
  
  
  // //Serial.println(translateIntToColumn(col_pos) + "," + translateIntToRow(row_pos));
  // lcd_print_bottom(lcd, translateIntToColumn(col_pos) + translateIntToRow(row_pos));

  // //Serial.println(ClockA->GetRemainingTime());

}
