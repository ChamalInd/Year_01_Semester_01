// Player decision-making algorithms
#include "functions.h"

void player_actions(Player players[], Cell board[], Cell *property_groups[][3], Game *game_status, Events national_events[]) {
    int player = game_status->current_player;
    int place_id = players[player].place;

    if (place_id != 0) {
        printf("%s Landed on %s.\n\n", players[player].name, board[place_id].name);
    }

    settle_outstanding_penalties(&players[game_status->current_player], board, *game_status);

    if (board[place_id].type == PROPERTY || board[place_id].type == RAILWAY || board[place_id].type == UTILITY) {
        if (board[place_id].type == PROPERTY && board[place_id].owner == players[player].id) {
            if (board[place_id].group != NO_COLOR && players[player].events[LABOUR_STRIKE].remaining_effect <= 0) {
                constructions(players, board, property_groups, *game_status);
            }

            property_renovations(&players[player], board);
            building_renovations(&players[player], board);
        }

        if (board[place_id].owner == BANK_OF_CEYLON) {
            buy(players, board, *game_status);

        } else if (board[place_id].owner != players[player].id && board[place_id].owner > 0)  {
            rent(players, &board[place_id], board, *game_status);
        }
        

    } else {
        if (place_id == 2) { // Community Development Fund
            tax_payments(players, board, *game_status, COMMUNITY_DEVELOPMENT_FUND);

        } else if (place_id == 4) { // Income Tax
            tax_payments(players, board, *game_status, INCOME_TAX);

        } else if (place_id == 7 || place_id == 22 || place_id == 36) { // National Event Card
            national_event_card_draw(players, board, national_events, game_status);
            
        } else if (place_id == 17 || place_id == 33) { // Insurance
            check_for_insurance_action(players, board, *game_status);
            
        } else if (place_id == 30) { // Jail square
            check_for_jailed(&players[player]);

        } else if (place_id == 38) { // Bank square
            check_for_bank_action(players, board, *game_status);
        } 
    }
}


