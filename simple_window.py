# -*- coding: UTF-8 -*-

from Tkconstants import *
import Tkinter as tk
import tkFileDialog
import tkMessageBox

import PyOpenFLUID

import os
from threading import Thread
from multiprocessing import Process, Queue

class WindowPyOF:

    def __init__(self):
        ### =======  INTERNAL  ======= ###
        self.ProjectPath = None
        self.PyOpenFLUID = PyOpenFLUID.PyOpenFLUID()
        self.ResultSimu = None

        ### =======  GRAPHICS PART  ======= ###
        # creation of the window
        self.Fen = tk.Tk()
        self.Fen.title("PyOpenFLUID simple simulation")
        self.Fen.protocol("WM_DELETE_WINDOW", self.quit)

        self.Elements = dict()
        self.Elements["workFrame"] = Frame = tk.Frame(self.Fen)
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=BOTH)
        self.Elements["workFramePackInfo"] = Frame.pack_info()

        Frame = tk.Frame(self.Elements["workFrame"])
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=X)

        width_button = 9
        # work frame
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

        # simulation frame
        self.Elements["simulationFrame"] = Frame = tk.Frame(self.Fen)
        Frame.pack(side=TOP, anchor=NW, expand=YES, fill=BOTH, padx=20, pady=20)
        self.Elements["simulationFramePackInfo"] = Frame.pack_info()
        Frame.pack_forget()

        label = tk.Label(Frame, text="The simulation is running.", justify=CENTER)
        label.pack(ipadx=3, ipady=3, side=TOP, anchor=CENTER,\
            expand=YES, fill=BOTH)

        self.Elements["textvarSimulation"] = simuvar = tk.StringVar(Frame, "<no project path>")
        label = tk.Label(Frame, textvariable=simuvar, justify=CENTER)
        label.pack(ipadx=3, ipady=3, side=TOP, anchor=CENTER,\
            expand=YES, fill=BOTH)

        self.Fen.minsize(500, 30)
        self.Fen.resizable(height=False, width=True)
        self.Fen.update()


    ## event function
    def quit(self, Event=None):
        self.Fen.destroy()

    def open(self, Event=None):
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

        self.Elements["runButton"].config(state=DISABLED) # security
        self.Elements["quitButton"].config(state=DISABLED) # security
        self.Elements["openButton"].config(state=DISABLED) # security
        self.Elements["workFrame"].pack_forget()
        self.Elements["simulationFrame"].pack(\
            **self.Elements["simulationFramePackInfo"] )
        self.Elements["textvarSimulation"].set(self.ProjectPath)
        self.resizeWindow()
        #
        Th = Thread(target=self._launchSimulation,\
            name="OpenFLUID simulation process launcher")
        Th.start()

    def endSimulation(self, Event=None):
        if self.ResultSimu is None:
            return
        #
        self.Elements["textvarSimulation"].set("<no project path>") # security
        self.Elements["simulationFrame"].pack_forget()
        self.Elements["workFrame"].pack( **self.Elements["workFramePackInfo"] )
        self.Elements["quitButton"].config(state=NORMAL) # end of security
        self.Elements["openButton"].config(state=NORMAL) # end of security
        self.resizeWindow()
        #
        if not self.ResultSimu:
            tkMessageBox._show(parent=self.Fen,\
                message="Problem(s) or errors occured during simulation.",\
                _icon=tkMessageBox.ERROR, _type=tkMessageBox.OK,\
                title="Error during the simulation")
        #
        self.ResultSimu = None

    def _runSimulation(self, ResStorage):
        try:
            Res = self.PyOpenFLUID.runSimulation()
        except Exception as e:
            ResStorage.put_nowait(False)
        else:
            ResStorage.put_nowait(Res)

    def _launchSimulation(self):
        ResQueue = Queue()
        ProcessSimu = Process(target=self._runSimulation, args=(ResQueue,),\
            name="OpenFLUID simulation process")
        ProcessSimu.start()
        self.ResultSimu = ProcessSimu.join()
        if self.ResultSimu is None:
            try:
                self.ResultSimu = ResQueue.get_nowait()
            except:
                self.ResultSimu = False
        #
        del ResQueue
        del ProcessSimu
        self.endSimulation()

    ## manage functions
    def openProject(self, Path):
        # Path must exist and be correct
        self.ProjectPath = Path
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


if __name__ == "__main__":
    WindowPyOF()
    tk.mainloop()
