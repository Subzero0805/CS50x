import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # setting variables
    user_id = session['user_id']
    tmp = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = float(tmp[0]['cash'])
    user_portfolio = db.execute("SELECT symbol, name, SUM(shares) FROM buys WHERE user_id = ? GROUP BY symbol", user_id)
    symbols = []
    names = []
    prices = []
    num_shares = []
    num_of_stocks = len(user_portfolio)
    totals = []
    stock_totals = 0

    # Getting values out of the dictionary
    for i in range(num_of_stocks):
        symbols.append(user_portfolio[i]['symbol'])
        names.append(user_portfolio[i]['name'])
        stock = lookup(user_portfolio[i]['symbol'])
        price = stock['price']
        prices.append(price)
        num_shares.append(user_portfolio[i]['SUM(shares)'])
        total = int(num_shares[i]) * price
        stock_totals += total
        totals.append(total)

    # This is the total value of the user's portfolio
    sum_total = stock_totals + cash

    return render_template('index.html', sum_total=sum_total, totals=totals, num_of_stocks=num_of_stocks, cash=cash, symbols=symbols, names=names, num_shares=num_shares, prices=prices)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # Exception catching
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)
        elif lookup(request.form.get("symbol")) == None:
            return apology("Enter a valid symbol", 400)
        elif not request.form.get("shares").isdigit():
            return apology("Enter a valid number (whole), 400")

        # Variable setting and getting data from Finance Data base
        users_id = session['user_id']
        get_cash = db.execute("SELECT cash FROM users WHERE id = ?", users_id)
        user_cash = float(get_cash[0]['cash'])
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        num_shares = int(request.form.get("shares"))
        buy_time = datetime.now()

        # Calculating remaining cash
        cash_left = user_cash - (quote['price'] * num_shares)
        if cash_left < 0:
            return apology("You don't have enough cash", 400)

        # Inserting data into Finance Database and buys Database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_left, users_id)
        db.execute("""INSERT INTO buys (user_id, transaction_id, symbol, name, shares, price)
                        VALUES (?, ?, ?, ?, ?, ?)""", users_id, buy_time, quote['symbol'], quote['name'], num_shares, quote['price'])

        # Return to the buy page
        return redirect("/")
     # Didn't reach the page via Post form.
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # setting variables
    user_id = session['user_id']
    tmp_port = db.execute("SELECT symbol, shares, price, transaction_id FROM buys WHERE user_id = ?", user_id)
    num_of_stocks = len(tmp_port)
    symbols = []
    shares = []
    prices = []
    transaction_ids = []

    for i in range(num_of_stocks):
        symbols.append(tmp_port[i]['symbol'])
        shares.append(tmp_port[i]['shares'])
        prices.append(tmp_port[i]['price'])
        transaction_ids.append(tmp_port[i]['transaction_id'])

    return render_template('history.html', num_of_stocks=num_of_stocks, symbols=symbols, shares=shares, prices=prices, transaction_ids=transaction_ids)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # if reached via get, display stock info
    if request.method == "GET":
        return render_template("quote.html")

    # Via Post, ask user for stock symbol
    if request.method == "POST":
        if request.form.get("symbol") == "":
            return apology("Enter a Symbol", 400)

        if lookup(request.form.get("symbol")) == None:
            return apology("Enter a valid Symbol", 400)

        symb = lookup(request.form.get("symbol"))
        symbol_name = symb['name']
        symbol_price = symb['price']
        return render_template("quoted.html", symbol_name=symbol_name, symbol_price=usd(symbol_price))

    return apology("How did you get here?", 403)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Exception catcing
        if request.form.get("username") == "":

            return apology("Enter username", 400)

        if request.form.get("password") != request.form.get("confirmation"):

            return apology("Please ensure passwords match!", 400)

        elif request.form.get("password") == "" or request.form.get("confirmation") == "":

            return apology("Please enter a password", 400)

        row = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(row) == 0:
            db.execute("""INSERT INTO users (username, hash)
                        VALUES (?, ?)""", request.form.get("username"), generate_password_hash(request.form.get("password")))

            user_row = db.execute("SELECT id FROM users WHERE username= ?", request.form.get("username"))
            session["user_id"] = user_row[0]["id"]
        else:
            return apology("username has been taken", 400)

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']

    # giving a list of symbols to choose from
    symbols = db.execute("SELECT symbol FROM buys WHERE user_id = ? GROUP BY symbol", user_id)
    user_symbols = []
    for i in range(len(symbols)):
        user_symbols.append(symbols[i]['symbol'])

    if request.method == "POST":

        # exception catching
        if request.form.get("symbol") not in user_symbols:
            return apology("must provide symbol", 400)
        elif not request.form.get("shares"):
            return apology("must provide number of shares", 400)

        chosen_symbol = request.form.get("symbol")
        shares_to_sell = int(request.form.get("shares"))
        shares_tmp = db.execute("SELECT SUM(shares) FROM buys WHERE symbol=?", chosen_symbol)
        total_shares = shares_tmp[0]['SUM(shares)']
        get_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = float(get_cash[0]['cash'])
        sell_time = datetime.now()

        if total_shares < shares_to_sell:
            return apology("You don't have that many shares to sell", 400)

        quote = lookup(chosen_symbol)

        # update the user's cash to account for sold shares
        user_cash += quote['price'] * shares_to_sell

        # update user database with this new cash amount
        db.execute("UPDATE users SET cash = ? WHERE id = ?", user_cash, user_id)

        # upate buy database
        db.execute("""INSERT INTO buys (user_id, transaction_id, symbol, name, shares, price)
                        VALUES (?, ?, ?, ?, ?, ?)""", user_id, sell_time, quote['symbol'], quote['name'], -shares_to_sell, quote['price'])

        return redirect("/")

    return render_template("sell.html", user_symbols=user_symbols)
