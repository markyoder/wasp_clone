/*
 * File:   HIVE.cpp
 * Author: Brandon Langley, Robert Lefebvre (migrated to WASP)
 *
 * Created on September 17, 2014, 8:19 PM
 */

#include "HIVE.h"

#include "wasphive/AlphaNum.h" // special alpha numeric sort logic

using namespace std;

static const std::atomic<bool> GLOBAL_STOP( false );

namespace wasp
{
const float HIVE::SUMERROR=.01;
const float HIVE::PRODERROR=.01;
const float HIVE::MAXERRORS=100;
const float HIVE::MAXENUMERRORCOUNT=6;

HIVE::HIVE() : stop( GLOBAL_STOP ) {
}

HIVE::HIVE( const std::atomic<bool> &stop ) : stop( stop ) {
}

HIVE::~HIVE() {
}
void HIVE::sort_errors(std::vector<string> &errors)
{
    std::sort(errors.begin(), errors.end(), doj::alphanum_less<std::string>());
}

void HIVE::printMessages(bool pass, vector<string>&errors,
                                        bool xmloutput, string file, std::ostream&output){

    if (!xmloutput){
        output << endl << (file!=""?file:"N/A") << " - " << (pass?"PASS":"FAIL")  << endl;
        output << "-------------------------------------------------------------" << endl;
        for (int i = 0; i < errors.size(); i++){
            output << errors[i] << endl;
        }
    }

    else{
        output << "  <file name=\"" << (file!=""?file:"N/A") << "\"";
        output <<        " pass=\"" << (pass?"true":"false") << "\"";
        output <<        " errors=\"" << errors.size();
        output << (errors.size()==0?"\"/>":"\">") << endl;
        for (int i = 0; i < errors.size(); i++){
            std::size_t foundline;
            std::size_t foundcolumn;
            std::size_t founddash;
            string line;
            string column;
            string message;
            foundline = errors[i].find("line:");
            foundcolumn = errors[i].find(" column:");
            founddash = errors[i].find(" - ");
            if (foundline   == string::npos ||
                foundcolumn == string::npos ||
                founddash   == string::npos ||
                foundline   != 0            ){
                line = "N/A";
                column = "N/A";
                message = errors[i];
            }
            else{
                line = errors[i].substr(foundline+5, foundcolumn-(foundline+5));
                column = errors[i].substr(foundcolumn+8, founddash-(foundcolumn+8));
                message = errors[i].substr(founddash+3);
            }
            output << "    <error id=\"" << i+1 << "\">" << endl;
            output << "      <location line=\"" << line << "\"";
            output <<                " column=\"" << column << "\"/>" << endl;
            output << "      <message>" << message << "</message>" << endl;
            output << "    </error>" << endl;
            if (i+1 == errors.size()) output << "  </file>" << endl;
        }
    }

}

} //namespace wasp
