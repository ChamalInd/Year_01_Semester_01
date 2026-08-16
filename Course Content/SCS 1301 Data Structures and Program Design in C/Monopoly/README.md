# MONOPOLY-LK

A complete, autonomous Monopoly-style simulation set in Sri Lanka, written in C for
**SCS 1301 — Data Structures and Program Design using C** at the University of Colombo
School of Computing (UCSC).

Four computer-controlled players — each following a distinct financial personality — buy,
develop, mortgage, insure, borrow, and trade their way around a 40-square board modelled
on real Sri Lankan locations, from Pettah and Maradana in Colombo to Jaffna, Trincomalee,
and Galle Face. On top of classic Monopoly mechanics, the game layers banking, insurance,
taxation, inflation, property depreciation, and a rotating dynamic property market to
mirror the behaviour of the real Sri Lankan economy.

Once the program starts, **no user interaction is required** — every purchase, bid, loan,
insurance policy, and construction decision is made programmatically by each player's
strategy. The simulation runs until one player remains solvent or **500 rounds** elapse,
and the player with the highest net worth wins.

---

## Quick Start

Requires a C99-compatible compiler (GCC recommended). No external libraries.

```bash
gcc *.c -o monopoly
./monopoly
```

To keep a full log of a run:

```bash
./monopoly > output.txt
```

---

## What Happens in a Turn

Each round, every solvent, non-jailed player takes a turn in dice-determined order:

1. **Resolve outstanding penalties** (e.g. Luxury Property Tax).
2. **Roll two six-sided dice** and move clockwise around the board.
3. **Resolve the landing square** — buy or auction a property, pay rent, draw an event
   card, pay tax, take a loan, buy insurance, go to jail, or collect GO money
   (LKR 2,000 when passing GO).
4. **Build** houses/hotels if the player owns a monopoly, and **manage** finances.
5. **End turn** — the next player goes.

At the end of every round, global systems tick: buildings depreciate, properties age,
insurance policies count down, and periodic events fire on fixed schedules.

## Periodic Event Schedule

| Interval | Trigger |
|----------|---------|
| Every round | Building condition decay, property ageing/depreciation, insurance expiry |
| Every 10 rounds | New inflation rate, possible disaster, property-market review (boom + decline) |
| Every 15 rounds | Economic event, Regional Development Card draw |
| Every 20 rounds | New Government Regulation |

---

## The Board

40 squares, indexed `0`–`39` clockwise (displayed to the user as Square 1–40), starting
from GO.

| # | Square | Type | Group |
|---|--------|------|-------|
| 1 | GO | Start | — |
| 2 | Pettah | Property | Brown |
| 3 | Community Development Fund | Tax | — |
| 4 | Maradana | Property | Brown |
| 5 | Income Tax | Tax | — |
| 6 | Colombo Fort Railway Station | Railway | — |
| 7 | Bambalapitiya | Property | Light Blue |
| 8 | National Event Card | Event | — |
| 9 | Wellawatta | Property | Light Blue |
| 10 | Mount Lavinia | Property | Light Blue |
| 11 | Jail / Just Visiting | Special | — |
| 12 | Nugegoda | Property | Pink |
| 13 | Ceylon Electricity Board | Utility | — |
| 14 | Maharagama | Property | Pink |
| 15 | Kottawa | Property | Pink |
| 16 | Kandy Railway Station | Railway | — |
| 17 | Negombo | Property | Orange |
| 18 | Sri Lanka Insurance | Insurance | — |
| 19 | Katunayake | Property | Orange |
| 20 | Ja-Ela | Property | Orange |
| 21 | Free Parking | Special | — |
| 22 | Kandy City | Property | Red |
| 23 | National Event Card | Event | — |
| 24 | Peradeniya | Property | Red |
| 25 | Katugastota | Property | Red |
| 26 | Galle Railway Station | Railway | — |
| 27 | Galle Fort | Property | Yellow |
| 28 | Unawatuna | Property | Yellow |
| 29 | NWSDB (Water Board) | Utility | — |
| 30 | Hikkaduwa | Property | Yellow |
| 31 | Go To Jail | Special | — |
| 32 | Jaffna Town | Property | Green |
| 33 | Nallur | Property | Green |
| 34 | Ceylinco Insurance | Insurance | — |
| 35 | Trincomalee | Property | Green |
| 36 | Jaffna Railway Station | Railway | — |
| 37 | National Event Card | Event | — |
| 38 | Nuwara Eliya | Property | Dark Blue |
| 39 | Bank of Ceylon | Bank | — |
| 40 | Galle Face | Property | Dark Blue |

