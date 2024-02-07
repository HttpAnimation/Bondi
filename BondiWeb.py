from flask import Flask, render_template, request
import subprocess
import json
import os

app = Flask(__name__)

class BondiApp:
    def __init__(self):
        self.categories = self.read_categories()
        self.games = self.read_games()
        self.sidebar_width = 230

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

@app.route("/")
def index():
    bondi_app = BondiApp()
    return render_template("index.html", bondi_app=bondi_app)

@app.route("/runcmd", methods=["POST"])
def run_command():
    command = request.form.get("command")
    if command:
        try:
            subprocess.run(command, shell=True, check=True)
            return "Command executed successfully"
        except subprocess.CalledProcessError as e:
            return f"Error executing command: {e}"
    else:
        return "No command provided"

if __name__ == "__main__":
    app.run(debug=True)
