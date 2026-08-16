// Prototypes of functions
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.h"

// Functions in helper.c
int round_off(double num);
void add_items(int int_array[], char *str_array[], char *file_name, int type);
void free_memory(Cell board[], Regional regional_cards[], Events national_events[]);
void destroy_property(Cell *place);
void unmortgage_property(Cell board[], Player player);
int dice_roll(void);
void sort_players(Player players[]);
int decide_winner(Player players[], Cell board[]);
void check_for_jailed(Player *player);
void check_for_bankruptcy(Player players[], Cell board[], Game game_status, int player);
void announce_bankruptcy(Player players[], Cell board[], Game game_status, int player);
Status calculate_player_status(Player player, Cell board[]);

// Functions in board.c
void initialize_game(Cell board[]);
void generate_board(Cell board[]);
void initialize_players(Player players[]);
void generate_event_cards(Events national_events[], Regional regional_cards[]);
void decide_player_order(Player players[]);

// Functions in game.c
void print_game_start();
void print_round_summary(Game game_status, Player players[], Cell board[], Events national_events[]);
void print_dynamic_market(Game game_status, Regional regional_cards[]);
void print_game_over(Player players[], Cell board[]);
void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3], Events national_events[], Regional regional_cards[]);

// Functions in players.c
void player_actions(Player players[], Cell board[], Cell *property_groups[][3], Game *game_status, Events national_events[]);
void check_for_bank_action(Player player[], Cell board[], Game game_status);
void check_for_insurance_action(Player players[], Cell board[], Game game_status);
void buy(Player players[], Cell board[], Game game_status);
int auction(Player players[], Cell board[], Cell *place, Ownership beneficiary, Game game_status);
void raise_money(Player players[], Cell board[], Game game_status, int amount_to_be_raised);
void rent(Player players[], Cell *place, Cell board[], Game game_status);
void constructions(Player players[], Cell board[], Cell *property_groups[][3], Game game_status);
void property_renovations(Player *player, Cell board[]);
void building_renovations(Player *player, Cell board[]);

// Functions in finance.c
void obtain_loan(Player *player, Cell board[], Game game_status);
void accumulated_interest(Player *player);
void check_for_loan_status(Player players[], Cell board[], Game game_status);
void repay_outstanding_loan(Player players[], Cell board[], Game game_status);
void extend_loan(Player *player);
void refinance_loan(Player *player, Cell board[], Game game_status);
void obtain_insurance(Player players[], Cell board[], Game game_status, int provider, int has_insurance, int place);
void check_for_insurance_status(Cell board[]);
void insurance_compensation(Cell board[], int property, int disaster, char *disaster_name);
void tax_payments(Player players[], Cell board[], Game game_status, int tax);
void settle_outstanding_penalties(Player *player, Cell board[], Game game_status);

// Functions in events.c
void property_depreciation(Cell board[], Game game_status);
void building_depreciation(Cell board[]);
void inflation(Cell board[], Game *game_status);
void dynamic_property_market(Cell *property_groups[][3], Game *game_status, int event);
void disaster_occurrence(Player players[], Cell board[], Game game_status);
void national_event_card_draw(Player players[], Cell board[], Events national_events[], Game *game_status);
void national_event_card_expiry(Player players[], Cell board[], Game *game_status);
void economic_events(Player players[], Cell board[], Game *game_status);
void government_regulations(Cell board[], Game *game_status);
void regional_card_draw(Cell board[], Game *game_status);

#endif