### Properties

22 residential properties across 8 colour groups. Owning **every** property in a group
establishes a monopoly, the only way to build. Buildings must be constructed evenly across
a group, max 4 houses per property; a hotel replaces all 4 houses.

| Group | Property | Price | Base Rent | Mortgage | House | Hotel |
|-------|----------|------:|----------:|---------:|------:|------:|
| Brown | Pettah | 1,500 | 100 | 750 | 500 | 2,000 |
| Brown | Maradana | 1,800 | 120 | 900 | 500 | 2,000 |
| Light Blue | Bambalapitiya | 2,500 | 180 | 1,250 | 750 | 3,000 |
| Light Blue | Wellawatta | 2,700 | 200 | 1,350 | 750 | 3,000 |
| Light Blue | Mount Lavinia | 3,000 | 220 | 1,500 | 750 | 3,000 |
| Pink | Nugegoda | 3,500 | 260 | 1,750 | 1,000 | 4,000 |
| Pink | Maharagama | 3,800 | 280 | 1,900 | 1,000 | 4,000 |
| Pink | Kottawa | 4,000 | 300 | 2,000 | 1,000 | 4,000 |
| Orange | Negombo | 4,500 | 350 | 2,250 | 1,250 | 5,000 |
| Orange | Katunayake | 4,700 | 370 | 2,350 | 1,250 | 5,000 |
| Orange | Ja-Ela | 5,000 | 400 | 2,500 | 1,250 | 5,000 |
| Red | Kandy City | 5,500 | 450 | 2,750 | 1,500 | 6,000 |
| Red | Peradeniya | 5,800 | 480 | 2,900 | 1,500 | 6,000 |
| Red | Katugastota | 6,000 | 500 | 3,000 | 1,500 | 6,000 |
| Yellow | Galle Fort | 6,500 | 600 | 3,250 | 2,000 | 8,000 |
| Yellow | Unawatuna | 6,800 | 620 | 3,400 | 2,000 | 8,000 |
| Yellow | Hikkaduwa | 7,000 | 650 | 3,500 | 2,000 | 8,000 |
| Green | Jaffna Town | 8,000 | 750 | 4,000 | 2,500 | 10,000 |
| Green | Nallur | 8,300 | 780 | 4,150 | 2,500 | 10,000 |
| Green | Trincomalee | 8,500 | 800 | 4,250 | 2,500 | 10,000 |
| Dark Blue | Nuwara Eliya | 10,000 | 1,000 | 5,000 | 3,000 | 12,000 |
| Dark Blue | Galle Face | 12,000 | 1,200 | 6,000 | 3,000 | 12,000 |

Mortgage value is always **50% of purchase price**.

**Rent multipliers by development:** no buildings 1× · 1 house 2× · 2 houses 3× ·
3 houses 5× · 4 houses 7× · hotel 10× the base rent (before market/event/condition
modifiers).

### Railways & Utilities

| Type | Price | Mortgage | Income |
|------|------:|---------:|--------|
| Railway (×4) | 1,500 | 750 | 250 / 500 / 1,000 / 2,000 for 1 / 2 / 3 / 4 owned |
| Utility (×2) | 1,500 | 750 | 4× dice roll (one), 10× dice roll (both) |

Railways and utilities can be mortgaged but never built upon or insured.

---

## The Sri Lankan Economy

This is where MONOPOLY-LK departs from the classic game.

