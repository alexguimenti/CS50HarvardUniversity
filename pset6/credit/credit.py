from cs50 import get_int


# main function
def main():
    number = get_int("Number: ")
    numberString = str(number)

    # American Express
    if len(numberString) == 15 and numberString[0] == '3' and (numberString[1] == '4' or numberString[1] == '7'):
        
        if check(number) == True:
            print("AMEX")
        else:
            print("INVALID")
    
    # MasterCard
    elif len(numberString) == 16 and numberString[0] == '5' and numberString[1] in ('1', '2', '3', '4', '5'):
        if check(number) == True:
            print("MASTERCARD")
        else:
            print("INVALID")
        
    # VISA
    elif 13 <= len(numberString) <= 16 and numberString[0] == '4':
        if check(number) == True:
            print("VISA")
        else:
            print("INVALID")
    
    # INVALID INPUT
    else:
        print("INVALID")
        

# function to check credit card        
def check(creditCardNumber):
    sum = 0
    product = 0
    start = len(str(creditCardNumber)) - 2
    for i in range(start, -1, -2):
        product = 2 * int(str(creditCardNumber)[i])
        if product > 9:
            product = (product % 10) + 1
        
        sum += product

    for i in range(start + 1, -1, -2):
        sum += int(str(creditCardNumber)[i])
    if sum % 10 == 0:
        return True
    else:
        return False
    
    
main()