void check_for_bank_action(Player players[], Cell board[], Game game_status) {
    int player = game_status.current_player;
    Status player_status = calculate_player_status(players[player], board);

    switch (players[player].id) {
        case AGGRESSIVE_INVESTOR : {        
            if (players[player].loan_status.no_of_loans == 0 && player_status.unmortgaged_properties > 0 && player_status.total_properties > player_status.hotels_built) {
                // only obtain loan when there are hotels to be built
                obtain_loan(&players[player], board, game_status);

            } else if (players[player].loan_status.no_of_loans == 1) {
                if (player_status.unmortgaged_properties > 0 && player_status.total_properties > player_status.hotels_built) {
                    // refinance loan when necessary
                    refinance_loan(&players[player], board, game_status);
                
                } else if (players[player].cash >= ((players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest) * 2)) {
                    // if cash is more than double the payable, pay the loan
                    repay_outstanding_loan(players, board, game_status);

                } else {
                    // extend loan before expiry
                    extend_loan(&players[player]);
                }
            }
            break;
        }
        case CONSERVATIVE_BANKER : {
            if (players[player].loan_status.no_of_loans == 0 && player_status.unmortgaged_properties > 0 && players[player].cash <= players[player].taxes_due) {
                // obtain loan only to reduce chance of bankruptcy
                obtain_loan(&players[player], board, game_status);

            } else if (players[player].loan_status.no_of_loans == 1) {
                if (player_status.unmortgaged_properties > 0 && players[player].cash <= players[player].taxes_due) {
                    // refinance loan when necessary
                    refinance_loan(&players[player], board, game_status);

                } else if (players[player].cash >= (players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest)) {
                    // pay loans when sufficient funds exists
                    repay_outstanding_loan(players, board, game_status);  

                } else {
                    // extend loan before expiry
                    extend_loan(&players[player]);
                }
            }
            break;
        }
        case RISK_TAKER : {
            if (players[player].loan_status.no_of_loans == 0 && player_status.unmortgaged_properties > 0) {
                // always get loans if non exists
                obtain_loan(&players[player], board, game_status);

            } else if (players[player].loan_status.no_of_loans == 1) {
                if (player_status.unmortgaged_properties > 0) {
                    // always get loans on newly accrued properties
                    refinance_loan(&players[player], board, game_status);

                } else {
                    // always extends loan
                    extend_loan(&players[player]);
                }
            }
            break;
        }
        case OPPORTUNISTIC_TRADER : {
            // calculating borrowing cost
            double max_loan = 0, accumulated_interest = 0;
            int total_unmortgaged_property_value = 0;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].owner == players[player].id && board[i].mortgage.status == UNMORTGAGED) {
                    total_unmortgaged_property_value += board[i].mortgage.value;
                }
            }
            
            max_loan = ((double) total_unmortgaged_property_value) * (75.0 / 100.0);
            accumulated_interest += max_loan * (1 + (20 * game_status.interest_rate / 100.0));
            // projected income
            int rent_income = 0;
            for (int i = 0; i < NO_OF_CELLS; i++) {
                if (board[i].owner == players[player].id) {
                    rent_income += board[i].value.base_rent * 2; // assuming houses are built
                }
            }
            if (players[player].loan_status.no_of_loans == 0 && player_status.unmortgaged_properties > 0 && rent_income > accumulated_interest) {
                // only obtain loans when projected income is higher
                obtain_loan(&players[player], board, game_status);

            } else if (players[player].loan_status.no_of_loans == 1) {
                if (player_status.unmortgaged_properties > 0 && rent_income > accumulated_interest) {
                    // refinance loan when necessary
                    refinance_loan(&players[player], board, game_status);

                } else if (players[player].cash >= (players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest)) {
                    // pay loans when sufficient funds exists
                    repay_outstanding_loan(players, board, game_status);  

                } else {
                    // extend loan before expiry
                    extend_loan(&players[player]);
                }
            }
            break;
        }
    }
}

void check_for_insurance_action(Player players[], Cell board[], Game game_status) {
    int player = game_status.current_player;
    int insurance_company = board[players[player].place].type;
    Status player_status = calculate_player_status(players[player], board);

    if (player_status.total_properties > 0) {
        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == players[player].id && board[i].type == PROPERTY && board[i].insurance.policy == NO_INSURANCE) {
                obtain_insurance(players, board, game_status, insurance_company, FALSE, i);

            } else if (board[i].owner == players[player].id && board[i].type == PROPERTY && board[i].insurance.policy != NO_INSURANCE && board[i].insurance.provider == insurance_company) {
                obtain_insurance(players, board, game_status, insurance_company, TRUE, i);
            }
        }
    } else {
        printf("No properties to be insured.\n\n");
    }
}

void buy(Player players[], Cell board[], Game game_status) {
    int going_to_buy = FALSE;
    int player = game_status.current_player;
    int place_id = players[player].place;

    switch (players[player].id) {
        case AGGRESSIVE_INVESTOR : {
            int future_rent = board[NO_OF_CELLS - 1].value.base_rent * 10; // maximum rent might have to pay (Galle Face with a hotel)

            if (board[place_id].id == 37 || board[place_id].id == 39) {
                // prioritize Galle Face and Nuwara Eliya
                going_to_buy = players[player].cash >= board[place_id].value.market_price;
            } else {
                going_to_buy = players[player].cash >= board[place_id].value.market_price + future_rent;
            }
            break;
        }
        case CONSERVATIVE_BANKER : {
            going_to_buy = game_status.economic_event != ECONOMIC_RECESSION && ((players[player].cash >= board[place_id].value.market_price && (board[place_id].type == RAILWAY || board[place_id].type == UTILITY)) || (round_off(players[player].cash / 2.0) >= board[place_id].value.market_price && board[place_id].type == PROPERTY));
            break;
        }
        case RISK_TAKER : {
            going_to_buy = players[player].cash >= board[place_id].value.market_price;
            break;
        }
        case OPPORTUNISTIC_TRADER : {
            double added_factors = game_status.inflation_rate;

            if (board[place_id].type == PROPERTY && game_status.dynamic_market[MARKET_BOOM].property_group == board[place_id].group) {
                added_factors += 20.0;
            }

            double projected_appreciation = board[place_id].value.market_price * (added_factors / 100.0);
            double construction_cost = board[place_id].value.house_construction_cost;

            going_to_buy = players[player].cash >= board[place_id].value.market_price && projected_appreciation > construction_cost;
            break;
        }
    }

    if (going_to_buy == TRUE) {
        board[place_id].owner = players[player].id;
        board[place_id].ownerptr = &players[player];
        
        printf("%s purchased %s for LKR %i.\n", players[player].name, board[place_id].name, board[place_id].value.market_price);
        players[player].cash -= board[place_id].value.market_price;
        printf("Remaining Balance : LKR %i.\n\n", players[player].cash);
    } else {
        auction(players, board, &board[place_id], BANK_OF_CEYLON, game_status);
    }
}