### Banking & Loans
Landing on **Bank of Ceylon** lets a player take one financial action: obtain, extend,
refinance, partially repay, or fully repay a loan. A player may hold **one active loan**
at a time, capped at **75% of the mortgage value of all unmortgaged collateral**
(properties, railways, utilities — never buildings). Pledged collateral becomes
*loan-locked*: it cannot be sold, traded, auctioned, or re-mortgaged, but still earns
rent and can be developed. Loans run 20 rounds, compound interest every round, and
default (foreclosure) if not settled in time — collateral reverts to the bank, buildings
are demolished, insurance is cancelled, and the debt is cleared.

### Insurance
Landing on **Sri Lanka Insurance** or **Ceylinco Insurance** lets a player insure any
owned property. Three policies, each valid 20 rounds (renewal reminder at 3 rounds left):

| Policy | Premium | Covers | Compensation |
|--------|---------|--------|--------------|
| Basic | 5% of property value | Fire, flood | 80% of repair cost |
| Comprehensive | 10% of property value | Fire, flood, riot, vandalism, earthquake | 100% of repair cost |
| Business Interruption | 15% of property value | Hotels: repair + 5 rounds of lost rent | Full |

Every 10 rounds a random **disaster** (fire, flood, riot, collapse, electrical failure)
may strike a developed property. Uninsured owners pay full repair costs; damaged buildings
earn no rent until repaired.

### Taxation
- **Income Tax** (base 15% of net worth) is charged when landing on the square; the rate
  moves with the market.
- **Community Development Fund** levies 10% of the market value of a player's properties
  (land only, not buildings) when landed upon.
- Government regulations can add penalties like the **Luxury Property Tax** on hotels,
  tracked as taxes-due and settled at the start of a turn.

### Inflation & the Dynamic Market
Every 10 rounds a new inflation/deflation rate (−3% to +12%) is applied to property
prices, rents, construction costs, premiums, repairs, and new loan rates — but **not** to
existing loans. The same review cycle picks one property group for a **Market Boom**
(prices, rents, and mortgage values up; construction cheaper to develop) and another for a
**Market Decline** (values and rents down, auction prices cheaper), each lasting 10 rounds.
A group can't boom or decline twice in a row.

### Depreciation & Maintenance
- **Buildings** start at 100% condition and decay 2% per round. Rent scales with condition
  (100% ≥90, 90% ≥75, 75% ≥50, 50% ≥25, below 25% the building is closed until
  maintenance). Maintenance at turn start restores 100%: 5% of construction cost per
  house, 8% per hotel. Ignore it for 20+ rounds and the building suffers structural damage
  (15% value loss, 25% rent cut, 50% pricier maintenance).
- **Properties** age each round; past 50 rounds they lose 1% of value every 5 rounds up to
  a 30% cap. Landing on an owned property lets the owner renovate (10% of current market
  value), resetting age and depreciation.

### Cards & Regulations
- **National Event Cards** (20) — drawn on the three Event squares, e.g. Tourism Hype,
  Fuel Shortage, Interest Rate Cuts, Tax Amnesty, National Disaster. Effects last 15
  rounds per player, then expire and reverse.
- **Economic Events** (8) every 15 rounds — Tourism Boom, Fuel Crisis, Heavy Monsoon,
  Economic Recession, Stock Market Boom, Government Housing Programme, Foreign
  Investment, Political Unrest — affecting every player.
- **Regional Development Cards** (12) every 15 rounds — Southern Tourism Boom, Port City
  Expansion, IT Industry Growth, Northern Development Programme, Tea Export Boom, Airport
  Expansion, University City Growth, Beach Pollution, Flood Damage, Transport Strike,
  Electricity Tariff Increase, Water Shortage — targeting specific property groups for 15
  rounds.
- **Government Regulations** (8) every 20 rounds — Property Tax hikes, Loan Interest cuts,
  Housing Subsidies, Luxury Property Tax, Railway Modernization, Electricity Tariff
  Revision, Insurance Regulation, Anti-Speculation Act.

Active market conditions, inflation, and loan interest are printed at the end of every
round.

---

## The Four Players

Each player starts with **LKR 30,000**, no properties, no loans, no insurance.

