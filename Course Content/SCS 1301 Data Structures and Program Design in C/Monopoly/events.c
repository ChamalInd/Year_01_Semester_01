// Economic events and government regulations
#include "functions.h"

void property_depreciation(Cell board[], Game game_status) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].owner != NO_OWNER && board[i].owner != BANK_OF_CEYLON) {
            board[i].depreciation.age++;

            if (board[i].depreciation.age >= 50 && board[i].depreciation.percentage < MAX_DEPRECIATION && game_status.rounds % 5 == 0) {
                board[i].depreciation.percentage++;
                board[i].value.market_price -= round_off((double) board[i].value.market_price * (1.0 / 100.0));

                printf("%s has depreciated by %i%%.\n", board[i].name, board[i].depreciation.percentage);
                printf("Current Value : LKR %i.\n\n", board[i].value.market_price);
            }
        }
    }
}

void building_depreciation(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].owner != NO_OWNER && board[i].owner != BANK_OF_CEYLON) {
            if ((board[i].buildings.no_of_houses + board[i].buildings.no_of_hotels) > 0) {
                board[i].buildings.age++;

                if (board[i].buildings.condition != 0) {
                    board[i].buildings.condition -= 2;
                }

                if (board[i].buildings.condition > 90) {
                    board[i].buildings.rent_reduction_rate = 0;

                } else if (board[i].buildings.condition > 75) {
                    board[i].buildings.rent_reduction_rate = 10;

                } else if (board[i].buildings.condition > 50) {
                    board[i].buildings.rent_reduction_rate = 25;
                    
                } else if (board[i].buildings.condition > 25) {
                    board[i].buildings.rent_reduction_rate = 50;
                    
                } else {
                    board[i].buildings.rent_reduction_rate = NONE;
                    board[i].buildings.has_damaged = TRUE;
                }

            }
        }
    }
}

void inflation(Cell board[], Game *game_status) {
    int inflation_rates[] = {-3, 0, 2, 5, 8, 12};
    game_status->inflation_rate = inflation_rates[rand() % (sizeof(inflation_rates) / sizeof(int))];
    double inflation_value = 1.0 + ((double) game_status->inflation_rate / 100.0);
    game_status->interest_rate = game_status->interest_rate * inflation_value;
    game_status->community_fund_rate = game_status->community_fund_rate * inflation_value;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY) {
            board[i].value.market_price = round_off((double) (board[i].value.market_price) * inflation_value);
            board[i].value.current_market_price = round_off((double) (board[i].value.current_market_price) * inflation_value);
            board[i].value.base_rent = round_off((double) (board[i].value.base_rent) * inflation_value);

            if (board[i].type == PROPERTY) {
                board[i].value.hotel_construction_cost = round_off((double) (board[i].value.hotel_construction_cost) * inflation_value);
                board[i].value.house_construction_cost = round_off((double) (board[i].value.house_construction_cost) * inflation_value);
                board[i].value.building_value = round_off((double) (board[i].value.building_value) * inflation_value);
            }
        }
    }
}

void dynamic_property_market(Cell *property_groups[][3], Game *game_status, int event) {
    if (game_status->dynamic_market[event].property_group == NONE) {
        game_status->dynamic_market[event].property_group = rand() % 8;

    } else {
        int new_market = NONE;

        while (TRUE) {
            new_market = rand() % 8;

            if (game_status->dynamic_market[event].property_group != new_market) {
                game_status->dynamic_market[event].property_group = new_market;
                if (game_status->dynamic_market[0].property_group != game_status->dynamic_market[1].property_group) {
                    break;
                }
            }
        }
    }

    game_status->dynamic_market[event].event = event;
    int property_group = game_status->dynamic_market[event].property_group;

    if (game_status->dynamic_market[event].event == MARKET_BOOM) {
        for (int i = 0; i < 3; i++) {
            if (property_groups[property_group][i] != NULL) {
                property_groups[property_group][i]->value.market_price += round_off((double) property_groups[property_group][i]->value.market_price * (15.0 / 100.0));
                property_groups[property_group][i]->value.current_market_price += round_off((double) property_groups[property_group][i]->value.current_market_price * (15.0 / 100.0));
                property_groups[property_group][i]->mortgage.value += round_off((double) property_groups[property_group][i]->mortgage.value * (15.0 / 100.0));
                property_groups[property_group][i]->value.base_rent += round_off((double) property_groups[property_group][i]->value.base_rent * (25.0 / 100.0));
                property_groups[property_group][i]->value.house_construction_cost += round_off((double) property_groups[property_group][i]->value.house_construction_cost * (10.0 / 100.0));
                property_groups[property_group][i]->value.hotel_construction_cost += round_off((double) property_groups[property_group][i]->value.hotel_construction_cost * (10.0 / 100.0));
            }
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (property_groups[property_group][i] != NULL) {
                property_groups[property_group][i]->value.market_price -= round_off((double) property_groups[property_group][i]->value.market_price * (15.0 / 100.0));
                property_groups[property_group][i]->value.current_market_price -= round_off((double) property_groups[property_group][i]->value.current_market_price * (15.0 / 100.0));
                property_groups[property_group][i]->mortgage.value -= round_off((double) property_groups[property_group][i]->mortgage.value * (10.0 / 100.0));
                property_groups[property_group][i]->value.base_rent -= round_off((double) property_groups[property_group][i]->value.base_rent * (20.0 / 100.0));
            }
        }
    }
}

