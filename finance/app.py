import os
import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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

    user_id = session["user_id"]

    # Alle Aktien des Nutzers aggregieren (nach symbol gruppieren)
    stocks = db.execute("""
        SELECT symbol, SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    portfolio = []
    total = 0

    for stock in stocks:
        symbol = stock["symbol"]
        shares = stock["total_shares"]

        # Aktuellen Preis holen
        quote = lookup(symbol)
        if not quote:
            flash(f"Could not find price for {symbol}.")
            continue

        current_price = quote["price"]
        total_value = shares * current_price
        total += total_value

        portfolio.append({
            "symbol": symbol,
            "shares": shares,
            "price": current_price,
            "total": total_value
        })

    # Bargeld des Users holen
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_row[0]["cash"]
    total += cash

    return render_template("index.html", portfolio=portfolio, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensure number of shares was submitted
        shares = request.form.get("shares")
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("must provide a valid number of shares", 400)

        # Convert shares to integer
        shares = int(shares)

        # Lookup the stock quote
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol", 400)

        # Retrieve user's cash balance
        user_id = session["user_id"]
        user = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = user[0]["cash"]

        # Calculate the total cost of the transaction
        total_cost = shares * stock["price"]

        # Ensure the user has enough cash
        if cash < total_cost:
            return apology("not enough cash", 400)

        # Update the user's cash balance
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # Add the stock to the user's portfolio (or update the existing amount)
        rows = db.execute("SELECT * FROM portfolio WHERE user_id = ? AND symbol = ?", user_id, symbol)
        if len(rows) == 0:
            db.execute("INSERT INTO portfolio (user_id, symbol, shares) VALUES (?, ?, ?)", user_id, symbol, shares)
        else:
            db.execute("UPDATE portfolio SET shares = shares + ? WHERE user_id = ? AND symbol = ?", shares, user_id, symbol)

        # Record the transaction in the history table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol, shares, stock["price"], "BUY")

        # Redirect to the portfolio page
        return redirect("/")

    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Holen der Transaktionsdaten des angemeldeten Benutzers
    rows = db.execute("""
        SELECT symbol, shares, price, timestamp, type
        FROM transactions
        WHERE user_id = ?
    """, session["user_id"])

    # Überprüfen, ob Transaktionen existieren
    if len(rows) == 0:
        flash("No transactions found.")

    # Geben der Daten an die HTML-Seite weiter
    return render_template("history.html", history=rows)




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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST
    if request.method == "POST":
        # Ensure username was submitted
        username = request.form.get("username")
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        password = request.form.get("password")
        if not password:
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("must confirm password", 400)

        # Ensure passwords match
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Check if username already exists
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("username already taken", 400)

        # Hash the password
        hash_password = generate_password_hash(password)

        # Insert new user into the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_password)

        # Redirect user to login page after successful registration
        return redirect("/login")

    # User reached route via GET
    else:
        return render_template("register.html")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (when form is submitted)
    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)

        # Lookup the symbol using helper function
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid symbol", 400)

        # Display stock quote
        return render_template("quoted.html", stock=stock)

    # User reached route via GET (show the quote form)
    else:
        return render_template("quote.html")





@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock (only using transactions table)"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)
        if not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("invalid number of shares", 400)

        shares = int(shares)

        # Aktuellen Besitz berechnen
        owned = db.execute("""
            SELECT SUM(shares) AS total
            FROM transactions
            WHERE user_id = ? AND symbol = ?
        """, session["user_id"], symbol)

        if not owned or owned[0]["total"] is None or owned[0]["total"] < shares:
            return apology("not enough shares to sell", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        price = stock["price"]
        total_sale = shares * price

        # Verkauf in transactions eintragen
        db.execute("""
            INSERT INTO transactions (user_id, symbol, shares, price, type)
            VALUES (?, ?, ?, ?, ?)
        """, session["user_id"], symbol, -shares, price, "SELL")

        # Cash aktualisieren
        db.execute("""
            UPDATE users SET cash = cash + ? WHERE id = ?
        """, total_sale, session["user_id"])

        flash(f"Sold {shares} share(s) of {symbol} for ${total_sale:.2f}")
        return redirect("/")

    else:
        # Nur Aktien mit positivem Besitz zeigen
        rows = db.execute("""
            SELECT symbol
            FROM transactions
            WHERE user_id = ?
            GROUP BY symbol
            HAVING SUM(shares) > 0
        """, session["user_id"])

        return render_template("sell.html", stocks=rows)
