import tkinter as tk
from tkinter import messagebox
import pygame
import json
import os

class BondiApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Bondi")
        self.root.geometry("800x600")

        pygame.init()

        self.categories = self.read_categories()
        self.games = self.read_games()

        self.dark_mode = True
        self.sidebar_width = 230

        self.sidebar = tk.Frame(self.root, width=self.sidebar_width, bg="#1e1e1e")
        self.sub_area = tk.Frame(self.root, bg="#1e1e1e")
        self.game_buttons_frame = tk.Frame(self.sub_area, bg="#1e1e1e")

        self.create_sidebar_buttons()

        self.sidebar.pack(side=tk.LEFT, fill=tk.Y)
        self.sub_area.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
        self.game_buttons_frame.pack(fill=tk.BOTH, expand=True)

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

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

    def create_sidebar_buttons(self):
        for category in self.categories:
            button = tk.Button(self.sidebar, text=category, command=lambda cat=category: self.display_game_buttons(cat), bg="#333", fg="white")
            button.pack(fill=tk.X)

    def display_game_buttons(self, category):
        for widget in self.game_buttons_frame.winfo_children():
            widget.destroy()

        category_games = self.games.get(category, [])

        for game in category_games:
            name = game["name"]
            command = game["command"]
            button = tk.Button(self.game_buttons_frame, text=name, command=lambda cmd=command: self.run_command(cmd), bg="#333", fg="white")
            button.pack(side=tk.TOP, anchor='w')

    def run_command(self, command):
        os.system(command)

    def on_close(self):
        if messagebox.askokcancel("Quit", "Are you sure you want to leave mate?"):
            self.root.destroy()

    def toggle_dark_mode(self):
        self.dark_mode = not self.dark_mode

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = BondiApp()
    app.run()
