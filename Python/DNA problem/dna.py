from sys import argv, exit
import csv

# check the command-line input
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# declare the variables for loops, and lists for iteration
count = temp = 0
strCounter = ['Name']
nameCounter = []

# open and read the two files
with open(f'{argv[1]}', 'r') as file:
    reader = csv.reader(file)
    database = list(reader)

with open(f"{argv[2]}", "r") as file:
    sequences = file.read()

# iterate through the database
for i in range(1, len(database[0])):
    temp = 0
    for c in range(0, len(sequences)):
        if sequences[c: c + len(database[0][i])] == database[0][i]:
            count = count + 1
            if count > temp:
                temp = count
            if sequences[c + len(database[0][i]): c + (len(database[0][i]) * 2)] != database[0][i]:
                count = 0
    strCounter.append(temp)
# checks the names that matchs with the str count and append on the names list
for row in range(1, len(database)):
    for col in range(1, len(database[0])):
        if int(database[row][col]) == strCounter[col]:
            nameCounter.append(database[row][0])

# get the name with most occurrences in the list
name = max(nameCounter, key=nameCounter.count)
# check if the name ocurrences matchs with the total str count
if nameCounter.count(name) == len(database[0]) - 1:
    print(name)
else:
    print("No match")