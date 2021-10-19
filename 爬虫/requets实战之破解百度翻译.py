#破解百度翻译

import requests
import json
from requests.api import request

from requests.models import Response

 
if __name__ == "__main__":
    #指定url
    post_url = 'https://fanyi.baidu.com/langdetect'
    #进行UA伪装
    headers ={
        'Usr-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.47'
    }

    #3 post请求参数处理（同get请求一致）

    word = input('enter word :')
    data={
        
        'query': word,
        
    }

    #4 请求发送
    response = requests.post(url=post_url,data=data,headers=headers)

    #5 获取相应数据 json方法返回的是obj（只有确认返回类型是json，才可以用json（）
    dic_obj = response.json()

    #6 持久化存储
    fileName = word + '.json'
    fp = open(fileName,'w',encoding='utf-8')
    json.dump(dic_obj,fp=fp,ensure_ascii=False)
    print('over !!!!')