int auction(Player players[], Cell board[], Cell *place, Ownership beneficiary, Game game_status) {
    if (place->type == PROPERTY || place->type == RAILWAY || place->type == UTILITY) {
        int bidding_players = 0, highest_bid = 0, bidder = NONE;
        int bidding[NO_OF_PLAYERS];

        int starting_price = place->value.market_price / 2;

        if (place->type == PROPERTY && place->group == game_status.dynamic_market[MARKET_DECLINE].property_group) {
            starting_price = round_off((double) starting_price * 75.0 / 100.0);
        }

        highest_bid = starting_price;

        // finding initial bidders
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].isBankrupt == FALSE && players[i].jail_status.isJailed == FALSE && players[i].id != beneficiary && players[i].cash >= starting_price) {
                if (players[i].id == AGGRESSIVE_INVESTOR) {
                    int choice = FALSE;
                    for (int j = 0; j < NO_OF_CELLS; j++) {
                        // prioritize having a monopoly
                        if (board[j].group == place->group && board[j].owner == players[i].id) {
                            choice = TRUE;
                            break;
                        }
                    }
                    if (choice == TRUE || place->id == 37 || place->id == 39) { // prioritize Galle Face and Nuwara Eliya 
                        players[i].going_to_bid = TRUE;
                        bidding[i] = i;
                        bidding_players++;
                    } else {
                        bidding[i] = NONE;
                    }

                } else if (((players[i].id == CONSERVATIVE_BANKER && game_status.economic_event != ECONOMIC_RECESSION) || players[i].id == OPPORTUNISTIC_TRADER) && starting_price < place->value.market_price) {
                    // both participate when price is discounted
                    players[i].going_to_bid = TRUE;
                    bidding[i] = i;
                    bidding_players++;

                } else if (players[i].id == RISK_TAKER) {
                    // always participates
                    players[i].going_to_bid = TRUE;
                    bidding[i] = i;
                    bidding_players++;

                } else {
                    bidding[i] = NONE;
                }
                
            } else {
                bidding[i] = NONE;
            }
        }
        printf("Auction Started.\n");
        printf("Property :\n\t%s\n", place->name);
        printf("Opening Bid : \n\tLKR %i.\n\n", starting_price);
        printf("Bidders : [");
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].going_to_bid == TRUE) {
                printf(" <%s> ", players[i].name);
            }
        }
        printf("]\n\n");

        if (bidding_players == 1) {
            for (int i = 0; i < NO_OF_PLAYERS; i++) {
                if (players[i].going_to_bid == TRUE) {
                    bidder = i;
                    printf("%s bids LKR %i.\n\n", players[i].name, highest_bid);
                    break;
                }
            }

        } else {
            while (bidding_players > 1) {
                for (int i = 0; i < NO_OF_PLAYERS; i++) {
                    if (players[i].going_to_bid == TRUE) {
                        bidding[i] = i;
                    } else {
                        bidding[i] = NONE;
                    }
                }

                // auction process
                for (int i = 0; i < NO_OF_PLAYERS; i++) {   
                    if (bidding[i] != NONE) { 
                        if (players[bidding[i]].cash >= highest_bid + 250) {
                            if (players[i].id == AGGRESSIVE_INVESTOR && highest_bid + 250 < round_off(place->value.market_price * (120.0 / 100.0))) {
                                // exists auction when bid exceeds 120%
                                highest_bid += 250;
                                bidder = bidding[i];
                                printf("%s bids LKR %i.\n", players[bidding[i]].name, highest_bid);

                            } else if ((players[i].id == CONSERVATIVE_BANKER || players[i].id == OPPORTUNISTIC_TRADER) && highest_bid + 250 < place->value.market_price) {
                                // exists auction when bid is higher than market price
                                highest_bid += 250;
                                bidder = bidding[i];
                                printf("%s bids LKR %i.\n", players[bidding[i]].name, highest_bid);
                            
                            } else if (players[i].id == RISK_TAKER) {
                                // never withdraws
                                highest_bid += 250;
                                bidder = bidding[i];
                                printf("%s bids LKR %i.\n", players[bidding[i]].name, highest_bid);

                            } else {
                                players[bidding[i]].going_to_bid = FALSE;
                                bidding_players--;
                                if (bidding_players == 0) {
                                    break;
                                }
                                printf("%s withdraws.\n", players[bidding[i]].name);
                            }
                        } else {
                            players[bidding[i]].going_to_bid = FALSE;
                            bidding_players--;
                            if (bidding_players == 0) {
                                break;
                            }
                            printf("%s withdraws.\n", players[bidding[i]].name);
                        }
                    }
                }

                printf("\n");
            }
        }

        // resetting auction parameters
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            players[i].going_to_bid = FALSE;
        }

        if (bidder != NONE) {
            if (beneficiary != BANK_OF_CEYLON) {
                for (int i = 0; i < NO_OF_PLAYERS; i++) {
                    if (players[i].id == beneficiary) {
                        players[i].cash += highest_bid;
                        destroy_property(place);
                        printf("%s sold %s for LKR %i in the auction.\n", players[i].name, place->name, highest_bid);
                        printf("Cash Balance : LKR %i.\n\n", players[i].cash);
                        break;
                    }
                }
            }

            place->owner = players[bidder].id;
            place->ownerptr = &players[bidder];
            players[bidder].cash -= highest_bid;

            printf("%s wins the auction.\n", players[bidder].name);
            printf("%s purchased %s for LKR %i.\n", players[bidder].name, place->name, highest_bid);
            printf("Remaining Balance : LKR %i.\n\n", players[bidder].cash);

            return TRUE;

        } else {
            if (beneficiary == BANK_OF_CEYLON) {
                printf("No bidder property goes back to bank.\n\n");
            } else {
                printf("No bidder property goes back to owner.\n\n");
            }

            return FALSE;
        }
    }
    return FALSE;
}

