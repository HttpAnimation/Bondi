import tkinter as tk
from tkinter import messagebox
import pygame
import configparser
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

        self.sidebar = tk.Frame(self.root, width=self.sidebar_width, bg="darkgray")
        self.sub_area = tk.Frame(self.root, bg="gray")
        self.game_buttons_frame = tk.Frame(self.sub_area, bg="gray")

        self.create_sidebar_buttons()

        self.sidebar.pack(side=tk.LEFT, fill=tk.Y)
        self.sub_area.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)
        self.game_buttons_frame.pack(fill=tk.BOTH, expand=True)

        self.root.protocol("WM_DELETE_WINDOW", self.on_close)

    def read_categories(self):
        config = configparser.ConfigParser(allow_no_value=True)
        config.read("Config/subsections.ini")

        if not config.sections():
            return [line.strip() for line in config.read("Config/subsections.ini")]

        return config.sections()

    def read_games(self):
        games = []
        with open("Config/Games.ini", "r") as file:
            for line in file:
                parts = [part.strip() for part in line.split('|')]
                if len(parts) >= 3:
                    category, game_name, launch_command = parts[0], parts[1], parts[2]
                    games.append((category, game_name, launch_command))
        return games

    def create_sidebar_buttons(self):
        for category in self.categories:
            button = tk.Button(self.sidebar, text=category, command=lambda cat=category: self.display_game_buttons(cat))
            button.pack(fill=tk.X)

    def display_game_buttons(self, category):
        for widget in self.game_buttons_frame.winfo_children():
            widget.destroy()

        category_games = [(name, command) for cat, name, command in self.games if cat == category]

        for name, command in category_games:
            button = tk.Button(self.game_buttons_frame, text=name, command=lambda cmd=command: self.run_command(cmd))
            button.pack(side=tk.LEFT)

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