from flask import Flask, render_template, request, jsonify
import json
import os
import time
import webview
from multiprocessing import Process

app = Flask(__name__)

class BondiApp:
    def __init__(self):
        self.categories = self.read_categories()
        self.games = self.read_games()

    def read_categories(self):
        try:
            with open("Config/subsections.json") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return []

    def read_games(self):
        try:
            with open("Config/Games.json") as f:
                return json.load(f)
        except (FileNotFoundError, json.JSONDecodeError):
            return {}

    def get_games_for_category(self, category):
        return self.games.get(category, [])

@app.route("/")
def index():
    bondi_app = BondiApp()
    return render_template("index.html", bondi_app=bondi_app)

@app.route("/games")
def get_games():
    category = request.args.get("category")
    bondi_app = BondiApp()
    games = bondi_app.get_games_for_category(category)
    return jsonify(games)

@app.route("/run_command", methods=["POST"])
def run_command():
    data = request.json
    command = data.get("command")
    os.system(command)
    return "Command executed successfully", 200

def start_flask_app():
    app.run(debug=True)

def start_webview():
    time.sleep(1) 
    webview.create_window("Bondi", "http://127.0.0.1:5000")
    webview.start()

if __name__ == "__main__":
    flask_process = Process(target=start_flask_app)
    flask_process.start()

    time.sleep(2)

    webview_process = Process(target=start_webview)
    webview_process.start()

    flask_process.join()  
