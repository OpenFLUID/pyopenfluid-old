#!/bin/python2.7
# -*- coding: UTF-8 -*-

import sys
import re

# verif script
if len(sys.argv) < 1:
    print "?? missing itself ?"
    sys.exit(1)
elif sys.argv.pop(0) != __file__:
    print "?? script isn't itsefl ?"
    sys.exit(1)

if len(sys.argv) < 1:
    print "missing examples file"
    sys.exit(1)

CUSTOM_OUTPUT_FILE = False
if len(sys.argv) >= 2:
    # openning
    try:
        flOuput = open(sys.argv[1], "w")
    except IOError:
        print "error while openning output file"
        sys.exit(1)
    CUSTOM_OUTPUT_FILE = True
else:
    flOuput = sys.stdout

# openning
try:
    fch = open(sys.argv[0], "r")
except IOError:
    print "error while openning examples file"
    sys.exit(1)

# log
def printLog(log, state):
    if state:
        print log

# function reading
BL_LOG_NWLINE = False
printLogNwLine = lambda msg: printLog("New line: "+msg, BL_LOG_NWLINE)
def readLine(f):
    line = f.readline()
    assert len(line) != 0
    printLogNwLine(line)
    return line.rstrip("\n")

# function line
def emptyLine(line):
    return len(line) == 0 or line.isspace()

# function reading line
def avoidEmptyLine(f):
    line = readLine(f)
    while emptyLine(line):
        line = readLine(f)
    return line

# reading
print "Reading file"
BL_LOG_READING = False
printLogReading = lambda msg: printLog("Reading: "+msg, BL_LOG_READING)
LIST_EXAMPLES = []
try:
    while True:
        line = readLine(fch)
        # start bloc example
        printLogReading("")
        if emptyLine(line.strip("-")):
            printLogReading("start bloc")
            avoidEmptyLine(fch)
            # reading functions
            printLogReading("reading functions")
            FUNCTIONS = []
            line = readLine(fch)
            while line.startswith(" - "):
                FUNCTIONS.extend(line.lstrip(" - ").split("/"))
                line = readLine(fch)
            # reading example
            printLogReading("reading examples")
            EXAMPLE = []
            while not emptyLine(line):
                EXAMPLE.append(line)
                line = readLine(fch)
            # enregistrement
            printLogReading("saving bloc")
            LIST_EXAMPLES.append( (FUNCTIONS, EXAMPLE) )
        elif emptyLine(line):
            printLogReading("line vide")
            continue
        else:
            printLogReading("line inconnue : '{0}'".format(line))
except AssertionError:
    pass

# function writing
def writeFile(pattern, rc=True):
    flOuput.write(pattern + rc*"\n")
    flOuput.flush()

#
REPLACE_LIST_BY_WORD = [\
  ("HLReserv", "( )%([ ]+)", ("print", "def", "except", "if", "else", "endally", "lambda", "in", "for", "assert", "continue", "break", "is", "del")),\
  ("HLSpecial", "([^\w]+)%([^\w]+)", ("str", "int", "long", "type", "float", "unicode", "id", "isinstance", "len", "set", "callable")),\
  ("HLValue", "([^\w]+)%([^\w]+)", ("None", "True", "False")),\
]

REPLACE_LIST = dict(number="HLNumber", pattern="HLString", comment="LineExComment", result="LineExResult", important="HLImportant", startexample="StartExample", endexample="EndExample")

SPECIAL_CHARACTERE = ["'", '"', '\\', "%"]

BEGINNIG_OF_LINE = "    # "

#
def createTag(text):
    return "@" + text
def putTag(tag, text):
    return createTag(tag + "{" + text + "}")

def fusionSplitRegex(listIn, word, end=""):
    res = ""
    for i, subpattern in enumerate(listIn):
        if i%3 == 0:
            res += subpattern
        elif i%3 == 1:
            res += subpattern + word
        elif i%3 == 2:
            res += end + subpattern
    return res

def fusionSplitRegexAvecValeur(listIn, prev, end):
    res = ""
    for i, subpattern in enumerate(listIn):
        if i%4 == 0:
            res += subpattern
        elif i%4 == 1:
            res += subpattern + prev
        elif i%4 == 2:
            res += subpattern + end
        elif i%4 == 3:
            res += subpattern
    return res

