import tweepy                                                               
from datetime import date

CONSUMER_KEY = '2L4yXxEb3LUBcVhYKFB4w'
CONSUMER_SECRET = 'BC3ogoSGzXdIcSoL9ybhcjQuKNC62IVAvSQbCLQe5M'
ACCESS_KEY = '1957735968-pMwDCuTJuF1vL5HC7tDLYuGRo5ZX0RrHFypV7Xe'
ACCESS_SECRET = 'ewefwX2pGLsPEhNEqs69NxD6u1xwSaIdE08Bx9jSw'

# create OAuth handler                                                      
auth = tweepy.OAuthHandler(CONSUMER_KEY, CONSUMER_SECRET)                   
# set access token to OAuth handler                                         
auth.set_access_token(ACCESS_KEY, ACCESS_SECRET)                            
# create API                                                                
api = tweepy.API(auth_handler=auth)

# post
#api.update_status("test - %s" % date.today())
api.update_status("testlsdjkdljfkdsljfkdlsfkjldksjflsdk")

