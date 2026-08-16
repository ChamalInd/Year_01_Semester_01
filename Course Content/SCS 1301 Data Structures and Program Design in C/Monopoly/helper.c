// Helper functions
#include "functions.h"

int round_off(double num) {
    if ((num - (int) num) >= 0.5) {
        return (int) num + 1;
    } else {
        return (int) num;
    }
}

void add_items(int int_array[], char *str_array[], char *file_name, int type) {
    FILE *fp = fopen(file_name, "r");

    if (fp != NULL) {
        char buffer[100];
        int i = 0;

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            if (type == STRING) {
                str_array[i] = strdup(buffer);

            } else {
                int_array[i] = atoi(buffer);
            }
            i++;
        }

        fclose(fp);
    } else {
        printf("Some essential files doesn't exists.\n");
        exit(1);
    }
}

void free_memory(Cell board[], Regional regional_cards[], Events national_events[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        free(board[i].name);
        board[i].name = NULL;
    }

    for (int i = 0; i < 20; i++) {
        free(national_events[i].name);
        free(national_events[i].event);
        national_events[i].name = NULL;
        national_events[i].event = NULL;
    }

    for (int i = 0; i < 12; i++) {
        free(regional_cards[i].name);
        free(regional_cards[i].value);
        regional_cards[i].name = NULL;
        regional_cards[i].value = NULL;
    }
}

void destroy_property(Cell *place) {
    place->mortgage.status = UNMORTGAGED;
    place->owner = BANK_OF_CEYLON;
    place->value.building_value = 0;
    place->ownerptr = NULL;
    place->insurance = (Insurance) {NO_INSURANCE, NONE, 0};
    place->depreciation = (Depreciation) {0, 0};
    place->buildings = (Building) {0, 0, 100, 0, 0, FALSE};
}

void unmortgage_property(Cell board[], Player player) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player.id && board[i].mortgage.status == MORTGAGED) {
            board[i].mortgage.status = UNMORTGAGED;
        }
    }
}


int dice_roll(void) {
    int die_1 = (rand() % 6) + 1;
    int die_2 = (rand() % 6) + 1;
    return die_1 + die_2;
}

void sort_players(Player players[]) {
    int swapped = TRUE;

    while (swapped) {
        swapped = FALSE;
        for (int i = 0; i < NO_OF_PLAYERS - 1; i++) {
            if (players[i].play_order == FALSE && players[i].die_roll < players[i + 1].die_roll) {
                Player temp;
                temp = players[i];
                players[i] = players[i + 1];
                players[i + 1] = temp;
                swapped = TRUE;
            }
        }
    }
}

int decide_winner(Player players[], Cell board[]) {
    int winner_id = NONE, non_bankrupt_count = 0, max_net_worth = NONE;
    int non_bankrupt_players[NO_OF_PLAYERS] = {NONE, NONE, NONE, NONE};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        if (players[i].isBankrupt == FALSE) {
            non_bankrupt_players[non_bankrupt_count] = i;
            non_bankrupt_count++;
        }
    }

    for (int i = 0; i < non_bankrupt_count; i++) {
        Status player_status = calculate_player_status(players[non_bankrupt_players[i]], board);

        if (max_net_worth < player_status.net_worth) {
            max_net_worth = player_status.net_worth;
            winner_id = non_bankrupt_players[i];
        }
    }

    return winner_id;
}

void check_for_jailed(Player *player) {
    if (player->jail_status.isJailed == FALSE) {
        player->jail_status.isJailed = TRUE;
        player->jail_status.no_of_rounds = 0;
        printf("%s is in Jail.\n%s moves from Square %i to Square 11.\n\n", player->name, player->name, player->place + 1);

        player->place = 10;

    } else if (player->jail_status.isJailed == TRUE) {
        player->jail_status.no_of_rounds++;

        if (player->jail_status.no_of_rounds == 3) {
            player->jail_status.isJailed = FALSE;
            player->jail_status.no_of_rounds = 0;
            printf("%s got out of Jail after spending 3 turns idle.\n\n", player->name);

        } else {
            int choice = rand() % 3;
            if (choice == 0 && player->cash >= 300) {
                player->cash -= 300;
                player->jail_status.isJailed = FALSE;
                player->jail_status.no_of_rounds = 0;
                printf("%s got out of Jail by paying bail of LKR 300.\n\n", player->name);
            } else if (choice == 1) {
                int die_1 = (rand() % 6) + 1;
                int die_2 = (rand() % 6) + 1;
                if (die_1 == die_2) {
                    player->jail_status.isJailed = FALSE;
                    player->jail_status.no_of_rounds = 0;
                    printf("%s got out of Jail by rolling doubles.\n\n", player->name);
                }
            }
        }
    }
}

void check_for_bankruptcy(Player players[], Cell board[], Game game_status, int player) {
    Status player_status = calculate_player_status(players[player], board);
    
    if (players[player].isBankrupt == FALSE && player_status.net_worth < 0) {
        players[player].isBankrupt = TRUE;
        announce_bankruptcy(players, board, game_status, player);
    } 
}

void announce_bankruptcy(Player players[], Cell board[], Game game_status, int player) {
    players[player].place = 0;
    players[player].cash = 0;
    players[player].loan_status.total_payable = 0;
    players[player].loan_status.accumulated_interest = 0;
    printf("%s has been declared bankrupt.\n", players[player].name);
    printf("Remaining assets transferred to the Bank.\n\n");

    for (int i = 0; i < 20; i++) {
        players[player].events[i].remaining_effect = 0;
    }

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == players[player].id && (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY)) {
            destroy_property(&board[i]);
            auction(players, board, &board[i], BANK_OF_CEYLON, game_status);
        }
    }
}

Status calculate_player_status(Player player, Cell board[]) {
    int properties = 0, railways = 0, utilities = 0, hotels = 0, net_worth = 0, unmortgaged_properties = 0, total_property_value = 0, assets = 0, liabilities = 0;
    // Net worth = cash + property value + building value + railway value + utility value + insurance claims receivables - outstanding loans - accrued interest - taxes due

    assets += player.cash;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player.id) {
            switch (board[i].type) {
                case PROPERTY : {
                    hotels += board[i].buildings.no_of_hotels;
                    assets += board[i].value.building_value;
                    total_property_value += board[i].value.market_price;
                    properties++;
                    break;
                }
                case RAILWAY : {
                    railways++;
                    break;
                } 
                case UTILITY : {
                    utilities++;
                    break;
                }
                default : {
                    continue;
                }
            }

            if (board[i].mortgage.status == UNMORTGAGED) {
                unmortgaged_properties++;
            }
            assets += board[i].value.market_price;
        }
    }

    liabilities += player.loan_status.total_payable;
    liabilities += player.loan_status.accumulated_interest;
    liabilities += player.taxes_due;

    net_worth = assets - liabilities;

    Status status = (Status) {
        .total_properties = properties,
        .total_property_value = total_property_value,
        .total_railways = railways,
        .total_utilities = utilities,
        .unmortgaged_properties = unmortgaged_properties,
        .hotels_built = hotels,
        .net_worth = net_worth
    };

    return status;
}