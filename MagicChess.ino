#include <RotaryEncoder.h>
#include "ChessDisplay.h"
#include <GFButton.h>
#include "CountdownTimer.h"
#include "MoveManager.h"
#include "LedControl.h"

// void MovePeça(int piece_pos, int desitination){
//  if(Board->IsOccupied(destination){
//    int* path = Mover->GetPathToCemitery(destination);
//    MotorControl->ExecutePath(path);  
//  }
//  
//  int* path = Mover->GetPath(piece_pos, destination)
//  MotorControl->ExecutePath(path);
//  Board[]
//}

/***** CONTROL STATES *****/

enum GameState {
  GAME_STARTING,
  WAITING_PIECE_SELECTION,
  WAITING_DESTINATION_SELECTION,
  GAME_ENDING,
  GAME_ENDED
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
LEDControl *ledControl = nullptr;

long lastTimerUpdateSeconds;
long lastInfoClearSeconds;
int selected_piece_position;
int selected_destination_position;
int col_pos;
int row_pos;
int *validMoves = nullptr;

/***********************************/

/***** CONTROL VAR INSTANTIATION *****/

void init_control(){
  gameState = GAME_STARTING;
  playerState = WAITING_LEFT_PLAYER;

  row_encoder = new RotaryEncoder(2,3);
  column_encoder = new RotaryEncoder(20, 21);
  lcd = new ChessDisplay(8, 9, 10, 11, 12, 13); // LiquidCrystal(rs,en,d4,d5,d6,d7);
  lcd->begin(20, 4);
  selectBtn = new GFButton(6);
  ledControl = new LEDControl(84);
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
  if (gameState != GAME_ENDING && gameState != GAME_STARTING && gameState != GAME_ENDED){

    // Check timers to see if game has ended
    if(TimerLeft->GetRemainingSeconds() == 0 || TimerRight->GetRemainingSeconds() == 0){
      gameState = GAME_ENDING;
    }
    
    // Get row and pos position
    row_pos = encoder_pos_to_game_pos(row_encoder->getPosition());
    col_pos = encoder_pos_to_game_pos(column_encoder->getPosition());

    // Acende led das casa cuja posicao é (row_pos, col_pos).
    ledControl->ShowHouseSelection(row_pos, col_pos);

    // Print encoder values.
    lcd->print_bottom(game_pos_to_row_pos(row_pos) + game_pos_to_column_pos(col_pos));
    
    // Print updated timer values.
    if(millis() - lastTimerUpdateSeconds > 1000){
      lcd->print_top_left(String(TimerLeft->GetRemainingTime()));
      lcd->print_top_right(String(TimerRight->GetRemainingTime()));

      lastTimerUpdateSeconds = millis();
    }

    // Clear previous info.
    if(millis() - lastInfoClearSeconds > 2000){
      
      
      lcd->clear_info();

      lastInfoClearSeconds = millis();
    }
  }

  switch (gameState)
  {
    case GAME_STARTING:

      // Init vars.      
      TimerLeft = new CountdownTimer(10);
      TimerRight = new CountdownTimer(60 * 3);
      
      lastTimerUpdateSeconds = millis();
      lastInfoClearSeconds = millis();
      selected_destination_position = 0; // [0..63]
      selected_destination_position = 0; // [0..63]
      col_pos = 0; // [0..7]
      row_pos = 0; // [0..7]
    
      lcd->print_top_left(TimerLeft->GetRemainingTime());
      lcd->print_top_right(TimerRight->GetRemainingTime());
      lcd->show_left_turn_indicator();

      TimerLeft->Start();
      TimerRight->Start();
      TimerRight->Pause();

      playerState = WAITING_LEFT_PLAYER;
      gameState = WAITING_PIECE_SELECTION;

      validMoves = new int[64];
      break;

    case WAITING_PIECE_SELECTION:
      lcd->show_select_piece_message();

      if(selectBtn->wasPressed()){
        selected_piece_position = row_pos * 8 + col_pos;
        Serial.println("Selected piece at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_piece_position));
        
        // Get valid movements for selected piece.
        MoveManager* moveManager = MoveManager::GetMoveManagerInstance(); // this line should be outside of loop
        moveManager->validMovements(selected_piece_position, validMoves);

        // Acende led das casas validas.
        ledControl->ShowPossibleMoves(validMoves);
        
        gameState = WAITING_DESTINATION_SELECTION;
      }
      break;

    case WAITING_DESTINATION_SELECTION:
      lcd->show_select_destination_message();
      
      if(selectBtn->wasPressed()){
        selected_destination_position = row_pos * 8 + col_pos;
        Serial.println("Selected destination at row " + String(row_pos) + " column " + String(col_pos) + " - ie. index " + String(selected_destination_position));

        Serial.println("Got valid moves:");
        for(int i = 0; i < 64; i++){
          Serial.print(String(validMoves[i]) + ", ");
        }
        Serial.println();

        // Check if selected destination is valid in valid movements
        if(validMoves[selected_destination_position] != -1){
          Serial.println("Good move!");
          changePlayerTurn();
          
          lcd->clear_info();
          lastInfoClearSeconds = millis();
          lcd->show_info("Piece moved!");
        }
        else{
          Serial.println("Bad move...");
          
          lcd->clear_info();
          lastInfoClearSeconds = millis();
          lcd->show_info("Invalid move");
        }
        
        // Apaga todos os leds.
        ledControl->TurnEverythingOff();
        
        gameState = WAITING_PIECE_SELECTION;
      }
      break;

    case GAME_ENDING:
      lcd->clear();
      gameState = GAME_ENDED;
      break;
      
    case GAME_ENDED:
      
      // Check who is the winner.
      String winner;
      if(playerState == WAITING_LEFT_PLAYER){
        winner = "Whites";
      }
      else{
        winner = "Blacks";
      }

      lcd->show_info("Game over");
      lcd->print_middle(winner + " have won!");
      lcd->print_bottom("Press btn to restart");

      if(selectBtn->wasPressed()){
        gameState = GAME_STARTING;
        lcd->clear();
      }
      
      break;

    default:
      break;
  }
}
