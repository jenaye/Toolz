from tkinter import *
from tkinter.messagebox import *
import re
from scapy.all import *



class Skanner:

    def __init__(self):
        self.win = Tk()
        self.label = Label(self.win, text="Hello world")

        #regex
        self.regexIp = re.compile("\d{1,3}.\d{1,3}.\d{1,3}.\d{1,3}")
        self.regexMask = "/(\d){1,2}"

        #Inputs
        self.value  = StringVar()
        self.valueIp.set("Ip")
        self.valueMask.set("Mask")
        self.inputIp = Entry(self.win, textvariable=self.valueIp, width=30)
        self.inputMask = Entry(self.win, textvariable=self.ValueMask, width=10)
        #Buttons
        self.submitButton = Button(self.win, text="Let's go!", command=self.checkInput)

        #pack
        self.label.pack()
        self.inputIp.pack()
        self.inputMask.pack()
        self.submitButton.pack()

        #mainloop
        self.win.mainloop()


    def checkInput(self):
        self.ip = self.inputIp.get()
        self.mask = self.inputMask.get()


        if self.ipRegex.match(self.ip):
            self.scan(self)
        else:
            showinfo("Merci de rentrer une IP valide!")


    def pingScan(self):





if __name__ == "__main__":
    sk = Skanner()
