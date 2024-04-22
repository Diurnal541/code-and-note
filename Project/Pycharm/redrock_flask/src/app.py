from flask import Flask, request, render_template, render_template_string
import os, re, pickle, base64
app = Flask(__name__)


@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html')

@app.route('/bigmouse', methods = ['GET', 'POST'])
def bigmouse():
    if request.method == "GET":
        return render_template('index.html')
    try:
        code = request.form.get('code')
        def waf(s):
            ban = [
                '_',
                '.',
                '\\',
                '\'',
                '"',
                'request',
                '+',
                'class',
                'init',
                'arg',
                'config',
                'app',
                'self',
                '[',
                ']',
                '0',
                '1',
                '2',
                '3',
                '4',
                '5',
                '6',
                '7',
                '8',
                '9'
            ]
            for i in ban:
                if i in s:
                    return "Hacker!!!"
            return s
        res = waf(code)
        return render_template_string('Hello %s' % res)
    except:
        return 'Oh no'

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


