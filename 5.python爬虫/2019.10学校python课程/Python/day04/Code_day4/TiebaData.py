from urllib import request,parse
import ssl,random
from lxml import etree

def loadPage(url):
    context = ssl._create_unverified_context()  # 创建未经验证的上下文

    # ua_list = [
    #     'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E; SE 2.X MetaSr 1.0)',
    #     'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.33 Safari/534.3 SE 2.X MetaSr 1.0',
    #     'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E)',
    #     'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.41 Safari/535.1 QQBrowser/6.9.11079.201',
    #     'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E) QQBrowser/6.9.11079.201',
    #     'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)',
    #     'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.70 Safari/537.36'
    # ]
    # user_agent = random.choice(ua_list)
    # #伪装一个User-agent
    # headers = {'User-Agent':user_agent}
    # print(headers)
    # req = request.Request(url,headers=headers)          #构建请求对象

    req = request.Request(url)          #构建请求对象
    response = request.urlopen(req)     #发送请求,得到响应对象
    html = response.read()              #获取响应对象的内容
    return html

def writePage(html,filename):
    ''' 将爬取回来的内容，写到文本中'''
    with open(filename,'w',encoding='utf-8') as f:
        f.write(html)


def tiebaInfo(html):
    content = etree.HTML(html)     #解析HTML文档
    title_list = content.xpath("//div[@class='t_con cleafix']/div/div/div/a/text()")
    link_list = content.xpath("//div[@class='t_con cleafix']/div/div/div/a/@href")
    ans_list = content.xpath("//div[@class='t_con cleafix']/div/span/text()")
    for title,link,ans in zip(title_list,link_list,ans_list):
        print(title)
        print(link)
        print(ans)

def tiebaSpider(url):
    ''' 输入起始页- 终止页 爬取贴吧的页面范围'''
    tieba = input('请输入要爬取的贴吧！')
    beginPage = int(input('请输入起始页：'))
    endPage = int(input('请输入结束页：'))

    kw = {'kw':tieba}
    param = parse.urlencode(kw)
    url = url + param

    for page in range(beginPage,endPage+1):
        pn = (page-1)*50
        fullurl = url + '&pn=' + str(pn)
        print(fullurl)

        html = loadPage(fullurl)

        tiebaInfo(html)

        dos_html = html.decode('utf-8')         # 对unicode编码进行解码
        # print(html)
        filename = '华农吧第%s页.html'%page
        writePage(dos_html, filename)

#定义一个程序的入口
if __name__ == '__main__':
    url = 'http://tieba.baidu.com/f?'
    tiebaSpider(url)