| Player | Personality |
|--------|-------------|
| **Aggressive Investor** | Buys fast, chases monopolies and premium estates (Galle Face, Nuwara Eliya), builds immediately, borrows to fund construction, never sells unless bankrupt. |
| **Conservative Banker** | Buys only when 50%+ cash remains, avoids debt, prefers railways/utilities, always comprehensively insures developments, renovates early, keeps the biggest emergency reserve. |
| **Risk Taker** | Maxes out loans, refinances constantly, bids until broke, builds hotels early, ignores maintenance until forced, sells weaker assets to fund premium ones. |
| **Opportunistic Trader** | Evaluates expected return before every decision, hunts discounted auctions, adapts to booms/regulations, delays builds during inflation, accelerates during subsidies, keeps a balanced portfolio. |

Turn order is decided by a pre-game dice roll-off (ties rerolled); bankrupt players are
skipped; jailed players must pay LKR 300 bail, roll doubles, or wait out three turns.

---

## Project Layout

| File | Responsibility |
|------|----------------|
| `main.c` | Entry point — seeds the RNG and starts the game. |
| `types.h` | All shared types: `Player`, `Cell`, `Game`, plus enums for colours, ownership, mortgage status, insurance policies, events, regulations — and global constants (`STARTUP_CASH`, `MAX_ROUNDS`, `GO_REWARD`, …). |
| `functions.h` | Prototypes for every function, grouped by implementation file. |
| `board.c` | Builds the 40-square board and player state, loads card decks, and decides turn order. |
| `game.c` | The simulation engine — turn/round loop, periodic triggers, round summaries, market report, winner declaration. |
| `players.c` | Per-turn AI: landing actions, purchase/auction decisions, rent calculation, cash-raising, construction, renovations. |
| `finance.c` | Banking & insurance subsystem — loans (interest, extend, refinance, foreclosure), policies & claims, tax collection, penalty settlement. |
| `events.c` | Time-based systems — depreciation, inflation, dynamic market, disasters, national/economic/regional events, government regulations. |
| `helper.c` | Shared utilities — dice roll, rounding, unmortgaging, jail logic, bankruptcy handling, net-worth/status computation. |

### Data Files (`Data/`)

The board is **data-driven**: instead of hard-coded numbers, the game reads its
configuration at startup, so values can be tweaked without recompiling logic.

| File | Contents |
|------|----------|
| `cell_names` | The 40 square names (one per line) |
| `cell_types` | Square type code per cell (0 start … 9 Ceylinco) |
| `cell_colors` | Property colour group per cell (−1 = not a property) |
| `cell_owners` | Initial ownership (all bank-owned) |
| `base_price` / `base_rent` | Purchase price and base rent per cell |
| `house_cost` / `hotel_cost` | Construction costs per cell |
| `mortgage_status` | Initial mortgage state per cell |
| `event_names` / `event_description` | The 20 National Event Cards |
| `regional_names` / `regional_values` | The 12 Regional Development Cards |

---

## Sample Output

```
Seed : 1786354770
========================================================
                 MONOPOLY-LK Simulation
========================================================

Player 1 : Aggressive Investor
Player 2 : Conservative Banker
Player 3 : Risk Taker
Player 4 : Opportunistic Trader

Each player begins with LKR 30000.

Risk Taker rolled 6.
Risk Taker moves from Square 1 to Square 7.

Risk Taker Landed on Bambalapitiya.

Risk Taker purchased Bambalapitiya for LKR 2500.
Remaining Balance : LKR 27500.
```

```
=================== Round 36 Summary ===================

Player : Aggressive Investor
	 Cash             : LKR   46373
	 Net Worth        : LKR   96220
	 Properties       :          11
	 Hotels           :           0
	 Outstanding Loan : LKR   25941
...
========================================================
                       GAME OVER
========================================================

Winner               : Aggressive Investor
Total Cash           : LKR  46373
Total Property Value : LKR  67098
Outstanding Loans    : LKR  25941
Net Worth            : LKR  96220
```

---

