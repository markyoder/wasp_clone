# Python import
import subprocess
import os
import json
import sys
import time
import threading
import re

# Workbench tools
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

    # Path to 'halite' engine for creating files from templates and json file
    template_engine = w2py.get_wasp_utility_path("halite")

    # Generate input file from template and Dakota parameters using halite
    input_file=document['application']['input_file']['value']
    tmpl_file=document['application']['input_tmpl']['value']
    args = "{} {} {} > {}".format(template_engine, tmpl_file, application_json_parameters, input_file)
    process = subprocess.check_output(args,shell=True)

    # Jobs are being submitted on a cluster using a scheduler. A submission 
    # script is generated from the 'scheduler_head' parameters provided by
    # the user in the *.drive file.
    if 'scheduler' in document.keys():
        # Get working directory and store it in 'document'
        document['working_dir'] = os.getcwd()
        # Get Dakota job id from workding directory and store it in 'document'
        document['job_id'] = document['working_dir'].split(".")[-1]
        # Store all information in 'submission_script.json' to generate
        # submission script
        submission_json_file = "submission_script.json"
        with open(submission_json_file, 'w') as outfile:
            f=json.dump(document, outfile, default=lambda o: o.__dict__)
        # Create the submission script from a template submission script using
        # halite
        input_file="submission_script"
        tmpl_file=os.path.dirname(__file__)+"/drive/templates/submission_script.tmpl"
        args = "{} {} {} > {}".format(template_engine, tmpl_file, submission_json_file, input_file)
        process = subprocess.check_output(args,shell=True)
        # Set 'external_app' to submit the submission script
        external_app = [str(document['scheduler']['submit_path']['value']), input_file]
        process = subprocess.Popen(external_app)
    # The jobs are not submitted to a schedule but run locally.
    else:
        external_app = document['application']['value']
        rtncode = os.system(external_app)
        if rtncode != 0:
            errorMsg = "Application could be run and returned code {} "
            raise IOError(errorMsg.format(rtncode))

    # The following is only run when using scheduler options in the drive file.
    # Look for 'exit_file_<id>.txt' file in the working directory. If not found,
    # the job on the scheduler has not completed and the python script needs to
    # be paused.
    if 'scheduler' in document.keys():
        isRunning = True
        exitFile = "exit_file_" + document['job_id'] + ".txt"
        exitFile = os.path.join(document['working_dir'], exitFile)
        while(isRunning):
            if os.path.isfile(exitFile):
                isRunning = False
            else:
                time.sleep(10)

def first_n_lines(str_file, n):
    #return the first n lines from a file as a list
    #if n > max line number, return all lines in the file
    lines=[]
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                line_count=0
                for line in islice(f, n):
                    lines.append(line)
                    line_count+=1
                if n > line_count :
                    print "Line index > max line number, return all lines!"
            except:
                print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
    return lines

def last_n_lines(str_file, n):
    #return the last n lines from a file as a list
    #if n > max line number, return all lines in the file
    lines=[]
    if os.path.exists(str_file):
        line_count = len(open(str_file).readlines())
        if n > line_count:
            lines=open(str_file).readlines()
            print "Line index > max line number, return all lines in file!"
        else:
            with open(str_file) as f:
                try:
                    lines=list(deque(f, maxlen=n))
                except:
                    print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
    return lines

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
                print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
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
                    print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
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
                elif int(end_n)==-1:#read the whole file if end_n=-1
                    lines=f.read();
                elif int(start_n)>int(end_n) and int(end_n)>0:
                    print "line index must be 0 < start_n <= end_n"
                    pass
                else:
                    for line in islice(f, start_n-1, end_n):
                        lines+=line
            except:
                print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"

    return lines

def between_patterns(str_file, start_pattern, end_pattern):
    #read between start_pattern and end_pattern from a file
    #return the lines in between
    section = ""
    if os.path.exists(str_file):
        with open(str_file) as f:
            try:
                content = f.read()
                # this method allows including multilines between
                # one pair of start-end patterns
                ends=[]
                for each_find in re.finditer(end_pattern, content):
                    #push all matched end_pattern into list
                    ends.append(each_find.start())
                for each_find in re.finditer(start_pattern, content):
                    #loop from each start_pattern
                    each_start=each_find.end()
                    if len(ends)>0:
                        #remove those matched ends before each start_pattern
                        while (each_start >= ends[0]):
                            ends.pop(0)
                        if len(ends)>0:
                            #add the matched section with one pair of [start:end]
                            section += content[each_start:ends[0]] \
                                        + ("\n" if (content[ends[0]-1] != "\n") else "")
                            ends.pop(0)#remove this matched end
            except:
                print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
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
                print "File reading error on" + os.getcwd()+ "/" + str_file +"!"
    else:
        print "No such file in "+ os.getcwd()+ "!"
    return lines

