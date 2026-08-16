// Loans, banking, insurance, depreciation, taxation
#include "functions.h"

void obtain_loan(Player *player, Cell board[], Game game_status) {
    double max_loan = 0;
    int total_unmortgaged_property_value = 0;
    int collateral_ids[NO_OF_CELLS];
    int no_of_collaterals = 0;

    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].owner == player->id && board[i].mortgage.status == UNMORTGAGED) {
            total_unmortgaged_property_value += board[i].mortgage.value;
            collateral_ids[no_of_collaterals] = board[i].id;
            no_of_collaterals++;
        }
    }

    max_loan = ((double) total_unmortgaged_property_value) * (75.0 / 100.0);

    if (player->loan_status.total_payable > 0) {
        player->cash += round_off(max_loan - player->loan_status.total_payable);
    
    } else {
        player->cash += round_off(max_loan);
    }

    player->loan_status.no_of_loans++;
    player->loan_status.total_payable = round_off(max_loan);
    player->loan_status.loan_duration = 20;
    player->loan_status.interest_rate = game_status.interest_rate;

    printf("%s obtained a secured loan.\n", player->name);
    printf("Loan Amount : LKR %i.\n", round_off(max_loan));
    printf("Outstanding Loan Amount : LKR %i.\n", player->loan_status.total_payable + player->loan_status.accumulated_interest);
    printf("\nCollateral : \n");

    for (int i = 0; i < no_of_collaterals; i++) {
        printf("\t%s\n", board[collateral_ids[i]].name);
        board[collateral_ids[i]].mortgage.status = MORTGAGED;
    }

    printf("\nInterest Rate : %.2f%%.\n", player->loan_status.interest_rate);
    printf("Duration : %i.\n\n", player->loan_status.loan_duration);
}

void accumulated_interest(Player *player) {
    if (player->isBankrupt == FALSE && player->loan_status.no_of_loans == 1 && player->loan_status.loan_duration > 0) {
        double interest = ((double) player->loan_status.total_payable + player->loan_status.accumulated_interest) * (player->loan_status.interest_rate / 100.0);
        player->loan_status.accumulated_interest = round_off(interest);
    }
}

void check_for_loan_status(Player players[], Cell board[], Game game_status) {
    int player = game_status.current_player;

    if (players[player].isBankrupt == FALSE) {
        if (players[player].loan_status.loan_duration > 0) {
            players[player].loan_status.loan_duration--;
            if (players[player].loan_status.loan_duration == 3) {
                printf("Loan of %s for LKR %i will overdue after 3 rounds.\n\n", players[player].name, players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest);
            }
        } 
        
        if (players[player].loan_status.no_of_loans == 1 && players[player].loan_status.loan_duration == 0) {
            players[player].loan_status.loan_duration = 0;
            players[player].loan_status.no_of_loans = 0;
            players[player].loan_status.total_payable = 0;
            players[player].loan_status.accumulated_interest = 0;
        
            printf("%s has defaulted.\n", players[player].name);
            printf("Collateral has been foreclosed.\nOutstanding debt cleared.\n\n");
            for (int j = 0; j < NO_OF_CELLS; j++) {
                if (board[j].owner == players[player].id && board[j].mortgage.status == MORTGAGED) {
                    destroy_property(&board[j]);
                    auction(players, board, &board[j], BANK_OF_CEYLON, game_status);
                }
            }
            check_for_bankruptcy(players, board, game_status, player);
        }
    }
}

void repay_outstanding_loan(Player players[], Cell board[], Game game_status) {
    int player = game_status.current_player;
    int amount = players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest;

    if (players[player].cash >= amount) {
        players[player].loan_status.no_of_loans = 0;
        players[player].loan_status.loan_duration = 0;
        players[player].cash -= amount;
        players[player].loan_status.total_payable = 0;
        players[player].loan_status.accumulated_interest = 0;

        unmortgage_property(board, players[player]);

        printf("%s repaid LKR %i.\n", players[player].name, amount);
        printf("Outstanding Balance : \n\tLKR %i.\n\n", players[player].loan_status.total_payable + players[player].loan_status.accumulated_interest);
        
    } else {
        check_for_bankruptcy(players, board, game_status, player);
    }
}

