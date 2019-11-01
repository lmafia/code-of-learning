from urllib import request,parse
import ssl,random
from lxml import etree
import csv
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
    req = request.Request(url, headers=headers)          #构建请求对象
    response = request.urlopen(req, context=context)
    # req = request.Request(url)          #构建请求对象
    # response = request.urlopen(req)     #发送请求,得到响应对象
    html = response.read()              #获取响应对象的内容
    return html

def htmlInfo(html,filename):
    f = open(filename, 'w', newline='',encoding='gbk')
    filetitle = ["职位","公司名", "工作地点", "薪资","发布时间"]
    my_writer = csv.DictWriter(f,fieldnames=filetitle)
    my_writer.writeheader()
    content = etree.HTML(html)     #解析HTML文档
    # '''利用etree和Xpath的正则表达式去定位元素的路，就好像解析json一样'''
    job_list = content.xpath("//div[@class='el']/p/span/a/@title")
    company_list = content.xpath("//div[@class='el']/span/a/@title")
    base_list = content.xpath("//div[@class='el']/span[@class='t3']/text()")
    salary_list = content.xpath("//div[@class='el']/span[@class='t4']/text()")
    date_list = content.xpath("//div[@class='el']/span[@class='t5']/text()")

    for job, company, base, salary, date in zip(job_list, company_list, base_list, salary_list, date_list):
        items = {

        }
        items["职位"] = str(job)
        items["公司名"] = str(company)
        items["工作地点"] = str(base)
        items["薪资"] = str(salary)
        items["发布时间"] = str(date)
        my_writer.writerow(items)
    f.close()
    ''' 将爬取回来的内容，写到文本中'''

#定义一个程序的入口
if __name__ == '__main__':
    page = int(input("请输入需要爬取的页码："))
    url = f'https://search.51job.com/list/030200,000000,0000,00,9,99,python,2,{page}.html?' \
          'lang=c&postchannel=0000&workyear=99&cotype=99&degreefrom=99&jobterm=99' \
          '&companysize=99&ord_field=0&dibiaoid=0&line=&welfare='
    html = loadPage(url)
    dos_html = html.decode('gbk')  # 对unicode编码进行解码
    filename = 'python工程师.csv'
    htmlInfo(dos_html, filename)
    # print(html)













