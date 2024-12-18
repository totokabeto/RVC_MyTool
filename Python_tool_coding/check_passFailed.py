import os
import shutil 
import re
import csv 
from filter import *


MODULE = 'MCU'

folder_path = 'C:/Users/rvc_sw_mss1_common/Khanh/Repo_F1KM/internal/X1X/F1x/modules/mcu/test_func/results/4.2.2/701764/Test_Report'

#Write a function to check wether that testcase is automated generated or manually done 
base_report_path = 'C:/Users/rvc_sw_mss1_common/Khanh/Repo_F1KM/internal/X1X/F1x/modules/mcu/test_func/results/4.2.2/701764/Test_Report'

directory_path = 'C:/Users/rvc_sw_mss1_common/Khanh/Repo_F1KM/internal/X1X/F1x/modules/mcu/test_func/cfg/F1KM/4.2.2'


file_list = os.listdir(folder_path)
report_list = os.listdir(base_report_path)
config_list = os.listdir(directory_path)

reality_report =[]

for item in file_list:
    if '.jpg' not in item: 
        if '_' in item[4:10]:
            reality_report.append(item[4:9].lower())
        else: 
            reality_report.append(item[4:10].lower())

check = []
auto_list =[]
manual_list =[]

def Auto_manual_check(my_list):
        for item in my_list: 
            if '.html' in item:
                with open(f'{base_report_path}/{item}', 'r', encoding='iso-8859-1') as temp:
                    compare = temp.read()
                    if "GENERATOR" in compare:
                        if '_' in item[4:10]:
                            auto_list.append(item[4:9].lower())
                        else: 
                            auto_list.append(item[4:10].lower())
                    else: 
                        if '_' in item[4:10]:
                            manual_list.append(item[4:9].lower())
                        else: 
                            manual_list.append(item[4:10].lower())
            else: 
                pass
            
            
def delete(need_to_delete):
    for item in need_to_delete:
            try:
            # Xóa toàn bộ thư mục và tất cả nội dung bên trong
                shutil.rmtree(f'{directory_path}/{item}')
                print(f"Thư mục {directory_path}/{item} và tất cả nội dung bên trong đã được xóa.")
            except FileNotFoundError:
                print(f"Thư mục {directory_path}/{item} không tồn tại.")
            except PermissionError:
                print(f"Bạn không có quyền xóa thư mục {directory_path}/{item}.")
            except Exception as e:
                print(f"Có lỗi xảy ra: {e}")
                
                
check_list = []
def append_filelist():
    for item in file_list: 
        if '.txt' in item: 
             check_list.append(item)
             if '_' in item[4:10]:
                check.append(item[4:9].lower())
             else: 
                check.append(item[4:10].lower())
    return check


count_pass = 0
count_failed = 0


def check_PassFailed(count_pass,count_failed): 
    for item in check_list: 
        with open(f'{folder_path}/{item}') as temp:
            compare = temp.read()
            if 'PASSED' in compare:
                count_pass += 1 
            else: 
                print(item)
                count_failed += 1  
                     
Auto_manual_check(report_list)
append_filelist()

def create_csv(file_name, value1, value2, value3):
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
    
        writer.writerow(['Config', 'Test case', 'PASSED/FAILED'])

        writer.writerow([value1, value2, value3])


def countNumberFailedCase(): 
    file_name = 'Test.csv'
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['Config', 'Test case', 'PASSED/FAILED'])
        for item in file_list: 
                if '.html' in item:
                    with open(f'{folder_path}/{item}', 'r', encoding='iso-8859-1') as temp:
                        compare = temp.read()
                        if '<td bgcolor=#FF0000>FAILED</td>' in compare or 'NOT TESTED' in compare or 'MCU_ETC_65535' in compare: 
                            matches = re.findall(fr'{MODULE}_ETC_\d+', compare)
                            writer.writerow([item, str(matches), "FAILED"])
                            print(item)
                        else: 
                            matches_2 = re.findall(fr'{MODULE}_ETC_\d+', compare)
                            writer.writerow([item, str(matches_2), "PASSED"])
                elif '.txt' in item: 
                    with open(f'{folder_path}/{item}') as temp:
                        compare_2 = temp.read()
                        if 'FAILED' in compare_2: 
                            matches_TXT = re.findall(fr'{MODULE}_ETC_\d+', compare_2)
                            writer.writerow([item, str(matches_TXT), "FAILED"])
                        elif 'throughput' in compare_2:
                            print(f"Case throughput la case {item}")
                        else:
                            matches_TXT = re.findall(fr'{MODULE}_ETC_\d+', compare_2)
                            writer.writerow([item, str(matches_TXT), "PASSED"])
                
                else: 
                    pass
        
tong_report = []
# Các phần tử có trong list1 nhưng không có trong list2
tong_report = auto_list + manual_list

diff1 = list(set(config_list) - set(auto_list))

diff2 = list(set(tong_report) - set(reality_report))


if __name__ == "__main__":
    """ 
    print(auto_list)
    print("-------------------------")
    print(check)
    print("-------------------------")
    print(diff2)  # [1, 2]
    """
    #check_PassFailed(count_pass,count_failed)
    #print(manual_list)
    delete(manual_list)
    #print(len(manual_list)),
    #countNumberFailedCase()
    #print(f"Cac test case bi test thieu la : {diff2}")
    #create_String(manual_list)
    #create_String_auto_list(auto_list)

        