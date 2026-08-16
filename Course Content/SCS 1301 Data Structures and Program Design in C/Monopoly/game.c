// Game controller and simulation engine
#include "functions.h"

void print_game_start() {
    for (int i = 0; i < 56; i++) {
        printf("=");
    }
    printf("\n                 MONOPOLY-LK Simulation\n");
    for (int i = 0; i < 56; i++) {
        printf("=");
    }
    printf("\n");
    printf("\nPlayer 1 : Aggressive Investor\nPlayer 2 : Conservative Banker\nPlayer 3 : Risk Taker\nPlayer 4 : Opportunistic Trader\n\nEach player begins with LKR %i.\n\n", STARTUP_CASH);
}

void print_round_summary(Game game_status, Player players[], Cell board[], Events national_events[]) {
    if (game_status.rounds < 10) {
        printf("\n=================== Round 0%i Summary ===================\n\n", game_status.rounds);
    } else {
        printf("\n=================== Round %i Summary ===================\n\n", game_status.rounds);
    }

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        Status player_status = calculate_player_status(players[i], board);
        printf("Player : %s ", players[i].name);
        if (players[i].isBankrupt == TRUE) {
            printf("(Bankrupt)\n\t");
        } else {
            printf("\n\t");
            printf(" %-16s : LKR %7i\n\t %-16s : LKR %7i\n\t", "Cash", players[i].cash, "Net Worth", player_status.net_worth);
            printf(" %-16s : %11i\n\t %-16s : %11i\n\t", "Properties", player_status.total_properties, "Hotels", player_status.hotels_built);
            printf(" %-16s : LKR %7i\n\n", "Outstanding Loan", players[i].loan_status.total_payable + players[i].loan_status.accumulated_interest);
            int present = FALSE;
            for (int j = 0; j < 20; j++) {
                present = FALSE;
                if (players[i].events[j].remaining_effect > 0) {
                    present = TRUE;
                    break;
                }
            }

            if (present == TRUE) {
            printf("\t Active National Event Cards : \n");
                for (int j = 0; j < 20; j++) {
                    if (players[i].events[j].remaining_effect > 0) {
                        if (players[i].events[j].remaining_effect < 10) {
                            printf("\t %-23s  (0%i rounds left)\n", national_events[players[i].events[j].event].name, players[i].events[j].remaining_effect);
                        } else {
                            printf("\t %-23s  (%i rounds left)\n", national_events[players[i].events[j].event].name, players[i].events[j].remaining_effect);
                        }
                    }
                }
            }
        }
        printf("\n"); 
    }
}

void print_dynamic_market(Game game_status, Regional regional_cards[]) {
    printf("=============== Current Market Conditions ==============\n");

    if (game_status.inflation_rate > 0) {
        printf("\n%-9s : +%2i%%", "Inflation", game_status.inflation_rate);
    } else {
        printf("\n%-9s : %2i%%", "Inflation", game_status.inflation_rate);
    }

    printf("         %-22s : %.2f%%\n", "Current Loan Interest", game_status.interest_rate);

    char *property_groups[] = {
        "Colombo Central",   // BROWN
        "Colombo South",     // LIGHTBLUE
        "Colombo Suburbs",   // PINK
        "Airport Corridor",  // ORANGE
        "Kandy District",    // RED
        "Southern Province", // YELLOW
        "Northern Province", // GREEN
        "Premium Estates",   // DARKBLUE
    };

    if (game_status.dynamic_market[0].event != NORMAL && game_status.dynamic_market[1].event != NORMAL) {
        if (10 - game_status.rounds % 10 < 10) {
            printf("\n----------- Market Condition (0%i rounds left) ----------\n\n", 10 - game_status.rounds % 10);
        } else {
            printf("\n----------- Market Condition (%i rounds left) ----------\n\n", 10 - game_status.rounds % 10);
        }
        printf("%-15s : %-20s (+15%%)\n\n", "Market Boom", property_groups[game_status.dynamic_market[0].property_group]);
        printf("%-15s : %-20s (-15%%)\n\n", "Market Decline", property_groups[game_status.dynamic_market[1].property_group]);
    }

    if (game_status.regional_card != NONE) {
        printf("--------------- Regional Development Cards -------------\n\n");

        if (15 - game_status.rounds % 15 < 10) {
            printf("%-31s    %s (0%i rounds left)\n", regional_cards[game_status.regional_card].name, regional_cards[game_status.regional_card].value, 15 - game_status.rounds % 15);
        } else {
            printf("%-31s    %s (%i rounds left)\n", regional_cards[game_status.regional_card].name, regional_cards[game_status.regional_card].value, 15 - game_status.rounds % 15);
        }
    }
    printf("\n--------------------------------------------------------\n");
}

