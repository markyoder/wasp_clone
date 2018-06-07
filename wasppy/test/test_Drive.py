import os, unittest, waspdrive

# class for unit testing
class TestDrive(unittest.TestCase):
    document = None
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
        ], results)        

    def test_pattern_column_driver(self):
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



