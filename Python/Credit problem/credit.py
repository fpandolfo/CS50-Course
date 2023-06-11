while True:
    try:
        number = int(input("Number: "))
        if number >= 0:
            number = str(number)
            flag = False
            s = 0
            break
    except:
        continue

for i in range(len(number) - 2, -1, -2):
    temp = int(number[i]) * 2
    if temp > 9:
        temp = temp % 10 + 1
    s += temp

for j in range(len(number) - 1, -1, -2):
    temp = int(number[j])
    s += temp

s = str(s)

if s[-1] == '0':
    flag = True

# MasterCard test
if len(number) == 16 and number[0] == '5' and number[1] in ['1', '2', '3', '4', '5'] and flag:
    print('MASTERCARD\n')

# American Express test
elif len(number) == 15 and number[0] == '3' and number[1] in ['4', '7'] and flag:
    print('AMEX\n')

# Vida test
elif (len(number) == 13 or len(number) == 16) and number[0] == '4' and flag:
    print('VISA\n')

else:
    print('INVALID\n')