void print_game_over(Player players[], Cell board[]) {
    int winner_id = decide_winner(players, board);

    for (int i = 0; i < 56; i++) {
        printf("=");
    }
    printf("\n                       GAME OVER\n");
    for (int i = 0; i < 56; i++) {
        printf("=");
    }
    printf("\n");
    
    if (winner_id != NONE) {
        Status player_status = calculate_player_status(players[winner_id], board);

        printf("\n%-20s : %s\n", "Winner", players[winner_id].name);
        printf("%-20s : LKR %6i\n%-20s : LKR %6i\n", "Total Cash", players[winner_id].cash, "Total Property Value", player_status.total_property_value);
        printf("%-20s : LKR %6i\n%-20s : LKR %6i\n", "Outstanding Loans", players[winner_id].loan_status.total_payable + players[winner_id].loan_status.accumulated_interest, "Net Worth", player_status.net_worth);
    } else {
        printf("No Winner");
    }
    printf("\n--------------------------------------------------------\n");
}

void game_loop(Game *game_status, Player players[], Cell board[], Cell *property_groups[][3], Events national_events[], Regional regional_cards[]) {
    int pass_go = FALSE, round_done = TRUE;
    int round_tracker[] = {0, 0, 0, 0};

    while (TRUE) {
        // skips bankrupt players
        check_for_bankruptcy(players, board, *game_status, game_status->current_player);
        if (players[game_status->current_player].isBankrupt == TRUE) {
            round_tracker[game_status->current_player] = 1;
            game_status->current_player = ((game_status->current_player + 1) % NO_OF_PLAYERS);
            continue;
        } 

        // skips jailed players after giving them a chance to get out
        if (players[game_status->current_player].jail_status.isJailed == TRUE) {
            check_for_jailed(&players[game_status->current_player]);
            if (players[game_status->current_player].jail_status.isJailed == TRUE) {
                game_status->current_player = ((game_status->current_player + 1) % NO_OF_PLAYERS);
                continue;
            }
        }

        int game_over = TRUE;

        // checks for game end signal
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            check_for_bankruptcy(players, board, *game_status, i);
            if (players[i].id != players[game_status->current_player].id && players[i].isBankrupt == FALSE) {
                game_over = FALSE;
                break;
            } 
        }

        if (game_over) {
            game_status->rounds++;
            print_round_summary(*game_status, players, board, national_events);
            print_dynamic_market(*game_status, regional_cards);
            print_game_over(players, board);
            return;
        }

        pass_go = FALSE;

        players[game_status->current_player].die_roll = dice_roll();
        printf("%s rolled %i.\n", players[game_status->current_player].name, players[game_status->current_player].die_roll);
        
        printf("%s moves from Square %i ", players[game_status->current_player].name, players[game_status->current_player].place + 1);
        players[game_status->current_player].place += players[game_status->current_player].die_roll;
        if (players[game_status->current_player].place >= NO_OF_CELLS) {
            pass_go = TRUE;
        }
        players[game_status->current_player].place %= NO_OF_CELLS;
        printf("to Square %i.\n\n", players[game_status->current_player].place + 1);

        if (pass_go) {
            players[game_status->current_player].cash += GO_REWARD;
            round_tracker[game_status->current_player]++;

            accumulated_interest(&players[game_status->current_player]);
            check_for_loan_status(players, board, *game_status);
            national_event_card_expiry(players, board, game_status);
            
            printf("%s passed GO.\n", players[game_status->current_player].name);
            printf("Collected LKR %i.\nCurrent Balance LKR %i.\n\n", GO_REWARD, players[game_status->current_player].cash);
        }

        round_done = TRUE;

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (round_tracker[i] == 0) {
                round_done = FALSE;
                break;
            }
        }

        player_actions(players, board, property_groups, game_status, national_events);

        if (round_done) {
            // tasks happening at every round
            game_status->rounds++;
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                round_tracker[i]--;
            }

            if (game_status->rounds == MAX_ROUNDS) {
                print_round_summary(*game_status, players, board, national_events);
                print_dynamic_market(*game_status, regional_cards);
                print_game_over(players, board);
                break;
            }

            check_for_insurance_status(board);
            building_depreciation(board);
            property_depreciation(board, *game_status);

            if (game_status->rounds % 10 == 0) {
                inflation(board, game_status);
                disaster_occurrence(players, board, *game_status);

                for (int i = 0; i < 2; i++) {
                    dynamic_property_market(property_groups, game_status, i);
                }
            }

            if (game_status->rounds % 15 == 0) {
                economic_events(players, board, game_status);
                regional_card_draw(board, game_status);
            }

            if (game_status->rounds % 20 == 0) {
                government_regulations(board, game_status);
            }

            print_round_summary(*game_status, players, board, national_events);
            print_dynamic_market(*game_status, regional_cards);
        }

        game_status->current_player++;
        game_status->current_player %= NO_OF_PLAYERS;
    } 
}