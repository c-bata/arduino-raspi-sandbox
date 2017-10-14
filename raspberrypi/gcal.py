#!/usr/bin/env python
# -*- coding: utf-8 -*-
 
import time
import httplib2
from apiclient.discovery import build
from oauth2client.client import OAuth2WebServerFlow
from oauth2client.file import Storage
from oauth2client.tools import run
 
def main():
 
    # get credentials with oauth
    storage = Storage('calendar.dat')
    credentials = storage.get()
    if not credentials or credentials.invalid:
        flow = OAuth2WebServerFlow(
            client_id='YOUR_CLIENT_ID',
            client_secret='YOUR_CLIENT_SECRET',
            scope=['https://www.googleapis.com/auth/calendar'],
            user_agent='Calendar Sample/1.0')
        credentials = run(flow, storage)
 
         
    http = httplib2.Http()
    credentials.authorize(http)
 
    service = build('oauth2', 'v2', http=http)
    userinfo = service.userinfo().get().execute()
 
    # カレンダーのイベント列挙
    sample_exists = False
    service = build('calendar', 'v3', http=http)
    calendars = service.calendarList().list().execute()
    for calendar in calendars['items']:
        events = service.events().list(calendarId=calendar['id']).execute()
        for event in events['items']:
            print event['summary'].encode('utf-8')
            if event['summary'] == 'event_from_api':
                sample_exists = True
 
    # カレンダーにイベントを追加
    if not sample_exists:
        now = time.time()
        print now
        event = {
            'start': {'date':'2012-05-15'},
            'end':   {'date':'2012-05-16'},
            'summary': 'event_from_api'
            }
        target_calendar_id = calendars['items'][0]['id']
        created_event = service.events().insert(calendarId=target_calendar_id, body=event).execute()
        print created_if
         
 
if __name__ == '__main__':
    main()
