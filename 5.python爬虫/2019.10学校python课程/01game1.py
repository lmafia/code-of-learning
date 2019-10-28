from urllib import request
from urllib import parse
def loadPage(url):
    req = request.Request(url)
    response = request.urlopen(req)
    html = response.read()
    return html

def writePage(html, filename):
    with open(filename, 'w', encoding = 'utf-8') as f:
        f.write(html)

def tiebaSpider(url, title):
    beginPage = int(input('请输入起始页：'))
    endPage = int(input('请输入结束页：'))
    for page in range(beginPage, endPage+1):
        pn = (page - 1) * 50
        fullurl = url + '&pn=' + str(pn)
        print(fullurl)

        html = loadPage(fullurl)
        html = html.decode('utf-8')
        #print(html)
        filename = title + '吧第%s页.html'%page
        writePage(html, filename)

if __name__ == '__main__':
    tiebaTitle = input('请输入贴吧名：')
    kw = {'kw':tiebaTitle}
    param = parse.urlencode(kw)
    url = 'http://tieba.baidu.com/f?' + param
    tiebaSpider(url, tiebaTitle)
