#!/usr/bin/env python
#-*- coding:utf-8 -*-

import sys
import os
import re
import urllib2
import socket
import serial
import time
from tweepy.streaming import StreamListener, Stream
from tweepy.auth import OAuthHandler
from tweepy.api import API 
from datetime import timedelta

class Weather(object):
    def get_html(self, url):
        socket.setdefaulttimeout(10.0)
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
            print('----Get HTML - ' + url)

        content = htmldata.read()
        htmldata.close()
        return content

    def kobe_yahoo(self):
        url = "http://rss.weather.yahoo.co.jp/rss/days/6310.xml"
        content = self.get_html(url)
        content_list = re.split(r'<\/?title>', content)
        count = 0 
    
        for line in content_list:
            count += 1
            if count == 4:
                print u"----今日の天気を読み上げます"
                os.system("/home/pi/aquestalkpi/AquesTalkPi \"%s\" | aplay" % line)
        
    def kobe_detail(self):
        url = "http://tenki.jp/forecast/pref-31.html"
        # 正規表現のパターンを定義 - タグ消し
        remove_tag = re.compile(r'<.*?>')
        content = self.get_html(url)
        content_list = content.split('\n')
        print u"----今日の天気を読み上げます"

        flag = False
    
        for line in content_list:
            if flag==True and not "</div>" in line:
                #正規表現でタグ消しした後にstripメソッドでスペースを除去。後ろに,をつけると改行しない
                os.system("/home/pi/aquestalkpi/AquesTalkPi \"%s\" | aplay" % remove_tag.sub("", line).strip())
            if flag==True and "</div>" in line:
                os.system("/home/pi/aquestalkpi/AquesTalkPi \"%s\" | aplay" % remove_tag.sub("", line).strip())
                flag = False
            elif "weatherCountryDescriptionBody" in line:
                os.system("/home/pi/aquestalkpi/AquesTalkPi \"%s\" | aplay" % remove_tag.sub("", line).strip())
                flag = True

class AirConditioner(object):
    def sendsignal(self, signal):
        ser = serial.Serial('/dev/ttyACM0', 9600)
        time.sleep(2)
        ser.write(signal)
        return ser.read()
    def heater(self):
        # Arduinoは文字列の扱いが面倒くさいから文字を送信する。
        return_signal = self.sendsignal('h')
        print return_signal
        print u"----暖房をつけました"
        os.system("/home/pi/aquestalkpi/AquesTalkPi \"暖房をつけました\" | aplay")
    def cooler(self):
        return_signal = self.sendsignal('c')
        print return_signal
        print u"----冷房をつけました"
        os.system("/home/pi/aquestalkpi/AquesTalkPi \"冷房をつけました\" | aplay")
    def dehumidifier(self):
        return_signal = self.sendsignal('d')
        print return_signal
        print u"----除湿をつけました"
        os.system("/home/pi/aquestalkpi/AquesTalkPi \"除湿をつけました\" | aplay")
    def stop(self):
        return_signal = self.sendsignal('s')
        print return_signal
        print u"----エアコンを停止しました"
        os.system("/home/pi/aquestalkpi/AquesTalkPi \"エアコンを停止しました\" | aplay")

class Controller(object):
    def __init__(self, twiline, twitime):
        self.twiline = twiline
        self.twitime = twitime
    def tenki(self):
        weather = Weather()
        if "detail" in self.twiline:
            weather.kobe_detail()
        elif "yahoo" in self.twiline:
            weather.kobe_yahoo()
        else:
            os.system("/home/pi/aquestalkpi/AquesTalkPi \"オプションが足りません\" | aplay")

    def aircon(self):
        aircon = AirConditioner()
        if "heater" in self.twiline:
            aircon.heater()
        elif "cooler" in self.twiline:
            aircon.cooler()
        elif "dehumidifier" in self.twiline:
            aircon.dehumidifier()
        elif "stop" in self.twiline:
            aircon.stop()
        else:
            os.system("/home/pi/aquestalkpi/AquesTalkPi \"操作を指定してください\" | aplay")

class AbstractedlyListener(StreamListener):
    def on_status(self, status):
        status.created_at += timedelta(hours=9)
        print(u"{text}({screen}) - {created}".format(text=status.text, screen=status.author.screen_name, created=status.created_at))

        tweet_line = "{text}".format(text=status.text)
        tweet_time = "{created}".format(created=status.created_at)

        if "exit" in tweet_line:
            print u"プログラムを終了します"
            os.system("aquestalkpi/AquesTalkPi \"プログラムを終了します\" | aplay")
            sys.exit()
        elif "ssh_logout" in tweet_line:
            print u"ログアウトします"
            os.system("exit")
        elif not "System:" in tweet_line:
            con = Controller(tweet_line,tweet_time)
            if "aircon" in tweet_line:
                con.aircon()
            elif "tenki" in tweet_line:
                con.tenki()
            else:
                print "----その命令は定義されていません"
                os.system("aquestalkpi/AquesTalkPi \"その命令は定義されていません\" | aplay")

def get_oauth():
    # 以下4つのキー等は適宜取得して置き換えてください。
    CONSUMER_KEY = '*********************'
    CONSUMER_SECRET = '******************************************'
    ACCESS_KEY = '**************************************************'
    ACCESS_SECRET = '*******************************************'
    auth = OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)
    auth.set_access_token(ACCESS_KEY, ACCESS_SECRET)
    return auth

if __name__ == '__main__':
    print "Starting twitter_timeline.py"
    os.system("aquestalkpi/AquesTalkPi \"Twitterプログラムを起動しました\" | aplay")
    auth = get_oauth()

    # Streamクラスのオブジェクト生成(このクラスはたぶんStreamモジュールの中にある)
    stream = Stream(auth, AbstractedlyListener(), secure=True)
    stream.userstream()