void raise_money(Player players[], Cell board[], Game game_status, int amount_to_be_raised) {
    Cell *available[NO_OF_CELLS];
    int available_count = 0;
    int player = game_status.current_player;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (i != players[player].place && board[i].owner == players[player].id && board[i].mortgage.status == UNMORTGAGED && (board[i].type == PROPERTY || board[i].type == RAILWAY || board[i].type == UTILITY)) {
            available[i] = &board[i];
            available_count++;
        } else {
            available[i] = NULL;
        }
    }

    if (available_count == 0) { // not enough property so declared bankrupt
        players[player].isBankrupt = TRUE;
        announce_bankruptcy(players, board, game_status, player);
        return;
    }

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (available[i] != NULL) {
            printf("%s decided to sell a property.\n\n", players[player].name);
            int result = auction(players, board, available[i], players[player].id, game_status);
            if (result == FALSE) {
                // when no bidders are available property is sold to bank at mortgage price
                players[player].cash += available[i]->mortgage.value;
                destroy_property(available[i]);
                printf("%s sold %s to Bank of Ceylon for LKR %i.\n\n", players[player].name, available[i]->name, available[i]->mortgage.value);
            }

            if (players[player].cash >= amount_to_be_raised) {
                break;
            }
        }
    }

    if (players[player].cash < amount_to_be_raised) { // not enough cash so declared bankrupt
        players[player].isBankrupt = TRUE;
        announce_bankruptcy(players, board, game_status, player);
        return;
    }
}

