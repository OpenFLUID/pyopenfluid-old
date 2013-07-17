#!/bin/env/python
# -*- coding: UTF-8 -*-

from BaseTest import *

class PyOpenFLUIDTest_Attribute(PyOpenFLUIDTest):

    def runTest(self):
        """Test of attributes functions."""
        # tests of type
        self.assertRaises(TypeError, self.openfluid.getAttribute, "", "", "")
        self.assertRaises(TypeError, self.openfluid.getAttribute, "", 0, 0)
        self.assertRaises(TypeError, self.openfluid.getAttribute, 0, 0, "")
        self.assertRaises(TypeError, self.openfluid.setAttribute, "", 0, "", 0)
        self.assertRaises(TypeError, self.openfluid.setAttribute, "", 0, 0, "")
        self.assertRaises(TypeError, self.openfluid.setAttribute, "", "", "", "")
        self.assertRaises(TypeError, self.openfluid.setAttribute, 0, 0, "", "")
        self.assertRaises(TypeError, self.openfluid.removeAttribute, "", 0)
        self.assertRaises(TypeError, self.openfluid.removeAttribute, 0, "")
        self.assertRaises(TypeError, self.openfluid.createAttribute, 0, "", "")
        self.assertRaises(TypeError, self.openfluid.createAttribute, "", 0, "")
        self.assertRaises(TypeError, self.openfluid.createAttribute, "", "", 0)

        # ID  -  inputVal  -  inputInc
        # 1   -   "test"   -    "inc"
        # 2   -   "test"   -    "autr"
        # 3   - "testdiff" -    "diff"
        InputKeys = (("inputVal", "test"), ("inputInc", "inc"))
        Input = ((1, ("test", "inc")), (2, ("test", "autr")), (3, ("testdiff", "diff")))

        # creation of attribute
        UnitClass = "TestClass"
        [self.openfluid.addUnit(UnitClass, a, 1) for a,b in Input]

        # tests of createAttribute/getAttribute
        self.assertIsNone(
            self.openfluid.getAttribute(UnitClass,Input[0][0],
            InputKeys[0][0]))
        [self.openfluid.createAttribute(UnitClass, a, b) for a,b in InputKeys]
        print "Res", Input[0][0], InputKeys[0][0], "-", self.openfluid.getAttribute(UnitClass,Input[0][0],InputKeys[0][0]), type(self.openfluid.getAttribute(UnitClass,Input[0][0],InputKeys[0][0]))
        self.assertTrue(isinstance(
            self.openfluid.getAttribute(UnitClass,Input[0][0],InputKeys[0][0]),
            str))

        # tests of setAttribute
        for UnitID, UnitValues in Input:
            for i, (UnitKey, UnitDefValue) in enumerate(InputKeys):
                self.assertEquals(
                    self.openfluid.getAttribute(UnitClass,UnitID,UnitKey),
                    UnitDefValue)
                self.openfluid.setAttribute(UnitClass,UnitID,UnitKey,UnitValues[i])
                self.assertEquals(
                    self.openfluid.getAttribute(UnitClass,UnitID,UnitKey),
                    UnitValues[i])

        # tests of removeAttribute/getAttribute
        for UnitKey, UnitDefValue in InputKeys:
            self.openfluid.removeAttribute(UnitClass,UnitKey)
            for UnitID, UnitValues in Input:
                self.assertIsNone(
                    self.openfluid.getAttribute(UnitClass,UnitID,UnitKey))


if __name__ == "__main__":
    unittest.main()
