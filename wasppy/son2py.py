import subprocess, os, json
from subprocess import Popen, PIPE

def get_json_dict(schema_filepath, son_input_filepath):
    if os.name == 'nt' : sonvalidjson = os.path.dirname(__file__) + "\\..\\wasputils\\sonvalidjson.exe"
    else               : sonvalidjson = os.path.dirname(__file__) + "/../wasputils/sonvalidjson"
    cmd = sonvalidjson + ' ' + schema_filepath + ' ' + son_input_filepath + " --json"
    proc = Popen(cmd, shell=True, stdout=PIPE)
    json_result = proc.communicate()[0]
    document_dictionary = json.loads(json_result)
    return document_dictionary