void disaster_occurrence(Player players[], Cell board[], Game game_status) {
    int property = 0, disaster = 0;
    int available[NO_OF_CELLS];
    int available_count = 0;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].ownerptr != NULL) {
            available[available_count] = i;
            available_count++;
        }
    }

    if (available_count > 0) {
        property = available[rand() % available_count];

        disaster = rand() % 6;

        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].events[HEAVY_FLOODS].remaining_effect > 0) {
                disaster = 1;
                break;
            } else if (players[i].events[NATIONAL_DISASTER].remaining_effect > 0) {
                disaster = 4;
            }
        }

        if (game_status.economic_event == HEAVY_MONSOON) {
            disaster = 1;

        } else if (game_status.economic_event == POLITICAL_UNREST) {
            disaster = 2;
        }

        board[property].ownerptr->has_disaster_occurred = TRUE;

        char *disaster_names[] = {"Fire", "Flood", "Riot", "Vandalism", "Building Collapse", "Electrical Failure"};

        printf("%s occurred.\n", disaster_names[disaster]);
        printf("Affected Property : \n\t%s\n\n", board[property].name);

        insurance_compensation(board, property, disaster, disaster_names[disaster]);
    }
}

void national_event_card_draw(Player players[], Cell board[], Events national_events[], Game *game_status) {
    int current_event = game_status->national_event_pointer;
    int player = game_status->current_player;

    printf("%s draws %s Card.\n", players[player].name, national_events[current_event].name);
    printf("%s.\n\n", national_events[current_event].event);

    switch (current_event) {
        case TOURISM_HYPE : {
            players[player].events[current_event].remaining_effect = 5;
            break;
        }
        case FUEL_SHORTAGE : {
            players[player].events[current_event].remaining_effect = 5;
            break;
        }
        case HEAVY_FLOODS : {
            players[player].events[current_event].remaining_effect = 1;
            disaster_occurrence(players, board, *game_status);
            break;
        }
        case POLITICAL_RALLY : {
            players[player].events[current_event].remaining_effect = 2;
            int rand_property = 0;
            while (board[rand_property].type != PROPERTY) {
                rand_property = rand() % NO_OF_CELLS;
            }

            players[player].events[POLITICAL_RALLY].property = rand_property;
            board[rand_property].buildings.has_damaged = TRUE;
            printf("%s is closed for 2 rounds.\n\n", board[rand_property].name);
            break;
        }
        case STOCK_MARKET_RISE : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY) {
                    board[i].value.market_price += round_off((double) board[i].value.market_price * (10.0 / 100.0));
                    board[i].value.current_market_price += round_off((double) board[i].value.current_market_price * (10.0 / 100.0));
                }
            }
            break;
        }
        case ECONOMIC_DOWNTURN : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY) {
                    board[i].value.market_price -= round_off((double) board[i].value.market_price * (15.0 / 100.0));
                    board[i].value.current_market_price -= round_off((double) board[i].value.current_market_price * (15.0 / 100.0));
                }
            }
            break;
        }
        case HOUSING_SUBSIDY : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost -= round_off((double) board[i].value.house_construction_cost * (30.0 / 100.0));
                }
            }
            break;
        }
        case INTEREST_RATE_CUT : {
            players[player].events[current_event].remaining_effect = 15;
            game_status->interest_rate *= (98.0 / 100.0);
            break;
        }
        case INTEREST_RATE_INCREASE : {
            players[player].events[current_event].remaining_effect = 15;
            game_status->interest_rate *= (102.0 / 100.0);
            break;
        }
        case TAX_AMNESTY : {
            players[player].events[current_event].remaining_effect = NONE;
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                if (players[i].isBankrupt == FALSE) {
                    players[i].cash += 2000;
                }
            }
            break;
        }
        case POWER_FAILURE : {
            players[player].events[current_event].remaining_effect = 3;
            break;
        }
        case FOREIGN_FUNDING : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY) {
                    board[i].value.market_price += round_off((double) board[i].value.market_price * (15.0 / 100.0));
                    board[i].value.current_market_price += round_off((double) board[i].value.current_market_price * (15.0 / 100.0));
                }
            }
            break;
        }
        case PORT_EXPANSION : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == RAILWAY) {
                    board[i].value.market_price += round_off((double) board[i].value.market_price * (20.0 / 100.0));
                    board[i].value.current_market_price += round_off((double) board[i].value.current_market_price * (20.0 / 100.0));
                }
            }
            break;
        }
        case LABOUR_STRIKE : {
            players[player].events[current_event].remaining_effect = 2;
            break;
        }
        case PROPERTY_REVALUATION : {
            players[player].events[current_event].remaining_effect = 15;
            int group = rand() % 8;
            players[player].events[PROPERTY_REVALUATION].property = group;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].group == players[player].events[PROPERTY_REVALUATION].property) {
                    board[i].value.market_price += round_off((double) board[i].value.market_price * (15.0 / 100.0));
                    board[i].value.current_market_price += round_off((double) board[i].value.current_market_price * (15.0 / 100.0));
                }
            }
            break;
        }
        case CURRENCY_DEPRECIATION : {
            players[player].events[current_event].remaining_effect = 15;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost += round_off((double) board[i].value.house_construction_cost * (10.0 / 100.0));
                    board[i].value.hotel_construction_cost += round_off((double) board[i].value.hotel_construction_cost * (10.0 / 100.0));
                }
            }
            break;
        }
        case GOVERNMENT_GRANT : {
            players[player].events[current_event].remaining_effect = NONE;
            int random_player = NONE;
            do  {
                random_player = rand() % NO_OF_PLAYERS;
            } while (players[random_player].isBankrupt == TRUE);
            players[random_player].cash += 5000;
            printf("%s got LKR 5000.\n\n", players[random_player].name);
            break;
        }
        case NATIONAL_DISASTER : {
            players[player].events[current_event].remaining_effect = 1;
            disaster_occurrence(players, board, *game_status);
            break;
        }
        default : {
            players[player].events[current_event].remaining_effect = 15;
            break;
        }
    }

    game_status->national_event_pointer++;
    game_status->national_event_pointer %= 20;
}

