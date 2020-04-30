from cs50 import get_int

while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break

for i in reversed(range(h)):
    print(f" " * i, end="")
    print("#" * (h - i))