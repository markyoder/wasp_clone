from __future__ import print_function
import subprocess, os, json
from subprocess import Popen, PIPE

def get_wasp_utility_path(utility_name):
    path = __file__
    if os.name == 'nt' :
        ### for windows intel
        path = os.path.dirname(__file__) + "\\..\\wasputils\\" + utility_name + ".exe"
        if not os.path.isfile(path) :
            ### for windows visual studio
            path = os.path.dirname(__file__) + "\\..\\wasputils\\Release\\" + utility_name + ".exe"
            if not os.path.isfile(path) :
                ### for windows visual studio shared with CMAKE_RUNTIME_OUTPUT_DIRECTORY fixup
                path = os.path.dirname(__file__) + "\\..\\cmake_runtime_output\\Release\\" + utility_name + ".exe"
                if not os.path.isfile(path):
                    path = os.path.dirname(__file__)+"\\..\\bin\\" + utility_name + ".exe"
    else : 
        path = os.path.dirname(__file__) + "/../wasputils/" + utility_name
        if not os.path.isfile(path):
            path = os.path.dirname(__file__)+"/../bin/" + utility_name
    return path

def get_json_dict(schema_filepath, input_filepath, ext=""):
    
    if   (ext == 'ddi') or (input_filepath[-4:] == '.ddi') : utility_name = 'ddivalidjson'
    elif (ext=="vii") : utility_name="viivalidjson"
    else : utility_name = 'sonvalidjson' 
    
    waspvalidjson = get_wasp_utility_path(utility_name)
    
    cmd = '"' + waspvalidjson + '" "' + schema_filepath + '" "' + input_filepath + '"'
    # print "CMD: ",cmd
    proc = Popen(cmd, shell=True, stdout=PIPE)
    json_result = proc.communicate()[0]
    document_dictionary = json.loads(json_result)
    return document_dictionary
