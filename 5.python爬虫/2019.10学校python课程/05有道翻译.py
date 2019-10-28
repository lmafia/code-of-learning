#导入库
from urllib import request,parse
#产生随机数
import random
import  json
ua_list = [
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1',
   'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:6.0) Gecko/20100101 Firefox/6.0',
   'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50',
   'Opera/9.80 (Windows NT 6.1; U; zh-cn) Presto/2.9.168 Version/11.50',
   'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Win64; x64; Trident/5.0; .NET CLR 2.0.50727; SLCC2; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; Tablet PC 2.0; .NET4.0E)',
   'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E; SE 2.X MetaSr 1.0)',
   'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E)',
   'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.41 Safari/535.1 QQBrowser/6.9.11079.201',
]
def loadPage(url,word):
    #从列表中随机选取一个useragent
    UserAgent = random.choice(ua_list)
    #构造请求头
    headers ={
        "User-Agent":UserAgent
    }
    #构造form_data
    data ={
        "i": "hello",
        "from": "AUTO",
        "to": "AUTO",
        "smartresult": "dict",
        "client": "fanyideskweb",
        "salt": "15722503603964",
        "sign": "dc51ee2395f1bc847784ebcdab2093ce",
        "ts": "1572250360396",
        "bv": "d39271655f6b7da338c7d58f74b0fad8",
        "doctype": "json",
        "version": "2.1",
        "keyfrom": "fanyi.web",
        "action": "FY_BY_REALTlME"
    }
    data['i'] = word
    #发送请求
    rep = request.Request(url=url,headers=headers)
    #转换data格式
    data = parse.urlencode(data).encode('utf-8')
    #进行相应
    resp = request.urlopen(rep,data=data)
    #读取内容
    html = resp.read().decode('utf-8')
    return html


if __name__ == '__main__':
    while True:
        inp = str(input("(qt退出!)输入英文单词："))
        if inp == "qt":
            break
        url ='http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule'
        html = loadPage(url, inp)
        #转换格式
        res_json = json.loads(html)
        print(res_json["translateResult"][0][0]["tgt"])



