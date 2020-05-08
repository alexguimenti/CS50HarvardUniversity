import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from time import gmtime, strftime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = []
    cash = 0
    rows = db.execute("SELECT company, symbol, sum(amount) as amount FROM history WHERE user = :id GROUP BY company, symbol" , id=session["user_id"])
    for row in rows:
        symbol = lookup(row["symbol"])
        row["price"] = format(round(symbol["price"], 2), '.2f')
        row["total"] = format(round(symbol["price"] * row["amount"], 2), '.2f')
        row["amount"] = row["amount"]
        cash = cash + float(row["total"])
        if row["amount"] > 0:
            stocks.append(row)
    print(stocks)
    rows = db.execute("SELECT * FROM users where id = :id", id=session["user_id"])
    wallet = round(rows[0]["cash"], 2)
    cash = round(cash + wallet, 2)
    return render_template("index.html", rows=stocks, cash=cash, wallet=wallet)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    else:
        shares = float(request.form.get("shares"))
        symbol = request.form.get("symbol")
        symbol = lookup(symbol)
        if symbol == None:
            return render_template("invalid.html")
        else:
            if shares < 1:
                return apology("Please enter a valid number.")
            else:
                price = symbol["price"]
                total = shares * price
                company = symbol["name"]
                symbol = symbol["symbol"]
                time = strftime("%Y-%m-%d %H:%M:%S", gmtime())
                # db.execute("INSERT INTO history (date, user, stock, share, amount, total, action) VALUES (:time, :user, :stock, :share, :amount, :total, :action)", time=time, user=session["user_id"], stock=symbol, share=price, amount=shares, total=total, action=buy)
                #print(session["user_id"])
                #print(type(session["user_id"]))
                rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
                # print("Rows:")
                for row in rows:
                    wallet = row["cash"]
                if wallet >= total:
                    db.execute(f"INSERT INTO history (date,user,company,symbol,share,amount,total,action) VALUES (:time,:user,:company,:symbol,:share,:amount,:total,'buy')", time=time, user=session["user_id"], company=company, symbol=symbol,share=price, amount=shares, total=total)
                    wallet = wallet - total
                    db.execute("UPDATE users SET cash = :wallet WHERE id = :id ", id=session["user_id"], wallet=wallet)
                    return apology("Stock bought!")
                else:
                    return apology("Not enough money!")
                


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = []
    rows = db.execute("SELECT * FROM history WHERE user = :user", user=session["user_id"])
    for row in rows:
        history.append(row)
    return render_template("history.html", history=history)


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        symbol = lookup(symbol)
        if symbol == None:
            return render_template("invalid.html")
        else:
            company = symbol["name"]
            price = symbol["price"]
            return render_template("quoted.html", company=company, price=price)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "GET":
        return render_template("register.html")
        
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        if username == "":
            return apology("Empty Username")
        elif password != confirmation or password == '' or confirmation == '':
            return apology("Password Error")
        else:
            password = generate_password_hash(password)
            rows = db.execute("SELECT * FROM users")
            for row in rows:
                if row["username"] == username:
                    return apology("User already exists")
            else:
                db.execute("INSERT INTO users (username, hash) values (:username, :hash)", username=username, hash=password)
                return apology("User Created!")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    rows = db.execute("SELECT company, symbol, sum(amount) as amount FROM history WHERE user = :id GROUP BY company, symbol" , id=session["user_id"])
    stocks = []
    for row in rows:
        # print(row)
        stocks.append(row) 
    if request.method == "GET":
         # print(stocks)
        return render_template("sell.html", stocks=stocks)
    else:
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user = session["user_id"]
        symbolInfo = lookup(symbol)
        # db.execute(f"INSERT INTO history (date,user,company,symbol,share,amount,total,action) VALUES (:time,:user,:company,:symbol,:share,:amount,:total,'buy')", time=time, user=session["user_id"], company=company, symbol=symbol,share=price, amount=shares, total=total)
                    
        rows = db.execute("SELECT company, symbol, sum(amount) as amount FROM history WHERE user = :id and symbol = :symbol GROUP BY company, symbol" , id=session["user_id"], symbol=symbol)
        currentShares = int(rows[0]["amount"])
        if shares > currentShares:
            return apology("Not enough stocks!")   
        else:
            time = strftime("%Y-%m-%d %H:%M:%S", gmtime())
            print("Symbol:")
            symbol = symbolInfo
            print(symbol)
            price = symbol["price"]
            total = shares * price
            company = symbol["name"]
            symbol = symbol["symbol"]
            db.execute(f"INSERT INTO history (date,user,company,symbol,share,amount,total,action) VALUES (:time,:user,:company,:symbol,:share,:amount,:total,'sell')", time=time, user=user, company=company, symbol=symbol,share=price, amount=-shares, total=total)
            rows = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
            wallet = round(rows[0]["cash"], 2)
            wallet = wallet + total
            db.execute("UPDATE users SET cash = :wallet WHERE id = :id", wallet=wallet, id=session["user_id"])
            return apology("Stock selled!")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
