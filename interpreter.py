import tkinter as tk
from tkinter import filedialog
import os

class Editor:
    def __init__(self, master):
        self.master = master
        self.running=False
        master.title("Bear language IDE")
        
        self.text = tk.Text(master, font=("Courier", 12))
        self.text.pack(expand=True, fill='both')
        
        self.menu = tk.Menu(master)
        
        self.file_menu = tk.Menu(self.menu, tearoff=0)
        self.file_menu.add_command(label="Open", command=self.open_file)
        self.file_menu.add_command(label="Save", command=self.save_file)
        self.menu.add_cascade(label="File", menu=self.file_menu)
        
        master.config(menu=self.menu)
        
        self.bottom_frame = tk.Frame(master)
        self.bottom_frame.pack(side='bottom', fill='x')
        
        self.run_button = tk.Button(self.bottom_frame, text='Run', font=("Arial", 14), command=self.run_program)
        self.run_button.pack(side='left', padx=5, pady=5)
        
        
    def open_file(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            with open(file_path, 'r') as f:
                content = f.read()
            self.text.delete('1.0', 'end')
            self.text.insert('1.0', content)
    
    def save_file(self):
        file_path = filedialog.asksaveasfilename()
        if file_path:
            with open(file_path, 'w') as f:
                content = self.text.get('1.0', 'end')
                f.write(content)
    
    def run_program(self):
        inputtoc=open("inputtoc.txt","w")
        inputtoc.write(self.text.get('1.0', 'end'))
        inputtoc.close()
        os.system("start main.exe")
        
root = tk.Tk()
root.geometry('800x600')
editor = Editor(root)
root.mainloop()