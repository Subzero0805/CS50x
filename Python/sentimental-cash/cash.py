# TODO

from cs50 import get_float


def main():

    change = get_change()

    total_change = 0

    quaters = calculate_quaters(change)

    # our function returns the number of each denomination
    total_change += quaters

    # updating our change value to account for the number of quaters used up
    updated_change = ((change*100) - (quaters * 25)) / 100
    print(updated_change)

    dimes = calculate_dimes(updated_change)

    total_change += dimes
    # due to floating point error, if we use these as ints
    # we can remove the rounding error
    updated_change = ((updated_change * 100) - (dimes * 10)) / 100

    nickels = calculate_nickels(updated_change)

    total_change += nickels

    updated_change = ((updated_change * 100) - (nickels * 5)) / 100

    pennies = calculate_pennies(updated_change)

    total_change += pennies

    updated_change = ((updated_change * 100) - (pennies * 1)) / 100

    return print(total_change)


def get_change():
    # ensuring a float is inputed and it's more than 0
    while True:
        try:
            money = get_float("Change owed: ")
            if money > 0:
                return money
        except ValueError:
            print("Please enter a change amount")


def calculate_quaters(change):
    quaters = int(change / 0.25)
    return quaters


def calculate_dimes(change):
    dimes = int(change / 0.10)
    return dimes


def calculate_nickels(change):
    nickels = int(change / 0.05)
    return nickels


def calculate_pennies(change):
    pennies = int(change / 0.01)
    return pennies


main()

