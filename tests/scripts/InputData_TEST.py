#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_InputData(PyOpenFLUIDTest):

    def runTest(self):
        """Test of input datas functions."""
        # tests of type
        self.assertRaises(TypeError, self.openfluid.getInputData, "", "", "")
        self.assertRaises(TypeError, self.openfluid.getInputData, "", 0, 0)
        self.assertRaises(TypeError, self.openfluid.getInputData, 0, 0, "")
        self.assertRaises(TypeError, self.openfluid.setInputData, "", 0, "", 0)
        self.assertRaises(TypeError, self.openfluid.setInputData, "", 0, 0, "")
        self.assertRaises(TypeError, self.openfluid.setInputData, "", "", "", "")
        self.assertRaises(TypeError, self.openfluid.setInputData, 0, 0, "", "")
        self.assertRaises(TypeError, self.openfluid.removeInputData, "", 0)
        self.assertRaises(TypeError, self.openfluid.removeInputData, 0, "")
        self.assertRaises(TypeError, self.openfluid.createInputData, 0, "", "")
        self.assertRaises(TypeError, self.openfluid.createInputData, "", 0, "")
        self.assertRaises(TypeError, self.openfluid.createInputData, "", "", 0)

        # ID  -  inputVal  -  inputInc
        # 1   -   "test"   -    "inc"
        # 2   -   "test"   -    "autr"
        # 3   - "testdiff" -    "diff"
        InputKeys = (("inputVal", "test"), ("inputInc", "inc"))
        Input = ((1, ("test", "inc")), (2, ("test", "autr")), (3, ("testdiff", "diff")))

        # creation of input data
        UnitClass = "TestClass"
        [self.openfluid.addUnit(UnitClass, a, 1) for a,b in Input]

        # tests of createInputData/getInputData
        self.assertIsNone(
            self.openfluid.getInputData(UnitClass,Input[0][0],
            InputKeys[0][0]))
        [self.openfluid.createInputData(UnitClass, a, b) for a,b in InputKeys]
        print "Res", Input[0][0], InputKeys[0][0], "-", self.openfluid.getInputData(UnitClass,Input[0][0],InputKeys[0][0]), type(self.openfluid.getInputData(UnitClass,Input[0][0],InputKeys[0][0]))
        self.assertTrue(isinstance(
            self.openfluid.getInputData(UnitClass,Input[0][0],InputKeys[0][0]),
            str))

        # tests of setInputData
        for UnitID, UnitValues in Input:
            for i, (UnitKey, UnitDefValue) in enumerate(InputKeys):
                self.assertEquals(
                    self.openfluid.getInputData(UnitClass,UnitID,UnitKey),
                    UnitDefValue)
                self.openfluid.setInputData(UnitClass,UnitID,UnitKey,UnitValues[i])
                self.assertEquals(
                    self.openfluid.getInputData(UnitClass,UnitID,UnitKey),
                    UnitValues[i])

        # tests of removeInputData/getInputData
        for UnitKey, UnitDefValue in InputKeys:
            self.openfluid.removeInputData(UnitClass,UnitKey)
            for UnitID, UnitValues in Input:
                self.assertIsNone(
                    self.openfluid.getInputData(UnitClass,UnitID,UnitKey))


if __name__ == "__main__":
    unittest.main()
