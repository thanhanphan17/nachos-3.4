# This file is using for clean .o and .coff file
import os

dir_path = r'/'
file_extenstion = '.o' # You can change it based on your need. 

for root, _, files in os.walk(dir_path):
    for file in files: 
        if file.endswith(file_extenstion): # for each file in the dir and the sub directories
            os.remove(os.path.join(root, file)) # Just delete it


file_extenstion = '.coff' # You can change it based on your need. 

for root, _, files in os.walk(dir_path):
    for file in files: 
        if file.endswith(file_extenstion): # for each file in the dir and the sub directories
            os.remove(os.path.join)


file_extenstion = '.' # You can change it based on your need. 

for root, _, files in os.walk(dir_path):
    for file in files: 
        if file.endswith(file_extenstion): # for each file in the dir and the sub directories
            os.remove(os.path.join)
