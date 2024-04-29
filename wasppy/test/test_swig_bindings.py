import unittest
from wasp import *
from Database import InputObject, storeFloat, storeStr, ExistsConstraint
import math
import re

class TestPyServer(ServerImpl):
    '''Concrete example server implementation meant for testing purposes'''

    def __init__(self):
        '''Set up capabilities of concrete example server implementation'''
        super().__init__()
        self.is_python_server = True
        self.enableFullSync()
        self.enableSymbols()
        self.enableCompletion()
        self.enableDefinition()
        self.enableFormatting()
        self.enableReferences()
        self.enableHover()

    def getConnection(self):
        '''Get connection object used by server for client communication'''

    def connectionRead(self, object):
        '''Read JSON-RPC from connection and put data in provided object'''
        return True

    def connectionWrite(self, object):
        '''Convert object to JSON-RPC packet and write out to connection'''
        return True

    def updateDocumentTextChanges(self, replace_text, beg_line, beg_char, end_line, end_char, range_len):
        '''Replace current document on server with provided text changes'''
        self.document_text = replace_text
        return True

    def parseDocumentForDiagnostics(self, diagnostics_list):
        '''Process current document and add diagnostics to provided list'''
        success = True
        diagnostic = DataObject()

        if self.document_text == "test doc text 01":

            beg_line, beg_char, end_line, end_char, severity = 11, 12, 13, 14, 1
            code, src, msg = "code.101", "source_101", "message 101"
            success &= buildDiagnosticObject(diagnostic, self.errorStream(),
                beg_line, beg_char, end_line, end_char, severity, code, src, msg)
            diagnostics_list.push_back(diagnostic)

            beg_line, beg_char, end_line, end_char, severity = 21, 22, 23, 24, 2
            code, src, msg = "code.202", "source_202", "message 202"
            success &= buildDiagnosticObject(diagnostic, self.errorStream(),
                beg_line, beg_char, end_line, end_char, severity, code, src, msg)
            diagnostics_list.push_back(diagnostic)

            beg_line, beg_char, end_line, end_char, severity = 31, 32, 33, 34, 3
            code, src, msg = "code.303", "source_303", "message 303"
            success &= buildDiagnosticObject(diagnostic, self.errorStream(),
                beg_line, beg_char, end_line, end_char, severity, code, src, msg)
            diagnostics_list.push_back(diagnostic)

        elif self.document_text == "test doc text 02":

            beg_line, beg_char, end_line, end_char, severity = 41, 42, 43, 44, 1
            code, src, msg = "code.404", "source_404", "message 404"
            success &= buildDiagnosticObject(diagnostic, self.errorStream(),
                beg_line, beg_char, end_line, end_char, severity, code, src, msg)
            diagnostics_list.push_back(diagnostic)

            beg_line, beg_char, end_line, end_char, severity = 51, 52, 53, 54, 2
            code, src, msg = "code.505", "source_505", "message 505"
            success &= buildDiagnosticObject(diagnostic, self.errorStream(),
                beg_line, beg_char, end_line, end_char, severity, code, src, msg)
            diagnostics_list.push_back(diagnostic)

        return success

    def gatherDocumentSymbols(self, document_symbols):
        '''Build hierarchical symbol tree of document in provided object'''
        success = True
        document_symbols.push_back(DataObject())

        if self.document_text == "test doc text 02":

            symbol_doc_root = document_symbols.back().to_object()
            beg_line,     beg_char,     end_line,     end_char     = 11, 12, 61, 62
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = 11, 12, 61, 62
            name, detail = "doc_root_name", "doc.root.detail"
            kind, deprecated = m_symbol_kind_object, False
            success &= buildDocumentSymbolObject(symbol_doc_root, self.errorStream(),
                name, detail, kind, deprecated, beg_line, beg_char, end_line, end_char,
                beg_line_sel, beg_char_sel, end_line_sel, end_char_sel)

            symbol_child_01 = addDocumentSymbolChild(symbol_doc_root)
            beg_line,    beg_char,      end_line,     end_char     = 11, 12, 31, 32
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = 11, 12, 31, 32
            name, detail = "child_01_name", "child.01.detail"
            kind, deprecated = m_symbol_kind_struct, False
            success &= buildDocumentSymbolObject(symbol_child_01, self.errorStream(),
                name, detail, kind, deprecated, beg_line, beg_char, end_line, end_char,
                beg_line_sel, beg_char_sel, end_line_sel, end_char_sel)

            symbol_child_02 = addDocumentSymbolChild(symbol_doc_root)
            beg_line,     beg_char,     end_line,     end_char     = 41, 42, 61, 62
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = 41, 42, 61, 62
            name, detail = "child_02_name", "child.02.detail"
            kind, deprecated = m_symbol_kind_method, False
            success &= buildDocumentSymbolObject(symbol_child_02, self.errorStream(),
                name, detail, kind, deprecated, beg_line, beg_char, end_line, end_char,
                beg_line_sel, beg_char_sel, end_line_sel, end_char_sel)

        return success

    def gatherDocumentCompletionItems(self, completion_items, req_line, req_char):
        '''Collect completion items for line and column in provided list'''
        success = True
        completion = DataObject()

        if req_line == 23 and req_char == 45:

            beg_line, beg_char, end_line, end_char = 23, 45, 23, 61
            label, doc = "test label 01", "test documentation 01"
            new_text, detail = "test new text 01", "test detail 01"
            kind, format = m_comp_kind_class, m_text_format_plaintext
            deprecated, preselect = False, False
            success &= buildCompletionObject(completion, self.errorStream(),
                label, beg_line, beg_char, end_line, end_char, new_text,
                kind, detail, doc, deprecated, preselect, format)
            completion_items.push_back(completion)

            beg_line, beg_char, end_line, end_char = 23, 45, 23, 61
            label, doc = "test label 02", "test documentation 02"
            new_text, detail = "test new text 02", "test detail 02"
            kind, format = m_comp_kind_value, m_text_format_snippet
            deprecated, preselect = False, False
            success &= buildCompletionObject(completion, self.errorStream(),
                label, beg_line, beg_char, end_line, end_char, new_text,
                kind, detail, doc, deprecated, preselect, format)
            completion_items.push_back(completion)

            beg_line, beg_char, end_line, end_char = 23, 45, 23, 61
            label, doc = "test label 03", "test documentation 03"
            new_text, detail = "test new text 03", "test detail 03"
            kind, format = m_comp_kind_event, m_text_format_plaintext
            deprecated, preselect = False, False
            success &= buildCompletionObject(completion, self.errorStream(),
                label, beg_line, beg_char, end_line, end_char, new_text,
                kind, detail, doc, deprecated, preselect, format)
            completion_items.push_back(completion)

        return success

    def gatherDocumentDefinitionLocations(self, definition_locations, req_line, req_char):
        '''Collect locations of definitions for request in provided list'''
        success = True
        definition = DataObject()

        if req_line == 34 and req_char == 56:

            beg_line, beg_char, end_line, end_char = 15, 21, 15, 31
            doc_path = "path/to/def/doc/01"
            success &= buildLocationObject(definition, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            definition_locations.push_back(definition)

            beg_line, beg_char, end_line, end_char = 25, 22, 25, 32
            doc_path = "path/to/def/doc/02"
            success &= buildLocationObject(definition, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            definition_locations.push_back(definition)

            beg_line, beg_char, end_line, end_char = 35, 23, 35, 33
            doc_path = "path/to/def/doc/03"
            success &= buildLocationObject(definition, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            definition_locations.push_back(definition)

        return success

    def gatherDocumentReferencesLocations(self, references_locations, req_line, req_char, include_decl):
        '''Collect locations of references to request with provided list'''
        success = True
        reference = DataObject()

        if req_line == 45 and req_char == 67 and include_decl:

            beg_line, beg_char, end_line, end_char = 45, 24, 45, 34
            doc_path = "path/to/ref/doc/04"
            success &= buildLocationObject(reference, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            references_locations.push_back(reference)

            beg_line, beg_char, end_line, end_char = 55, 25, 55, 35
            doc_path = "path/to/ref/doc/05"
            success &= buildLocationObject(reference, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            references_locations.push_back(reference)

            beg_line, beg_char, end_line, end_char = 65, 26, 65, 36
            doc_path = "path/to/ref/doc/06"
            success &= buildLocationObject(reference, self.errorStream(),
                doc_path, beg_line, beg_char, end_line, end_char)
            references_locations.push_back(reference)

        return success

    def gatherDocumentFormattingTextEdits(self, formatting_textedits, tab_size, insert_spaces):
        '''Collect formatting edits to apply in order with provided list'''
        success = True
        textedit = DataObject()
        # Example format replaces whitespaces with indented newlines
        if insert_spaces:
            doc_lines = self.document_text.splitlines()
            beg_line, beg_char = 0, 0
            end_line, end_char = len(doc_lines)-1, len(doc_lines[-1])
            doc_format = re.sub(r"\s+", r"\n"+" "*tab_size, self.document_text)
            success &= buildTextEditObject(textedit, self.errorStream(),
                beg_line, beg_char, end_line, end_char, doc_format)
            formatting_textedits.push_back(textedit)
        return success

    def getHoverDisplayText(self, req_line, req_char):
        '''Return text that should be shown on hover at request position'''
        display_text = string()
        if req_line == 56 and req_char == 78:
            display_text = "hover text of example test server"
        return display_text

class LinearModel:
    Definition = None
    @staticmethod
    def definition():
        if LinearModel.Definition is not None: return LinearModel.Definition
        dens = InputObject(Desc="Salt density")
        dens.createRequiredSingle("A", Desc="Density A Coefficient").createRequiredSingle("value", Action=storeFloat)
        dens.createRequiredSingle("B", Desc="Density B Coefficient").createRequiredSingle("value", Action=storeFloat)
        dens.createSingle("C", Default=1.0, Desc="Density C Coefficient").createRequiredSingle("value", Action=storeFloat)
        dens.createRequiredSingle("MinTemp", Desc="Minimum temperature").createRequiredSingle("value", MinValExc=0, Action=storeFloat)
        # TODO add max temperature MinValExc dependency support
        dens.createRequiredSingle("MaxTemp", Desc="Maximum temperature").createRequiredSingle("value", Action=storeFloat)
        dens.createSingle("Type", Default="linear", Desc="interpolation type").createRequiredSingle("value", Enums=["linear"], Action=storeStr)

        LinearModel.Definition = dens
        return LinearModel.Definition

    @staticmethod
    def createFrom(do:'DeserializedObject'):

        result = LinearModel()
        result._a = do["A"].value()
        result._b = do["B"].value()
        result._c = do["C"].value()
        result._minT = do["MinTemp"].value()
        result._maxT = do["MaxTemp"].value()

        theType = do["Type"].value()

        # Require Type to be a supported enumeration
        # This demonstrates post deserialization diagnostic generation
        enumerations = result.definition()["Type"]["value"].enumerations()
        if theType not in enumerations:
            do.interpreter.createWarningDiagnostic(do["Type"].node, "has value of "+str(do["Type"].node)+" which is not listed in "+str(enumerations))

        return result

    ''' _b*x + _c*y = _a '''
    def __init__(self,params=None):
        self._a = 0.0
        self._b = 1.0
        self._c = 1.0
        self._minT = math.inf
        self._maxT = -math.inf

        if params is not None:
            for it in params:
                if it.name() == "MinTemp":
                    self._maxT = float(it)
                elif it.name() == "MaxTemp":
                    self._minT = float(it)
                elif it.name() == "A":
                    self._a = float(it)
                elif it.name() == "B":
                    self._b = float(it)
                elif it.name() == "C":
                    self._c = float(it)

    def get_y(self,x: float) -> "float":
        if self._c == 0.0:
            return math.inf

        return (self._a - (self._b * x)) / self._c
    def __str__(self):
        return "density - a:"+str(self._a)+" b:"+str(self._b)+" c:"+str(self._c)+" min:"+str(self._minT)+" max:"+str(self._maxT)

class Salt:
    Definition = None
    @staticmethod
    def definition():
        '''
            return inputObject - the definition of this object

        '''
        if Salt.Definition is not None: return Salt.Definition
        salt = InputObject(Desc="Single Salt instance")
        salt.createRequiredSingle("id", Enums=["LiF", "NaF", "CaF2", "NH4F", "NaCl"], Desc="Salt type", Action=storeStr)
        salt.createRequiredSingle("BoilTemp", Desc="Salting boiling temperature") \
                .createRequiredSingle("value", MinValExc=0, Action=storeFloat)
        salt.createRequiredSingle("MeltTemp", Desc="Salt melting temperature").createRequiredSingle("value", Action=storeFloat)
        salt.createSingle("MolecularWeight", Desc="Salt's molecular weight").createRequiredSingle("value", MinValExc=0, Action=storeFloat)
        salt.addRequiredSingle("Density", LinearModel.definition())

        Salt.Definition = salt
        return Salt.Definition

    @staticmethod
    def createFrom(do:'DeserializedObject'):
        '''
            deserializedObject - Salt object data deserialized from user input
            Create a Salt object from the given data and return it to the caller
        '''

        result = Salt()
        result._name = do["id"] # not an id=value, just salt(id)
        result._molew = do["MolecularWeight"].value() # is a key=value MolecularWeight=value
        result._meltT = do["MeltTemp"].value()
        result._boilT = do["BoilTemp"].value()
        result._density = LinearModel.createFrom(do["Density"])

        return result

    def __init__(self,params=None):
        self._name = ""
        self._molew = 0.0
        self._meltT = 0.0
        self._boilT = 0.0
        self._density: LinearModel

        # Process parse tree parameters if provided
        if params is not None:
            for it in params:
                if it.name() == "id":
                    self._name = str(it)
                elif it.name() == "MolecularWeight":
                    self._molew = float(it)
                elif it.name() == "MeltTemp":
                    self._meltT = float(it)
                elif it.name() == "BoilTemp":
                    self._boilT = float(it)
                elif it.name() == "Density":
                    self._density = LinearModel(it)


    def density(self,T: float) -> "float":
        return self._density.get_y(T)

    def __str__(self):
        return "salt id:"+self._name+" mw:"+str(self._molew)+" melt:"+str(self._meltT)+" boil:"+str(self._boilT)+"\n    "+str(self._density)

class TheInput:
    Definition = None
    @staticmethod
    def definition():
        if TheInput.Definition is not None: return TheInput.Definition
        db = InputObject()
        salts = db.createRequiredSingle("salts", Desc="The collection of salts in the system")
        salts.addRequired("salt", Salt.definition())
        salts.addUniqueConstraint(["salt/id"])
        db.createRequiredSingle("queries", Desc="Parameters for queries salt properties") \
            .createRequiredSingle("temperatures", Desc="Temperatures (C) at which to query density") \
                .createRequired("value", MinValExc=0, Action=storeFloat)
        TheInput.Definition = db
        return TheInput.Definition

    def createFrom(do:'DeserializedObject'):

        result = TheInput()
        result.salts = [Salt.createFrom(salt) for salt in do["salts"]["salt"]]
        result.queryTemps = do["queries"]["temperatures"].valuelist()

        return result

    def __init__(self):
        self.salts = None
        self.queryTemps = None

    def __str__(self):
        return "".join(str(x)+"\n" for x in self.salts) + "\nqueried at: "+(",".join(str(t) for t in self.queryTemps))

class TestSwigInterface(unittest.TestCase):

    def test_parseString(self):
         self.son = DefaultSONInterpreter()
         son_data = "obj{ c1{} a1{} } k=3.14"
         self.assertTrue(self.son.parseString(son_data))
         self.assertEqual(son_data, self.son.root().data())
         # obj, k
         self.assertEqual(2, self.son.root().child_count())
         expected = {"obj":"obj{ c1{} a1{} }", "k" :"k=3.14"}
         for nv in self.son.root().non_decorative_children():
              self.assertEqual(expected[nv.name()], nv.data())

    def test_ddi(self):
        #son
        self.son = DefaultSONInterpreter()
        self.assertTrue(self.son.parseFile(string("test/DDI2Python_schema.sch")))

        #definition
        ddi_def = Definition()
        #At present we have to get a wrapped std::ostream from the wrapper...
        #It would be nice, to add an interface that would let us use something
        #like StringIO
        psuedo_ss = stringstream()
        self.assertTrue(HIVE.create_definition(ddi_def,self.son.root(),psuedo_ss,False))

        #ddi
        ddi = DefaultDDInterpreter()
        #NOTE: there is some magic here with python to smart pointer
        ddi.set_definition_store(ddi_def)
        self.assertTrue(ddi.parseFile(string("test/DDI2Python_input.ddi")))

    def test_eddi(self):
        #son
        self.son = DefaultSONInterpreter()
        self.assertTrue(self.son.parseFile(string("test/DDI2Python_schema.sch")))

        #definition
        ddi_def = Definition()
        #At present we have to get a wrapped std::ostream from the wrapper...
        #It would be nice, to add an interface that would let us use something
        #like StringIO
        psuedo_ss = stringstream()
        self.assertTrue(HIVE.create_definition(ddi_def,self.son.root(),psuedo_ss,False))

        #ddi
        ddi = DefaultEDDInterpreter()
        #NOTE: there is some magic here with python to smart pointer
        ddi.set_definition_store(ddi_def)
        self.assertTrue(ddi.parseFile(string("test/DDI2Python_input.ddi")))

    def test_API(self):
        doc = Interpreter(Syntax.DDI,
                path="test/DDI2Python_input.ddi",
                schema="test/DDI2Python_schema.sch"
                )
        self.assertEqual(None, doc.errors())
        root = doc.root()
        self.assertTrue(isinstance(root,WaspNode))
        self.assertTrue(isinstance(root[1],WaspNode))
        self.assertTrue(isinstance(root[1]._nodeview,DDINodeView))
        self.assertEqual(root[1]._nodeview.data(),root.extract_from[0]._nodeview.data())
        self.assertEqual(root[2]._nodeview.data(),root.extract_from[1]._nodeview.data())
        self.assertEqual(root["extract_from"][0]._nodeview.data(),root.extract_from[0]._nodeview.data())
        self.assertEqual(int(doc.root().extract_from[1].find[0][3][2]),5)
        self.assertEqual(str(doc.root().extract_from[1].find[0][3]['as']),"response_name_6")
        self.assertEqual(str(doc.root().extract_from[1].find[0][3]['as'].value),"response_name_6")

        i = 0
        for it in root:
            j = 0
            for jt in it:
                if len(jt) > 0:
                    k = 0
                    for kt in jt:
                        if len(kt) > 0:
                            l = 0
                            for lt in kt:
                                self.assertEqual(str(root[i][j][k][l]),str(lt))
                                ref = int(root[i][j][k][l])
                                if not ref == 0:
                                    self.assertEqual(int(root[i][j][k][l]),int(lt))
                                else:
                                    ref = float(root[i][j][k][l])
                                    if not ref == 0.0:
                                        self.assertEqual(float(root[i][j][k][l]),float(lt))
                                l += 1
                        k += 1
                j += 1
            i += 1

        #We are going to get "response_name_4" from the line "column 3 4 delimiter '-' as 'response_name_4'
        for it in root:
            if it.name() == "extract_from" and str(it) == "filename_1.out":
                for jt in it:
                    if jt.name() == "find":
                        for kt in jt:
                            if kt.name() == "column" and int(kt) == 3:
                                for lt in kt:
                                    if lt.name() == "as":
                                        self.assertEqual(str(lt),"response_name_4")

    def test_error(self):
        # This test is just checking that it fails to find a file,
        # a far more robust set could be considered

        doc = Interpreter(Syntax.SON,path="Not_Real.son")
        self.assertFalse(doc) # documents are not valid
        parse_diagnostics = doc.parseDiagnostics()
        self.assertEqual(["Not_Real.son:1.1 is either inaccessible or doesn't exist! Unable to read."], [str(x) for x in parse_diagnostics])


    def test_example(self):
        import tempfile

        doc: Interpreter
        import_name:str
        with tempfile.NamedTemporaryFile(mode='r+',delete=False) as f_i:
            f_i.write('  temperatures = [1100,1200,1300,1400]\n')
            import_name = f_i.name

        with tempfile.NamedTemporaryFile(mode='r+',delete=False) as mainfile:
            mainfile.write('salts {\n')
            mainfile.write('  salt(LiF) {\n')
            mainfile.write('      MeltTemp : 1121.2\n')
            mainfile.write('      MolecularWeight : 25.9394\n')
            mainfile.write('      BoilTemp : 2512\n')
            mainfile.write('      Density\n')
            mainfile.write('      {\n')
            mainfile.write('          Type : linear\n')
            mainfile.write('          A : 2.37\n')
            mainfile.write('          B : 5.0e-4\n')
            mainfile.write('          MinTemp : 1123.6\n')
            mainfile.write('          MaxTemp : 1367.5\n')
            mainfile.write('      }\n')
            mainfile.write('  }\n')
            mainfile.write('  salt(NaF) {\n')
            mainfile.write('      MolecularWeight : 41.9882\n')
            mainfile.write('      MeltTemp : 1268\n')
            mainfile.write('      BoilTemp : 1978\n')
            mainfile.write('      Density\n')
            mainfile.write('      {\n')
            mainfile.write('          Type : linear\n')
            mainfile.write('          A : 2.76\n')
            mainfile.write('          B : 6.36e-4\n')
            mainfile.write('          MinTemp : 1273\n')
            mainfile.write('          MaxTemp : 1373\n')
            mainfile.write('      }\n')
            mainfile.write('  }\n')
            mainfile.write('}\n')
            #The import statement
            mainfile.write('queries {\n')
            mainfile.write(f'`import ("{import_name}")')
            #mainfile.write('  temperatures = [1100,1200,1300,1400]\n')
            mainfile.write('  }\n')

        doc = Interpreter(Syntax.SON,path=mainfile.name)

        temps = []
        salt = []
        for it in doc: #either salts or queries
            for jt in it: # salt or temperatures
                if it.name() == "queries" and jt.name() == "temperatures":
                    for kt in jt:
                        if kt.name() == "value":
                            temps.append(float(kt))
                elif jt.name() == "salt":
                    #The call to iter.__next__() returns a doc node, which is
                    #passed in as params and used to initialize the object
                    salt.append(Salt(jt))

        #Check that 2 Salt objects were set up correctly
        self.assertTrue(len(salt) == 2)
        self.assertEqual(salt[0]._name,"LiF")
        self.assertEqual(salt[0]._meltT,1121.2)
        self.assertEqual(salt[0]._boilT,2512.0)
        self.assertEqual(salt[0]._molew,25.9394)
        self.assertEqual(salt[1]._name,"NaF")
        self.assertEqual(salt[1]._meltT,1268.0)
        self.assertEqual(salt[1]._boilT,1978.0)
        self.assertEqual(salt[1]._molew,41.9882)

        # #Check that a set of queries were read correctly from input
        self.assertTrue(len(temps) == 4)
        self.assertEqual(temps[0],1100.0)
        self.assertEqual(temps[1],1200.0)
        self.assertEqual(temps[2],1300.0)
        self.assertEqual(temps[3],1400.0)

        #Final sanity check that all is well using the two test classes
        self.assertEqual(salt[0].density(1200.0),1.77)
        self.assertEqual(salt[1].density(1200.0),1.9968)

    def test_stream(self):
        import tempfile

        mainfile = tempfile.NamedTemporaryFile(mode='r+',delete=False)
        doc: Interpreter
        ss = '''
        salts {
          salt(LiF) {
              MeltTemp : 1121.2
              MolecularWeight : 25.9394
              BoilTemp : 2512
              Density
              {
                  Type : linear
                  A : 2.37
                  B : 5.0e-4
                  MinTemp : 1123.6
                  MaxTemp : 1367.5
              }
          }
          salt(NaF) {
              MolecularWeight : 41.9882
              MeltTemp : 1268
              BoilTemp : 1978
              Density
              {
                  Type : linear
                  A : 2.76
                  B : 6.36e-4
                  MinTemp : 1273
                  MaxTemp : 1373
              }
          }
        }
        queries {
          temperatures = [1100,1200,1300,1400]
        }'''
        schema='''salts{
    Description = "The collection of salts in the system"
    MinOccurs = 1
    MaxOccurs = 1

    salt{
        MinOccurs = 1
        MaxOccurs = NoLimit
        id{
            MinOccurs = 1
            MaxOccurs = 1
            ValEnums = [LiF NaF CaF2 NH4F NaCl]
        }
        BoilTemp{
            MinOccurs = 1
            MaxOccurs = 1
            value{
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = Real
            } % end value
        } % end BoilTemp

        Density{
            MinOccurs = 1
            MaxOccurs = 1
            A{
                MinOccurs = 1
                MaxOccurs = 1
                value{
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = Real
                } % end value
            } % end A

            B{
                MinOccurs = 1
                MaxOccurs = 1
                value{
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = Real
                    MinValInc = 0
                } % end value
            } % end B
            C{
                MinOccurs = 1
                MaxOccurs = 1
                value{
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = Real
                    MinValInc = 0
                } % end value
            } % end C

            MaxTemp{
                MinOccurs = 1
                MaxOccurs = 1
                value{
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = Real
                    MinValExc = "../../MinTemp/value"
                } % end value
            } % end MaxTemp

            MinTemp{
                MinOccurs = 1
                MaxOccurs = 1
                value{
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = Real
                    MinValExc = 0
                } % end value
            } % end MinTemp

            Type{
                Description = "Type of interpolation"
                MinOccurs = 0
                MaxOccurs = 1
                value{
                    InputDefault = "linear"
                    MinOccurs = 1
                    MaxOccurs = 1
                    ValType   = String
                    ValEnums  = [ "linear" ]
                } % end value
            } % end Type
        } % end Density

        MeltTemp{
            MinOccurs = 1
            MaxOccurs = 1

            value{
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = Real
                MinValInc = 0
            } % end value
        } % end MeltTemp

        MolecularWeight{
            MinOccurs = 0
            MaxOccurs = 1
            InputDefault = "1.0"
            value{
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = Real
                MinValExc = 0
            } % end value
        } % end MolecularWeight
    } % end salt
} % end salts

queries{
    Description = "Parameters for queries salt properties"
    MinOccurs = 1
    MaxOccurs = 1

    temperatures{
        Description = "Temperatures (C) at which to query density"
        MinOccurs = 1
        MaxOccurs = 1
        value{
            MinOccurs = 1
            MaxOccurs = NoLimit
            ValType   = Real
            MinValInc = 0
        } % end value
    } % end temperatures
} % end queries
'''
        doc = Interpreter(Syntax.SON, schema=schema, data=ss, path=mainfile.name)

        temps = []
        salt = []
        for it in doc: #either salts or queries
            for jt in it: # salt or temperatures
                if it.name() == "queries" and jt.name() == "temperatures":
                    for kt in jt:
                        if kt.name() == "value":
                            temps.append(float(kt))
                elif jt.name() == "salt":
                    #The call to iter.__next__() returns a doc node, which is
                    #passed in as params and used to initialize the object
                    salt.append(Salt(jt))

        #Check that 2 Salt objects were set up correctly
        self.assertTrue(len(salt) == 2)
        self.assertEqual(salt[0]._name,"LiF")
        self.assertEqual(salt[0]._meltT,1121.2)
        self.assertEqual(salt[0]._boilT,2512.0)
        self.assertEqual(salt[0]._molew,25.9394)
        self.assertEqual(salt[1]._name,"NaF")
        self.assertEqual(salt[1]._meltT,1268.0)
        self.assertEqual(salt[1]._boilT,1978.0)
        self.assertEqual(salt[1]._molew,41.9882)

        # #Check that a set of queries were read correctly from input
        self.assertTrue(len(temps) == 4)
        self.assertEqual(temps[0],1100.0)
        self.assertEqual(temps[1],1200.0)
        self.assertEqual(temps[2],1300.0)
        self.assertEqual(temps[3],1400.0)

        #Final sanity check that all is well using the two test classes
        self.assertEqual(salt[0].density(1200.0),1.77)
        self.assertEqual(salt[1].density(1200.0),1.9968)

        # Test __getattr__ (. operator) through VectorWaspNode
        # Each value belongs to different 'BoilTemp' requiring a VectorWaspNode
        boiltemps = doc.root().salts.salt.BoilTemp.value
        self.assertEqual(2, len(boiltemps))
        self.assertEqual(2512, float(boiltemps[0]))
        self.assertEqual(1978, float(boiltemps[1]))
        self.assertEqual("LiF", str(boiltemps[0].parent().parent().id))
        self.assertEqual("NaF", str(boiltemps[1].parent().parent().id))

    def test_validation_errors(self):
        schema = '''data{MaxOccurs=1 value{MaxOccurs=1 MaxValInc=1.0 ValType=Real}}'''
        input = '''data 1.1'''

        # Test EDDI
        interpreter = Interpreter(Syntax.EDDI, schema=schema, data=input, path="myfile.inp")

        errors = interpreter.errors()
        expected = ["line:1 column:6 - Validation Error: data value \"1.1\" is greater than the allowed maximum inclusive value of 1.0"]
        self.assertEqual(expected, errors)
        # The 'data' is ambiguous between the child 'data' and the node method 'data()'
        # Get the child by using the string-based query bracket operator
        data = interpreter.root()['data']
        self.assertEqual("myfile.inp", data.source())
        self.assertFalse(data.isDecorative())

        # Test DDI
        input = "data 1.3"
        interpreter = Interpreter(Syntax.DDI, schema=schema, data=input, path="myfile.inp")
        errors = interpreter.errors()
        expected = ["line:1 column:6 - Validation Error: data value \"1.3\" is greater than the allowed maximum inclusive value of 1.0"]
        self.assertEqual(expected, errors)

        # Test SON
        input = "data=1.8"
        interpreter = Interpreter(Syntax.SON, schema=schema, data=input, path="myfile.inp")
        errors = interpreter.errors()
        expected = ["line:1 column:6 - Validation Error: data value \"1.8\" is greater than the allowed maximum inclusive value of 1.0"]
        self.assertEqual(expected, errors)

        # Test HIT
        input = "data=1.7"
        interpreter = Interpreter(Syntax.HIT, schema=schema, data=input, path="myfile.inp")
        errors = interpreter.errors()
        expected = ["line:1 column:6 - Validation Error: data value \"1.7\" is greater than the allowed maximum inclusive value of 1.0"]
        self.assertEqual(expected, errors)

    def test_parse_diagnostics(self):
        input = 'data =' # missing value

        # Test HIT parse error
        interpreter = Interpreter(Syntax.HIT, data=input, path="myfile.inp")
        self.assertFalse(interpreter)
        errors = interpreter.parseDiagnostics()
        expected = [
            "myfile.inp:1.7: syntax error, unexpected end of file",
            "myfile.inp:1.6: syntax error, 'data' has a missing or malformed value",
        ]

        error_strings = [str(x).rstrip() for x in errors]
        self.assertEqual(expected, error_strings)

    def test_diagnostics(self):
        input = "key=1.8"
        interpreter = Interpreter(Syntax.SON, data=input, path="myfile.inp")
        self.assertTrue(interpreter)
        node = interpreter.root().key[0]['value'][0]
        interpreter.createErrorDiagnostic(node, "is an unexpected parameter!")
        interpreter.createWarningDiagnostic(node, "is an unexpected parameter!")
        interpreter.createInformationDiagnostic(node, "is skipped as an unexpected parameter!")
        interpreter.createHintDiagnostic(node, "should be named less ambiguously!")
        dd = interpreter.deserializeDiagnostics()
        self.assertEqual(4, len(dd))

        expected = ["myfile.inp:1.5: value is an unexpected parameter!",
                    "myfile.inp:1.5: value is an unexpected parameter!",
                    "myfile.inp:1.5: value is skipped as an unexpected parameter!",
                    "myfile.inp:1.5: value should be named less ambiguously!"]
        for i, e in enumerate(expected):
            self.assertEqual(e, str(dd[i]))

    def test_database_inputobject(self):
        '''This test exercises the input object definition creation, deserialization, selection, and diagnostics
        as used by the toy salts classes above
        '''
        ss = '''
        salts {
          salt(LiF) {
              MeltTemp : 1121.2
              MolecularWeight : 25.9394
              BoilTemp : 0
              Density
              {
                  Type : foo
                  A : 2.37
                  B : 5.0e-4
                  MinTemp : 1123.6
                  MaxTemp : 1367.5
              }
          }
          salt(NaF) {
              MolecularWeight : 41.9882
              MeltTemp : 1268
              BoilTemp : 1978
              Density
              {
                  Type : linear
                  A : 2.76
                  B : 6.36e-4
                  MinTemp : 1273
                  MaxTemp : 1373
              }
          }
          salt(NaF){
              MolecularWeight : 41.9882
              MeltTemp : 1268
              BoilTemp : 1978
              Density
              {
                  Type : linear
                  A : 2.76
                  B : 6.36e-4
                  MinTemp : 1273
                  MaxTemp : 1373
              }
          }
        }
        queries {
          temperatures = [1100,-1200,1300,1400]
        }'''

        interpreter = Interpreter(Syntax.SON, path="input.son", data=ss)

        self.assertTrue(interpreter)

        definition = TheInput.definition()
        # Test input object (definition) selection logic
        self.assertEqual(definition['salts']['salt']['MolecularWeight']['value'], definition.select("salts/salt/MolecularWeight/value")[0])
        self.assertEqual(definition['salts']['salt']['MolecularWeight']['value'], definition.select("*/*/MolecularWeight/value")[0])
        self.assertEqual(definition['salts']['salt']['MolecularWeight']['value'], definition.select("*/*/MolecularWeight/*")[0])
        self.assertTrue(definition)

        db = definition.deserialize(interpreter.root(), interpreter)
        self.assertTrue(interpreter.deserializeDiagnostics())
        expectedDiagnostics = '''input.son:6.26: value 0.0 is less than or equal to the allowed minimum exclusive value of 0!
input.son:9.26: value foo is not one of the allows values ['linear']!
input.son:16.16: id NaF must be unique but is duplicate to id on line 29 column 16
input.son:29.16: id NaF must be unique but is duplicate to id on line 16 column 16
input.son:44.32: value -1200.0 is less than or equal to the allowed minimum exclusive value of 0!
'''
        self.maxDiff = None
        self.assertEqual(expectedDiagnostics,"".join(str(x)+"\n" for x in interpreter.deserializeDiagnostics()))

        # Test deserialized result selection
        saltids = db.select("salts/salt/id")
        self.assertEqual(3, len(saltids))
        self.assertEqual("LiF", saltids[0].storedResult())
        self.assertEqual("NaF", saltids[1].storedResult())
        self.assertEqual("NaF", saltids[2].storedResult())

        self.assertTrue(db["salts"])
        self.assertTrue(type(db["salts"]["salt"]) == list)
        self.assertEqual(3, len(db["salts"]["salt"]))
        self.assertTrue(db["salts"]["salt"][1])
        self.assertTrue(db["salts"]["salt"][1]["MolecularWeight"])
        self.assertEqual(41.9882, db["salts"]["salt"][1]["MolecularWeight"].value())

        # Test defaulted 'C' and given A density coefficient
        self.assertTrue(db["salts"]["salt"][1]["Density"])
        self.assertTrue(db["salts"]["salt"][1]["Density"]["A"])
        self.assertEqual(2.76, db["salts"]["salt"][1]["Density"]["A"].value())
        self.assertTrue(db["salts"]["salt"][1]["Density"]["C"])
        self.assertEqual(1.0, db["salts"]["salt"][1]["Density"]["C"].value())

        self.assertTrue(db["queries"])
        self.assertEqual([1100.0,-1200.0,1300.0,1400.0], db["queries"]["temperatures"].valuelist())

        # create program data structure
        theInput = TheInput.createFrom(db)
        # This test illustrates the additional diagnostics from result to object creation
        expectedDiagnostics = '''input.son:6.26: value 0.0 is less than or equal to the allowed minimum exclusive value of 0!
input.son:9.26: value foo is not one of the allows values ['linear']!
input.son:16.16: id NaF must be unique but is duplicate to id on line 29 column 16
input.son:29.16: id NaF must be unique but is duplicate to id on line 16 column 16
input.son:44.32: value -1200.0 is less than or equal to the allowed minimum exclusive value of 0!
input.son:9.19: Type has value of foo which is not listed in ['linear']
'''
        self.assertEqual(expectedDiagnostics,"".join(str(x)+"\n" for x in interpreter.deserializeDiagnostics()))
        self.assertEqual([1100.0,-1200.0,1300.0,1400.0],theInput.queryTemps)
        self.assertEqual(3, len(theInput.salts))

        # Test theInput for deserialized result
        expectedSummary = '''salt id:LiF mw:25.9394 melt:1121.2 boil:0.0
    density - a:2.37 b:0.0005 c:1.0 min:1123.6 max:1367.5
salt id:NaF mw:41.9882 melt:1268.0 boil:1978.0
    density - a:2.76 b:0.000636 c:1.0 min:1273.0 max:1373.0
salt id:NaF mw:41.9882 melt:1268.0 boil:1978.0
    density - a:2.76 b:0.000636 c:1.0 min:1273.0 max:1373.0

queried at: 1100.0,-1200.0,1300.0,1400.0'''
        self.assertEqual(expectedSummary, str(theInput))

    def test_database_inputobject_exists(self):
        definition = InputObject()
        definition.createRequiredSingle("ids", Desc="List of viable identifers").createRequired("value", Action=storeStr)
        definition.createRequiredSingle("ref", Desc="The id reference").createRequiredSingle("value", Action=storeStr)
        definition.addExistsConstraint(ExistsConstraint(["ref/value"], target=["ids/value"]))

        inputcontents = '''ids=[foo bar ted]
        ref=bart
        '''
        interpreter = Interpreter(Syntax.SON, path="input.son", data=inputcontents)

        self.assertTrue(interpreter)

        db = definition.deserialize(interpreter.root(), interpreter)
        self.assertTrue(interpreter.deserializeDiagnostics())
        expectedDiagnostics = '''input.son:2.13: value bart is not one of the required existing targets! Required existing targets are foo, bar, ted!
'''
        self.maxDiff = None
        self.assertEqual(expectedDiagnostics,"".join(str(x)+"\n" for x in interpreter.deserializeDiagnostics()))

    def test_language_server(self):
        self.maxDiff = None
        error_stream = stringstream()
        test_py_server = TestPyServer()
        # test_py_server.run() # needs to be run on a thread and communicated with

        with self.subTest(msg='test_py_server.initialize'):
            # Build test initialize request and use server to handle
            initialize_request  = DataObject()
            client_request_id   = 1
            client_process_id   = -1
            client_root_path    = ""
            client_capabilities = DataObject()
            self.assertTrue(buildInitializeRequest(initialize_request,
                                                   error_stream,
                                                   client_request_id,
                                                   client_process_id,
                                                   client_root_path,
                                                   client_capabilities))
            self.assertFalse(error_stream.str())
            initialize_response = DataObject()
            self.assertFalse(test_py_server.isRunning())
            self.assertTrue(test_py_server.handleInitializeRequest(initialize_request,
                                                                   initialize_response))
            self.assertTrue(test_py_server.isRunning())
            self.assertFalse(test_py_server.clientSupportsSnippets())
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server initialize response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 1
  ,"result" : {
    "capabilities" : {
    "completionProvider" : {
    "resolveProvider" : false
  }
    ,"definitionProvider" : true
    ,"documentFormattingProvider" : true
    ,"documentSymbolProvider" : true
    ,"hoverProvider" : true
    ,"referencesProvider" : true
    ,"textDocumentSync" : {
      "change" : 1
      ,"openClose" : true
    }
  }
  }
}
            '''
            self.assertTrue(initialize_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check values dissected from server initialize response
            server_capabilities = DataObject()
            success, server_response_id = dissectInitializeResponse(initialize_response,
                                                                    error_stream,
                                                                    server_capabilities)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual(7, server_capabilities.size())
            # Build initialized notification and handle using server
            initialized_notification = DataObject()
            self.assertTrue(buildInitializedNotification(initialized_notification, error_stream))
            self.assertFalse(error_stream.str())
            self.assertTrue(test_py_server.handleInitializedNotification(initialized_notification))
            self.assertFalse(test_py_server.getErrors())

        with self.subTest(msg='test_py_server.didopen'):
            # Build test didopen notification and handle with server
            didopen_notification = DataObject()
            document_path        = "test/path/to/doc"
            document_language_id = "test_language_id"
            document_text        = "test doc text 01"
            document_version     = 1
            self.assertTrue(buildDidOpenNotification(didopen_notification,
                                                     error_stream,
                                                     document_path,
                                                     document_language_id,
                                                     document_version,
                                                     document_text))
            self.assertFalse(error_stream.str())
            diag_notification = DataObject()
            self.assertTrue(test_py_server.handleDidOpenNotification(didopen_notification,
                                                                     diag_notification))
            self.assertFalse(test_py_server.getErrors())
            # Check json rpc body of server diagnostics notification
            json_actual = stringstream()
            json_expect = '''
{
  "method" : "textDocument/publishDiagnostics"
  ,"params" : {
    "diagnostics" : [
    {
    "code" : "code.101"
    ,"message" : "message 101"
    ,"range" : {
      "end" : {
      "character" : 14
      ,"line" : 13
    }
      ,"start" : {
        "character" : 12
        ,"line" : 11
      }
    }
    ,"severity" : 1
    ,"source" : "source_101"
  }
    ,{
    "code" : "code.202"
    ,"message" : "message 202"
    ,"range" : {
      "end" : {
      "character" : 24
      ,"line" : 23
    }
      ,"start" : {
        "character" : 22
        ,"line" : 21
      }
    }
    ,"severity" : 2
    ,"source" : "source_202"
  }
    ,{
    "code" : "code.303"
    ,"message" : "message 303"
    ,"range" : {
      "end" : {
      "character" : 34
      ,"line" : 33
    }
      ,"start" : {
        "character" : 32
        ,"line" : 31
      }
    }
    ,"severity" : 3
    ,"source" : "source_303"
  }
  ]
    ,"uri" : "test/path/to/doc"
  }
}
            '''
            self.assertTrue(diag_notification.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check server diagnostics notification values dissected
            response_path, diag_array = string(), DataArray()
            self.assertTrue(dissectPublishDiagnosticsNotification(diag_notification,
                                                                  error_stream,
                                                                  response_path,
                                                                  diag_array))
            self.assertFalse(error_stream.str())
            self.assertEqual(document_path, response_path)
            self.assertEqual(3, diag_array.size())
            for i in range(diag_array.size()):
                diag_object = diag_array.at(i).to_object()
                code, src, msg = string(), string(), string()
                success, beg_line, beg_char, end_line, end_char, severity = \
                    dissectDiagnosticObject(diag_object, error_stream, code, src, msg)
                self.assertTrue(success)
                if i == 0:
                    self.assertEqual( 11            , beg_line )
                    self.assertEqual( 12            , beg_char )
                    self.assertEqual( 13            , end_line )
                    self.assertEqual( 14            , end_char )
                    self.assertEqual( 1             , severity )
                    self.assertEqual( "code.101"    , code     )
                    self.assertEqual( "source_101"  , src      )
                    self.assertEqual( "message 101" , msg      )
                elif i == 1:
                    self.assertEqual( 21            , beg_line )
                    self.assertEqual( 22            , beg_char )
                    self.assertEqual( 23            , end_line )
                    self.assertEqual( 24            , end_char )
                    self.assertEqual( 2             , severity )
                    self.assertEqual( "code.202"    , code     )
                    self.assertEqual( "source_202"  , src      )
                    self.assertEqual( "message 202" , msg      )
                elif i == 2:
                    self.assertEqual( 31            , beg_line )
                    self.assertEqual( 32            , beg_char )
                    self.assertEqual( 33            , end_line )
                    self.assertEqual( 34            , end_char )
                    self.assertEqual( 3             , severity )
                    self.assertEqual( "code.303"    , code     )
                    self.assertEqual( "source_303"  , src      )
                    self.assertEqual( "message 303" , msg      )

        with self.subTest(msg='test_py_server.didchange'):
            # Build test didchange notification and handle in server
            didchange_notification = DataObject()
            document_path          = "test/path/to/doc"
            document_text_change   = "test doc text 02"
            document_version       = 2
            self.assertTrue(buildDidChangeNotification(didchange_notification,
                                                       error_stream,
                                                       document_path,
                                                       document_version,
                                                       -1, -1, -1, -1, -1,
                                                       document_text_change))
            self.assertFalse(error_stream.str())
            diag_notification = DataObject()
            self.assertTrue(test_py_server.handleDidChangeNotification(didchange_notification,
                                                                       diag_notification))
            self.assertFalse(test_py_server.getErrors())
            # Check json rpc body of server diagnostics notification
            json_actual = stringstream()
            json_expect = '''
{
  "method" : "textDocument/publishDiagnostics"
  ,"params" : {
    "diagnostics" : [
    {
    "code" : "code.404"
    ,"message" : "message 404"
    ,"range" : {
      "end" : {
      "character" : 44
      ,"line" : 43
    }
      ,"start" : {
        "character" : 42
        ,"line" : 41
      }
    }
    ,"severity" : 1
    ,"source" : "source_404"
  }
    ,{
    "code" : "code.505"
    ,"message" : "message 505"
    ,"range" : {
      "end" : {
      "character" : 54
      ,"line" : 53
    }
      ,"start" : {
        "character" : 52
        ,"line" : 51
      }
    }
    ,"severity" : 2
    ,"source" : "source_505"
  }
  ]
    ,"uri" : "test/path/to/doc"
  }
}
            '''
            self.assertTrue(diag_notification.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check server diagnostics notification values dissected
            response_path, diag_array = string(), DataArray()
            self.assertTrue(dissectPublishDiagnosticsNotification(diag_notification,
                                                                  error_stream,
                                                                  response_path,
                                                                  diag_array))
            self.assertFalse(error_stream.str())
            self.assertEqual(document_path, response_path)
            self.assertEqual(2, diag_array.size())
            for i in range(diag_array.size()):
                diag_object = diag_array.at(i).to_object()
                code, src, msg = string(), string(), string()
                success, beg_line, beg_char, end_line, end_char, severity = \
                    dissectDiagnosticObject(diag_object, error_stream, code, src, msg)
                self.assertTrue(success)
                if i == 0:
                    self.assertEqual( 41            , beg_line )
                    self.assertEqual( 42            , beg_char )
                    self.assertEqual( 43            , end_line )
                    self.assertEqual( 44            , end_char )
                    self.assertEqual( 1             , severity )
                    self.assertEqual( "code.404"    , code     )
                    self.assertEqual( "source_404"  , src      )
                    self.assertEqual( "message 404" , msg      )
                elif i == 1:
                    self.assertEqual( 51            , beg_line )
                    self.assertEqual( 52            , beg_char )
                    self.assertEqual( 53            , end_line )
                    self.assertEqual( 54            , end_char )
                    self.assertEqual( 2             , severity )
                    self.assertEqual( "code.505"    , code     )
                    self.assertEqual( "source_505"  , src      )
                    self.assertEqual( "message 505" , msg      )

        with self.subTest(msg='test_py_server.symbols'):
            # Build test documentsymbols request to handle in server
            symbols_request   = DataObject()
            document_path     = "test/path/to/doc"
            client_request_id = 2
            self.assertTrue(buildSymbolsRequest(symbols_request,
                                                error_stream,
                                                client_request_id,
                                                document_path))
            self.assertFalse(error_stream.str())
            symbols_response = DataObject()
            self.assertTrue(test_py_server.handleSymbolsRequest(symbols_request,
                                                                symbols_response))
            self.assertFalse(test_py_server.getErrors())
            # Check json rpc body of server documentsymbols response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 2
  ,"result" : [
    {
    "children" : [
    {
    "children" : []
    ,"deprecated" : false
    ,"detail" : "child.01.detail"
    ,"kind" : 23
    ,"name" : "child_01_name"
    ,"range" : {
      "end" : {
      "character" : 32
      ,"line" : 31
    }
      ,"start" : {
        "character" : 12
        ,"line" : 11
      }
    }
    ,"selectionRange" : {
      "end" : {
      "character" : 32
      ,"line" : 31
    }
      ,"start" : {
        "character" : 12
        ,"line" : 11
      }
    }
  }
    ,{
    "children" : []
    ,"deprecated" : false
    ,"detail" : "child.02.detail"
    ,"kind" : 6
    ,"name" : "child_02_name"
    ,"range" : {
      "end" : {
      "character" : 62
      ,"line" : 61
    }
      ,"start" : {
        "character" : 42
        ,"line" : 41
      }
    }
    ,"selectionRange" : {
      "end" : {
      "character" : 62
      ,"line" : 61
    }
      ,"start" : {
        "character" : 42
        ,"line" : 41
      }
    }
  }
  ]
    ,"deprecated" : false
    ,"detail" : "doc.root.detail"
    ,"kind" : 19
    ,"name" : "doc_root_name"
    ,"range" : {
      "end" : {
      "character" : 62
      ,"line" : 61
    }
      ,"start" : {
        "character" : 12
        ,"line" : 11
      }
    }
    ,"selectionRange" : {
      "end" : {
      "character" : 62
      ,"line" : 61
    }
      ,"start" : {
        "character" : 12
        ,"line" : 11
      }
    }
  }
  ]
}
            '''
            self.assertTrue(symbols_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check server documentsymbols response values dissected
            symbols_array = DataArray()
            success, server_response_id = dissectSymbolsResponse(symbols_response,
                                                                 error_stream,
                                                                 symbols_array)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual(1, symbols_array.size())
            symbol_doc_root = symbols_array.at(0).to_object()
            self.assertEqual(2, getDocumentSymbolChildren(symbol_doc_root).size())
            symbol_child_01 = getDocumentSymbolChildren(symbol_doc_root).at(0).to_object()
            symbol_child_02 = getDocumentSymbolChildren(symbol_doc_root).at(1).to_object()
            self.assertEqual(0, getDocumentSymbolChildren(symbol_child_01).size())
            self.assertEqual(0, getDocumentSymbolChildren(symbol_child_02).size())

            name, detail = string(), string()
            success,      kind,         deprecated,                  \
            beg_line,     beg_char,     end_line,     end_char,      \
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = \
                dissectDocumentSymbolObject(symbol_doc_root, error_stream, name, detail)
            self.assertTrue(success)
            self.assertEqual( "doc_root_name"      , name         )
            self.assertEqual( "doc.root.detail"    , detail       )
            self.assertEqual( m_symbol_kind_object , kind         )
            self.assertEqual( False                , deprecated   )
            self.assertEqual( 11                   , beg_line     )
            self.assertEqual( 12                   , beg_char     )
            self.assertEqual( 61                   , end_line     )
            self.assertEqual( 62                   , end_char     )
            self.assertEqual( 11                   , beg_line_sel )
            self.assertEqual( 12                   , beg_char_sel )
            self.assertEqual( 61                   , end_line_sel )
            self.assertEqual( 62                   , end_char_sel )

            name, detail = string(), string()
            success,      kind,         deprecated,                  \
            beg_line,     beg_char,     end_line,     end_char,      \
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = \
                dissectDocumentSymbolObject(symbol_child_01, error_stream, name, detail)
            self.assertTrue(success)
            self.assertEqual( "child_01_name"      , name         )
            self.assertEqual( "child.01.detail"    , detail       )
            self.assertEqual( m_symbol_kind_struct , kind         )
            self.assertEqual( False                , deprecated   )
            self.assertEqual( 11                   , beg_line     )
            self.assertEqual( 12                   , beg_char     )
            self.assertEqual( 31                   , end_line     )
            self.assertEqual( 32                   , end_char     )
            self.assertEqual( 11                   , beg_line_sel )
            self.assertEqual( 12                   , beg_char_sel )
            self.assertEqual( 31                   , end_line_sel )
            self.assertEqual( 32                   , end_char_sel )

            name, detail = string(), string()
            success,      kind,         deprecated,                  \
            beg_line,     beg_char,     end_line,     end_char,      \
            beg_line_sel, beg_char_sel, end_line_sel, end_char_sel = \
                dissectDocumentSymbolObject(symbol_child_02, error_stream, name, detail)
            self.assertTrue(success)
            self.assertEqual( "child_02_name"      , name         )
            self.assertEqual( "child.02.detail"    , detail       )
            self.assertEqual( m_symbol_kind_method , kind         )
            self.assertEqual( False                , deprecated   )
            self.assertEqual( 41                   , beg_line     )
            self.assertEqual( 42                   , beg_char     )
            self.assertEqual( 61                   , end_line     )
            self.assertEqual( 62                   , end_char     )
            self.assertEqual( 41                   , beg_line_sel )
            self.assertEqual( 42                   , beg_char_sel )
            self.assertEqual( 61                   , end_line_sel )
            self.assertEqual( 62                   , end_char_sel )

        with self.subTest(msg='test_py_server.completion'):
            # Build test completion request and use server to handle
            completion_request         = DataObject()
            document_path              = "test/path/to/doc"
            client_request_id          = 3
            request_line, request_char = 23, 45
            self.assertTrue(buildCompletionRequest(completion_request,
                                                   error_stream,
                                                   client_request_id,
                                                   document_path,
                                                   request_line,
                                                   request_char))
            self.assertFalse(error_stream.str())
            completion_response = DataObject()
            self.assertTrue(test_py_server.handleCompletionRequest(completion_request,
                                                                   completion_response))
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server completion response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 3
  ,"result" : {
    "isIncomplete" : false
    ,"items" : [
      {
      "deprecated" : false
      ,"detail" : "test detail 01"
      ,"documentation" : "test documentation 01"
      ,"insertTextFormat" : 1
      ,"kind" : 7
      ,"label" : "test label 01"
      ,"preselect" : false
      ,"textEdit" : {
        "newText" : "test new text 01"
        ,"range" : {
          "end" : {
          "character" : 61
          ,"line" : 23
        }
          ,"start" : {
            "character" : 45
            ,"line" : 23
          }
        }
      }
    }
      ,{
      "deprecated" : false
      ,"detail" : "test detail 02"
      ,"documentation" : "test documentation 02"
      ,"insertTextFormat" : 2
      ,"kind" : 12
      ,"label" : "test label 02"
      ,"preselect" : false
      ,"textEdit" : {
        "newText" : "test new text 02"
        ,"range" : {
          "end" : {
          "character" : 61
          ,"line" : 23
        }
          ,"start" : {
            "character" : 45
            ,"line" : 23
          }
        }
      }
    }
      ,{
      "deprecated" : false
      ,"detail" : "test detail 03"
      ,"documentation" : "test documentation 03"
      ,"insertTextFormat" : 1
      ,"kind" : 23
      ,"label" : "test label 03"
      ,"preselect" : false
      ,"textEdit" : {
        "newText" : "test new text 03"
        ,"range" : {
          "end" : {
          "character" : 61
          ,"line" : 23
        }
          ,"start" : {
            "character" : 45
            ,"line" : 23
          }
        }
      }
    }
    ]
  }
}
            '''
            self.assertTrue(completion_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check values dissected from server completion response
            completion_items = DataArray()
            success, server_response_id, is_inc = dissectCompletionResponse(completion_response,
                                                                            error_stream,
                                                                            completion_items)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertFalse(is_inc)
            self.assertEqual(3, completion_items.size())
            for i in range(completion_items.size()):
                item = completion_items.at(i).to_object()
                label, text, detail, doc = string(), string(), string(), string()
                success, beg_line, beg_char, end_line, end_char, \
                kind, deprecated, preselect, format = \
                    dissectCompletionObject(item, error_stream, label, text, detail, doc)
                self.assertTrue(success)
                if i == 0:
                    self.assertEqual( "test label 01"         , label      )
                    self.assertEqual( "test new text 01"      , text       )
                    self.assertEqual( "test detail 01"        , detail     )
                    self.assertEqual( "test documentation 01" , doc        )
                    self.assertEqual( 23                      , beg_line   )
                    self.assertEqual( 45                      , beg_char   )
                    self.assertEqual( 23                      , end_line   )
                    self.assertEqual( 61                      , end_char   )
                    self.assertEqual( m_comp_kind_class       , kind       )
                    self.assertEqual( False                   , deprecated )
                    self.assertEqual( False                   , preselect  )
                    self.assertEqual( m_text_format_plaintext , format     )
                elif i == 1:
                    self.assertEqual( "test label 02"         , label      )
                    self.assertEqual( "test new text 02"      , text       )
                    self.assertEqual( "test detail 02"        , detail     )
                    self.assertEqual( "test documentation 02" , doc        )
                    self.assertEqual( 23                      , beg_line   )
                    self.assertEqual( 45                      , beg_char   )
                    self.assertEqual( 23                      , end_line   )
                    self.assertEqual( 61                      , end_char   )
                    self.assertEqual( m_comp_kind_value       , kind       )
                    self.assertEqual( False                   , deprecated )
                    self.assertEqual( False                   , preselect  )
                    self.assertEqual( m_text_format_snippet   , format     )
                elif i == 2:
                    self.assertEqual( "test label 03"         , label      )
                    self.assertEqual( "test new text 03"      , text       )
                    self.assertEqual( "test detail 03"        , detail     )
                    self.assertEqual( "test documentation 03" , doc        )
                    self.assertEqual( 23                      , beg_line   )
                    self.assertEqual( 45                      , beg_char   )
                    self.assertEqual( 23                      , end_line   )
                    self.assertEqual( 61                      , end_char   )
                    self.assertEqual( m_comp_kind_event       , kind       )
                    self.assertEqual( False                   , deprecated )
                    self.assertEqual( False                   , preselect  )
                    self.assertEqual( m_text_format_plaintext , format     )

        with self.subTest(msg='test_py_server.definition'):
            # Build test definition request and use server to handle
            definition_request         = DataObject()
            document_path              = "test/path/to/doc"
            client_request_id          = 4
            request_line, request_char = 34, 56
            self.assertTrue(buildDefinitionRequest(definition_request,
                                                   error_stream,
                                                   client_request_id,
                                                   document_path,
                                                   request_line,
                                                   request_char))
            self.assertFalse(error_stream.str())
            definition_response = DataObject()
            self.assertTrue(test_py_server.handleDefinitionRequest(definition_request,
                                                                   definition_response))
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server definition response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 4
  ,"result" : [
    {
    "range" : {
    "end" : {
    "character" : 31
    ,"line" : 15
  }
    ,"start" : {
      "character" : 21
      ,"line" : 15
    }
  }
    ,"uri" : "path/to/def/doc/01"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 32
    ,"line" : 25
  }
    ,"start" : {
      "character" : 22
      ,"line" : 25
    }
  }
    ,"uri" : "path/to/def/doc/02"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 33
    ,"line" : 35
  }
    ,"start" : {
      "character" : 23
      ,"line" : 35
    }
  }
    ,"uri" : "path/to/def/doc/03"
  }
  ]
}
            '''
            self.assertTrue(definition_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check values dissected from server definition response
            definition_locations = DataArray()
            success, server_response_id = dissectLocationsResponse(definition_response,
                                                                   error_stream,
                                                                   definition_locations)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual(3, definition_locations.size())
            for i in range(definition_locations.size()):
                location_object = definition_locations.at(i).to_object()
                doc_path = string()
                success, beg_line, beg_char, end_line, end_char = \
                    dissectLocationObject(location_object, error_stream, doc_path)
                self.assertTrue(success)
                if i == 0:
                    self.assertEqual( "path/to/def/doc/01" , doc_path )
                    self.assertEqual( 15                   , beg_line )
                    self.assertEqual( 21                   , beg_char )
                    self.assertEqual( 15                   , end_line )
                    self.assertEqual( 31                   , end_char )
                elif i == 1:
                    self.assertEqual( "path/to/def/doc/02" , doc_path )
                    self.assertEqual( 25                   , beg_line )
                    self.assertEqual( 22                   , beg_char )
                    self.assertEqual( 25                   , end_line )
                    self.assertEqual( 32                   , end_char )
                elif i == 2:
                    self.assertEqual( "path/to/def/doc/03" , doc_path )
                    self.assertEqual( 35                   , beg_line )
                    self.assertEqual( 23                   , beg_char )
                    self.assertEqual( 35                   , end_line )
                    self.assertEqual( 33                   , end_char )

        with self.subTest(msg='test_py_server.references'):
            # Build test references request and use server to handle
            references_request         = DataObject()
            document_path              = "test/path/to/doc"
            client_request_id          = 5
            request_line, request_char = 45, 67
            include_decl               = True
            self.assertTrue(buildReferencesRequest(references_request,
                                                   error_stream,
                                                   client_request_id,
                                                   document_path,
                                                   request_line,
                                                   request_char,
                                                   include_decl))
            self.assertFalse(error_stream.str())
            references_response = DataObject()
            self.assertTrue(test_py_server.handleReferencesRequest(references_request,
                                                                   references_response))
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server references response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 5
  ,"result" : [
    {
    "range" : {
    "end" : {
    "character" : 34
    ,"line" : 45
  }
    ,"start" : {
      "character" : 24
      ,"line" : 45
    }
  }
    ,"uri" : "path/to/ref/doc/04"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 35
    ,"line" : 55
  }
    ,"start" : {
      "character" : 25
      ,"line" : 55
    }
  }
    ,"uri" : "path/to/ref/doc/05"
  }
    ,{
    "range" : {
    "end" : {
    "character" : 36
    ,"line" : 65
  }
    ,"start" : {
      "character" : 26
      ,"line" : 65
    }
  }
    ,"uri" : "path/to/ref/doc/06"
  }
  ]
}
            '''
            self.assertTrue(references_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check values dissected from server references response
            references_locations = DataArray()
            success, server_response_id = dissectLocationsResponse(references_response,
                                                                   error_stream,
                                                                   references_locations)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual(3, references_locations.size())
            for i in range(references_locations.size()):
                location_object = references_locations.at(i).to_object()
                doc_path = string()
                success, beg_line, beg_char, end_line, end_char = \
                    dissectLocationObject(location_object, error_stream, doc_path)
                self.assertTrue(success)
                if i == 0:
                    self.assertEqual( "path/to/ref/doc/04" , doc_path )
                    self.assertEqual( 45                   , beg_line )
                    self.assertEqual( 24                   , beg_char )
                    self.assertEqual( 45                   , end_line )
                    self.assertEqual( 34                   , end_char )
                elif i == 1:
                    self.assertEqual( "path/to/ref/doc/05" , doc_path )
                    self.assertEqual( 55                   , beg_line )
                    self.assertEqual( 25                   , beg_char )
                    self.assertEqual( 55                   , end_line )
                    self.assertEqual( 35                   , end_char )
                elif i == 2:
                    self.assertEqual( "path/to/ref/doc/06" , doc_path )
                    self.assertEqual( 65                   , beg_line )
                    self.assertEqual( 26                   , beg_char )
                    self.assertEqual( 65                   , end_line )
                    self.assertEqual( 36                   , end_char )

        with self.subTest(msg='test_py_server.formatting'):
            # Build test formatting request and use server to handle
            formatting_request = DataObject()
            document_path      = "test/path/to/doc"
            client_request_id  = 6
            tab_size           = 5
            insert_spaces      = True
            self.assertTrue(buildFormattingRequest(formatting_request,
                                                   error_stream,
                                                   client_request_id,
                                                   document_path,
                                                   tab_size,
                                                   insert_spaces))
            self.assertFalse(error_stream.str())
            formatting_response = DataObject()
            self.assertTrue(test_py_server.handleFormattingRequest(formatting_request,
                                                                   formatting_response))
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server formatting response
            json_actual = stringstream()
            json_expect = r'''
{
  "id" : 6
  ,"result" : [
    {
    "newText" : "test\n     doc\n     text\n     02"
    ,"range" : {
      "end" : {
      "character" : 16
      ,"line" : 0
    }
      ,"start" : {
        "character" : 0
        ,"line" : 0
      }
    }
  }
  ]
}
            '''
            self.assertTrue(formatting_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check values dissected from server formatting response
            textedits_array = DataArray()
            success, server_response_id = dissectFormattingResponse(formatting_response,
                                                                    error_stream,
                                                                    textedits_array)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual(1, textedits_array.size())
            textedit = textedits_array.at(0).to_object()
            new_text = string()
            success, beg_line, beg_char, end_line, end_char = \
                dissectTextEditObject(textedit, error_stream, new_text)
            self.assertTrue(success)
            self.assertEqual( 0                                    , beg_line )
            self.assertEqual( 0                                    , beg_char )
            self.assertEqual( 0                                    , end_line )
            self.assertEqual( 16                                   , end_char )
            self.assertEqual( "test\n     doc\n     text\n     02" , new_text )

        with self.subTest(msg='test_py_server.hover'):
            # Build test hover text request and use server to handle
            hover_request              = DataObject()
            document_path              = "test/path/to/doc"
            client_request_id          = 7
            request_line, request_char = 56, 78
            self.assertTrue(buildHoverRequest(hover_request,
                                              error_stream,
                                              client_request_id,
                                              document_path,
                                              request_line,
                                              request_char))
            self.assertFalse(error_stream.str())
            hover_response = DataObject()
            self.assertTrue(test_py_server.handleHoverRequest(hover_request,
                                                              hover_response))
            self.assertFalse(test_py_server.getErrors())
            # Check body of json rpc from server hover text response
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 7
  ,"result" : {
    "contents" : "hover text of example test server"
  }
}
            '''
            self.assertTrue(hover_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check text string dissected from server hover response
            display_text = string()
            success, server_response_id = dissectHoverResponse(hover_response,
                                                               error_stream,
                                                               display_text)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)
            self.assertEqual("hover text of example test server", display_text)

        with self.subTest(msg='test_py_server.didclose'):
            # Build test didclose notification to handle with server
            didclose_notification = DataObject()
            document_path         = "test/path/to/doc"
            self.assertTrue(buildDidCloseNotification(didclose_notification,
                                                      error_stream,
                                                      document_path))
            self.assertFalse(error_stream.str())
            self.assertTrue(test_py_server.handleDidCloseNotification(didclose_notification))
            self.assertFalse(test_py_server.getErrors())

        with self.subTest(msg='test_py_server.shutdown'):
            # Build test shutdown request and handle by using server
            shutdown_request  = DataObject()
            client_request_id = 8
            self.assertTrue(buildShutdownRequest(shutdown_request,
                                                 error_stream,
                                                 client_request_id))
            self.assertFalse(error_stream.str())
            shutdown_response = DataObject()
            self.assertTrue(test_py_server.isRunning())
            self.assertTrue(test_py_server.handleShutdownRequest(shutdown_request,
                                                                 shutdown_response))
            self.assertFalse(test_py_server.isRunning())
            self.assertFalse(test_py_server.getErrors())
            # Check json rpc body with shutdown response from server
            json_actual = stringstream()
            json_expect = '''
{
  "id" : 8
  ,"result" : {}
}
            '''
            self.assertTrue(shutdown_response.format_json(json_actual))
            self.assertEqual(json_expect.strip(), json_actual.str())
            # Check id value dissected from server shutdown response
            success, server_response_id = dissectShutdownResponse(shutdown_response,
                                                                  error_stream)
            self.assertTrue(success)
            self.assertFalse(error_stream.str())
            self.assertEqual(client_request_id, server_response_id)

        with self.subTest(msg='test_py_server.exit'):
            # Build test exit notification for handling using server
            exit_notification = DataObject()
            self.assertTrue(buildExitNotification(exit_notification, error_stream))
            self.assertFalse(error_stream.str())
            self.assertTrue(test_py_server.handleExitNotification(exit_notification))
            self.assertFalse(test_py_server.getErrors())

if __name__ == '__main__':
     unittest.main()