void national_event_card_expiry(Player players[], Cell board[], Game *game_status) {
    int player = game_status->current_player;

    for (int i = 0; i < 20; i++) {
        if (players[player].events[i].remaining_effect == NONE) { 
            continue;
        }

        if (players[player].events[i].remaining_effect > 0) {
            players[player].events[i].remaining_effect--;
        } 
        
        if (players[player].events[i].remaining_effect == 0) {
            players[player].events[i].remaining_effect = NONE;

            switch (players[player].events[i].event) {
                case POLITICAL_RALLY : {
                    if (players[player].events[POLITICAL_RALLY].property != NONE && board[players[player].events[POLITICAL_RALLY].property].buildings.condition >= 25) {
                        board[players[player].events[POLITICAL_RALLY].property].buildings.has_damaged = FALSE;
                    }
                    printf("%s is open again.\n\n", board[players[player].events[POLITICAL_RALLY].property].name);
                    players[player].events[POLITICAL_RALLY].property = NONE;
                    break;
                }
                case STOCK_MARKET_RISE : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == PROPERTY || board[j].type == RAILWAY || board[j].type == UTILITY) {
                            board[j].value.market_price -= round_off((double) board[j].value.market_price * (10.0 / 100.0));
                            board[j].value.current_market_price -= round_off((double) board[j].value.current_market_price * (10.0 / 100.0));
                        }   
                    }
                    break;
                }
                case ECONOMIC_DOWNTURN : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == PROPERTY || board[j].type == RAILWAY || board[j].type == UTILITY) {
                            board[j].value.market_price += round_off((double) board[j].value.market_price * (15.0 / 100.0));
                            board[j].value.current_market_price += round_off((double) board[j].value.current_market_price * (15.0 / 100.0));
                        }                        
                    }
                    break;
                }
                case HOUSING_SUBSIDY : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == PROPERTY) {
                            board[j].value.house_construction_cost += round_off((double) board[j].value.house_construction_cost * (30.0 / 100.0));
                        }
                    }
                    break;
                }
                case INTEREST_RATE_CUT : {
                    game_status->interest_rate *= (102.0 / 100.0);
                    break;
                }
                case INTEREST_RATE_INCREASE : {
                    game_status->interest_rate *= (98.0 / 100.0);
                    break;
                }
                case FOREIGN_FUNDING : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == PROPERTY || board[j].type == RAILWAY || board[j].type == UTILITY) {
                            board[j].value.market_price -= round_off((double) board[j].value.market_price * (15.0 / 100.0));
                            board[j].value.current_market_price -= round_off((double) board[j].value.current_market_price * (15.0 / 100.0));
                        }
                    }
                    break;
                }
                case PORT_EXPANSION : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == RAILWAY) {
                            board[j].value.market_price -= round_off((double) board[j].value.market_price * (20.0 / 100.0));
                            board[j].value.current_market_price -= round_off((double) board[j].value.current_market_price * (20.0 / 100.0));
                        }
                    }
                    break;
                }
                case PROPERTY_REVALUATION : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].group == players[player].events[PROPERTY_REVALUATION].property) {
                            board[j].value.market_price -= round_off((double) board[j].value.market_price * (15.0 / 100.0));
                            board[j].value.current_market_price -= round_off((double) board[j].value.current_market_price * (15.0 / 100.0));
                        }
                    }
                    players[player].events[PROPERTY_REVALUATION].property = NONE;
                    break;
                }
                case CURRENCY_DEPRECIATION : {
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        if (board[j].type == PROPERTY) {
                            board[j].value.house_construction_cost -= round_off((double) board[j].value.house_construction_cost * (10.0 / 100.0));
                            board[j].value.hotel_construction_cost -= round_off((double) board[j].value.hotel_construction_cost * (10.0 / 100.0));
                        }
                    }
                    break;
                }
                default :
                    break;
            }
        }
    }
}

