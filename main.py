from flask import Flask, render_template, request

app = Flask("SuperScrapper")

@app.route("/")
def home():
    return render_template("home.html")

@app.route("/report")
def report():
    word = request.args.get('word')
    if word:
        word = word.lower()
    else:
        return redirect("/")
    return render_template("report.html", searchingBy=word)

app.run()
