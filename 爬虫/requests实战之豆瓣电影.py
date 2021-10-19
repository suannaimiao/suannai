# 豆瓣电影戏剧排行
import requests
import json


if __name__ == "__main__":
    url = 'https://movie.douban.com/j/chart/top_list'
    param = {
        'type': '24',
        'interval_id': '100: 90',
        'action': '',
        'start': '1',  # 从库中第几部电影去取
        'limit': '20',  # 一次取出得个数
    }

    # 按住Alt,然后用鼠标左键点击文本，可以让光标在多个位置出现,然后输入一个单引号
    headers = {
        'Usr-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.47'
    }

    response = requests.get(url=url, params=param, headers=headers)

    list_data = response.json()

    fp = open('./douban.json', 'w', encoding='utf-8')
    json.dump(list_data, fp=fp, ensure_ascii=False)

    print('over')
