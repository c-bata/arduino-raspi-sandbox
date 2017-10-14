#coding: UTF-8

import urllib2
import re
import socket

def tenki():
    url = "http://tenki.jp/forecast/pref-31.html"
    socket.setdefaulttimeout(10.0)
    # 正規表現のパターンを定義 - タグ消し
    remove_tag = re.compile(r'<.*?>')
    
    try:
        htmldata = urllib2.urlopen(url)
    except urllib2.HTTPError as err:
        print('HTTPError')
        print(err)
    except urllib2.URLError as err:
        print('URLError')
        print(err)
        if isinstanse(err.reason, socket.timeout):
            print('timeout')
    else:
        print('Get HTML')

    # http://ja.pymotw.com/2/urllib2/
    content = htmldata.read()
    htmldata.close()
    content_list = content.split('\n')

    flag = False

    for line in content_list:
        if flag==True and not "</div>" in line:
            #正規表現でタグ消しした後にstripメソッドでスペースを除去。後ろに,をつけると改行しない
            print remove_tag.sub("", line).strip(),
            #print line
            #filewrite(line)
        if flag==True and "</div>" in line:
            print remove_tag.sub("", line).strip(),
            #print line
            #filewrite(line)
            flag = False
        elif "weatherCountryDescriptionBody" in line:
            print remove_tag.sub("", line).strip(),
            #print line
            #filewrite(line)
            flag = True

# def file_write(text):
#     try:
#         cache = open('weather.txt','w')
#         cache.write(content)
#     except IOError:
#         print "weather.txtが見つかりません。"
#     cache.close()
    

if __name__ == "__main__":
    tenki()
