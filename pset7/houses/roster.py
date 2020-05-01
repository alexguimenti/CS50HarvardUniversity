from cs50 import SQL
import csv
import sys
import json


def main():
    # check arguments
    if len(sys.argv) == 2:
        getData()
        return True
    else:
        print("Use: python roster.py 'HOUSE'")
        return False
        
        
def getData():
    # get DB
    db = SQL("sqlite:///students.db")
    
    # make query 
    rows = db.execute(f"select * from students where house = '{sys.argv[1]}' order by last, first;")

    # loop through results
    for row in rows:
        if not row["middle"]:
            print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
        else:
            print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))

    
main()