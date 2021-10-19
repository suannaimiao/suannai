#网页采集器


#UA：User-Agent（请求载体的身份标识）
#UA检测： 门户网的服务器会检测对应请求的载体身份标识，如果检测到标识为一款浏览器
#则认为是一个正常的请求，若检测到不是一个浏览器，则认为可能是爬虫，有可能会拒绝请求
#UA伪装： 让爬虫对应的请求载体的身份标识伪装成某一款浏览器



import requests

if __name__ == "__main__":
    #UA伪装： 将对应的Usr—Agent 封装到一个字典中
    headers ={
        'Usr-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.47'
    }
    url = 'https://www.sogou.com/web'
    #处理url携带的参数：封装到字典
    kw = input('enter a world')
    param = {
        'query': kw
    }
    #对指定的url发起的请求对应的url是携带参数的，并且请求过程中处理了参数

    response = requests.get(url=url,params=param,headers=headers)
    page_text = response.text

    filename = './'+kw +'.html'
    with open(filename,'w',encoding='utf-8') as fp:
        fp.write(page_text)
    print("爬取成功")
