from flask import Flask, render_template, request
from flask import redirect, url_for, flash
import pandas as pd
import numpy as np
import pickle
from sklearn.linear_model import LinearRegression


app = Flask(__name__)

df = pd.read_csv('test.csv')
clf = pickle.load(open('out.pkl','rb'))
elc = pickle.load(open('elct.pkl','rb'))


@app.route('/')
def index():
   return render_template('index.html')




@app.route('/result',methods = ['POST', 'GET'])
def result():
   if request.method == 'POST':
      result = request.form
      #alert = result['alert']
      wind = result['windspeed']
      rain = result['rainfall']
      #sea = result['sea']
      #river = result['river']
      #dev = result['devlop']
      #dis = result['disaster']
      
      #alert = int(alert)
      wind = int(wind)
      rain = int(rain)
      #sea = int(sea)
      #river = int(river)
      #dev = int(dev)
      #dis = int(dis)
      
      option = request.form['options']
      sea = int(option)
      option1 = request.form['options1']
      alert = int(option1)
      option2 = request.form['options2']
      river = int(option2)
      option3 = request.form['options3']
      dev = int(option3)
      option4 = request.form['options4']
      dis = int(option4)
      
      y = [[alert,wind,rain,sea,river,dev,dis]]
      y = np.array(y)
          
      x = clf.predict(y) 
          
      z = elc.predict(y)
      
      if alert == 0:
          alert = 'Red'
      elif alert==1:
          alert ='Orange'
      else:
          alert = 'Yellow'
          
      if sea == 0:
          sea = 'Yes'
      else:
          sea = 'No'
          
      if river == 0:
          river = 'Yes'
      else:
          river = 'No'
          
      if dev == 0:
          dev = 'Fully'
      elif dev==1:
          dev ='Semi'
      else:
          dev = 'Under'
          
      if dis == 0:
          dis = 'Cyclone'
      else:
          dis = 'Flood'
          
      context1 = {'x':x,'z':z,'alert':alert,'rain':rain,'wind':wind,'sea':sea,'river':river,'dev':dev,'dis':dis}
      #context2 = {'z':z}
      return render_template("result.html",result=result,**context1)

if __name__ == '__main__':
   app.run(debug = True)