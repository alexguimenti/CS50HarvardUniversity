from cs50 import get_string

# ge text
text = get_string("Text: ")

# setting variables
words = 1
letters = 0
sentences = 0
others = 0
    
# loop chars
for i in range(len(text)):
    if(text[i] == ' '):
        words += 1
    elif(text[i] in ('.', '!', '?')):
        sentences += 1
    elif(text[i] in (',', '\'', ':', '"')):
        others += 1
    else:
        letters += 1
        
# getting values for the formula
L = (letters / words) * 100
S = (sentences / words) * 100

# getting index
index = int((0.0588 * L - 0.296 * S - 15.8) + 0.5)

# checking index
if index <= 1:
    print("Before Grade 1")
    
elif index >= 16:
    print("Grade 16+")
    
else:
    print(f"Grade {index}")