void economic_events(Player players[], Cell board[], Game *game_status) {
    switch (game_status->economic_event) {
        case TOURISM_BOOM : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY && board[i].group == YELLOW) {
                    board[i].value.market_price -= round_off(board[i].value.market_price * (15.0 / 100.0));
                    board[i].value.current_market_price -= round_off(board[i].value.current_market_price * (15.0 / 100.0));
                }
            }
            break;
        }
        case FUEL_CRISIS : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.hotel_construction_cost -= round_off(board[i].value.hotel_construction_cost * (20.0 / 100.0));
                    board[i].value.house_construction_cost -= round_off(board[i].value.house_construction_cost * (20.0 / 100.0));
                }
            }
            break;
        }
        case HEAVY_MONSOON : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].group == YELLOW) {
                    board[i].value.market_price += round_off(board[i].value.market_price * (10.0 / 100.0));
                    board[i].value.current_market_price += round_off(board[i].value.current_market_price * (10.0 / 100.0));
                }
            }
            board[9].value.market_price += round_off(board[9].value.market_price * (10.0 / 100.0)); // mount lavinia
            board[16].value.market_price += round_off(board[16].value.market_price * (10.0 / 100.0)); // negombo
            board[31].value.market_price += round_off(board[31].value.market_price * (10.0 / 100.0)); // jaffna
            board[34].value.market_price += round_off(board[34].value.market_price * (10.0 / 100.0)); // trincomalee
            board[39].value.market_price += round_off(board[39].value.market_price * (10.0 / 100.0)); // galle face

            board[9].value.current_market_price += round_off(board[9].value.current_market_price * (10.0 / 100.0)); // mount lavinia
            board[16].value.current_market_price += round_off(board[16].value.current_market_price * (10.0 / 100.0)); // negombo
            board[31].value.current_market_price += round_off(board[31].value.current_market_price * (10.0 / 100.0)); // jaffna
            board[34].value.current_market_price += round_off(board[34].value.current_market_price * (10.0 / 100.0)); // trincomalee
            board[39].value.current_market_price += round_off(board[39].value.current_market_price * (10.0 / 100.0)); // galle face
            break;
        }
        case ECONOMIC_RECESSION : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                board[i].value.market_price += round_off(board[i].value.market_price * (15.0 / 100.0));
                board[i].value.current_market_price += round_off(board[i].value.current_market_price * (15.0 / 100.0));
            }
            game_status->interest_rate -= game_status->interest_rate * (15.0 / 100.0);
            break;
        }
        case STOCK_MARKET_BOOM : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                board[i].value.market_price -= round_off(board[i].value.market_price * (10.0 / 100.0));
                board[i].value.current_market_price -= round_off(board[i].value.current_market_price * (10.0 / 100.0));
            }
            game_status->interest_rate += game_status->interest_rate * (10.0 / 100.0);
            break;
        }
        case GOVERNMENT_HOUSING_PROGRAMME : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost += round_off(board[i].value.house_construction_cost * (25.0 / 100.0));
                }
            }
            break;
        }
        case FOREIGN_INVESTMENT : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.market_price -= round_off(board[i].value.market_price * (20.0 / 100.0));
                    board[i].value.current_market_price -= round_off(board[i].value.current_market_price * (20.0 / 100.0));
                }
            }
            break;
        }
        default :
            break;
    }

    game_status->economic_event = rand() % 8;

    switch (game_status->economic_event) {
        case TOURISM_BOOM : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY && board[i].group == YELLOW) {
                    board[i].value.market_price += round_off(board[i].value.market_price * (15.0 / 100.0));
                    board[i].value.current_market_price += round_off(board[i].value.current_market_price * (15.0 / 100.0));
                }
            }
            printf("Economic Event\n\tTourism Boom\n\tSouthern Province properties increase in value by 15%%.\n\n");
            break;
        }
        case FUEL_CRISIS : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.hotel_construction_cost += round_off(board[i].value.hotel_construction_cost * (20.0 / 100.0));
                    board[i].value.house_construction_cost += round_off(board[i].value.house_construction_cost * (20.0 / 100.0));
                }
            }
            printf("Economic Event\n\tFuel Crisis\n\tProperty development costs increase 20%%.\n\n");
            break;
        }
        case HEAVY_MONSOON : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].group == YELLOW) {
                    board[i].value.market_price -= round_off(board[i].value.market_price * (10.0 / 100.0));
                    board[i].value.current_market_price -= round_off(board[i].value.current_market_price * (10.0 / 100.0));
                }
            }
            board[9].value.market_price -= round_off(board[9].value.market_price * (10.0 / 100.0)); // mount lavinia
            board[16].value.market_price -= round_off(board[16].value.market_price * (10.0 / 100.0)); // negombo
            board[31].value.market_price -= round_off(board[31].value.market_price * (10.0 / 100.0)); // jaffna
            board[34].value.market_price -= round_off(board[34].value.market_price * (10.0 / 100.0)); // trincomalee
            board[39].value.market_price -= round_off(board[39].value.market_price * (10.0 / 100.0)); // galle face

            board[9].value.current_market_price -= round_off(board[9].value.current_market_price * (10.0 / 100.0)); // mount lavinia
            board[16].value.current_market_price -= round_off(board[16].value.current_market_price * (10.0 / 100.0)); // negombo
            board[31].value.current_market_price -= round_off(board[31].value.current_market_price * (10.0 / 100.0)); // jaffna
            board[34].value.current_market_price -= round_off(board[34].value.current_market_price * (10.0 / 100.0)); // trincomalee
            board[39].value.current_market_price -= round_off(board[39].value.current_market_price * (10.0 / 100.0)); // galle face
            printf("Economic Event\n\tHeavy Monsoon\n\tCoastal properties lose 10%% value.\n\n");
            disaster_occurrence(players, board, *game_status);
            break;
        }
        case ECONOMIC_RECESSION : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                board[i].value.market_price -= round_off(board[i].value.market_price * (15.0 / 100.0));
                board[i].value.current_market_price -= round_off(board[i].value.current_market_price * (15.0 / 100.0));
            }
            game_status->interest_rate += game_status->interest_rate * (15.0 / 100.0);
            printf("Economic Event\n\tEconomic Recession\n\tProperty values decrease 15%%.\n\tRent decreases 10%%.\n\tLoan interest increases by 15%%\n\n");
            break;
        }
        case STOCK_MARKET_BOOM : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                board[i].value.market_price += round_off(board[i].value.market_price * (10.0 / 100.0));
                board[i].value.current_market_price += round_off(board[i].value.current_market_price * (10.0 / 100.0));
            }
            game_status->interest_rate -= game_status->interest_rate * (10.0 / 100.0);
            printf("Economic Event\n\tStock Market Boom\n\tProperty values increase 10%%.\n\tLoan interest decreases by 10%%\n\n");
            break;
        }
        case GOVERNMENT_HOUSING_PROGRAMME : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost -= round_off(board[i].value.house_construction_cost * (25.0 / 100.0));
                }
            }
            printf("Economic Event\n\tGovernment Housing Programme\n\tHouse construction costs reduce 25%%.\n\n");
            break;
        }
        case FOREIGN_INVESTMENT : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.market_price += round_off(board[i].value.market_price * (20.0 / 100.0));
                    board[i].value.current_market_price += round_off(board[i].value.current_market_price * (20.0 / 100.0));
                }
            }
            printf("Economic Event\n\tForeign Investment\n\tCommercial properties increase 20%%.\n\n");
            break;
        }
        case POLITICAL_UNREST : {
            printf("Economic Event\n\tPolitical Unrest\n\tHotel occupancy decreases and the hotel rent drops by 50%%.\n\n");
            break;
        }
        default :
            break;
    }
}

