# Limit Order Book Matching Engine

This project implements a simple in-memory limit order book supporting:

- Limit orders
- Market orders
- Price-time priority matching
- Cancel orders
- Trade execution output
- Aggregated order book view

## Order Format

ORDER_ID SIDE PRICE QUANTITY

Example:

O1 BUY 100.50 10

Market order:
PRICE = 0

Cancel:

CANCEL O1

## Compile

g++ main.cpp OrderBook.cpp -o orderbook

## Run

./orderbook < sample_input.txt

## Output

TRADE BUY_ORDER SELL_ORDER PRICE QUANTITY