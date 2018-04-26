import subprocess, os, json
from subprocess import Popen, PIPE

def get_json_dict(schema_filepath, input_filepath, ext=""):
    
    if   (ext == 'ddi') or (input_filepath[-4:] == '.ddi') : utility_name = 'ddivalidjson'
    else : utility_name = 'sonvalidjson' 
    
    if os.name == 'nt' :
        ### for windows intel
        waspvalidjson = os.path.dirname(__file__) + "\\..\\wasputils\\" + utility_name + ".exe"
        if not os.path.isfile(waspvalidjson) :
            ### for windows visual studio
            waspvalidjson = os.path.dirname(__file__) + "\\..\\wasputils\\Release\\" + utility_name + ".exe"
            if not os.path.isfile(waspvalidjson) :
                ### for windows visual studio shared with CMAKE_RUNTIME_OUTPUT_DIRECTORY fixup
                waspvalidjson = os.path.dirname(__file__) + "\\..\\cmake_runtime_output\\Release\\" + utility_name + ".exe"
                if not os.path.isfile(waspvalidjson):
                    waspvalidjson = os.path.dirname(__file__)+"\\..\\bin\\" + utility_name + ".exe"
    else : 
        waspvalidjson = os.path.dirname(__file__) + "/../wasputils/" + utility_name
        if not os.path.isfile(waspvalidjson):
            waspvalidjson = os.path.dirname(__file__)+"/../bin/" + utility_name
    cmd = waspvalidjson + ' ' + schema_filepath + ' ' + input_filepath
    proc = Popen(cmd, shell=True, stdout=PIPE)
    json_result = proc.communicate()[0]
    document_dictionary = json.loads(json_result)
    return document_dictionary
