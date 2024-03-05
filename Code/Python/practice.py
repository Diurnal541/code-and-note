# -*- coding: utf-8 -*-
id = input()
year = id[6:10]
month = id[10:12]
day = id[12:14]
date1 = str(year) + "年" + str(month) + "月" + str(day) + "日"
date2 = date1.replace(" ","")
print(date2)