void rent(Player players[], Cell *place, Cell board[], Game game_status) {
    int rent = 0;
    Status owner_status = calculate_player_status(*place->ownerptr, board);
    int player = game_status.current_player;
    
    if (place->type == PROPERTY) {
        int house_rent_multiplier[] = {2, 3, 5, 7};

        if (place->buildings.no_of_houses != 0) {
            rent = place->value.base_rent * house_rent_multiplier[place->buildings.no_of_houses - 1];

        } else if (place->buildings.no_of_hotels != 0) {
            rent = place->value.base_rent * 10;

        } else {
            rent = place->value.base_rent;
        }

        // for tourism hype & tourism boom
        if (place->ownerptr->events[TOURISM_HYPE].remaining_effect > 0 || (game_status.economic_event == TOURISM_BOOM && place->group == YELLOW)) {
            rent *= 2;
        }
        // for festival season
        if (place->ownerptr->events[FESTIVAL_SEASON].remaining_effect > 0 && place->buildings.no_of_hotels > 0) { 
            rent = round_off((double) rent * (150.0 / 100.0));
        }
        // for political unrest
        if (game_status.economic_event == POLITICAL_UNREST && place->buildings.no_of_hotels > 0) {
            rent = round_off((double) rent * (50.0 / 100.0));
        }
        // for southern tourism boom
        if (game_status.regional_card == SOUTHERN_TOURISM_BOOM && place->buildings.no_of_hotels > 0) {
            // Galle face | unawatuna | hikkaduwa
            if (place->id == 39 || place->id == 27 || place->id == 29) {
                rent += round_off(rent * (40.0 / 100.0));
            }
        }
        // for water shortage
        if (game_status.regional_card == WATER_SHORTAGE) {
            if (place->id == 27 || place->id == 29) {
                rent -= round_off(rent * (10.0 / 100.0));
            }
        }
        // for beach population
        if (game_status.regional_card == BEACH_POLLUTION) {
            if (place->id == 26 || place->id == 27 || place->id == 29) {
                rent -= round_off(rent * (30.0 / 100.0));
            }
        }

        // additional calculation for building depreciation
        if (place->buildings.has_damaged == TRUE) {
            rent = 0;
        } else if (place->buildings.age >= 20) {
            rent -= round_off((double) rent * (25.0 / 100.0));
        } else {
            rent -= round_off((double) rent * (place->buildings.rent_reduction_rate / 100.0));
        }

    } else if (place->type == RAILWAY) {
        int rent_values[] = {250, 500, 1000, 2000};
        rent = rent_values[owner_status.total_railways - 1];

        // for fuel shortage & fuel crisis
        if (place->ownerptr->events[FUEL_SHORTAGE].remaining_effect > 0 || game_status.economic_event == FUEL_CRISIS) {
            rent *= 2;
        }
        // for government regulations
        if (game_status.government_regulation == RAILWAY_MODERNIZATION) {
            rent += round_off(rent * (25.0 / 100.0));
        }
        // for transport strike
        if (game_status.regional_card == TRANSPORT_STRIKE) {
            rent -= round_off(rent * (40.0 / 100.0));
        }

    } else if (place->type == UTILITY) {
        int rent_values[] = {4 * players[player].die_roll, 10 * players[player].die_roll};
        rent = rent_values[owner_status.total_utilities - 1];

        // for power failure
        if (place->ownerptr->events[POWER_FAILURE].remaining_effect > 0) {
            rent = round_off((float) rent / 2.0);
        }
        // for government regulations
        if (game_status.government_regulation == ELECTRICITY_TARIFF_REVISION) {
            rent += round_off(rent * (20.0 / 100.0));
        }
        // for electricity tariff
        if (game_status.regional_card == ELECTRICITY_TARIFF_INCREASE) {
            rent += round_off(rent * (25.0 / 100.0));
        }
        // for water shortage
        if (game_status.regional_card == WATER_SHORTAGE) {
            rent += round_off(rent * (20.0 / 100.0));
        }
    }

    // economic recession 
    if (game_status.economic_event == ECONOMIC_RECESSION) {
        rent -= round_off(rent * (10.0 / 100.0));
    }
        
    // if low on cash sell property to pay rent
    if ((players[player].cash - rent) < 0) {
        printf("%s do not have enough cash to pay rent.\n", players[player].name);
        printf("Cash Balance : LKR %i.\nRequired Amount : LKR %i\n\n", players[player].cash, rent);
        
        raise_money(players, board, game_status, rent);
    }  
    
    if (players[player].isBankrupt == FALSE && players[player].cash >= rent) {
        players[player].cash -= rent;
        place->ownerptr->cash += rent;

        printf("Rent Paid : LKR %i.\n", rent);
        printf("Owner : %s.\n\n", place->ownerptr->name); 
    }
}