# writing
print "Writing du file - DOXYGEN"
#print LIST_EXAMPLES
BL_LOG_WRITING = True
printLogWriting = lambda msg: printLog("Writing: "+msg, BL_LOG_WRITING)
for lFunc, lRawEx in LIST_EXAMPLES:
#    print lFunc, lRawEx
    assert len(lFunc) != 0, "no functions"
    assert len(lRawEx) != 0, "no examples"
    # preparation example
    FINAL_EXAMPLE = []
    for line_ex in lRawEx:
        # comment
        if '#' in line_ex:
            iComm = line_ex.index("#")
            if not "'" in line_ex[:iComm] and not '"' in line_ex[:iComm]:
                OK_COMM = True
            else:
                OK_COMM = line_ex[:iComm].count("'")+line_ex[:iComm].count('"')\
                    -line_ex[:iComm].count("\\'")-line_ex[:iComm].count('\\"')
                OK_COMM = (OK_COMM % 2 == 0)
            if OK_COMM:
                line_ex = line_ex[:iComm] + createTag(REPLACE_LIST["comment"]) + "{\\" +  line_ex[iComm+1:] + "}"
        # caracteres speciaux
        for speCar in SPECIAL_CHARACTERE:
            line_ex = line_ex.replace(speCar, "\\"+speCar)
        # number
#        SPLIT_LIGNE = re.split("([^\w]?)([-]?[0-9]+)([^\w]?)", line_ex)
#        line_ex = fusionSplitRegexAvecValeur(SPLIT_LIGNE, createTag(REPLACE_LIST["number"]+"{"), "}")
        # mise en valeur des words
        for tag, wordif, lMotSpe in REPLACE_LIST_BY_WORD:
            for wordSpe in lMotSpe:
                SPLIT_LIGNE = re.split(wordif.replace("%", wordSpe), line_ex)
                if len(SPLIT_LIGNE) != 1:
                    line_ex = fusionSplitRegex(SPLIT_LIGNE, putTag(tag, wordSpe))
                else:
                    line_ex = SPLIT_LIGNE[0]
        # type de line
        if line_ex.startswith(">>> "):
            line = createTag("LineExSimple{"+line_ex[4:]+"}")
            FINAL_EXAMPLE.append(line)
        elif line_ex.startswith("... "):
            line = createTag("LineExSimpleContinue{"+line_ex[4:]+"}")
            FINAL_EXAMPLE.append(line)
        else:
            line = createTag("LineExResult{"+line_ex+"}")
            FINAL_EXAMPLE.append(line)
    # writing par function
    for function in lFunc:
        tmp = "="*10 + " "*3 + function + " "*3 + "="*10
        writeFile("="*len(tmp) + "\n" + tmp)
        writeFile(BEGINNIG_OF_LINE+createTag(REPLACE_LIST["startexample"]))
        #
        for line_ex in FINAL_EXAMPLE:
            FINAL_LIGNE = line_ex

            FINAL_LIGNE = re.split("([^\w])"+function+"([^\w])", line_ex)

            FINAL_LIGNE = fusionSplitRegex(FINAL_LIGNE,
                putTag(REPLACE_LIST["important"], function))

            indexvirg = -1
            for _tmp in range(FINAL_LIGNE.count(",")):
                indexvirg = indexvirg+1 + FINAL_LIGNE[indexvirg+1:].index(",")
                n = FINAL_LIGNE[:indexvirg].count("{") - FINAL_LIGNE[:indexvirg].count("}")
                FINAL_LIGNE = FINAL_LIGNE[:indexvirg] + n*"\\" + FINAL_LIGNE[indexvirg:]
                indexvirg += n

            FINAL_LIGNE = FINAL_LIGNE.replace('\\\\"', '\\"')
            FINAL_LIGNE = FINAL_LIGNE.replace("@LineExComment{\\ ", "@LineExComment{ ")

            writeFile(BEGINNIG_OF_LINE+"  "+FINAL_LIGNE)
        #
        writeFile(BEGINNIG_OF_LINE+createTag(REPLACE_LIST["endexample"]))
        writeFile("")

# closing
flOuput.flush()
print "Closing"
fch.close()
if CUSTOM_OUTPUT_FILE:
    flOuput.close()
