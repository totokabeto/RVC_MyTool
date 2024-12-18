import pandas as pd
import csv 
import json 

from openpyxl import load_workbook

# Read a specific sheet by name
df_sheet1 = pd.read_excel('MCU_ESTR_Test_Report_F1K.xlsx', sheet_name='Front_Page')  # Replace 'Sheet1' with your sheet name
#print(df_sheet1)

# Read a specific sheet by index (e.g., first sheet is 0, second is 1)
df_sheet2 = pd.read_excel('MCU_ESTR_Test_Report_F1K.xlsx', sheet_name='Test_Result_701587')  # 1 for the second sheet
#print(df_sheet2.columns.tolist())
xulyDict = df_sheet2.loc[7].to_dict()
#print(xulyDict)
values = df_sheet2['Test Case ID'].tolist() 
print(values)