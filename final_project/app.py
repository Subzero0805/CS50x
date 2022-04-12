"""
This projects takes the concepts that I have learnt in Problem Set 9 (Finance) and
applies them in order to build a website that enables the user to compare various
elements between two stocks.
"""

from flask import Flask, render_template, redirect, flash, request, session
from flask_session import Session
from math import comb
import numpy as np
import pandas as pd
import yfinance as yf
from datetime import datetime
from cs50 import SQL
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import login_required, apology, get_stocks, to_dict, format_df, log_returns, rolling_corr

# Config flask app
app = Flask(__name__)


app.config["TEMPLATES_AUTO_RELOAD"] = True


# Again using PSet 9's settings to store session in file system.
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Prevent the caching of responses
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

db = SQL("sqlite:///data.db")


@app.route("/", methods =["GET", "POST"])
@login_required
def home():


    user_id = session["user_id"]

    # Getting the list of tickers the user has submitted
    tickers = db.execute("SELECT ticker FROM tickers WHERE user_id = ? ", user_id)
    user_tickers = []
    for i in range(len(tickers)):
        user_tickers.append(tickers[i]['ticker'])

    # if the user selected two stocks and submitted it
    if request.method == "POST":

        # exception catching
        if request.form.get("ticker1") not in user_tickers:
            return apology("Please go to 'Add Tickers' first", 400)
        if request.form.get("ticker2") not in user_tickers:
            return apology("Please go to 'Add Tickers' first", 400)

        #Store the two tickers the user has decided to look at
        chosen_stock1 = request.form.get("ticker1")
        session["ticker1"] = chosen_stock1
        chosen_stock2 = request.form.get("ticker2")
        session["ticker2"] = chosen_stock2

        # Get the data, format it, and turn it into a dict for labels and values
        df1 = get_stocks(chosen_stock1)
        formatted_df1 = format_df(df1)
        data1 = to_dict(formatted_df1)
        df2 = get_stocks(chosen_stock2)
        formatted_df2 = format_df(df2)
        data2 = to_dict(formatted_df2)

        # Creating labels and values for charts of each stock
        labels1 = data1['Date'][-253:]
        values1 = data1['Adj Close'][-253:]
        labels2 = data2['Date'][-253:]
        values2 = data2['Adj Close'][-253:]

        return render_template("graph.html", labels1=labels1, values1=values1, labels2=labels2, values2=values2, chosen_stock1=chosen_stock1, chosen_stock2=chosen_stock2)

    return render_template("home.html", user_tickers=user_tickers)


@app.route("/stocks", methods =["GET", "POST"])
@login_required
def stocks():
    """Get the the user to select two stocks for analysis"""


    if request.method == "POST":


        user_id = session["user_id"]

        # Exception handling
        if not request.form.get("stock1"):
            return apology("Please provide a ticker", 400)

        if not request.form.get("stock2"):
            return apology("Please provide a second ticker", 400)

        if get_stocks(request.form.get("stock1")).empty:
            return apology("Please provide a valid ticker", 400)

        if get_stocks(request.form.get("stock2")).empty:
            return apology("Please provide a valid ticker", 400)


        stock1 = request.form.get("stock1")
        stock2 = request.form.get("stock2")
        row1 = db.execute("SELECT * FROM tickers WHERE ticker = ? AND user_id = ?", stock1, user_id)
        row2 = db.execute("SELECT * FROM tickers WHERE ticker = ? AND user_id = ?", stock2, user_id)

        #check if the ticker has already been entered by the user.
        if len(row1) == 0:
            #store the ticker if it hasn't
            db.execute("INSERT INTO tickers (user_id, ticker) VALUES(?,?)", user_id, stock1)
        else:
            #let the user know they need to input a new ticker
            return apology(f"{stock1} already exists, please choose a new ticker",400)

        if len(row2) == 0:
            db.execute("INSERT INTO tickers (user_id, ticker) VALUES(?,?)", user_id, stock2)
        else:
            return apology(f"{stock2} already exists, please choose a new ticker",400)

        return redirect("/")

    return render_template("stocks.html")


@app.route("/logReturns", methods =["GET", "POST"])
@login_required
def logReturns():

    # Ensure tickers have been added and seleted
    try:
        tmp = session["ticker1"]
        tmp2 = session["ticker2"]
    except (KeyError):
        return apology("Please enter/select tickers first", 400)

    #Store the two tickers the user has decided to look at
    chosen_stock1 = session["ticker1"]
    chosen_stock2 = session["ticker2"]

    # Get the data, and let us then extract the data
    df1 = get_stocks(chosen_stock1)
    df1_logReturns = log_returns(df1)
    format1 = format_df(df1_logReturns)
    data1 = to_dict(format1)

    df2 = get_stocks(chosen_stock2)
    df2_logReturns = log_returns(df2)
    format2 = format_df(df2_logReturns)
    data2 = to_dict(format2)

    # Creating labels and values for charts of each stock
    labels1 = data1['Date'][-253:]
    values1 = data1['Adj Close'][-253:]
    labels2 = data2['Date'][-253:]
    values2 = data2['Adj Close'][-253:]

    return render_template("logReturns.html", labels1=labels1, values1=values1, labels2=labels2, values2=values2, chosen_stock1=chosen_stock1, chosen_stock2=chosen_stock2)


@app.route("/correlation", methods =["GET","POST"])
@login_required
def corr():

    try:
        tmp = session["ticker1"]
        tmp2 = session["ticker2"]
    except (KeyError):
        return apology("Please enter/select tickers first", 400)

    #Store the two tickers the user has decided to look at
    chosen_stock1 = session["ticker1"]
    chosen_stock2 = session["ticker2"]

    # Get the data, and let us then extract the data
    df1 = get_stocks(chosen_stock1)
    df1_logReturns = log_returns(df1)
    # Currently chart.js (scatter) doesn't enable an itteration to extract x, y
    #format1 = format_df(df1_logReturns)
    #data1 = to_dict(format1)

    df2 = get_stocks(chosen_stock2)
    df2_logReturns = log_returns(df2)
    #format2 = format_df(df2_logReturns)
    #data2 = to_dict(format2)

    s1_s2_rolling_corr = rolling_corr(df1_logReturns, df2_logReturns)
    formatted = format_df(s1_s2_rolling_corr)
    data3 = to_dict(formatted)

    # Creating labels and values for charts of each stock
    #labels1 = data['Date'][-253:]
    #df_length = len(data1)
    #values1 = data1['Adj Close'][-253:]
    #labels2 = data2['Date'][-253:]
    #values2 = data2['Adj Close'][-253:]
    labels3 = data3['Date']
    values3 = data3['Adj Close']

    return render_template("correlation.html", labels3=labels3, values3=values3, chosen_stock1=chosen_stock1, chosen_stock2=chosen_stock2)



@app.route("/login", methods=["GET","POST"])
def login():
    """User can log into the website"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/stocks")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


#Taken from my solution to PSet9
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


@app.route("/logout")
def logout():
    # Enable the user to logout

    session.clear()
    return redirect("/")