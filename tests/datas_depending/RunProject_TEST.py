#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_RunProject(PyOpenFLUIDTest):

    def runTest(self):
        """Test of project functions."""
        self.assertEquals(len(ArgList), 1)
        Path = ArgList[0]

        self.checkDirectory(Path)
        Res = self.openfluid.runProject(Path)

        self.assertTrue(isinstance(Res, bool))
        self.assertTrue(Res)

        # verification dossier sortie non vide
        OutPath = self.openfluid.getCurrentOutputDir()
        self.checkDirectory(OutPath)
        Contenu = os.listdir(OutPath)
        self.assertGreater(len(Contenu), 0)

        # verification des fichiers que le dossier contient
        ListModel = ["^.*$"]
        ListModel = [re.compile(Model) for Model in ListModel]
        for Fichier in Contenu:
            for ValidModel in ListModel:
                if not ValidModel.search(Fichier) is None:
                    break
            else:
                self.assertTrue(False, "file '{0}' doesn't suit any format.".format(Fichier))

if __name__ == "__main__":
  ArgList = skipArgFromLC()
  unittest.main()
