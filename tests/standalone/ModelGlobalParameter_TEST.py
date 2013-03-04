#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_ModelGlobalParameter(PyOpenFLUIDTest):

    def runTest(self):
        """Test of model global parameters functions."""

        ParamsList = (("test_bidon","vrai",True),("gvalue","37.2",True),("wind","60",True),("megabidon","??",True),("erreur.pk","rien",False))
        for ParamName, ParamValue, ParamSuccess in ParamsList:
            self.openfluid.setModelGlobalParam(ParamName, ParamValue)

            # test of memory access
            for i in range(15):
                # will crash if the memory isn't managed good enough
                Tmp = self.openfluid.getModelGlobalParam(ParamName)

            # test of recording value
            if ParamSuccess :
                self.assertEquals(self.openfluid.getModelGlobalParam(ParamName), ParamValue)
            else:
                self.assertNotEquals(self.openfluid.getModelGlobalParam(ParamName), ParamValue)

if __name__ == "__main__":
  unittest.main()
