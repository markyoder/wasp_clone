import subprocess, os, json
import re
import wasp2py as w2py
from itertools import islice
from collections import deque

#todo: follow Rob's driver schema and example to revise codes

def process_drive_input(file_extract_driver):
    """Process and obtain the driver document data"""
    drive_schema =  os.path.dirname(__file__)+"/drive/driver.sch"
    document=w2py.get_json_dict(drive_schema, file_extract_driver, ext="ddi" )    
    return document

def run_external_app(document, application_json_parameters):    
    """Runs the external application as listed in the given document.
    Expands the application input template using the provided application_json_parameters prior to application execution.    
    """ 
    external_app=document['application']['value'] #
    input_file=document['application']['input_file']['value'] #
    tmpl_file=document['application']['input_tmpl']['value'] #
    template_engine = w2py.get_wasp_utility_path("halite")

    args = "{} {} {} > {}".format(template_engine, tmpl_file, application_json_parameters, input_file)
    print "Executing template engine..."
    print "-- ",args
    rtncode = os.system(args)
    print "Template expansion completed. Return code ",rtncode
    if rtncode != 0:
        return rtncode

    print "Running external simulation..."
    print " -- ",external_app
    
    rtncode = os.system(external_app) 
    print "External simulation complete. Return code ",rtncode
    return rtncode

def first_n_line(str_file, n):
    #read the first n lines from a file,
    #return the last line only
    last_line=""
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                line_count=0
                for line in islice(f, n):
                    last_line=line
                    line_count+=1
                if n > line_count :
                    last_line=""
                    print "Line index > max line number!"
            except:
                print "File reading error!"
    else:
        print "No such file!"
    return last_line

def last_n_line(str_file, n):
    #read the last n line from a file,
    #return the first line only
    first_line=""
    if os.path.exists(str_file):
        line_count = len(open(str_file).readlines())
        if n > line_count:
            print "Line index > max line number!"
        else:
            with open(str_file) as f:
                try:
                    first_line=deque(f, maxlen=n).popleft()
                except:
                    print "File reading error!"
    else:
        print "No such file!"
    return first_line

def between_lines(str_file, start_n, end_n):
    #read between start_n and end_n from a file
    #return the lines in between
    #to include start_n line, begin with start_n-1
    lines=""
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                if int(start_n)==0:
                    print "start index must be integer > 0"
                    pass
                elif int(start_n)>int(end_n):
                    print "line index must be 0 < start_n <= end_n"
                    pass
                else:
                    for line in islice(f, start_n-1, end_n):
                        lines+=line
            except:
                print "File reading error!"
    else:
        print "No such file!"
    return lines

def between_patterns(str_file, start_pattern, end_pattern):
    #read between start_pattern and end_pattern from a file
    #return the lines in between
    section = ""
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                content = f.read()
                start = content.index(start_pattern)
                end = content.index(end_pattern, start)
                section = content[start:end]
            except:
                print "File reading error!"
    else:
        print "No such file!"
    return section

def grep_string(str_file, pattern):
    #read the file and return the first line with matched pattern
    lines=""
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                for line in f:
                    m=re.search(pattern, line)
                    if m:
                       lines+=line
            except:
                print "File reading error!"
    else:
        print "No such file!"
    return lines

def extract_results(document):
    res_output=[]
    output_file=[]
    #demo for extraction.driver
    i=0;
    #process logic here
    for idx, extract in enumerate(document['extract_from']):
        output_file.append(extract['value'])

        if 'using' in extract: # run the user provided script
            for using in extract['using']:            
                using_what = using['value']
                print "Using '"+using_what+"'"
                output = subprocess.check_output(using_what,shell=True).strip()            
                print "Using produced '"+output+"'"
                res_output.extend([float(r) for r in output.split("\n")])
        
        elif 'find' in extract: # Finding pattern or line
            for each_find in extract['find']:
                if len(each_find)==1: #one line of extraction command only
                    if "column" in each_find:
                        delimiter=str(each_find["column"][0]["delimiter"]["value"])
                        for each_col in each_find["column"][0]["value"]:
                            res_output.append(float((first_n_line(output_file[i],1).strip().split(delimiter)[int(each_col)-1]).strip('\n')))
                    if "first_line" in each_find:
                        int_line="-"+str(each_find["first_line"]['value'])
                        #extract the whole line
                        res_output.append(str((first_n_line(output_file[i],int(each_find["first_line"]['value']))).strip('\n')))
                    if "last_line" in each_find:
                        int_line="-"+str(each_find["last_line"]['value'])
                        #extract the whole line
                        res_output.append(str((last_n_line(output_file[i],int(each_find["first_line"]['value']))).strip('\n')))
                    if "pattern" in each_find:
                        str_pattern=str(each_find["pattern"]['value'])
                        #extract the whole line
                        data = str((grep_string(output_file[i], str_pattern)).strip('\n'))
                        res_output.append(data)         
                    if "between" in each_find:
                        str_pattern_start=str(each_find["between"]['value'][0])
                        str_pattern_end=str(each_find["between"]['value'][1])
                        res_output.append(str((between_patterns(output_file[i], str_pattern_start, str_pattern_end)).strip('\n')))
                elif len(each_find)==2: #two layers of extraction command
                    if ("column" in each_find) and ("last_line" in each_find):
                        int_line="-"+str(each_find["last_line"]['value'])
                        delimiter=str(each_find["column"][0]["delimiter"]["value"])
                        str_last_n_line=last_n_line(output_file[i],int(each_find["last_line"]['value']))
                        if str_last_n_line != "":
                            for each_column in each_find["column"]:
                                res_output.append(float((str_last_n_line \
                                                    .strip().split(delimiter)[int(each_column["value"][0])-1]).strip('\n')))
                    if ("column" in each_find) and ("first_line" in each_find):
                        int_line="-"+str(each_find["first_line"]['value'])
                        delimiter=str(each_find["column"][0]["delimiter"]["value"])
                        str_first_n_line=first_n_line(output_file[i],int(each_find["first_line"]['value']))
                        if str_first_n_line != "":
                            for each_column in each_find["column"]:
                                res_output.append(float((str_first_n_line \
                                                    .strip().split(delimiter)[int(each_column["value"][0])-1]).strip('\n')))
                    if ("column" in each_find) and ("pattern" in each_find):
                        str_pattern=str(each_find["pattern"]['value'])
                        lines=grep_string(output_file[i],str_pattern).split('\n')
                        for each_line in lines:
                            if each_line!="":
                                split = each_line.strip().split()
                                for each_column in each_find["column"]:
                                    data = split[int(each_column["value"][0])-1]
                                    res_output.append(float(data))
                            
                    if ("column" in each_find) and ("between" in each_find):
                        str_pattern_start=str(each_find["between"]['value'][0])
                        str_pattern_end=str(each_find["between"]['value'][1])
                        for each_column in each_find["column"]:
                            res_output.append(float((between_patterns(output_file[i], str_pattern_start, str_pattern_end) \
                                                    .strip().split()[int(each_column["value"][0])-1]).strip('\n')))

        i+=1
    return res_output

def drive(driver_input_path, application_parameter_json_path):
    document = process_drive_input(sys.argv[1])
    if None == document :
        print "***Error: Failed to process driver input in '",sys.argv[1]

    rtncode = run_external_app(document, sys.argv[2])
    if rtncode != 0:
        print "***Error: Failed to run application"

    print extract_results(document)

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print "Usage: "
        print __file__+" /path/to/input /path/to/parameters"

    drive(sys.argv[1], sys.argv[2])

