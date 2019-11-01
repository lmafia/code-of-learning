#导入对应包
from urllib import request
import random
from lxml import etree
import json
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
def loadPage(url):
    #随机的选取ua
    ua = random.choice(ua_list)
    #构造请求头
    headers = {
        "User-Agent":ua
    }
    #对服务器进行请求
    res = request.Request(url=url,headers=headers)
    #进行响应
    result = request.urlopen(url=res)
    #读取结果
    html = result.read().decode('utf-8')
    print(html)
    #先用xpath看看转换
    # html_xpath =etree.HTML(html)
    # href = html_xpath.xpath('//ul[@class="wf_position"]//a//img/@src')
   #不行，因为是用异步发送，观察异步访问的网页是返回json的
    # json_html = json.loads(html)
    # json_list = json_html['list']
    # #搞第一个图片试试水
    # href = json_list[0]['qhimg_url']
    # name = json_list[0]['title']
    # print(href, name)
    # request.urlretrieve(url=href, filename="0.jpg")
    return html

def loadImage(html):
    json_html = json.loads(html)
    json_list = json_html['list']
    #搞第一个图片试试水
    for i in range(0,30):
        href = json_list[i]['qhimg_url']
        name = json_list[i]['id']
        print(href, name)
        request.urlretrieve(url=href, filename='./car_images/%s.jpg' % name)
if __name__ == '__main__':
    #url = 'https://image.so.com/zjl?ch=car&sn=30&listtype=new&temp=1'#异步访问的url
#进行改造

    page_start = int(input("输入起始页："))
    page_end = int(input("输入结束页："))
    for i in range(page_start-1, page_end):
        url = f'https://image.so.com/zjl?ch=car&sn={i*30}&listtype=new&temp=1'
        html = loadPage(url)
        loadImage(html)
