import requests
import json

from requests.api import head

if __name__ == "__main__":
    # 批量获取不同企业的ID值
    url = 'http://scxk.nmpa.gov.cn:81/xk/itownet/portalAction.do?method=getXkzsList'
    # 参数的封装
    data = {
        'on': 'true',
        'page': 1,
        'pageSize': 15,
        'productName': '',
        'conditionType': 1,
        'applyname': '',
        'applysn': '',
    }

    # UA 伪装
    headers = {
        'Usr-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.63 Safari/537.36 Edg/93.0.961.47'
    }

    id_list = []  # 存储企业的ID值
    json_ids = requests.post(url=url, headers=headers, data=data).json()
    for dic in json_ids['list']:
        id_list.append(dic['ID'])

    print(id_list)
    print('name')
