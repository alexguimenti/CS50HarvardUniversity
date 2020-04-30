import sys
import csv


# define main
def main():
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return False

    # open filer
    sequenceFile = open(sys.argv[2], "r")
    sequence = sequenceFile.read()
    amount = []
    people = []

    input = []
    with open(sys.argv[1], 'r') as csvfile:
        readCSV = csv.reader(csvfile, delimiter=',')
        row1 = next(readCSV)
        for i in range(len(row1) - 1):
            input.append(row1[i + 1])
        for line in readCSV:
            people.append(line)

    for i in range(len(input)):
        amount.append(check(input[i], sequence))
    
    for i in range(len(people)):
        if people[i][1:len(people) + 1] == amount:
            print(people[i][0])
            # returning person
            return True
    # no match
    print("No match.")
    return False


# define check function
def check(lettersSequence, sampleDNA):
    indexes = []
    difference = []
    for i in range(len(sampleDNA)):
        if((i + len(lettersSequence) - 1) < (len(sampleDNA) - 1)):
            if sampleDNA[i:i+len(lettersSequence)] == lettersSequence:
                indexes.append(i)

    # looping
    for j in range(len(indexes)):
        if j + 1 < len(indexes):
            difference.append(indexes[j + 1] - indexes[j])
    counter = 1
    tempCounter = 1
    for i in range(len(difference)):
        if difference[i] == len(lettersSequence):
            tempCounter += 1
        else:
            if (tempCounter > counter):
                counter = tempCounter
            tempCounter = 1
        if (tempCounter > counter):
            counter = tempCounter
    # returning values
    return str(counter)


main()
