application{
    MinOccurs=1
    MaxOccurs=1
    InputTmpl="application"
    Description="specify path to executable, arguments, and input filename"
    value{
        MinOccurs=1
        MaxOccurs=1
        ValType=String
    }
    input_file{
        MinOccurs=1
        MaxOccurs=1
        InputTmpl="input_file"
        Description="specify application's input file name"
        value{
            MinOccurs=1
            MaxOccurs=1
            ValType=String
        }
    }
    input_tmpl{
        MinOccurs=1
        MaxOccurs=1
        InputTmpl="input_tmpl"
        Description="specify input template name"
        value{
            MinOccurs=1
            MaxOccurs=1
            ValType=String
        }
    }
}

extract_from{

    MinOccurs=1
    MaxOccurs=NoLimit
    InputTmpl="extract_from"
    Description="specify a file name and what data to extract from that file"
    value{
        MinOccurs=1
        MaxOccurs=1
        ValType=String
    }
    ChildExactlyOne[ find using ] 
    using{
        MinOccurs=0
        MaxOccurs=NoLimit
        InputTmpl="using"
        Description="specify a custom command for data extraction"
        value{
            MinOccurs=1
            MaxOccurs=1
            ValType=String
        }

    }
    find{

        MinOccurs=0
        MaxOccurs=NoLimit
        InputTmpl="find"

        InputVariants=[ "grab all lines containing a search pattern"
                        "grab either last line or last N lines"
                        ]

        ChildAtMostOne  = [ pattern between last_line ]
        ChildAtLeastOne = [ pattern between last_line column]

        pattern{
           MinOccurs=0
           MaxOccurs=1
           ValType=String
           InputTmpl="pattern"
           Description="grab all lines containing a search pattern"
        }
        last_line{
           MinOccurs=0
           MaxOccurs=1
           InputTmpl="last_line"
           Description="grab either last line or last N lines"
           value{
               MinOccurs=0
               MaxOccurs=1
               ValType=Int
           }
        }
        first_line{
           MinOccurs=0
           MaxOccurs=1
           InputTmpl="first_line"
           Description="grab either first line or first N line"
           value{
               MinOccurs=0
               MaxOccurs=1
               ValType=Int
           }
        }

        column{
            MinOccurs=0
            MaxOccurs=NoLimit
            InputTmpl="column"
            Description="grab specific columns"
            value{
                MinOccurs=1
                MaxOccurs=NoLimit
                ValType=Int
            }
            delimiter{
                MinOccurs=0
                MaxOccurs=1
                InputTmpl="delimiter"
                value{
                    MinOccurs=1
                    MaxOccurs=1
                    ValType=String
                }
            }
            as{
     			MinOccurs=0
      			MaxOccurs=1
      			InputTmpl="as"
      			value{
          			MinOccurs=1
          			MaxOccurs=1
          			ValType=String
      			}
 			}
        }

    }

}

