# 肯德基位置
import requests
import json

if __name__ == '__main__':
    post_url = 'http://www.kfc.com.cn/kfccda/ashx/GetStoreList.ashx?op=keyword'

    word = input('enter word :')

    param = {
        'cname': '',
        'pid': '',
        'keyword': word,
        'pageIndex': 1,
        'pageSize': 10
    }

    # UA 伪装
    headers = {
        'Usr-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.47'
    }

    # 发送请求
    response = requests.post(url=post_url, data=param, headers=headers)

    # 获取相应数据
    page_text = response.text

    filename = word + '.html'
    # with open(filename, 'w', encoding='utf-8') as fp:
    #    fp.write(page_text)

    fp = open(filename, 'w', encoding='utf-8')
    json.dump(page_text, fp=fp, ensure_ascii=False)
    print("爬取成功")
