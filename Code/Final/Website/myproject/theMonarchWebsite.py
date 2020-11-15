from flask import Flask, request, url_for, redirect, render_template
from flask_bootstrap import Bootstrap
from os import listdir

import matplotlib.pyplot as plt
import io
import base64

from flask import Flask, render_template
import json
import plotly
from plotly import graph_objs as go
import plotly.express as px
import numpy as np

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("home.html")

    img = io.BytesIO()

    y = [1,2,3,4,5]
    x = [0,2,1,3,4]
    plt.plot(x,y)
    plt.savefig(img, format='png')
    img.seek(0)

    plot_url = base64.b64encode(img.getvalue()).decode()

    return '<img src="data:image/png;base64,{}">'.format(plot_url)

@app.route('/references')
def references():
    return render_template('references.html')

@app.route('/coords')
def coords():
    return render_template('coords.txt')

#--------------------------------------------------------------------------
##@app.route('/test', methods=['GET', 'POST'])
##def my_form():
##    inputed_email = request.form.get("email")
##    if request.method == 'POST' and inputed_email:
##        print(listdir) ## print listdir python 2
##        # write to file
##        with open('/var/www/FlaskApp/FlaskApp/test3.txt', 'w') as f:
##            f.write(str(inputed_email))
##
##        return render_template('my-form.html', email=inputed_email)
##    return render_template('my-form.html')
##
###--------------------------------------------------------------------------
##@app.route('/plot')
##def build_plot():
##
##    img = io.BytesIO()
##
##    y = [1,2,3,4,5]
##    x = [0,2,1,3,4]
##    plt.plot(x,y)
##    plt.savefig(img, format='png')
##    img.seek(0)
##
##    plot_url = base64.b64encode(img.getvalue()).decode()
##
##    return '<img src="data:image/png;base64,{}">'.format(plot_url)
##
###--------------------------------------------------------------------------
##@app.route('/plotly', methods=['GET', 'POST'])
##def kek():
##    t = np.linspace(0, 10, 100)
##    fig = go.Figure()
##    fig.add_trace(go.Scatter(
##        x=t, y=np.sin(t),
##        name='sin',
##        mode='markers',
##        marker_color='rgba(152, 0, 0, .8)'
##    ))
##    fig.add_trace(go.Scatter(
##        x=t, y=np.cos(t),
##        name='cos',
##        marker_color='rgba(255, 182, 193, .9)'
##    ))
##    fig.update_traces(mode='markers', marker_line_width=2, marker_size=10)
##    fig.update_layout(title='Styled Scatter',
##                      yaxis_zeroline=False, xaxis_zeroline=False)
##    data = [fig]
##    graphJSON = json.dumps(data, cls=plotly.utils.PlotlyJSONEncoder)
##    return render_template('test1.html', graphJSON=graphJSON)
##
###--------------------------------------------------------------------------
##@app.route('/circle')
##def xy():
##    #gapminder = px.data.gapminder()
##    #fig = px.scatter(gapminder.query("year==2007"), x="gdpPercap", y="lifeExp", size="pop", color="continent",
##    #           hover_name="country", log_x=True, size_max=60)
##    animals=['giraffes', 'orangutans', 'monkeys']
##
##    fig = go.Figure(data=[
##        go.Bar(name='SF Zoo', x=animals, y=[20, 14, 23]),
##        go.Bar(name='LA Zoo', x=animals, y=[12, 18, 29])
##    ])
##    # Change the bar mode
##    fig.update_layout(barmode='group')
##    fig.show()
##    return "showed"
  
if __name__ == "__main__":
    app.debug = True
    app.run(host= '172.20.10.8')
    ##app.run(host= '192.168.15.2')
    bootstrap = Bootstrap(app)
    
