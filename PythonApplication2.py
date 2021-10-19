import math
import tkinter as tk
from tkinter.filedialog import asksaveasfile
import matplotlib.pyplot as plt
import numpy as np

file = open("test.txt", 'w')
file.close()


class SampleApp(tk.Tk):

    def __init__(self):
        tk.Tk.__init__(self)

        menubar = tk.Menu(self)
        self.config(menu=menubar)

        self.popup_menu = tk.Menu(self, tearoff=0)
        self.popup_menu.add_command(label="Save",
                                    command=self.file_save)
        filemenu = tk.Menu(menubar, tearoff=0)
        filemenu.add_command(label="Save", command=self.file_save)
        filemenu.add_command(label="Exit", command=self.quit)
        menubar.add_cascade(label="File", menu=filemenu)
        filemenu.add_command(label="Save", command=self.file_save)

        self.label1 = tk.Label(self, text="Введите a:").grid(row=0)
        self.entry1 = tk.Entry(self)
        self.entry1.insert(0, 2)
        self.entry1.grid(row=0, column=1)

        self.label2 = tk.Label(self, text="Введите шаг:").grid(row=1)
        self.entry2 = tk.Entry(self)
        self.entry2.insert(0, 2)
        self.entry2.grid(row=1, column=1)

        self.label3 = tk.Label(self, text="Введите кол-во:").grid(row=2)
        self.entry3 = tk.Entry(self)
        self.entry3.insert(0, 10)
        self.entry3.grid(row=2, column=1)

        self.button1 = tk.Button(self, text="Функция 1", command=self.on_button1).grid(row=3, column=0)
        self.button2 = tk.Button(self, text="Функция 2", command=self.on_button2).grid(row=3, column=1)
        self.button3 = tk.Button(self, text="Построить график", command=self.build_plot).grid(row=4)
        self.button4 = tk.Button(self, text="Сохранить решение", command=self.on_button4).grid(row=5, column=2)
    
    def file_save(self):
        text = tk.Text(self)
        file4 = asksaveasfile(mode='w', defaultextension=".txt")
        if file4 is None:
            return
        fileRead = open("test.txt", "r")
        text4save = fileRead.read()  # starts from `1.0`, not `0.0`
        file4.write(text4save)
        fileRead.close()
        file4.close()

    def file_save(self):
        text = tk.Text(self)
        file2 = asksaveasfile(mode='w', defaultextension=".txt")
        if file2 is None:
            return
        fileRead = open("test.txt", "r")
        text2save = fileRead.read()  # starts from `1.0`, not `0.0`
        file2.write(text2save)
        fileRead.close()
        file2.close()

    def build_plot(self):
        fig, (ax1, ax2) = plt.subplots(2, 1)
        x = np.linspace(float(self.entry1.get()),
                        float(self.entry3.get()) * float(self.entry2.get()) + float(self.entry1.get()), 10000)
        y1 = np.sin(x) + np.cos(x) + np.sin(3 * x) + np.cos(3 * x)
        y2 = 2 * np.sqrt(2) * np.cos(x) * np.sin(2 * x + np.pi / 4)
        fun1 = ax1.plot(x, y1, 'r', label='y1 = sin(x) + cos(x) + sin(3x) + cos(3x)')
        fun2 = ax2.plot(x, y2, 'b', label='y2 = 2√2cos(x)sin(2x + π/4)')
        functions = fun1 + fun2
        labels = [f.get_label() for f in functions]
        plt.legend(functions, labels, loc=0)
        ax1.set_xlabel('$x$')
        ax1.set_ylabel('$y_1$')
        ax2.set_xlabel('$x$')
        ax2.set_ylabel('$y_2$')
        plt.title('Func1 ')
        plt.tight_layout()
        plt.show()


    def on_button1(self):
        a = float(self.entry1.get())
        b = float(self.entry2.get())
        c = float(self.entry3.get())
        t = a + c * b
        file = open("test.txt", 'a')
        while a < t:
            func1 = math.sin(a) + math.cos(a) + math.sin(3 * a) + math.cos(3 * a)
            file.write("\n a = %.2f , func = %.4f" % (a, func1))
            a = a + b
        file.close()

    def on_button2(self):
        a = float(self.entry1.get())
        b = float(self.entry2.get())
        c = float(self.entry3.get())
        t = a + c * b
        file = open("test.txt", 'a')
        while a < t:
            func2 = 2 * math.sqrt(2) * math.cos(a) * math.sin(2 * a + math.pi / 4)
            file.write("\n a = %.2f , result = %.4f" % (a, func2))
            a = a + b
        file.close()
    def on_button4(self):
        text = tk.Text(self)
        file2 = asksaveasfile(mode='w', defaultextension=".txt")
        if file2 is None:
            return
        fileRead = open("test.txt", "r")
        text2save = fileRead.read()  # starts from `1.0`, not `0.0`
        file2.write(text2save)
        fileRead.close()
        file2.close()


app = SampleApp()
app.mainloop()
