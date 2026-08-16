// Board initialization and movement logic
#include "functions.h"

void initialize_game(Cell board[]) {
    Player players[NO_OF_PLAYERS];

    Cell *property_groups[8][3] = {
        {&board[1], &board[3], NULL},
        {&board[6], &board[8], &board[9]},
        {&board[11], &board[13], &board[14]},
        {&board[16], &board[18], &board[19]},
        {&board[21], &board[23], &board[24]},
        {&board[26], &board[27], &board[29]},
        {&board[31], &board[32], &board[34]},
        {&board[37], &board[39], NULL}
    };

    Events national_events[20];
    Regional regional_cards[12];

    Game game_status = (Game) {
        .rounds = 0,
        .current_player = 0,
        .dynamic_market = {
            (Dynamic_Market) {
                .event = NORMAL,
                .property_group = NONE
            },
            (Dynamic_Market) {
                .event = NORMAL,
                .property_group = NONE
            }
        },
        .economic_event = NO_EVENT,
        .government_regulation = NO_REGULATION,
        .regional_card = NONE,
        .national_event_pointer = 0,
        .inflation_rate = 0,
        .interest_rate = (float) INITIAL_INTEREST_RATE,  
        .income_tax_rate = 15.0f,
        .community_fund_rate = 10.0f
    };

    generate_board(board);
    generate_event_cards(national_events, regional_cards);
    initialize_players(players);
    print_game_start();
    decide_player_order(players);
    game_loop(&game_status, players, board, property_groups, national_events, regional_cards);
    free_memory(board, regional_cards, national_events);
}

void generate_board(Cell board[]) {
    char *cell_names[NO_OF_CELLS];
    int cell_types[NO_OF_CELLS];
    int cell_colors[NO_OF_CELLS];
    int cell_owners[NO_OF_CELLS];
    int cell_base_price[NO_OF_CELLS];
    int cell_base_rent[NO_OF_CELLS];
    int cell_price_of_house[NO_OF_CELLS];
    int cell_price_of_hotel[NO_OF_CELLS];
    int cell_mortgage_status[NO_OF_CELLS];
    
    add_items(NULL, cell_names, "Data/cell_names", STRING);
    add_items(cell_types, NULL, "Data/cell_types", INTEGER);
    add_items(cell_colors, NULL, "Data/cell_colors", INTEGER);
    add_items(cell_owners, NULL, "Data/cell_owners", INTEGER);
    add_items(cell_base_price, NULL, "Data/base_price", INTEGER);
    add_items(cell_base_rent, NULL, "Data/base_rent", INTEGER);
    add_items(cell_price_of_house, NULL, "Data/house_cost", INTEGER);
    add_items(cell_price_of_hotel, NULL, "Data/hotel_cost", INTEGER);
    add_items(cell_mortgage_status, NULL, "Data/mortgage_status", INTEGER);

    for (int i = 0; i < NO_OF_CELLS; i++) {
        board[i] = (Cell) {
            .name = cell_names[i],
            .id = i,
            .depreciation = (Depreciation) {0, 0},
            .type = cell_types[i],
            .group = cell_colors[i],
            .owner = cell_owners[i],
            .ownerptr = NULL,
            .insurance = (Insurance) {
                .policy = NO_INSURANCE,
                .provider = NONE,
                .duration = 0
            },
            .value = (Values) {
                .market_price = cell_base_price[i],
                .current_market_price = cell_base_price[i],
                .base_rent = cell_base_rent[i],
                .house_construction_cost = cell_price_of_house[i],
                .hotel_construction_cost = cell_price_of_hotel[i],
                .building_value = 0
            },
            .buildings = (Building) {
                .no_of_houses = 0,
                .no_of_hotels = 0,
                .condition = 100,
                .rent_reduction_rate = 0,
                .age = 0,
                .has_damaged = FALSE
            },
            .mortgage = (Mortgage) {
                .status = cell_mortgage_status[i],
                .value = cell_base_price[i] / 2
            }
        };
    }
}

void initialize_players(Player players[]) {
    char *player_names[] = {"Aggressive Investor", "Conservative Banker", "Risk Taker", "Opportunistic Trader"};
    int plays[] = {AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER};

    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        players[i] = (Player) {
            .name = player_names[i],
            .id = plays[i],
            .isBankrupt = FALSE,
            .has_disaster_occurred = FALSE,
            .going_to_bid = FALSE,
            .jail_status = (Jail) {FALSE, 0},
            .loan_status = (Loan) {0, 0, 0, 0, (float) INITIAL_INTEREST_RATE}, 
            .events_own = 0,
            .play_order = FALSE, 
            .die_roll = NONE,
            .cash = STARTUP_CASH,
            .taxes_due = 0,
            .place = 0
        };

        for (int j = 0; j < 20; j++) {
            players[i].events[j] = (National_Events) {j, NONE, NONE};
        }
    }
}

void generate_event_cards(Events national_events[], Regional regional_cards[]) {
    char *event_names[20];
    char *event_description[20];

    add_items(NULL, event_names, "Data/event_names", STRING);
    add_items(NULL, event_description, "Data/event_description", STRING);

    for (int i = 0; i < 20; i++) {
        national_events[i] = (Events) {
            .name = event_names[i],
            .event = event_description[i]
        };
    }

    char *regional_names[12];
    char *regional_values[12];

    add_items(NULL, regional_names, "Data/regional_names", STRING);
    add_items(NULL, regional_values, "Data/regional_values", STRING);

    for (int i = 0; i < 12; i++) {
        regional_cards[i] = (Regional) {
            .name = regional_names[i],
            .value = regional_values[i]
        };
    }
      
}

void decide_player_order(Player players[]) {
    int assigned_players = 0, count;

    while (assigned_players < NO_OF_PLAYERS) {
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == FALSE) {
                players[i].die_roll = dice_roll();
                printf("%s rolls %i.\n", players[i].name, players[i].die_roll);
            }
        }

        sort_players(players);
        
        for (int x = 0; x < NO_OF_PLAYERS; x++) {
            count = 0;
            if (players[x].play_order == FALSE) {
                for (int y = 0; y < NO_OF_PLAYERS; y++) {
                    if (players[y].play_order == FALSE && players[x].die_roll == players[y].die_roll) {
                        count++;
                    }
                }
            }
            
            if (count > 1) {
                players[x].play_order = FALSE;
            } else {
                players[x].play_order = TRUE;
            }
        }

        printf("\n");

        assigned_players = 0;
        for (int i = 0; i < NO_OF_PLAYERS; i++) {
            if (players[i].play_order == TRUE) {
                assigned_players++;
            }
        } 
    }

    printf("%s will begin the game.\n\n", players[0].name);
    printf("Turn order:\n");
    for (int i = 0; i < NO_OF_PLAYERS; i++) {
        printf("%s\n", players[i].name);
    }
    printf("\n");

}