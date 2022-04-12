# Financial Dashboard
#### Video Demo:  <URL https://youtu.be/SKi5XicfzI8>
#### Description:
This project aims to enable users to select two stocks for comparison. Users will be able to look at various metrics, such as 1 year price history, returns are 6-month rolling correlation. I had to do alot of research into pandas and chart.js in order to compelete this project, and I'm glad I did, as this is something I'm personally interested in. I also wanted to include a scatterplot for a simple correlation visual, however chart.js wouldn't enable me to loop through variables for values therefore, this is something I will endevor to add in the future. In addition, I plan to take this project full online and remove the dependencies on CS50's library, however I will undertake this when I have more time outside of
work/studying.

helpers.py :
Helpers contains many functions that enable me to generate various things.
`login_requried`
Ensures that the user has logged in before accessing various other pages on the site (borrowed from PS9)
`get_stocks`
Uses the `yfinance` library to import data about the relevant ticker/stock. I ensure to drop any missng values, as these won't have a large on the future calculations and there isn't much value to graphing data prior to the stock existance or weekends where there may be no trade activity. `yfinance.download()` returns a ***Panda DataFrame*** that can be manipulated in a similar way to arrays/lists. The ***DataFrame*** has many different columns, such as `Adj Close` and `Open Price`, therefore I filter the data for only the `Adj Close` column, as we only need to work with just the close data. This filtering causes the ***DataFrame*** to be stored as a ***Series***, therefore I ensure to convert it into a ***Pandas DataFrame*** prior to `return`.
`format_df`
Takes in a DataFrame, and formats the columns. This is done by selected the relevant *column* and applying functions to it. I decided to create this seperate function as I knew that I would be changing DataFrames often, and it would be cleaner to abstract this into a function.
`apology`
I used PS9's apology function, however I changed the photo that is used for the error message.
`to_dict`
Much like the ***format_df*** function, this function was abstracted, as I knew I would often be converting DataFrames back to dictionaries. In order to meet the `label` and `value` requirements of **chart.js** I realised I would need to convert the data into a dictionary in order to acceess the relevant data for dates and prices. I tried to find creative ways to simply input a dataframe, however due chart.js being a JavaScript "library" I realised it would be easier to simply use a dictionary.
`log_returns`
This function simply takes a ticker's dataframe and calcualtes the log daily returns for that ticker by shifting the data by 1 column and dividing the two columns. I ensure to drop any NA values (these would be the first and last value) and return the series.
`rolling_corr`
This function calcualtes a 6 month rolling correlation between two tickers, again dropping na values where relvant.

app.py
`home`
The user will be presented with two dorpdown selections where they can choose two tickers they have inputted. If they sucessfully choose two tickers, they will be presented with two price graphs for the two tickers. I ensure to filter the data/labels via `data['key'][-x:]` where x is the amount of days prior to today I would like to present. Here, I am selecting the ***key*** from the ticker's dictionary and then choosing the latests **x** value from today's date. This is possible as the structure of the dictionary is `key: [values]`.
`stocks`
This function/page, prompts the user to enter two tickers. If they sucessfully do, it will first check that the user is entering new tickers, if they aren't it will let them know. Otherwise, it will update the `tickers` table with their `user_id` and relvant ticker. Finally redirecting them to the home page.
`logReturns`
This function/page first ensures that two tickers were selected on the home page, if they haven't been, it will render the apology page. If the first condition is satisfied, it will get the relvant data, caluclate the log returns are render the graph template for the log returns for both tickers.
`corr`
This function is similar to ***log returns*** except ti will calcaute the rolling correlation for the stocks. It was also going to produce a scatter graph, however as previosuly metioned, chart.js doesn't allow for iterating through the suppled x,y values.
`login`
This functino/page borrows alot from my login solution to PSET 9 and checks that the user and password match, and that the user exsits, showing the apology page if none of these requirements are met. The user's session is then stored and they are sent to the stocks page.
`register`
This function is the same as my solution to PSET 9's register function.
`logout`
A simple function that will clear the session, logging out the user.
Thank you to the CS50x team, it's been amazing learning more about CS and coding, I never thought I would enjoy it as much as I did!
