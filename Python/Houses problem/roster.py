from sys import exit, argv
from cs50 import SQL
import csv

# If the incorrect number of command-line arguments are provided, NOTHING ABOUT THE FORMAT, LOWERCASE ETC. <<<<<
if len(argv) != 2:
    print("Incorrect")
    exit(1)

db = SQL("sqlite:///students.db")
nomes = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[1])

for c in nomes:
    first = c['first']
    middle = c['middle']
    last = c['last']
    birth = c['birth']

    if middle == None:
        print(f"{first} {last}, born {birth}")

    else:
        print(f"{first} {middle} {last}, born {birth}")