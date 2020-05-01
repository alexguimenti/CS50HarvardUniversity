# TODO
from cs50 import SQL
import csv
import sys


# getting arguments
def main():
    if len(sys.argv) == 2:
        importCSV()
        return True
    else:
        return False
        
        
def importCSV():        
    # connecting into SQL
    db = SQL("sqlite:///students.db")
    # creating table
    #db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC);")
    
    # reading CSV
    with open(sys.argv[1], "r") as students:
        
        reader = csv.DictReader(students)
        
        for row in reader:
            namesCount = row["name"].count(" ")
            names = row["name"].split(" ")
            house = row["house"]
            birth = row["birth"]
            if namesCount == 1:
                first = names[0]
                middle = "NULL"
                last = names[1]
                result = db.execute(
                    f"insert into students (first, last, house, birth) values ('{first}', '{last}', '{house}', '{birth}')")
            else:
                first = names[0]
                middle = names[1]
                last = names[2]
                result = db.execute(
                    f"insert into students (first, middle, last, house, birth) values ('{first}', '{middle}', '{last}', '{house}', '{birth}')")
            
            print(result)
            
    return True
        
        
main()