void constructions(Player players[], Cell board[], Cell *property_groups[][3], Game game_status) {
    int player = game_status.current_player;
    int place_id = players[player].place;
    int group_id = board[place_id].group;

    for (int j = 0; j < 3; j++) {
        if (property_groups[group_id][j] == NULL) {
            continue;
        }
        if (property_groups[group_id][j]->owner != players[player].id) {
            return;
        }
    }

    int going_to_build_houses = FALSE, going_to_build_hotels = FALSE;
    int basic_housing_rules = board[place_id].buildings.no_of_houses < 4 && board[place_id].buildings.no_of_hotels == 0 && players[player].cash >= board[place_id].value.house_construction_cost;
    int basic_hotel_rules = board[place_id].buildings.no_of_houses == 4 && players[player].cash >= board[place_id].value.hotel_construction_cost;

    switch (players[player].id) {
        case AGGRESSIVE_INVESTOR : {
            going_to_build_houses = basic_housing_rules;
            going_to_build_hotels = basic_hotel_rules;
            break;
        }
        case CONSERVATIVE_BANKER : {
            if (game_status.economic_event != ECONOMIC_RECESSION) {
                going_to_build_houses = basic_housing_rules;
                going_to_build_hotels = players[player].loan_status.no_of_loans == 0 && basic_hotel_rules;
            }
            break;
        }
        case RISK_TAKER : {
            if (board[place_id].value.market_price > HIGH_VALUE_PROPERTY && players[player].cash < board[place_id].value.hotel_construction_cost) {
                // sell low valued properties for constructions on high valued properties
                raise_money(players, board, game_status, board[place_id].value.hotel_construction_cost);
            }

            going_to_build_houses = basic_housing_rules;
            going_to_build_hotels = basic_hotel_rules;
            break;
        }
        case OPPORTUNISTIC_TRADER : {
            if (game_status.inflation_rate < 0 || game_status.government_regulation == HOUSING_SUBSIDY_REGULATION) {
                going_to_build_houses = basic_housing_rules;
                going_to_build_hotels = basic_hotel_rules;
            }
            break;
        }
    }

    if (going_to_build_houses == TRUE) {
        for (int i = 0; i < 3; i++) {
            if (property_groups[group_id][i] == NULL) {
                continue;
            }
            if (board[place_id].buildings.no_of_houses > property_groups[group_id][i]->buildings.no_of_houses && property_groups[group_id][i]->buildings.no_of_hotels == 0) {
                return;
            }
        }
        board[place_id].buildings.no_of_houses++;
        board[place_id].value.building_value = board[place_id].value.house_construction_cost * board[place_id].buildings.no_of_houses;
        players[player].cash -= board[place_id].value.house_construction_cost;

        printf("%s constructed one house on %s.\n", players[player].name, board[place_id].name);
        printf("Construction cost : LKR %i.\n\n", board[place_id].value.house_construction_cost);

    } else if (going_to_build_hotels == TRUE) {
        board[place_id].buildings.no_of_houses = 0;
        board[place_id].buildings.no_of_hotels++;
        board[place_id].value.building_value = board[place_id].value.hotel_construction_cost;
        players[player].cash -= board[place_id].value.hotel_construction_cost;
        board[place_id].buildings.age = 0;
        board[place_id].buildings.condition = 100;
        board[place_id].buildings.has_damaged = FALSE;
        board[place_id].buildings.rent_reduction_rate = 0;

        printf("%s upgraded houses in %s to a Hotel.\n", players[player].name, board[place_id].name);
        printf("Upgrade cost : LKR %i.\n\n", board[place_id].value.hotel_construction_cost);
    }
}

