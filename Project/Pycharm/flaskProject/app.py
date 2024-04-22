from flask import Flask, request, render_template, render_template_string, flash, redirect, url_for
import os, re, pickle, base64
app = Flask(__name__)

app.secret_key = "dwrg"

@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/bigmouse', methods = ['GET', 'POST'])
def bigmouse():
    try:
        def waf(s):
            ban = [
                '_',
                '.',
                '\'',
                '"',
                'request',
                '[',
                ']',
                '+',
                '0',
                '1',
                '2',
                '3',
                '4',
                '5',
                '6',
                '7',
                '8',
                '9',
                'class',
                'init',
                'arg',
                'config',
                'app',
                'self',
                '\\',
            ]
            for i in ban:
                if i in s:
                    return "Hacker!!!"
            return s
        if request.method == 'GET':
            mouse = request.args.get('mouse')
            mouse = waf(mouse)
            return render_template_string('Hello %s' % mouse)
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            if username == 'admin':
                if password == 'ThreeBigMouse':
                    return redirect('hugh')
                else:
                    flash('"dwrg" is a secret that cannot be told')
                    return redirect('index')
            else:
                flash('wrong username and password')
                return redirect('index')
    except Exception as e:
        return "Error: {}".format(str(e))

@app.route('/hugh', methods = ['GET','PUT'])
def get_flag():
    if request.method == 'GET':
        return render_template('hugh.html')
    try:
        data = request.json
        if data:
            return pickle.loads(base64.b64decode(data["payload"]))
        return "Wrong"
    except Exception as e:
        return "Error: {}".format(str(e))

if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80)


