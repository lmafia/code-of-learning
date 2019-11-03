from urllib import parse

kw = {'kw':'华南农业大学'}

param = parse.urlencode(kw)
print(param)

# url = 'https' + param + pn