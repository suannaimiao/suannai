#requests_test

import requests
if __name__ == "__main__":
    #step 1: 指定url
    url ='https://www.sogou.com/'
    #step 2: 发起请求
    #get方法会返回一个相应对象
    response = requests.get(url=url)
    #step 3 : 获取相应数据   text 返回的是字符串形式的响应数据
    page_text=response.text
    print(page_text)
    #step_4:持久化存储
    with open('./sogou.html','w',encoding='utf-8') as fp:
        fp.write(page_text)
    print('爬取成功')