def print_column_error(idx_column):
    print "Column " + str(idx_column) + " is wrong or type mismatch!"

def line_count(line):
    if 'value' in line:
        return line['value']
    return 1

def extract_results(document):
    res_output=[]
    output_file=[]
    #demo for extraction.driver
    i=0;
    #process logic here
    for idx, extract in enumerate(document['extract_from']):
        output_file.append(extract['value'])
        if os.path.exists(extract['value']):
            # extract_file=open(output_file[i],"r")
            # reading file into string buffer, find in string buffer
            # vs. reading file at each find operation
            # which solution is better?
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
                            lines=between_lines(output_file[i],1,-1).strip().split("\n")
                            for each_line in lines:
                                for each_col in each_find["column"][0]["value"]:
                                    try:
                                        data=(each_line.strip().split(delimiter)[int(each_col)-1]).strip('\n')
                                        res_output.append(data)
                                    except:
                                        print_column_error(each_col)
                        if "first_line" in each_find:
                            int_line="-"+str(line_count(each_find['first_line']))
                            #extract lines
                            lines=first_n_lines(output_file[i],int(line_count(each_find['first_line'])))
                            str_lines=""
                            for each_line in lines:
                                str_lines+=each_line
                            res_output.append(str_lines)
                        if "last_line" in each_find:
                            int_line="-"+str(line_count(each_find['last_line']))
                            #extract lines
                            lines=last_n_lines(output_file[i],int(line_count(each_find['last_line'])))
                            str_lines=""
                            for each_line in lines:
                                str_lines+=each_line
                            res_output.append(str_lines)
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
                            print each_find["last_line"]
                            int_line="-"+str(line_count(each_find['last_line']))
                            delimiter=str(each_find["column"][0]["delimiter"]["value"])
                            #str_last_n_line=last_n_line(output_file[i],int(line_count(each_find['last_line'])))
                            str_last_n_lines=last_n_lines(output_file[i],int(line_count(each_find['last_line'])))
                            for each_line in str_last_n_lines:
                            #if str_last_n_line != "":
                                for each_column in each_find["column"]:
                                    try:
                                        data=(each_line.strip().split(delimiter)[int(each_column["value"][0])-1]).strip('\n')
                                        res_output.append(float(data))
                                    except:
                                        print_column_error(each_column["value"][0])
                        if ("column" in each_find) and ("first_line" in each_find):
                            int_line="-"+str(line_count(each_find['first_line']))
                            delimiter=str(each_find["column"][0]["delimiter"]["value"])
                            #str_first_n_line=first_n_line(output_file[i],int(line_count(each_find['first_line'])))
                            str_first_n_lines=first_n_lines(output_file[i],int(line_count(each_find['first_line'])))
                            for each_line in str_first_n_lines:
                            #if str_first_n_line != "":
                                for each_column in each_find["column"]:
                                    try:
                                        data=(each_line.strip().split(delimiter)[int(each_column["value"][0])-1]).strip('\n')
                                        res_output.append(float(data))
                                    except:
                                        print_column_error(each_column["value"][0])
                        if ("column" in each_find) and ("pattern" in each_find):
                            str_pattern=str(each_find["pattern"]['value'])
                            lines=grep_string(output_file[i],str_pattern).split('\n')
                            for each_line in lines:
                                if each_line!="":
                                    split = each_line.strip().split()
                                    for each_column in each_find["column"]:
                                        for single_col in each_column["value"]:#added for multi columns
                                            try:
                                                data = split[int(single_col)-1]
                                                res_output.append(float(data))
                                            except:
                                                print_column_error(each_column["value"][0])
                                
                        if ("column" in each_find) and ("between" in each_find):
                            str_pattern_start=str(each_find["between"]['value'][0])
                            str_pattern_end=str(each_find["between"]['value'][1])
                            lines=between_patterns(output_file[i], str_pattern_start, str_pattern_end).strip().split("\n")
                            #split search results with '\n' if multiple lines returned
                            for each_line in lines:
                                for each_column in each_find["column"]:
                                    try:
                                        data=(each_line.strip().split()[int(each_column["value"][0])-1]).strip('\n')
                                        res_output.append(float(data))
                                    except:
                                        print_column_error(each_column["value"][0])
        else:
            print "No such file: "+os.getcwd()+"/"+ extract['value'] + "!"

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

