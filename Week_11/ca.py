# importing required modules 
from zipfile import ZipFile

import zipfile 
  
# specifying the zip file name 
file_name = "encrypted.zip"
file = open("cain.txt", "r")
# Read all the lines into a list
lines = file.readlines()

# Print each line in the list
for line in lines:
    #print(line.strip())
    password_to_try = line.strip()
    with ZipFile(file_name, 'r') as zip: 
        # printing all the contents of the zip file 
        zip.printdir() 
    
        # extracting all the files 
        print('Extracting all the files now...') 
        try:
            zip.extractall(pwd=bytes(password_to_try, 'utf-8'))
            print(password_to_try)
            print('Done!')
            break
        except (RuntimeError, zipfile.BadZipFile):
            print('Wrong password')
# Close the file
file.close()
