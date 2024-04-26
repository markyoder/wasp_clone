import unittest, threading
from wasp import *
from .example_server import ExampleServer

class TestLspServerRunning(unittest.TestCase):

    def test_server_running(self):

        with self.subTest(msg='server_running.launch_thread_and_run_server'):
            # Launch thread to execute server run method and connect client
            example_server = ExampleServer()
            testing_client = ClientImpl()
            running_thread = threading.Thread(target=example_server.run, daemon=True)
            running_thread.start()
            self.assertFalse(testing_client.isConnected())
            self.assertTrue(testing_client.connect(example_server.getConnection()))
            self.assertTrue(testing_client.isConnected())

        with self.subTest(msg='server_running.initialize_and_open_document'):
            # Initialize server and handle initialized using startUpCleanly
            self.assertFalse(testing_client.getConnection().isServerRunning())
            self.assertTrue(testing_client.startUpCleanly())
            self.assertTrue(testing_client.getConnection().isServerRunning())
            self.assertFalse(testing_client.getConnection().getServerErrors())
            self.assertFalse(testing_client.getErrors())
            self.assertEqual(1, testing_client.getPreviousRequestID())
            # Open document which contains initial text by notifying server
            doc_path = "test/path/to/doc"
            doc_lang = "test_language_id"
            doc_text = "test doc text 01"
            self.assertFalse(testing_client.isDocumentOpen())
            self.assertTrue(testing_client.doDocumentOpen(doc_path, doc_lang, doc_text))
            self.assertTrue(testing_client.isDocumentOpen())
            self.assertEqual(1, testing_client.getCurrentDocumentVersion())
            self.assertFalse(testing_client.getConnection().getServerErrors())
            self.assertFalse(testing_client.getErrors())
            self.assertEqual(1, testing_client.getPreviousRequestID())
            # Check diagnostic list provided by server for initial document
            self.assertEqual(3, testing_client.getDiagnosticSize())
            for i in range(testing_client.getDiagnosticSize()):
                diag = clientDiagnostic()
                self.assertTrue(testing_client.getDiagnosticAt(i, diag))
                if i == 0:
                    self.assertEqual( 11            , diag.start_line      )
                    self.assertEqual( 12            , diag.start_character )
                    self.assertEqual( 13            , diag.end_line        )
                    self.assertEqual( 14            , diag.end_character   )
                    self.assertEqual( 1             , diag.severity        )
                    self.assertEqual( "code.101"    , diag.code            )
                    self.assertEqual( "source_101"  , diag.source          )
                    self.assertEqual( "message 101" , diag.message         )
                elif i == 1:
                    self.assertEqual( 21            , diag.start_line      )
                    self.assertEqual( 22            , diag.start_character )
                    self.assertEqual( 23            , diag.end_line        )
                    self.assertEqual( 24            , diag.end_character   )
                    self.assertEqual( 2             , diag.severity        )
                    self.assertEqual( "code.202"    , diag.code            )
                    self.assertEqual( "source_202"  , diag.source          )
                    self.assertEqual( "message 202" , diag.message         )
                elif i == 2:
                    self.assertEqual( 31            , diag.start_line      )
                    self.assertEqual( 32            , diag.start_character )
                    self.assertEqual( 33            , diag.end_line        )
                    self.assertEqual( 34            , diag.end_character   )
                    self.assertEqual( 3             , diag.severity        )
                    self.assertEqual( "code.303"    , diag.code            )
                    self.assertEqual( "source_303"  , diag.source          )
                    self.assertEqual( "message 303" , diag.message         )

        with self.subTest(msg='server_running.update_text_and_send_changes'):
            # Change text within open document and notify server of updates
            doc_edit = "test doc text 02"
            self.assertEqual(1, testing_client.getCurrentDocumentVersion())
            self.assertTrue(testing_client.doDocumentChange(-1, -1, -1, -1, -1, doc_edit))
            self.assertEqual(2, testing_client.getCurrentDocumentVersion())
            self.assertFalse(testing_client.getConnection().getServerErrors())
            self.assertFalse(testing_client.getErrors())
            self.assertEqual(1, testing_client.getPreviousRequestID())
            # Check diagnostic list provided by server for updated document
            self.assertEqual(2, testing_client.getDiagnosticSize())
            for i in range(testing_client.getDiagnosticSize()):
                diag = clientDiagnostic()
                self.assertTrue(testing_client.getDiagnosticAt(i, diag))
                if i == 0:
                    self.assertEqual( 41            , diag.start_line      )
                    self.assertEqual( 42            , diag.start_character )
                    self.assertEqual( 43            , diag.end_line        )
                    self.assertEqual( 44            , diag.end_character   )
                    self.assertEqual( 1             , diag.severity        )
                    self.assertEqual( "code.404"    , diag.code            )
                    self.assertEqual( "source_404"  , diag.source          )
                    self.assertEqual( "message 404" , diag.message         )
                elif i == 1:
                    self.assertEqual( 51            , diag.start_line      )
                    self.assertEqual( 52            , diag.start_character )
                    self.assertEqual( 53            , diag.end_line        )
                    self.assertEqual( 54            , diag.end_character   )
                    self.assertEqual( 2             , diag.severity        )
                    self.assertEqual( "code.505"    , diag.code            )
                    self.assertEqual( "source_505"  , diag.source          )
                    self.assertEqual( "message 505" , diag.message         )

        with self.subTest(msg='server_running.close_document_and_finish_up'):
            # Close document and quit with wrapUpCleanly so server can exit
            self.assertTrue(testing_client.getConnection().isServerRunning())
            self.assertTrue(testing_client.isDocumentOpen())
            self.assertTrue(testing_client.isConnected())
            self.assertTrue(testing_client.wrapUpCleanly())
            self.assertFalse(testing_client.isConnected())
            self.assertFalse(testing_client.isDocumentOpen())
            self.assertFalse(testing_client.getConnection().isServerRunning())
            self.assertFalse(testing_client.getConnection().getServerErrors())
            self.assertFalse(testing_client.getErrors())
            self.assertEqual(2, testing_client.getPreviousRequestID())
            running_thread.join()

if __name__ == '__main__':
    unittest.main()
