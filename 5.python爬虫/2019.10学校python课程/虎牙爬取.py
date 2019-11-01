from selenium import webdriver
import csv , time


class Huya(object):
    def __init__(self):
        self.driver = webdriver.Chrome("C:\\Users\Administrator\\Desktop\\19年10月Python学习\\chromedriver.exe")
        self.driver.get('https://www.huya.com/l')
        self.csv = open("douyu.csv", 'w', newline='', encoding= 'utf-8')
        self.field = ["title", "user", "type", "hot"]
        self.my_write = csv.DictWriter(self.csv, fieldnames=self.field)
        self.my_write.writeheader()

    def run(self):
        page = 0
        while True:
            li_list = self.driver.find_elements_by_xpath("//div[@class='box-bd']/ul/li")
            for li in li_list:
                item = {
                }
                item["title"] = li.find_element_by_xpath(".//a[@class='title new-clickstat']").get_attribute("title")
                item["user"] = li.find_element_by_xpath(".//i[@class='nick']").get_attribute("title")
                item["type"] = li.find_element_by_xpath(".//span[@class='game-type fr']/a").text
                item["hot"] = li.find_element_by_xpath(".//i[@class='js-num']").text
                self.my_write.writerow(item)

            self.driver.find_element_by_xpath('.//a[@class="laypage_next"]').click()
            page += 1
            if(page==3):
                break
        self.csv.close()


if __name__ == '__main__':
    huya = Huya()
    huya.run()