void extend_loan(Player *player) {
    player->loan_status.loan_duration = 20;
    printf("%s extended the loan of LKR %i.\n", player->name, player->loan_status.total_payable + player->loan_status.accumulated_interest);
    printf("Duration : %i.\n\n", player->loan_status.loan_duration);
}

void refinance_loan(Player *player, Cell board[], Game game_status) {
    Status player_status = calculate_player_status(*player, board);
    if (player_status.unmortgaged_properties > 0) {
        player->loan_status.no_of_loans = 0;

        unmortgage_property(board, *player);

        printf("%s decided to refinance existing loan.\n\n", player->name);
        obtain_loan(player, board, game_status);
    }
}

void obtain_insurance(Player players[], Cell board[], Game game_status, int provider, int has_insurance, int place) {
    int premium = 0, policy = board[place].insurance.policy;
    char *insurance_policy_names[] = {"Basic Property Insurance", "Comprehensive Insurance", "Business Interruption Insurance"};

    if (has_insurance == FALSE) {
        switch (players[game_status.current_player].id) {
            case AGGRESSIVE_INVESTOR : {
                if (board[place].buildings.no_of_houses > 0) {
                    policy = BASIC;

                } else if (board[place].buildings.no_of_hotels > 0) {
                    policy = COMPREHENSIVE;
                } else {
                    return;
                }
                break;
            }
            case CONSERVATIVE_BANKER : {
                policy = COMPREHENSIVE;
                break;
            }
            case RISK_TAKER : {
                if (players[game_status.current_player].has_disaster_occurred == TRUE) {
                    policy = rand() % 3;

                    while (board[place].buildings.no_of_hotels == 0 && policy == BUSINESS_INTERRUPTION) {
                        policy = rand() % 3;
                    }
                } else {
                    return;
                }
                break;
            }
            case OPPORTUNISTIC_TRADER : {
                if (board[place].value.market_price >= HIGH_VALUE_PROPERTY) {
                    policy = COMPREHENSIVE;
                } else {
                    policy = BASIC;
                }
                break;
            }
        }
    }

    switch (policy) {
        case BASIC:
            premium = round_off((double) board[place].value.market_price * (5.0 / 100.0));
            break;
        case COMPREHENSIVE:
            premium = round_off((double) board[place].value.market_price * (10.0 / 100.0));
            break;
        case BUSINESS_INTERRUPTION:
            premium = round_off((double) board[place].value.market_price * (15.0 / 100.0));
            break;
        case NO_INSURANCE:
            break;
    }

    // for insurance discount
    if (players[game_status.current_player].events[INSURANCE_DISCOUNT].remaining_effect > 0) {
        premium = round_off((double) premium * (80.0 / 100.0));
    }

    // insurance regulations
    if (game_status.government_regulation == INSURANCE_REGULATION) {
        premium -= round_off(premium * (15.0 / 100.0));
    }

    if (players[game_status.current_player].cash >= premium) {
        players[game_status.current_player].cash -= premium;
        board[place].insurance.duration = 20;
        board[place].insurance.policy = policy;
        board[place].insurance.provider = provider;

        if (has_insurance == FALSE) {
            printf("%s purchased.\n", insurance_policy_names[board[place].insurance.policy]);

        } else {
            printf("%s renewed.\n", insurance_policy_names[board[place].insurance.policy]);
        }

        printf("Property : %s.\n", board[place].name);
        printf("Premium : LKR %i.\n\n", premium);

    } else {
        if (has_insurance == FALSE) {
            printf("Not enough money to purchase insurance premium.\n\n");

        } else {
            printf("Not enough money to renew insurance premium.\n\n");
        }
    }   
}

void check_for_insurance_status(Cell board[]) {
    for (int i = 0; i < NO_OF_CELLS; i++) {
        if (board[i].type == PROPERTY && board[i].insurance.policy != NO_INSURANCE && board[i].insurance.duration > 0) {
            board[i].insurance.duration--;
            if (board[i].insurance.duration == 3) {
                printf("Insurance policy on %s expires in 3 rounds.\n\n", board[i].name);

            } else if (board[i].insurance.duration == 0) {
                printf("Insurance policy on %s has expired.\n\n", board[i].name);
                board[i].insurance.duration = 0;
                board[i].insurance.policy = NO_INSURANCE;
                board[i].insurance.provider = NONE;
            }
        } 
    }
}

