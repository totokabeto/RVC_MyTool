import os

folder_path = 'C:/Users/rvc_sw_mss1_common/Khanh/Repo_F1KH/internal/X1X/F1x/modules/mcu/test_func/results/4.2.2/701764/Test_Report'

file_list = os.listdir(folder_path)
#print(file_list)
new_haha = []

for item in file_list: 
    if '.html' in item:
        new_haha.append(item)
    else: 
        new_haha.append(item)
        
print(new_haha)

html_list = []

for item in new_haha: 
    if '_' in item[4:10]:
        html_list.append(item[4:9].lower())
    else: 
        html_list.append(item[4:10].lower())
 
print(html_list)

path = 'C:/Users/rvc_sw_mss1_common/Khanh/Repo_F1KM/internal/X1X/F1x/modules/mcu/test_func/rc/F1KM/4.2.2'
for file_name in html_list:
    rc_file_name = f"{file_name}.rc"  
    rc_file_path = os.path.join(path, rc_file_name) 

    rc_content = rf"""
                    /*MCU RC file for {file_name}*/
                    /* Connect to target */ 
                    connect 850eserv2  -df="U:\external\X1X\F1x\common_family\include\ghs\dr7f701764.dvf" -rh850 -e1lpd4=11000KHz -dclock=16000,0,swoff -noiop -fastflashload -id ffffffffffffffffffffffffffffffff -opbyte_disable
                    /* Download NCT test program */
                    load   
                    /* Run to the break point */
                    cb
                    savedebugpane io "U:\internal\X1X\F1x\modules\mcu\test_func\results\4.2.2\701764\Test_Report\Mcu_{file_name}_F1KH_Report.txt"
                    /* Disconnect from the target */
                    disconnect
                    /* Quit Debugger */
                    quit """

    with open(rc_file_path, 'w', encoding='utf-8') as rc_file:
        rc_file.write(rc_content)
    print(f"Đã tạo file: {rc_file_name}")


