import os
import requests
import urllib.parse
import yfinance as yf
from flask import redirect, render_template, request, session
from functools import wraps
import pandas as pd
import numpy as np

def login_required(f):
    """
    Using Flask Decorator routes, inspertation taken from Finance Problem Set.

    User needs to have inputted stocks in order to proceed.
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function



def get_stocks(ticker):

    try:
        # Download the relevant stock data
        data = yf.download(ticker)

        # Remove any Null value if any.
        data.dropna(inplace = True)

        # Filter the data for only the Adjusted Close
        data_filtered = data['Adj Close']

        # Creating a Pandas DF for ease of use
        df = pd.DataFrame(data_filtered, columns=['Adj Close'])

        return df
    except:
        return None


def format_df(df):

    # Format df so we can use the date column, and limit prices to 4 dp
    df = df.reset_index()
    df['Date'] = df['Date'].astype(str)
    df['Adj Close'] = df['Adj Close'].round(4)
    return df



#Similar to PSet 9's apology function/method
def apology(message, code = 400):
    """Render a message to the user"""
    def escape(s):
        """
        Escape special characters.
        source:
        https://github.com/jacebrowning/memegen#special-characters
        """

        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top = code, bottom=escape(message)), code

def to_dict(df):

    # Convert our dataframe to a dictionary with list so we can use
    # the columns for our label and values required by chart.js
    df_dict = df.to_dict('list')

    return df_dict

def log_returns(df):
    # This takes the unformatted DataFrame as we need
    # the DateTime column from 'Date'
    logReturns = np.log(df / df.shift(1))
    logReturns.dropna(inplace = True)
    return logReturns

def rolling_corr(returns_df1, returns_df2):
    # Calculate a 6month rolling correlation between the two stocks
    # We need to use the unformated returns in order to maniuplate the data
    rolling_corr = returns_df1.rolling(window = 252).corr(returns_df2)
    rolling_corr.dropna(inplace = True)
    return rolling_corr