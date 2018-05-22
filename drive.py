import subprocess, os, json
import wasp2py as w2py
#todo: follow Rob's driver schema and example to revise codes

def run_external_app(file_schema, file_extract_driver):
    #use ddi to generate dict of driver instruction
    #include: 1. name of external application; 
    #2. input of external application; 
    #3. run external application;
    #4. the complete logic for result extraction 
    instruction=w2py.get_json_dict(file_schema, file_extract_driver, ext="ddi" )
    external_app=instruction['application']['value'] #
    input_file=instruction['application']['input_file']['value'] #
    tmpl_file=instruction['application']['input_tmpl']['value'] #
    subprocess.call(['dprepro', 'params.in', tmpl_file,input_file, '>run.log'],shell=True, stdout=open(os.devnull, 'wb'))
    print "Running external simulation..."
    #Example:
    #os.system("python dakota_driver_test_demo.py input.i")
    os.system(external_app+ " " + input_file) 
    print "External simulation complete."
    return instruction

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