void government_regulations(Cell board[], Game *game_status) {
    switch (game_status->government_regulation) {
        case NO_REGULATION : {
            break;
        }
        case INCREASE_PROPERTY_TAX : {
            game_status->income_tax_rate -= game_status->income_tax_rate * (50.0 / 100.0);
            break;
        }
        case REDUCE_LOAN_INTEREST : {
            game_status->interest_rate += game_status->interest_rate * (2.0 / 100.0);
            break;
        }
        case HOUSING_SUBSIDY_REGULATION : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost += round_off(board[i].value.house_construction_cost * (30.0 / 100.0));
                }
            }
            break;
        }
        default :
            break;
    }

    game_status->government_regulation = rand() % 8;

    switch (game_status->government_regulation) {
        case NO_REGULATION : {
            break;
        }
        case INCREASE_PROPERTY_TAX : {
            game_status->income_tax_rate += game_status->income_tax_rate * (50.0 / 100.0);
            printf("Government Regulations\n\tIncome Tax increases by 50%%.\n\n");
            break;
        }
        case REDUCE_LOAN_INTEREST : {
            game_status->interest_rate -= game_status->interest_rate * (2.0 / 100.0);
            printf("Government Regulations\n\tInterest decreases by 2%%.\n\n");
            break;
        }
        case HOUSING_SUBSIDY_REGULATION : {
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].type == PROPERTY) {
                    board[i].value.house_construction_cost -= round_off(board[i].value.house_construction_cost * (30.0 / 100.0));
                }
            }
            printf("Government Regulations\n\tHouse construction costs reduce 30%%.\n\n");
            break;
        }
        case LUXURY_PROPERTY_TAX : {
            printf("Government Regulations\n\tHotels incur an annual maintenance tax of 25%% of property value with developments.\n\n");
            break;
        }
        case RAILWAY_MODERNIZATION : {
            printf("Government Regulations\n\tRailway rents increase 25%%.\n\n");
            break;
        }
        case ELECTRICITY_TARIFF_REVISION : {
            printf("Government Regulations\n\tUtility rents increase 20%%.\n\n");
            break;
        }
        case INSURANCE_REGULATION : {
            printf("Government Regulations\n\tInsurance premiums decrease 15%%.\n\n");
            break;
        }
        case ANTI_SPECULATION_ACT : {
            // to be implemented
            printf("Government Regulations\n\tPlayers may own at most three undeveloped properties.\n\n");
            break;
        }
    }
}

