# TODO

def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n >= 1 and n <= 8:
                return n
        except ValueError:
            print("That's not an integer!")
            

height = get_height()
i = 0
j = height - 1
for i in range(height):
    x = "#" * (i + 1)
    y = " " * j
    print(f"{y}{x}")
    j -= 1

