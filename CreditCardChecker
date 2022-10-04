# Program to analyze and verify written by Giulio Bracci
# Part of the CS50 course

# Cards specifications:
# AMERICAN EXPRESS: 15 digits, starts with 34 or 37
# MASTER CARD: 16 digits, starts with 51, 52, 53, 54, 55
# VISA: 13 or 16 digits, starts with 4


# HOW TO VERIFY CARD - Luhn's Algorithm
# Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
# Add the sum to the sum of the digits that weren’t multiplied by 2.
# If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid


def main():

    # Check for numeric input
    while True:
        cardnumber = input("Insert credit card number: ")
        if cardnumber.isdecimal() == True:
            break
        else:
            print("Please insert only numbers")

    lenght = len(cardnumber)

    # Apply the Luhn's algorithm with cardnumber passed as a string
    if luhn(cardnumber, lenght) == True:
        # Last check
        cardchecker(cardnumber, lenght)

    else:
        print("INVALID")

    return


def luhn(cardnumber, lenght):

    multiplied_digits = []
    sumdigits = 0

    # Multiply each of the underlined digits by 2 starting from the one before the last digit in reversed order
    for i in range((lenght - 2), -1, -2):

        multiplied_digits.append(int(cardnumber[i]) * 2)

    # Create a string with all the single digits
    digits = "".join(str(x) for x in (multiplied_digits))

    # Add single digits together
    for j in range(len(digits)):

        sumdigits += int(digits[j])

    # Add the rest of the digits that weren't multiplied by 2 from the credit card to the sum
    for k in range((lenght - 1), -1, -2):

        sumdigits += int(cardnumber[k])

    while sumdigits % 10 == 0:
        return True

    return False


def cardchecker(cardnumber, lenght):

    # Get the first two digits to check AMEX and Mastercard and the first digit for VISA
    digits = cardnumber[0] + cardnumber[1]
    digit = int(digits[0])
    digits = int(digits)

    # CASE A: MASTERCARD
    if digits in range(51, (55 + 1)) and lenght == 16:
        print("MASTERCARD")
        return

    # CASE B: AMERICAN EXPRESS
    elif (digits == 34 or digits == 37) and lenght == 15:

        print("AMEX")
        return

    # CASE C: VISA
    elif digit == 4 and (lenght == 13 or lenght == 16):
        print("VISA")
        return

    # CASE D: INVALID
    else:
        print("INVALID")
        return


main()

