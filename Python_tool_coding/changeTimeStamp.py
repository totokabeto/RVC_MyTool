from enum import Enum
import re
import os

class DayOfWeek(Enum):
    Mon = 1
    Tue = 2
    Wed = 3
    Thu = 4
    Fri = 5
    Sat = 6
    Sun = 7
    
needtoreplace = [' 15 ','  15 ','  5 ', '  6 ' , '  7 ', '  8 ', '  9 ', '  10 ' , '  11 ', ]

need = {'Mon',
    'Tue',
    'Wed',
    'Thu',
    'Fri',
    'Sat',
    'Sun'}

folder_path = 'C:/Users/rvc_sw_mss1_common/Downloads/F1KH_Result'
file_list = os.listdir(folder_path)

pattern = r"b[A-Za-z]{3} [A-Za-z]{3} \d{1,2} \d{2}:\d{2}:\d{2} \d{4}\b"

for item in file_list: 
        if '.html' in item:
            with open(f'{folder_path}/{item}', 'r', encoding='iso-8859-1') as temp:
                compare = temp.read()
                for place in needtoreplace:  
                    if place in compare:
                        for date in need: 
                            print(item)
                            content = compare.replace(place, ' 15 ')
                            new_content = content.replace(date, 'Fri')
                            with open(f'{folder_path}/{item}', 'w', encoding='iso-8859-1') as file:
                                file.write(new_content)
                