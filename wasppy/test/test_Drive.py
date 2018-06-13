import os, unittest, waspdrive

# class for unit testing
class TestDrive(unittest.TestCase):
    document = None
    def test_first_n_lines(self):
        app_file= os.path.dirname(__file__)+"/last_line.driver"
        os.chdir("test")
        str_line=waspdrive.first_n_line(app_file,3)
        os.chdir("../") # go back a director, in case of failure
        self.assertEqual(str_line, 
            "    input_tmpl 'my_fake_app.tmpl'\n", "Line doesn't match")

    def test_last_n_line(self):
        app_file= os.path.dirname(__file__)+"/last_line.driver"
        os.chdir("test")
        str_line=waspdrive.last_n_line(app_file,3)
        os.chdir("../") # go back a director, in case of failure
        self.assertEqual(str_line, 
            "        column 2 delimiter ' ' as 'x1' \n", 
            "Line doesn't match")

    def test_between_lines(self):
        app_file= os.path.dirname(__file__)+"/last_line.driver"
        os.chdir("test")
        str_lines=waspdrive.between_lines(app_file,2,5)
        os.chdir("../") # go back a director, in case of failure
        self.assertEqual(str_lines, 
            "    input_file 'fake_app_input'\n"+
            "    input_tmpl 'my_fake_app.tmpl'\n"+
            "extract_from 'fake_driver_app.csv'\n"+
            "    find last_line 1\n", 
            "Lines don't match")

    def test_between_patterns(self):
        app_file= os.path.dirname(__file__)+"/last_line.driver"
        os.chdir("test")
        str_lines=waspdrive.between_patterns(app_file,"input_file",
            "    input_tmpl")
        os.chdir("../") # go back a director, in case of failure
        self.assertEqual(str_lines,"input_file 'fake_app_input'\n",
            "Lines don't match")

    def test_grep_string(self):
        app_file=os.path.dirname(__file__)+"/last_line.driver"
        os.chdir("test")
        str_lines=waspdrive.grep_string(app_file,"column")
        os.chdir("../")
        self.assertEqual(str_lines,
            "        column 2 delimiter ' ' as 'x1' \n"+
            "        column 3 delimiter ' ' as 'x2' \n"+
            "        column 4 delimiter ' ' as 'x3'\n",
            "Lines don't match")

    
    def test_first_line_driver(self):
        app_driver_input = os.path.dirname(__file__)+"/first_line.driver"
        app_json_parameters = os.path.dirname(__file__)+"/first_line.json"
        os.chdir("test")
        ### obtain pieces of input by name for convenience
        self.document = waspdrive.process_drive_input(app_driver_input)
        self.assertIsNotNone(self.document, "Failed to acquire document!")
        
        rtncode = waspdrive.run_external_app(self.document, app_json_parameters)
        self.assertEqual(0, rtncode, "External application return code is not 0!")
        
        results = waspdrive.extract_results(self.document)
        os.chdir("../") # go back a director, in case of failure
        self.assertListEqual([16.0, 11.25, 75.0], results, results)
    
    def test_last_line_driver(self):
        app_driver_input = os.path.dirname(__file__)+"/last_line.driver"
        app_json_parameters = os.path.dirname(__file__)+"/last_line.json"
        
        os.chdir("test")
        ### obtain pieces of input by name for convenience
        self.document = waspdrive.process_drive_input(app_driver_input)
        self.assertIsNotNone(self.document, "Failed to acquire document!")

        rtncode = waspdrive.run_external_app(self.document, app_json_parameters)
        self.assertEqual(0, rtncode, "External application return code is not 0!")
    
        results = waspdrive.extract_results(self.document)
        os.chdir("../") # go back a director, in case of failure
        self.assertListEqual([16.0, 11.25, 75.0], results)
        

    def test_pattern_column_driver(self):
        """Test """
        app_driver_input = os.path.dirname(__file__)+"/pattern_column.driver"
        app_json_parameters = os.path.dirname(__file__)+"/pattern_column.json"

        os.chdir("test")
        ### obtain pieces of input by name for convenience
        self.document = waspdrive.process_drive_input(app_driver_input)
        self.assertIsNotNone(self.document, "Failed to acquire document!")

        rtncode = waspdrive.run_external_app(self.document, app_json_parameters)
        self.assertEqual(0, rtncode, "External application return code is not 0!")
    
        results = waspdrive.extract_results(self.document)
        os.chdir("../") # go back a director, in case of failure
        self.assertListEqual(
            [58.5, 37.0, # x
             48.0, 32.0, # x
             40.5, 4.5, # v             
        ], results, results)        

    def test_using_driver(self):
        """Test """
        app_driver_input = os.path.dirname(__file__)+"/using.driver"
        app_json_parameters = os.path.dirname(__file__)+"/using.json"

        os.chdir("test")
        ### obtain pieces of input by name for convenience
        self.document = waspdrive.process_drive_input(app_driver_input)
        self.assertIsNotNone(self.document, "Failed to acquire document!")

        rtncode = waspdrive.run_external_app(self.document, app_json_parameters)
        self.assertEqual(0, rtncode, "External application return code is not 0!")
    
        results = waspdrive.extract_results(self.document)
        os.chdir("../") # go back a director, in case of failure
        self.assertListEqual(
            [123456789], results) 

if __name__ == '__main__':
    unittest.main()



