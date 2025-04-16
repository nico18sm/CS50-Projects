from cs50 import get_float

while True:
    dollars = get_float("Change: ")
    if dollars >= 0:
        break

#In Cents umrechnen
cents = round(dollars * 100)

#Setzen des Anfangszustandes
coins = 0

#Rechnen der Quarters
coins += cents // 25
cents %= 25

#Rechnen der Dimes
coins += cents // 10
cents %= 10

#Rechnen der Nickels
coins += cents // 5
cents %= 5

#Rechnen der Pennys
coins += cents // 1
cents %= 1

#Print des Ergebnisses
print(f"{coins}")
