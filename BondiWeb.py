from flask import Flask, render_template
import pygame
import json
import os

app = Flask(__name__)

class BondiApp:
    def __init__(self):
        pygame.init()
        pygame.joystick.init()

        self.joysticks = []
        self.current_joystick_index = 0

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

bondi_app = BondiApp()

if __name__ == "__main__":
    app.run(debug=True)
