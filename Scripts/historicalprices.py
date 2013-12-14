import urllib
import re

#https://www.google.com/finance/historical?cid=694653&startdate=Dec+15%2C+2000&enddate=Dec+14%2C+2013&ei=jcSsUpDrIKjmsgemUg

def get_historical(symbol):
	base_url = 'http://www.google.com/finance/historical?q='
	time_range = '&startdate=Dec+15%2C+2000&enddate=Dec+14%2C+2013' #Esto se formatea para unas fechas concretas
	urllib.urlretrieve (base_url + symbol + "&output=csv", symbol+".csv")
