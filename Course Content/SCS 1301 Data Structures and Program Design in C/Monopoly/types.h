// Definitions of structures, enumerations, constants, and data types
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SEED          time(NULL)
#define NO_OF_PLAYERS          4
#define NO_OF_CELLS           40
#define TRUE                   1
#define FALSE                  0
#define NONE                  -1
#define INITIAL_INTEREST_RATE  8 // assuming stable economy
#define MAX_DEPRECIATION      30
#define MAX_ROUNDS           500
#define STARTUP_CASH       30000
#define GO_REWARD           2000
#define HIGH_VALUE_PROPERTY 5000
#define BUFFER_SIZE          100
#define INTEGER                0
#define STRING                 1

// Declaring data structures required for players
typedef struct{
    int total_properties;
    int total_property_value;
    int total_railways;
    int total_utilities;
    int unmortgaged_properties;
    int hotels_built;
    int net_worth;
} Status;

typedef struct {
    int isJailed;
    int no_of_rounds;
} Jail;

typedef struct {
    int no_of_loans;
    int loan_duration;
    int total_payable;
    int accumulated_interest;
    float interest_rate;
} Loan;

typedef struct {
    int event;
    int remaining_effect;
    int property;
} National_Events;

typedef struct {
    char *name;
    int id;
    int isBankrupt;
    int has_disaster_occurred;
    int going_to_bid;
    Jail jail_status;
    Loan loan_status;
    National_Events events[20];
    int events_own;
    int play_order;
    int die_roll;
    int cash;
    int taxes_due;
    int place;
} Player;

// Declaring data structures required to build the board.
typedef enum {
    START, PROPERTY, RAILWAY, UTILITY, EVENT, SPECIAL, TAX, BANK, SRI_LANKA_INSURANCE, CEYLINCO
} Type;

typedef enum {
    NO_COLOR = -1, BROWN, LIGHT_BLUE, PINK, ORANGE, RED, YELLOW, GREEN, DARK_BLUE
} Color;

typedef enum {
    NO_OWNER = -1, BANK_OF_CEYLON, AGGRESSIVE_INVESTOR, CONSERVATIVE_BANKER, RISK_TAKER, OPPORTUNISTIC_TRADER
} Ownership;

typedef enum {
    CANNOT_MORTGAGED = -1, MORTGAGED, UNMORTGAGED
} Mortgage_Status;

typedef enum {
    NO_INSURANCE = -1, BASIC, COMPREHENSIVE, BUSINESS_INTERRUPTION
} Policy;

typedef struct {
    int market_price;
    int current_market_price;
    int base_rent; 
    int hotel_construction_cost;
    int house_construction_cost;
    int building_value;
} Values;

typedef struct {
    int no_of_houses;
    int no_of_hotels;
    int condition;
    int rent_reduction_rate;
    int age;
    int has_damaged;
} Building;

typedef struct {
    Mortgage_Status status;
    int value;
} Mortgage;

typedef struct {
    int age;
    int percentage;
} Depreciation;

typedef struct {
    Policy policy;
    int provider;
    int duration;
} Insurance;

typedef struct {
    char *name;
    int id;
    Depreciation depreciation;
    Type type;
    Color group;
    Ownership owner;
    Insurance insurance;
    Player *ownerptr;
    Values value;
    Building buildings; 
    Mortgage mortgage;
} Cell;

// Declaring data structures for the game
typedef enum {
    NORMAL = -1, MARKET_BOOM, MARKET_DECLINE
} Market;

typedef enum {
    INCOME_TAX, COMMUNITY_DEVELOPMENT_FUND
} Taxes;

typedef enum {
    TOURISM_HYPE, FUEL_SHORTAGE, HEAVY_FLOODS, POLITICAL_RALLY, STOCK_MARKET_RISE, ECONOMIC_DOWNTURN, HOUSING_SUBSIDY, INTEREST_RATE_CUT, INTEREST_RATE_INCREASE, TAX_AMNESTY, POWER_FAILURE, FOREIGN_FUNDING, PORT_EXPANSION, FESTIVAL_SEASON, LABOUR_STRIKE, INSURANCE_DISCOUNT, PROPERTY_REVALUATION, CURRENCY_DEPRECIATION, GOVERNMENT_GRANT, NATIONAL_DISASTER
} Event_Nums;

typedef enum {
    NO_EVENT = -1, TOURISM_BOOM, FUEL_CRISIS, HEAVY_MONSOON, ECONOMIC_RECESSION, STOCK_MARKET_BOOM, GOVERNMENT_HOUSING_PROGRAMME, FOREIGN_INVESTMENT, POLITICAL_UNREST
} Economic_Events;

typedef enum {
    NO_REGULATION = -1, INCREASE_PROPERTY_TAX, REDUCE_LOAN_INTEREST, HOUSING_SUBSIDY_REGULATION, LUXURY_PROPERTY_TAX, RAILWAY_MODERNIZATION, ELECTRICITY_TARIFF_REVISION, INSURANCE_REGULATION, ANTI_SPECULATION_ACT
} Government_Regulations;

typedef enum {
    NO_CARD = -1, SOUTHERN_TOURISM_BOOM, PORT_CITY_EXPANSION, IT_INDUSTRY_GROWTH, NORTHERN_DEVELOPMENT_PROGRAMME, TEA_EXPORT_BOOM, AIRPORT_EXPANSION, UNIVERSITY_CITY_GROWTH, BEACH_POLLUTION, FLOOD_DAMAGE, TRANSPORT_STRIKE, ELECTRICITY_TARIFF_INCREASE, WATER_SHORTAGE
} Regional_Card;

typedef struct {
    Market event;
    int property_group;
} Dynamic_Market;

typedef struct {
    char *name;
    char *event;
} Events;

typedef struct {
    char *name;
    char *value;
} Regional;

typedef struct {
    int rounds;
    int current_player;
    Dynamic_Market dynamic_market[2];
    Economic_Events economic_event;
    Government_Regulations government_regulation;
    Regional_Card regional_card;
    int national_event_pointer;
    int inflation_rate;
    float interest_rate;
    float income_tax_rate;
    float community_fund_rate;
} Game;

#endif