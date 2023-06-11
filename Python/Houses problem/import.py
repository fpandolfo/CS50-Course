from sys import exit, argv
from cs50 import SQL
import csv

if len(argv) != 2:
    print("Incorret Usage")
    exit(1)

count = 0

db = SQL("sqlite:///students.db")  # give access to the db

with open(f"{argv[1]}", "r") as file:
    for row in file:
        count = count + 1
        if count == 1:
            continue
        temp = row.strip()
        temp = row.replace(" ", ",").split(",")
        temp[-1] = temp[-1].replace("\n", "")
        if len(temp) == 4:
            temp.insert(1, None)
            print(temp)

        db.execute(f"INSERT INTO students (first, middle, last, house, birth)  VALUES (?, ?, ?, ?, ?)",
                  temp[0], temp[1], temp[2], temp[3], int(temp[4]))
