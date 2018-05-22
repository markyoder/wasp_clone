import subprocess, os, json

import wasp2py as w2py
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

def extract_results(document):
    res_output=[]
    output_file=[]
    #demo for extraction.driver
    i=0;
    #process logic here
    for idx, extract in enumerate(document['extract_from']):
        output_file.append(extract['value'])

        for each_find in extract['find']:
         if len(each_find)==1: #one line of extraction command only
             if "column" in each_find:
                 delimiter=str(each_find["column"][0]["delimiter"]["value"])
                 for each_col in each_find["column"][0]["value"]:
                     res_output.append(float(subprocess.check_output("head -1 " + output_file[i] \
                         + " | awk -F\"" + delimiter +"\" '/1/ {print $" + str(each_col) + "}'",shell=True).strip('\n')))
             if "first_line" in each_find:
                 int_line="-"+str(each_find["first_line"]['value'])
                 #extract the whole line
                 res_output.append(str(subprocess.check_output("head "+int_line + " " + output_file[i] + "| tail -1" \
                     ,shell=True).strip('\n')))
             if "last_line" in each_find:
                 int_line="-"+str(each_find["last_line"]['value'])
                 #extract the whole line
                 res_output.append(str(subprocess.check_output("tail "+int_line + " " + output_file[i] + "| head -1" \
                     ,shell=True).strip('\n')))
             if "pattern" in each_find:
                 str_pattern=str(each_find["pattern"]['value'])
                 #extract the whole line
                 res_output.append(str(subprocess.check_output("grep " + str_pattern + " " + output_file[i] \
                     ,shell=True).strip('\n')))                
             if "between" in each_find:
                 str_tmp="" #todo
         elif len(each_find)==2: #two layers of extraction command
             if ("column" in each_find) and ("last_line" in each_find):
                 int_line="-"+str(each_find["last_line"]['value'])
                 for each_column in each_find["column"]:
                     res_output.append(float(subprocess.check_output("tail "+int_line + " " + output_file[i] +" | head -1" \
                         + " | awk '{print $" + str(each_column["value"][0]) + "}'",shell=True).strip('\n')))
             if ("column" in each_find) and ("first_line" in each_find):
                 int_line="-"+str(each_find["first_line"]['value'])
                 for each_column in each_find["column"]:
                     res_output.append(float(subprocess.check_output("head "+int_line + " " + output_file[i] + "| tail -1" \
                         + " | awk '{print $" + str(each_column["value"][0]) + "}'",shell=True).strip('\n')))
             if ("column" in each_find) and ("pattern" in each_find):
                 str_pattern=str(each_find["pattern"]['value'])
                 for each_column in each_find["column"]:
                     res_output.append(float(subprocess.check_output("grep " + str_pattern + " " + output_file[i] \
                         + "| head -n 1 | awk '{print $" + str(each_column["value"][0]) + "}'",shell=True).strip('\n')))
             if ("column" in each_find) and ("between" in each_find):
                 str_tmp=""#todo

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

