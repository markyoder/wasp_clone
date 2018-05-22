import os, unittest, waspdrive

if os.name == 'nt' :
    app_driver_input = os.path.dirname(__file__)+"\\fake_app.driver"
    app_json_parameters = os.path.dirname(__file__)+"\\fake_app.json"
else:
    app_driver_input = os.path.dirname(__file__)+"/fake_app.driver"
    app_json_parameters = os.path.dirname(__file__)+"/fake_app.json"



# class for unit testing
class TestDrive(unittest.TestCase):
    document = None
    def test_driver(self):
        os.chdir("test")
        ### obtain pieces of input by name for convenience
        self.document = waspdrive.process_drive_input(app_driver_input)
        self.assertIsNotNone(self.document, "Failed to acquire document!")

        rtncode = waspdrive.run_external_app(self.document, app_json_parameters)
        self.assertEqual(0, rtncode, "External application return code is not 0!")
    
        results = waspdrive.extract_results(self.document)
        self.assertListEqual([75.0, 15.5, 0.25], results)

if __name__ == '__main__':
    unittest.main()