void property_renovations(Player *player, Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        int going_to_renovate = FALSE;

        switch (player->id) {
            case AGGRESSIVE_INVESTOR : {
                going_to_renovate = TRUE;
                break;
            }
            case CONSERVATIVE_BANKER : {
                // do not renovate until depreciation reaches 10%
                going_to_renovate = board[i].depreciation.percentage >= 10;
                break;
            } 
            case RISK_TAKER : {
                // ignore until repair becomes unavoidable
                going_to_renovate = board[i].depreciation.percentage == 30;
                break;
            }
            case OPPORTUNISTIC_TRADER : {
                // do not renovate until depreciation reaches 15%
                going_to_renovate = board[i].depreciation.percentage >= 15;
                break;
            }
        }

        if (board[i].owner == player->id && board[i].depreciation.age >= 50 && going_to_renovate) {
            double renovation_cost = (double) board[i].value.current_market_price * (10.0 / 100.0);
            if (player->cash >= round_off(renovation_cost)) {
                player->cash -= round_off(renovation_cost);
                board[i].depreciation.age = 0;
                board[i].depreciation.percentage = 0;
                board[i].value.market_price = board[i].value.current_market_price;

                printf("%s renovated %s for LKR %i.\n", player->name, board[i].name, (int) renovation_cost);
                printf("Remaining Balance : LKR %i.\n\n", player->cash);
            }
        }
    }
}

void building_renovations(Player *player, Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player->id && (board[i].buildings.no_of_houses + board[i].buildings.no_of_hotels) > 0 && board[i].buildings.age > 0) {
            double maintenance_cost = 0.0f;

            if (board[i].buildings.no_of_hotels > 0) {
                if (board[i].buildings.age >= 20) {
                    maintenance_cost = (double) (board[i].value.hotel_construction_cost * (8.0 / 100.0)) * (150.0 / 100);
                } else {
                    maintenance_cost = (double) board[i].value.hotel_construction_cost * (8.0 / 100.0);
                }
            } else {
                if (board[i].buildings.age >= 20) {
                    maintenance_cost = (double) (board[i].value.house_construction_cost * (5.0 / 100.0)) * (150.0 / 100) * board[i].buildings.no_of_houses;
                } else {
                    maintenance_cost = (double) board[i].value.house_construction_cost * (5.0 / 100.0) * board[i].buildings.no_of_houses;
                }
                
            }

            if (player->cash >= round_off(maintenance_cost)) {
                player->cash -= round_off(maintenance_cost);
                board[i].buildings.age = 0;
                board[i].buildings.condition = 100;
                board[i].buildings.has_damaged = FALSE;
                board[i].buildings.rent_reduction_rate = 0;
                printf("%s renovated buildings in %s for LKR %i.\n", player->name, board[i].name, (int) maintenance_cost);
                printf("Remaining Balance : LKR %i.\n\n", player->cash);
            }
        }
    }
}