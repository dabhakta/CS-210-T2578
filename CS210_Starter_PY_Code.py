import re
import string

# Open and read the input file
items = dict()
f = open("CS210_Project_Three_Input_File.txt", "r")
for line in f:
    line = line.strip()
    words = line.split(" ")
    for word in words:
        if word in items:
            items[word] = items[word] + 1
        else:
            items[word] = 1
f.close()

# Prints each item along with its quantity
def printItemCount():
    print("\nItems:\n")
    for item in list(items.keys()):
        print(item, end="")
        print(":", items[item])
    print()

# Prints a specific item's quantity
def printCount(userItem):
    userItem = userItem.capitalize()
    for item in list(items.keys()):
        if (userItem == item):
            return items[item]
    return 0

# Creates a file and writes the items and their quantities
def createFile(fileName):
    f = open(fileName, "w")
    for item in list(items.keys()):
        f.write("\n" + item + " " + str(items[item]))
    f.close()
    return 0
