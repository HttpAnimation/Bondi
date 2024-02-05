import tkinter as tk
from tkinter import ttk
import pygame
from configparser import ConfigParser

def run_command(command):
    print(f"Running command: {command}")

def load_category_games(category):
    game_frame.destroy()
    game_frame.pack_forget()

    game_frame.pack(side=tk.LEFT, padx=20, pady=20)

    config = ConfigParser()
    config.read('Games.ini')

    games = config.items(category)

    row = 0
    col = 0
    for name, command in games:
        button = ttk.Button(game_frame, text=name, command=lambda c=command: run_command(c))
        button.grid(row=row, column=col, padx=10, pady=10)

        col += 1
        if col > 2:
            col = 0
            row += 1

def on_sidebar_click(category):
    load_category_games(category)

pygame.init()
screen = pygame.display.set_mode((1, 1), pygame.FULLSCREEN)
pygame.mouse.set_visible(False)

config_subsections = ConfigParser()
config_subsections.read('subsections.ini')
categories = config_subsections.sections()

root = tk.Tk()
root.title("Bondi")
root.attributes("-alpha", 0.0)
root.wm_attributes("-fullscreen", True)
root.wm_attributes("-topmost", True)

sidebar = ttk.Frame(root, width=150, bg='black')
sidebar.pack(side=tk.LEFT, fill=tk.Y)

for category in categories:
    button = ttk.Button(sidebar, text=category, command=lambda c=category: on_sidebar_click(c))
    button.pack(fill=tk.X, padx=10, pady=10)

game_frame = ttk.Frame(root, width=650, height=600, bg='black')

root.mainloop()
