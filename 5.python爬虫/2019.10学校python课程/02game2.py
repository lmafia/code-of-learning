#
# name:模拟购物车程序
# designedBy:lmafia
# data:2019.10.22
#
money = int(input("请输入您的余额："))
goodList = { 'A': 100, 'B': 200, 'C': 300, 'D': 400, 'E': 500}
nums = 1
total = 0
buyList = []
for key, value in goodList.items():
    print("%d %s --- %s" % (nums, key, value))
    nums += 1
while True:
    goodsName = str(input("(完成购买时请输入：Y)\n请输入你的商品名称："))
    if goodsName == 'Y':
        for i in buyList:
            print(i)
        print("您的余额：%d" % money)
        break
    if money-goodList[goodsName] >= 0:
        money -= goodList[goodsName]
        buyList.append(goodsName)
    else:
        print("余额不足，无法购买")

