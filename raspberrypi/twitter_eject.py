#! /usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import tweepy

# トークンキーを入力する
consumer_key = ""
consumer_secret = ""
access_key = ""
access_secret = ""

# Ejectを受け付けるユーザ名
ejectuser = ""

# CD-ROMドライブのパス
cdrom = "/dev/sr0"

auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_key, access_secret)

api = tweepy.API(auth)

class CustomStreamListener(tweepy.StreamListener):
    def on_status(self, status):
        if hasattr(status, 'text'):
            # 特定のユーザからのツイートのみ受け入れる
            if (status.user.screen_name == ejectuser):
                # ツイートの本文から文字列を検索して動作を分ける例
                if (-1 < status.text.find(u'いっかい')):
                    os.system('eject -T ' + cdrom)
                elif (-1 < status.text.find(u'にかい')):
                    os.system('eject -T ' + cdrom)
                    os.system('eject -T ' + cdrom)

    def on_error(self,status_code):
        print >> sys.stderr, 'Encountered error with status code :', status_code
        return True

    def on_timeout(self,status_code):
        print >> sys.stderr, 'Timeout...'
        return True

sapi = tweepy.streaming.Stream(auth, CustomStreamListener())
sapi.userstream()
