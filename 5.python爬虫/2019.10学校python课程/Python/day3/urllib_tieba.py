from urllib import request

def loadPage(url):
    req = request.Request(url)          #构建请求对象
    response = request.urlopen(req)     #发送请求,得到响应对象
    html = response.read()              #获取响应对象的内容
    return html

def writePage(html,filename):
    ''' 将爬取回来的内容，写到文本中'''
    with open(filename,'w',encoding='utf-8') as f:
        f.write(html)

def tiebaSpider(url):
    ''' 输入起始页- 终止页 爬取贴吧的页面范围'''
    beginPage = int(input('请输入起始页：'))
    endPage = int(input('请输入结束页：'))
    for page in range(beginPage,endPage+1):
        pn = (page-1)*50
        fullurl = url + str(pn)
        print(fullurl)

        html = loadPage(fullurl)
        html = html.decode('utf-8')         # 对unicode编码进行解码
        print(html)
        filename = '华农吧第%s页.html'%page
        writePage(html, filename)

#定义一个程序的入口
if __name__ == '__main__':
    url = 'http://tieba.baidu.com/f?kw=%E5%8D%8E%E5%8D%97%E5%86%9C%E4%B8%9A%E5%A4%A7%E5%AD%A6&pn='
    tiebaSpider(url)












