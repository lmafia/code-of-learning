from urllib import request,parse
import ssl,random
from lxml import etree

def loadPage(url):
    context = ssl._create_unverified_context()  # 创建未经验证的上下文

    ua_list = [
        'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E; SE 2.X MetaSr 1.0)',
        'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.33 Safari/534.3 SE 2.X MetaSr 1.0',
        'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E)',
        'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.41 Safari/535.1 QQBrowser/6.9.11079.201',
        'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E) QQBrowser/6.9.11079.201',
        'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)',
        'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.70 Safari/537.36'
    ]

    user_agent = random.choice(ua_list)
    #伪装一个User-agent
    headers = {'User-Agent':user_agent}
    print(headers)
    req = request.Request(url,headers=headers)          #构建请求对象
    response = request.urlopen(req, context=context)

    # req = request.Request(url)          #构建请求对象
    # response = request.urlopen(req)     #发送请求,得到响应对象
    html = response.read()              #获取响应对象的内容
    return html

def writePage(html,filename):
    ''' 将爬取回来的内容，写到文本中'''
    with open(filename,'w',encoding='utf-8') as f:
        f.write(html)




def tiebaInfo(html,filename):

    f = open(filename,'w',encoding='utf-8')
    html.decode('utf-8')
    content = etree.HTML(html)     #解析HTML文档
    '''利用etree和Xpath的正则表达式去定位元素的路，就好像解析json一样'''
    title_list = content.xpath("//div[@class='t_con cleafix']/div/div/div/a/text()")
    link_list = content.xpath("//div[@class='t_con cleafix']/div/div/div/a/@href")
    ans_list = content.xpath("//div[@class='t_con cleafix']/div/span/text()")
    comment_list = content.xpath("//div [@class='threadlist_abs threadlist_abs_onlyline ']/text()")
    author_list = content.xpath("//div[@class='threadlist_author pull_right']/span[@class='tb_icon_author ']/@title")
    last_rep_list = content.xpath("//div[@class='threadlist_author pull_right']/span[@class='tb_icon_author_rely j_replyer']/@title")

    ''' 将爬取回来的内容，写到文本中'''
    for title,link,ans,comment,author,last_rep in zip(title_list,link_list,ans_list,comment_list,author_list,last_rep_list):
        print("标题: ",title)
        f.write("标题: "+title+'\n')
        print("链接: ","http://tieba.baidu.com"+link)
        f.write("链接: "+"http://tieba.baidu.com"+link+'\n')
        print(author)   #作者
        f.write(author+'\n')
        print("简介: ",comment)
        f.write("简介: "+comment+'\n')
        print("回复数: ",ans)
        f.write("回复数: "+ ans+'\n')
        print(last_rep)  #最后回复人
        f.write(last_rep+'\n'*3)
        print()
    f.close()


def tiebaSpider(url):
    '''输入起始页- 终止页 爬取贴吧的页面范围'''
    tieba = input('请输入要爬取的贴吧：')
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

        dos_html = html.decode('utf-8')         # 对unicode编码进行解码
        filename = '%s吧第%s页.txt' % (tieba, page)
        tiebaInfo(html, filename)

        # print(html)
        filename = '%s吧第%s页.html' % (tieba, page)
        writePage(dos_html, filename)

#定义一个程序的入口
if __name__ == '__main__':
    url = 'http://tieba.baidu.com/f?'
    tiebaSpider(url)












