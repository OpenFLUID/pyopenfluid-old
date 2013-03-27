# -*- coding: UTF-8 -*-

from Tkconstants import *
import Tkinter as tk
import tkFileDialog
import tkMessageBox

import PyOpenFLUID

import os
from threading import Thread, Event
from multiprocessing import Process, Queue


def Simulate(PyOFClass, ResStorage):
    try:
        Res = PyOFClass.runSimulation()
        import time
        time.sleep(6)
    except Exception as e:
        ResStorage.put_nowait(False)
        ResStorage.put_nowait(e.message)
    else:
        ResStorage.put_nowait(Res)


class WindowPyOF:
    def __init__(self):
        ### =======  INTERNAL  ======= ###
        self.ProjectPath = None
        self.PyOpenFLUID = PyOpenFLUID.PyOpenFLUID()
        self.ResultSimu = None
        self.ErrorMessage = None
        self.IsSimulationRunned = Event()
        self.IsSimulationRunned.set() # <=> True
        self.NbSimu = 0

        ### =======  GRAPHICS PART  ======= ###
        # creation of the window
        self.Fen = tk.Tk()
        self.Fen.title("PyOpenFLUID simple simulation")
        self.Fen.protocol("WM_DELETE_WINDOW", self.quit)

        self.Elements = dict()
        self.Elements["workFrame"] = Frame = tk.Frame(self.Fen)
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=X)
        self.Elements["workFramePackInfo"] = Frame.pack_info()


        width_button = 9
        # work frame
        Frame = tk.Frame(self.Elements["workFrame"])
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=X)

        self.Elements["openButton"] = button = tk.Button(Frame,\
            text="Open project", command=self.open, width=width_button)
        button.pack(padx=3, pady=3, ipadx=2, ipady=2, side=LEFT, anchor=NW,\
            expand=NO, fill=X)

        self.Elements["textvarPath"] = pathvar = tk.StringVar(Frame, "<no project path>")
        label = tk.Label(Frame, textvariable=pathvar, justify=LEFT)
        label.pack(padx=3, pady=3, ipadx=2, ipady=2, side=LEFT, anchor=W,\
            expand=NO, fill=X)

        Frame = tk.Frame(self.Elements["workFrame"])
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=X)

        self.Elements["quitButton"] = button = tk.Button(Frame, text="Quit",\
            command=self.quit, width=width_button)
        button.pack(padx=3, pady=3, ipadx=2, ipady=2, side=LEFT, anchor=NW,\
            expand=NO, fill=X)

        self.Elements["runButton"] = button = tk.Button(Frame,\
            text="Run simulation", command=self.startSimulation, state=DISABLED)
        button.pack(padx=3, pady=3, ipadx=2, ipady=2, side=LEFT, anchor=NW,\
            expand=YES, fill=X)

        # log
        Frame = tk.Frame(self.Elements["workFrame"])
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=BOTH)

        YScrollBar = tk.Scrollbar(Frame)
        YScrollBar.pack(side=RIGHT, fill=Y, padx=1, pady=1)

        self.Elements["textError"] = Text = tk.Text(Frame, wrap=WORD,\
            yscrollcommand=YScrollBar.set, height=10)
        Text.pack(expand=YES, fill=BOTH, ipadx=3, ipady=3, side=LEFT)
        YScrollBar.config(command=Text.yview)

        # simulation frame
        self.Elements["simulationFrame"] = Frame = tk.Frame(self.Fen)
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=X, padx=20, pady=20)
        self.Elements["simulationFramePackInfo"] = Frame.pack_info()
        Frame.pack_forget()

        label = tk.Label(Frame, text="The simulation is running.", justify=CENTER)
        label.pack(ipadx=3, ipady=3, side=TOP, anchor=CENTER,\
            expand=YES, fill=BOTH)

        self.Elements["textvarSimulation"] = simuvar = tk.StringVar(Frame, "<no project path>")
        label = tk.Label(Frame, textvariable=simuvar, justify=CENTER)
        label.pack(ipadx=3, ipady=3, side=TOP, anchor=CENTER,\
            expand=YES, fill=BOTH)

        # window
        self.Fen.bind("<Control-o>", self.open)
        self.Fen.bind("<Control-q>", self.quit)
        self.Fen.bind("<Control-r>", self.startSimulation)
        self.Fen.minsize(500, 30)
        self.Fen.resizable(height=False, width=True)
        self.Fen.update()

        self.centerWindow()


    ## event function
    def quit(self, Event=None):
        if not self.IsSimulationRunned.isSet():
            tkMessageBox._show(parent=self.Fen,\
                message="You can't close the window during a simulation.",\
                _icon=tkMessageBox.WARNING, _type=tkMessageBox.OK,\
                title="PyOpenFLUID simulation running")
            return

        self.Fen.destroy()

    def open(self, Event=None):
        if not self.IsSimulationRunned.isSet():
            return

        if self.ProjectPath is None:
            TmpRoot = os.getcwd()
        else:
            TmpRoot = self.ProjectPath

        InputDir = tkFileDialog.askdirectory(parent=self.Fen, mustexist=True,\
            title="open an OpenFLUID project path", initialdir=TmpRoot)

        if len(InputDir) == 0:
            self.ProjectPath = None
            return

        Message = "'%s' isn't a correct OpenFLUID project path." % InputDir
        Title = ""
        for Suffix in ["", "IN"]:
            if not (os.path.exists(os.path.join(InputDir, Suffix)) and \
                    os.path.isdir(os.path.join(InputDir, Suffix)) ):
                tkMessageBox._show(parent=self.Fen, message=Message,\
                    _icon=tkMessageBox.ERROR, _type=tkMessageBox.OK, title=Title)
                return

        self.openProject(InputDir)

    def startSimulation(self, Event=None):
        if self.ProjectPath is None:
            return
        if not self.IsSimulationRunned.isSet():
            return
        if self.NbSimu >= 1:
            return

        self.NbSimu += 1
        self.hideLogText()
        self.Elements["workFrame"].pack_forget()
        self.Elements["simulationFrame"].pack(\
            **self.Elements["simulationFramePackInfo"])
        self.Elements["runButton"].config(state=DISABLED) # security
        self.Elements["quitButton"].config(state=DISABLED) # security
        self.Elements["openButton"].config(state=DISABLED) # security
        self.Elements["textvarSimulation"].set(self.ProjectPath)
        self.resizeWindow()
        #
        Th = Thread(target=self._launchSimulation,\
            name="OpenFLUID simulation process launcher")
        Th.start()
        Th = Thread(target=self._endSimulation,\
            name="end of simulation thread")
        Th.start()

    def _launchSimulation(self):
        self.IsSimulationRunned.clear()
        #
        ResQueue = Queue()
        ProcessSimu = Process(target=Simulate,\
            args=(self.PyOpenFLUID, ResQueue,),\
            name="OpenFLUID simulation process")
        ProcessSimu.start()
        self.ResultSimu = ProcessSimu.join()
        self.ErrorMessage = None
        if self.ResultSimu is None:
            try:
                self.ResultSimu = ResQueue.get_nowait()
                if self.ResultSimu is False:
                    self.ErrorMessage = ResQueue.get_nowait()
            except:
                self.ResultSimu = False
                self.ErrorMessage = None
        #
        del ResQueue
        del ProcessSimu
        self.IsSimulationRunned.set()

    def _endSimulation(self, Event=None):
        self.IsSimulationRunned.wait()
        if self.ResultSimu is None:
            return
        #
        self.Elements["simulationFrame"].pack_forget()
        self.Elements["workFrame"].pack( **self.Elements["workFramePackInfo"] )
        if not self.ErrorMessage is None:
            self.showLogText()
        self.Elements["textvarSimulation"].set("<no project path>") # security
        self.Elements["quitButton"].config(state=NORMAL) # end of security
        self.Elements["openButton"].config(state=NORMAL) # end of security
        #
        self.resizeWindow()
        #
        if not self.ResultSimu:
            tkMessageBox._show(parent=self.Fen,\
                message="Problem(s) or errors occured during simulation.",\
                _icon=tkMessageBox.ERROR, _type=tkMessageBox.OK,\
                title="Error during the simulation")
        #
        self.ResultSimu = None

    ## manage functions
    def openProject(self, Path):
        # Path must exist and be correct
        self.ProjectPath = Path
        self.NbSimu = 0
        if not self.IsSimulationRunned.isSet():
            return
        #
        self.hideLogText()
        self.Elements["textvarPath"].set(Path)
        self.Elements["runButton"].config(state=NORMAL)
        self.resizeWindow()

        try:
            self.PyOpenFLUID.openProject(Path)
        except Exception as e:
            tkMessageBox._show(parent=self.Fen, message=e.message,\
                _icon=tkMessageBox.ERROR, _type=tkMessageBox.OK,\
                title="Error during project opening with PyOpenFLUID")
            self.Elements["runButton"].config(state=DISABLED)

    def resizeWindow(self):
        self.Fen.pack_propagate(True)
        self.Fen.update_idletasks()

    def showLogText(self):
        self.Elements["textError"].delete("0.0", END)
        self.Elements["textError"].insert("0.0", self.ErrorMessage)

    def hideLogText(self):
        self.ErrorMessage = None
        self.Elements["textError"].delete("0.0", END)

    def centerWindow(self):
        self.Fen.update_idletasks()
        width = self.Fen.winfo_width()
        height = self.Fen.winfo_height()
        x = (self.Fen.winfo_screenwidth() / 2) - (width / 2)
        y = (self.Fen.winfo_screenheight() / 2) - (height / 2)
        self.Fen.geometry('{0}x{1}+{2}+{3}'.format(width, height, x, y))


if __name__ == "__main__":
    WindowPyOF()
    tk.mainloop()
