from cs50 import get_string

# Eingabe
text = get_string("Text: ")

# Initialisieren
letters = 0
words = 1  # fängt bei 1 an, da letztes Wort kein Leerzeichen hat
sentences = 0

# Durch jeden Buchstaben im Text gehen
for char in text:
    if char.isalpha():
        letters += 1
    elif char == " ":
        words += 1
    elif char in [".", "!", "?"]:
        sentences += 1

# Berechnungen
L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Ausgabe
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
