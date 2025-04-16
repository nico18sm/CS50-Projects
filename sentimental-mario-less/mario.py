while True:
    try:
        # Eingabe des Benutzers
        userInput = int(input("Height: "))

        # Überprüfung, ob die Eingabe im gültigen Bereich liegt
        if userInput < 1 or userInput > 8:
            print("Bitte gebe eine Gültige Zahl zwischen 1 und 8 ein")
        else:
            # Wenn die Eingabe gültig ist, brechen wir die Schleife ab
            break
    except ValueError:
        # Fehlerbehandlung für den Fall, dass der Benutzer keine Zahl eingibt
        print("Bitte gebe eine Zahl zwischen 1 und 8 ein")

# Ausgabe der "Pyramide" nach der Eingabe
for i in range(userInput):
    spaces = userInput - i - 1  # Berechnung der Leerzeichen
    hashes = i + 1              # Berechnung der Hashtags
    print(" " * spaces + "#" * hashes)
