from urllib import request
import random
from lxml import etree
ua_list = [
    'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E; SE 2.X MetaSr 1.0)',
    'Mozilla/5.0 (Windows; U; Windows NT 6.1; en-US) AppleWebKit/534.3 (KHTML, like Gecko) Chrome/6.0.472.33 Safari/534.3 SE 2.X MetaSr 1.0',
    'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E)',
    'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/13.0.782.41 Safari/535.1 QQBrowser/6.9.11079.201',
    'Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.1; WOW64; Trident/5.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; InfoPath.3; .NET4.0C; .NET4.0E) QQBrowser/6.9.11079.201',
    'Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)',
    'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/78.0.3904.70 Safari/537.36'
]


def load_page(url):
    user_agent = random.choice(ua_list)
    headers = { "User-Agent":user_agent}
    req = request.Request(url=url, headers=headers)
    response = request.urlopen(req)
    html = response.read().decode('utf-8')
    return html

def writePage(html,filename):
    with open(filename,'w',encoding='utf-8') as f:
        f.write(html)

def print_content_text(html):
    f = open("发烧友test.txt", 'w', encoding='utf-8')

    xpath_html = etree.HTML(html)
    text_list = xpath_html.xpath("//p[@style='text-indent: 2em;']/text()")
    # res_list = xpath_html.xpath("//p[@style='text-align: center; text-indent: 2em;']/text()")
    for text in text_list:
        print(text)
        f.write(text.strip(text))

       # print(res)

def content_info(html):
    xpath_html = etree.HTML(html)
    title_list = xpath_html.xpath("//div[@class='article-list']/h3/a/@title")
    href_list = xpath_html.xpath("//div[@class='article-list']/h3/a/@href")
    summary_list = xpath_html.xpath("//p[@class='a-summary']/text()")
    # load_page(str(href_list[0]))
    print_content_text(load_page(str(href_list[2])))
    # for title, href, summary in zip(title_list, href_list, summary_list):
    #     print(title)
    #     print(href)
    #     print((load_page(str(href))))
    #     print(summary)
    #     print()


if __name__ == '__main__':
    url = "http://www.elecfans.com/news/hangye/"
    content_info(load_page(url))