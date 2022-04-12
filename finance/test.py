import os
from cs50 import SQL
from helpers import lookup, usd
# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

x = [1, 2, 3, 4, 5]
y = []
for i in range(len(x)):

    y.append(usd(i))


print(type(y[0]))