void regional_card_draw(Cell board[], Game *game_status) {
    switch (game_status->regional_card) {
        case PORT_CITY_EXPANSION : {
            board[1].value.market_price -= round_off(board[1].value.market_price * (25.0 / 100.0)); //pettah
            board[3].value.market_price -= round_off(board[3].value.market_price * (25.0 / 100.0)); //maradhana
            board[5].value.market_price -= round_off(board[5].value.market_price * (25.0 / 100.0)); //colombo fort railway

            board[1].value.current_market_price -= round_off(board[1].value.current_market_price * (25.0 / 100.0)); //pettah
            board[3].value.current_market_price -= round_off(board[3].value.current_market_price * (25.0 / 100.0)); //maradhana
            board[5].value.current_market_price -= round_off(board[5].value.current_market_price * (25.0 / 100.0)); //colombo fort railway
            break;
        } 
        case IT_INDUSTRY_GROWTH : {
            board[13].value.market_price -= round_off(board[13].value.market_price * (20.0 / 100.0)); //maharagama
            board[11].value.market_price -= round_off(board[11].value.market_price * (20.0 / 100.0)); //nugegoda
            board[14].value.market_price -= round_off(board[14].value.market_price * (20.0 / 100.0)); //kottawa

            board[13].value.current_market_price -= round_off(board[13].value.current_market_price * (20.0 / 100.0)); //maharagama
            board[11].value.current_market_price -= round_off(board[11].value.current_market_price * (20.0 / 100.0)); //nugegoda
            board[14].value.current_market_price -= round_off(board[14].value.current_market_price * (20.0 / 100.0)); //kottawa
            break;
        }  
        case NORTHERN_DEVELOPMENT_PROGRAMME : {
            board[31].value.market_price -= round_off(board[31].value.market_price * (30.0 / 100.0)); //jaffna
            board[32].value.market_price -= round_off(board[32].value.market_price * (30.0 / 100.0)); //nallur
            board[34].value.market_price -= round_off(board[34].value.market_price * (30.0 / 100.0)); //trincomalee

            board[31].value.current_market_price -= round_off(board[31].value.current_market_price * (30.0 / 100.0)); //jaffna
            board[32].value.current_market_price -= round_off(board[32].value.current_market_price * (30.0 / 100.0)); //nallur
            board[34].value.current_market_price -= round_off(board[34].value.current_market_price * (30.0 / 100.0)); //trincomalee
            break;
        } 
        case TEA_EXPORT_BOOM : {
            board[37].value.market_price -= round_off(board[37].value.market_price * (35.0 / 100.0)); //nuwara-eliya
            board[37].value.current_market_price -= round_off(board[37].value.current_market_price * (35.0 / 100.0)); //nuwara-eliya
            break;
        }    
        case AIRPORT_EXPANSION : {
            board[16].value.market_price -= round_off(board[16].value.market_price * (30.0 / 100.0)); //negambo
            board[18].value.market_price -= round_off(board[18].value.market_price * (30.0 / 100.0)); //katunayek
            board[19].value.market_price -= round_off(board[19].value.market_price * (30.0 / 100.0)); //ja-ela

            board[16].value.current_market_price -= round_off(board[16].value.current_market_price * (30.0 / 100.0)); //negambo
            board[18].value.current_market_price -= round_off(board[18].value.current_market_price * (30.0 / 100.0)); //katunayek
            board[19].value.current_market_price -= round_off(board[19].value.current_market_price * (30.0 / 100.0)); //ja-ela
            break;
        } 
        case UNIVERSITY_CITY_GROWTH : {
            board[21].value.market_price -= round_off(board[21].value.market_price * (20.0 / 100.0)); //kandy
            board[23].value.market_price -= round_off(board[23].value.market_price * (20.0 / 100.0)); //peradeniya

            board[21].value.current_market_price -= round_off(board[21].value.current_market_price * (20.0 / 100.0)); //kandy
            board[23].value.current_market_price -= round_off(board[23].value.current_market_price * (20.0 / 100.0)); //peradeniya
            break;
        } 
        case FLOOD_DAMAGE : {
            board[26].value.market_price -= round_off(board[26].value.market_price * (20.0 / 100.0)); //galle fort
            board[27].value.market_price -= round_off(board[27].value.market_price * (20.0 / 100.0)); //unawatuna
            board[29].value.market_price -= round_off(board[29].value.market_price * (20.0 / 100.0)); //hikkaduwa
            board[9].value.market_price -= round_off(board[9].value.market_price * (20.0 / 100.0)); //mount lavinia
            board[16].value.market_price -= round_off(board[16].value.market_price * (20.0 / 100.0)); //negambo
            board[39].value.market_price -= round_off(board[39].value.market_price * (20.0 / 100.0)); //galle face
            board[31].value.market_price -= round_off(board[31].value.market_price * (20.0 / 100.0)); //jaffna
            board[34].value.market_price -= round_off(board[34].value.market_price * (20.0 / 100.0)); //trincomalee

            board[26].value.current_market_price -= round_off(board[26].value.current_market_price * (20.0 / 100.0)); //galle fort
            board[27].value.current_market_price -= round_off(board[27].value.current_market_price * (20.0 / 100.0)); //unawatuna
            board[29].value.current_market_price -= round_off(board[29].value.current_market_price * (20.0 / 100.0)); //hikkaduwa
            board[9].value.current_market_price -= round_off(board[9].value.current_market_price * (20.0 / 100.0)); //mount lavinia
            board[16].value.current_market_price -= round_off(board[16].value.current_market_price * (20.0 / 100.0)); //negambo
            board[39].value.current_market_price -= round_off(board[39].value.current_market_price * (20.0 / 100.0)); //galle face
            board[31].value.current_market_price -= round_off(board[31].value.current_market_price * (20.0 / 100.0)); //jaffna
            board[34].value.current_market_price -= round_off(board[34].value.current_market_price * (20.0 / 100.0)); //trincomalee
            break;
        } 
        default : 
            break;
    }

    game_status->regional_card = rand() % 12;

    switch (game_status->regional_card) {
        case PORT_CITY_EXPANSION : {
            board[1].value.market_price += round_off(board[1].value.market_price * (25.0 / 100.0)); //pettah
            board[3].value.market_price += round_off(board[3].value.market_price * (25.0 / 100.0)); //maradhana
            board[5].value.market_price += round_off(board[5].value.market_price * (25.0 / 100.0)); //colombo fort railway

            board[1].value.current_market_price += round_off(board[1].value.current_market_price * (25.0 / 100.0)); //pettah
            board[3].value.current_market_price += round_off(board[3].value.current_market_price * (25.0 / 100.0)); //maradhana
            board[5].value.current_market_price += round_off(board[5].value.current_market_price * (25.0 / 100.0)); //colombo fort railway
            break;
        }  
        case IT_INDUSTRY_GROWTH : {
            board[13].value.market_price += round_off(board[13].value.market_price * (20.0 / 100.0)); //maharagama
            board[11].value.market_price += round_off(board[11].value.market_price * (20.0 / 100.0)); //nugegoda
            board[14].value.market_price += round_off(board[14].value.market_price * (20.0 / 100.0)); //kottawa

            board[13].value.current_market_price += round_off(board[13].value.current_market_price * (20.0 / 100.0)); //maharagama
            board[11].value.current_market_price += round_off(board[11].value.current_market_price * (20.0 / 100.0)); //nugegoda
            board[14].value.current_market_price += round_off(board[14].value.current_market_price * (20.0 / 100.0)); //kottawa
            break;
        }  
        case NORTHERN_DEVELOPMENT_PROGRAMME : {
            board[31].value.market_price += round_off(board[31].value.market_price * (30.0 / 100.0)); //jaffna
            board[32].value.market_price += round_off(board[32].value.market_price * (30.0 / 100.0)); //nallur
            board[34].value.market_price += round_off(board[34].value.market_price * (30.0 / 100.0)); //trincomalee

            board[31].value.current_market_price += round_off(board[31].value.current_market_price * (30.0 / 100.0)); //jaffna
            board[32].value.current_market_price += round_off(board[32].value.current_market_price * (30.0 / 100.0)); //nallur
            board[34].value.current_market_price += round_off(board[34].value.current_market_price * (30.0 / 100.0)); //trincomalee
            break;
        } 
        case TEA_EXPORT_BOOM : {
            board[37].value.market_price += round_off(board[37].value.market_price * (35.0 / 100.0)); //nuwara-eliya
            board[37].value.current_market_price += round_off(board[37].value.current_market_price * (35.0 / 100.0)); //nuwara-eliya
            break;
        }    
        case AIRPORT_EXPANSION : {
            board[16].value.market_price += round_off(board[16].value.market_price * (30.0 / 100.0)); //negambo
            board[18].value.market_price += round_off(board[18].value.market_price * (30.0 / 100.0)); //katunayek
            board[19].value.market_price += round_off(board[19].value.market_price * (30.0 / 100.0)); //ja-ela

            board[16].value.current_market_price += round_off(board[16].value.current_market_price * (30.0 / 100.0)); //negambo
            board[18].value.current_market_price += round_off(board[18].value.current_market_price * (30.0 / 100.0)); //katunayek
            board[19].value.current_market_price += round_off(board[19].value.current_market_price * (30.0 / 100.0)); //ja-ela
            break;
        } 
        case UNIVERSITY_CITY_GROWTH : {
            board[21].value.market_price += round_off(board[21].value.market_price * (20.0 / 100.0)); //kandy
            board[23].value.market_price += round_off(board[23].value.market_price * (20.0 / 100.0)); //peradeniya

            board[21].value.current_market_price += round_off(board[21].value.current_market_price * (20.0 / 100.0)); //kandy
            board[23].value.current_market_price += round_off(board[23].value.current_market_price * (20.0 / 100.0)); //peradeniya
            break;
        } 
        case FLOOD_DAMAGE : {
            board[26].value.market_price += round_off(board[26].value.market_price * (20.0 / 100.0)); //galle fort
            board[27].value.market_price += round_off(board[27].value.market_price * (20.0 / 100.0)); //unawatuna
            board[29].value.market_price += round_off(board[29].value.market_price * (20.0 / 100.0)); //hikkaduwa
            board[9].value.market_price += round_off(board[9].value.market_price * (20.0 / 100.0)); //mount lavinia
            board[16].value.market_price += round_off(board[16].value.market_price * (20.0 / 100.0)); //negambo
            board[39].value.market_price += round_off(board[39].value.market_price * (20.0 / 100.0)); //galle face
            board[31].value.market_price += round_off(board[31].value.market_price * (20.0 / 100.0)); //jaffna
            board[34].value.market_price += round_off(board[34].value.market_price * (20.0 / 100.0)); //trincomalee

            board[26].value.current_market_price += round_off(board[26].value.current_market_price * (20.0 / 100.0)); //galle fort
            board[27].value.current_market_price += round_off(board[27].value.current_market_price * (20.0 / 100.0)); //unawatuna
            board[29].value.current_market_price += round_off(board[29].value.current_market_price * (20.0 / 100.0)); //hikkaduwa
            board[9].value.current_market_price += round_off(board[9].value.current_market_price * (20.0 / 100.0)); //mount lavinia
            board[16].value.current_market_price += round_off(board[16].value.current_market_price * (20.0 / 100.0)); //negambo
            board[39].value.current_market_price += round_off(board[39].value.current_market_price * (20.0 / 100.0)); //galle face
            board[31].value.current_market_price += round_off(board[31].value.current_market_price * (20.0 / 100.0)); //jaffna
            board[34].value.current_market_price += round_off(board[34].value.current_market_price * (20.0 / 100.0)); //trincomalee
            break;
        }  
        default : 
            break;
    }
}