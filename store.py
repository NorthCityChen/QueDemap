'''
@Author: Mr.Sen
@LastEditTime: 2020-05-27 13:24:51
@Website: https://grimoire.cn
@Mr.Sen All rights reserved
'''

import os
from webdav3.client import Client

options = {
 'webdav_hostname': "https://pan.grimoire.cn/dav",
 'webdav_login':    "mrsen@grimoire.cn",
 'webdav_password': "g6DReYbJFZMtrGXUCROIdQOEc7R1Gt3b",
 'disable_check':True
}

def fetch(options=options):
    client = Client(options)
    if not client.check("/blocks"):
        client.mkdir("/blocks")
    lst=client.list("/blocks")[1::]
    cnt=0
    for i in lst:
        cnt+=1
        print("Index:",cnt,i)
    index=int(input("Please select the block you want to install:"))%len(lst)
    client.download("/blocks/"+lst[index-1],"./blocks/"+lst[index-1])
    # print(parse_time(lst[index-1]),"has been restored")
    print(lst[index-1],"has been installed successfully")
    
if __name__=="__main__":
    fetch()