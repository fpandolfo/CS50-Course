# initialize the variables
letters = sentences = 0
# input the text
text = input("Text: ")
# words is equal to len of te text splited
words = len(text.split())
# loop each char in the text
for c in range(len(text)):
    if text[c].isalpha():
        letters = letters + 1
    if text[c] in ['!', '?', '.'] and text[c - 2] not in ['M', 'm'] and text[c - 3] not in ['M', 'm']:
        sentences = sentences + 1
# calculus
L = letters / words * 100
S = sentences / words * 100

index = 0.0588 * L - 0.296 * S - 15.8
# round the grade
grade = round(index)
# output
if grade < 1:
    print("Before Grade 1\n")
elif grade >= 1 and grade <= 16:
    print(f"Grade {grade}\n")
else:
    print("Grade 16+\n")