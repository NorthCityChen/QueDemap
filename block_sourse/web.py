'''
@Author: Mr.Sen
@LastEditTime: 2020-05-27 13:12:02
@Website: https://grimoire.cn
@Mr.Sen All rights reserved
'''
import time
import os
from webdav3.client import Client

options = {
 'webdav_hostname': "https://pan.grimoire.cn/dav",
 'webdav_login':    "mrsen@grimoire.cn",
 'webdav_password': "g6DReYbJFZMtrGXUCROIdQOEc7R1Gt3b",
 'disable_check':True
}
def parse_time(i):
    t=int(round(int(i[0:-1:])*1000))
    st=time.strftime('%Y-%m-%d %H:%M:%S',time.localtime(t/1000))
    # print("Time:"+st)
    return st

def upload(options=options):
    client = Client(options)
    if not client.check("/server"):
        client.mkdir("/server")
    path="/server/"+str(int(time.time()))
    client.mkdir(path)
    client.upload(path,"./dat/")
    print("Data backup succeeded!")
    # print(path,os.path.dirname(os.getcwd())+"/dat/")
    # client.upload("/server2/file.txt","D:\\autotg\\rg\\requirement.txt")

def fetch(options=options):
    client = Client(options)
    if not client.check("/server"):
        client.mkdir("/server")
    lst=client.list("/server")[1::]
    cnt=0
    for i in lst:
        cnt+=1
        print("Index:",cnt," Time:",parse_time(i))
    index=int(input("Please select the file you want to restore:"))%len(lst)
    client.download("/server/"+lst[index-1],"./dat/")
    print(parse_time(lst[index-1]),"has been restored")
    
if __name__=="__main__":
    # praser=argparse.ArgumentParser()
    # praser.add_argument("type")
    # args = praser.parse_args()
    # if args.type=="fetch":
    #     fetch()
    # if args.type=="upload":
    #     upload()
    # upload()
    cmd=input("Backup Or Restore?")
    if (cmd=="backup" or cmd=="Backup"):
        upload()
    elif (cmd=="restore" or cmd=="Restore"):
        fetch()
    else:
        print("cmd not defined! exiting...")