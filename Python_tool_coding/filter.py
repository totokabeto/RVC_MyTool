from pathlib import Path
import subprocess
import time
import os
import pyautogui
device = "701764"


list_file = []


def list_files_in_directory(directory):
    path = Path(directory)
    for file in path.iterdir():
        #print(file.name)
        if '.log'and device in file.name:
            list_file.append(file.name)
            
            
directory = 'U:\internal\X1X\F1x\common_family\make\ghs'
list_files_in_directory('U:\internal\X1X\F1x\common_family\make\ghs')
list_file_loi = []

comman_build =[]
for item in list_file: 
    with open(f'{directory}/{item}','r',encoding='latin-1') as temp:
        compare = temp.read()
        if 'elxr' in compare: 
            if ('.'in item[20:26]): 
                new_item = item[20:25]
                comman_build.append(new_item)
            else: 
                new_item = item[20:26]
                comman_build.append(new_item)
            print(f"file co loi ko build dc o file {item}")
            #list_file_loi.append(item)

#print(comman_build)

chuoi_mau = f'./TstApp.bat cfg06 mcu 4.2.2 {device} manual > Mcu_422_F1KH_{device}_cfg06.log 2>&1'

chuoi_mau_auto = f'./TstApp.bat cfg06 mcu 4.2.2 {device} auto > Mcu_422_F1KH_{device}_cfg06.log 2>&1'

line_path = "cd U:\internal\X1X\F1x\common_family\make\ghs"
execute =[]
def create_String(command_build_list):
    for item in command_build_list: 
        new_chuoi_mau= chuoi_mau.replace('cfg06',f'{item}')
        execute.append(new_chuoi_mau)
    for line in execute:
        with open('manual_List.txt', 'r') as file: 
            content = file.read()
            new_content = content + line + '\n'
            with open('manual_List.txt', 'w') as document: 
                document.write(new_content)

def create_String_auto_list(command_build_list):
    for item in command_build_list: 
        new_chuoi_mau= chuoi_mau_auto.replace('cfg06',f'{item}')
        execute.append(new_chuoi_mau)
    for line in execute:
        with open('auto_List.txt', 'r') as file: 
            content = file.read()
            new_content = content + line + '\n'
            with open('auto_List.txt', 'w') as document: 
                document.write(new_content)

if __name__ == "__main__":
    #create_String(comman_build)
    pass

