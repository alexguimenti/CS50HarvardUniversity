from cs50 import get_float

while True:
    amount = round(get_float("Change owed: "), 2)
    if amount > 0:
        break

amount = int(amount * 100)
coins = int(amount / 25)
amount = amount % 25

coins = int(amount / 10) + coins
amount = amount % 10

coins = int(amount / 5) + coins
amount = amount % 5

coins = int(amount / 1 + coins)
amount = amount % 1

print(coins)