void insurance_compensation(Cell board[], int property, int disaster, char *disaster_name) {
    int covered_by_insurance = FALSE, compensation = 0;
    char *policy = NULL;
    int repair_cost = round_off(board[property].value.market_price * (10.0 / 100.0)); // assumed that the repair cost is the same as the renovation cost for depreciated properties

    switch (board[property].insurance.policy) {
        case BASIC : {
            if (disaster < 2) {
                compensation = round_off(repair_cost * (80.0 / 100.0));
                covered_by_insurance = TRUE;
            } else {
                covered_by_insurance = FALSE;
                policy = "Basic Property";
            }
            break;
        }
        case COMPREHENSIVE : {
            if (disaster < 4) {
                compensation = repair_cost;
                covered_by_insurance = TRUE;
            } else {
                covered_by_insurance = FALSE;
                policy = "Comprehensive";
            }
            break;
        }
        case BUSINESS_INTERRUPTION : {
            int lost_rent = board[property].value.base_rent * 10 * 5;
            compensation = repair_cost + lost_rent;
            covered_by_insurance = TRUE;
            break;
        }
        default :
            compensation = NONE;
            break;
    }

    if (compensation != NONE) {
        if (covered_by_insurance == TRUE) {
            printf("Insurance claim Approved.\n\n");
            printf("Compensation Paid : LKR %i.\n\n", compensation);

            board[property].ownerptr->cash += compensation;

            if (board[property].ownerptr->cash >= repair_cost) {
                board[property].ownerptr->cash -= repair_cost;
                if (board[property].insurance.policy == BASIC) {
                    printf("%s Paid the rest : LKR %i.\n\n", board[property].ownerptr->name, repair_cost - compensation);
                }
            }
        } else {
            printf("%s Insurance doesn't cover %s.\n\n", policy, disaster_name);

            if (board[property].ownerptr->cash >= repair_cost) {
                board[property].ownerptr->cash -= repair_cost;
                printf("%s Paid the repair cost : LKR %i.\n\n", board[property].ownerptr->name, repair_cost);
            }
        }
    } else {
        printf("%s isn't insured.\n\n", board[property].name);

        if (board[property].ownerptr->cash >= repair_cost) {
            board[property].ownerptr->cash -= repair_cost;
            printf("%s Paid the repair cost : LKR %i.\n\n", board[property].ownerptr->name, repair_cost);
        }
    }
}

void tax_payments(Player players[], Cell board[], Game game_status, int tax) {
    int player = game_status.current_player;
    Status player_status = calculate_player_status(players[player], board);
    int amount = 0;
    char *tax_name;

    if (tax == INCOME_TAX && player_status.net_worth > 0) {
        amount = round_off((double) player_status.net_worth * (game_status.income_tax_rate / 100.0));
        tax_name = "Income Tax";

    } else if (tax == COMMUNITY_DEVELOPMENT_FUND && player_status.total_property_value > 0) {
        amount = round_off((double) player_status.total_property_value * (game_status.community_fund_rate / 100.0));
        tax_name = "Community Development Fund";
    }

    if (amount > 0) {
        printf("%s Amount : LKR %i.\n", tax_name, amount);

        if (players[player].cash >= amount) {
            players[player].cash -= amount;
            printf("%s paid Full %s Amount.\nRemaining Balance : LKR %i.\n\n", players[player].name, tax_name, players[player].cash);

        } else {
            players[player].taxes_due += (amount - players[player].cash);
            players[player].cash = 0;
            printf("%s partially paid %s.\nRemaining Balance : LKR %i.\n\n", players[player].name, tax_name, players[player].cash);
            check_for_bankruptcy(players, board, game_status, player);
        }
    }
}

void settle_outstanding_penalties(Player *player, Cell board[], Game game_status) {
    if (game_status.government_regulation == LUXURY_PROPERTY_TAX) {
        for (int i = 0; i < NO_OF_CELLS; i++) {
            if (board[i].owner == player->id && board[i].type == PROPERTY && board[i].buildings.no_of_hotels > 0) {
                player->taxes_due += round_off(board[i].value.market_price * (25.0 / 100.0));
            }
        }
    }
    if (player->taxes_due > 0 && player->cash >= player->taxes_due) {
        printf("%s settled outstanding taxes of LKR %i.\n\n", player->name, player->taxes_due);
        player->cash -= player->taxes_due;
        player->taxes_due = 0;
    }
}