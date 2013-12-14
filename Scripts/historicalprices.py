import urllib
import re

def get_historical(symbol):
    base_url = 'http://www.google.com/finance/historical?q='
    urllib.urlretrieve (base_url + symbol + "&output=csv", symbol+".csv")
