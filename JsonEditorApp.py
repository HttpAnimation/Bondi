import tkinter as tk
from tkinter import ttk, messagebox, simpledialog
import json
import os

class JsonEditorApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Bondi JSON Editor")

        self.root.configure(bg="#1e1e1e")
        self.tree = ttk.Treeview(self.root, style="Treeview")
        self.tree["columns"] = ("Name", "Command")
        self.tree.column("#0", width=100, minwidth=100, stretch=tk.NO)
        self.tree.column("Name", anchor=tk.W, width=100)
        self.tree.column("Command", anchor=tk.W, width=200)
        self.tree.heading("#0", text="Category")
        self.tree.heading("Name", text="Name")
        self.tree.heading("Command", text="Command")
        self.tree.bind("<ButtonRelease-1>", self.on_tree_select)
        self.tree.bind("<Double-Button-1>", self.edit_selected_double_click)  # Added binding for double-click

        self.tree.pack(fill=tk.BOTH, expand=True)

        self.edit_button = tk.Button(self.root, text="Edit", command=self.edit_selected, bg="#333", fg="white")
        self.edit_button.pack(side=tk.LEFT, padx=5)

        self.delete_button = tk.Button(self.root, text="Delete", command=self.delete_selected, bg="#333", fg="white")
        self.delete_button.pack(side=tk.LEFT, padx=5)

        self.add_button = tk.Button(self.root, text="Add", command=self.add_entry, bg="#333", fg="white")
        self.add_button.pack(side=tk.LEFT, padx=5)

        self.save_button = tk.Button(self.root, text="Save", command=self.save_json, bg="#333", fg="white")
        self.save_button.pack(side=tk.LEFT, padx=5)

        style = ttk.Style(self.root)
        style.configure("Treeview", background="#1e1e1e", fieldbackground="#1e1e1e", foreground="white", bordercolor="#1e1e1e", lightcolor="#1e1e1e", darkcolor="#1e1e1e", troughcolor="#1e1e1e")

        self.load_json()

    def load_json(self):
        try:
            with open("Config/Games.json") as f:
                self.data = json.load(f)
                self.refresh_tree()
        except (FileNotFoundError, json.JSONDecodeError):
            self.data = {}

    def refresh_tree(self):
        self.tree.delete(*self.tree.get_children())
        for category, games in self.data.items():
            category_id = self.tree.insert("", "end", text=category)
            for game in games:
                self.tree.insert(category_id, "end", values=(game["name"], game["command"]))

    def on_tree_select(self, event):
        selected_item = self.tree.selection()
        if selected_item:
            self.tree.selection_set(selected_item)
            self.selected_category = self.tree.item(selected_item, "text")
            self.selected_game = self.tree.item(selected_item, "values")
        else:
            self.selected_category = None
            self.selected_game = None

    def edit_selected_double_click(self, event):
        self.edit_selected()

    def edit_selected(self):
        if not self.selected_category or not self.selected_game:
            return

        new_name = simpledialog.askstring("Edit Name", "Enter new name:", initialvalue=self.selected_game[0])
        new_command = simpledialog.askstring("Edit Command", "Enter new command:", initialvalue=self.selected_game[1])

        if new_name is not None and new_command is not None:
            for game in self.data[self.selected_category]:
                if game["name"] == self.selected_game[0] and game["command"] == self.selected_game[1]:
                    game["name"] = new_name
                    game["command"] = new_command
                    break
            self.refresh_tree()

    def delete_selected(self):
        if not self.selected_category or not self.selected_game:
            return

        confirm = messagebox.askyesno("Delete", f"Do you want to delete {self.selected_game[0]}?")
        if confirm:
            self.data[self.selected_category] = [game for game in self.data[self.selected_category] if
                                                 game["name"] != self.selected_game[0] or game["command"] !=
                                                 self.selected_game[1]]
            if not self.data[self.selected_category]:
                del self.data[self.selected_category]
            self.refresh_tree()

    def add_entry(self):
        new_category = simpledialog.askstring("Add Category", "Enter new category:")
        if new_category is not None:
            if new_category not in self.data:
                self.data[new_category] = []
            new_name = simpledialog.askstring("Add Name", "Enter name:")
            new_command = simpledialog.askstring("Add Command", "Enter command:")
            if new_name is not None and new_command is not None:
                self.data[new_category].append({"name": new_name, "command": new_command})
                self.refresh_tree()

    def save_json(self):
        with open("Config/Games.json", "w") as f:
            json.dump(self.data, f, indent=2)
        messagebox.showinfo("Saved", "Changes saved successfully.")

    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    if not os.path.exists("LICENSE"):
        messagebox.showerror("Error", "LICENSE file not found. Cannot run the application with out this pls redownload or update.")
    else:
        app = JsonEditorApp()
        app.run()
