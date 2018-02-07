#include <iostream>
#include "waspson/SONInterpreter.h"
#include "waspcore/TokenPool.h"
#include "waspcore/TreeNodePool.h"
#include "waspson/SONInterpreter.h"
#include "waspson/SONNodeView.h"
#include "wasphive/HIVE.h"
#include "gtest/gtest.h"

using namespace wasp;

typedef TokenPool<unsigned int, unsigned int, unsigned int> TP;
typedef TreeNodePool<unsigned int, unsigned int, TP>        TNP;
typedef SONInterpreter<TNP>            SONInterp;
typedef SONNodeView<NodeView<TNP>> SONNV;

// macro to print a cleaner text diff if strings are different
#define EXPECT_JSON(EXPECTED, ACTUAL)                                       \
    EXPECT_TRUE(EXPECTED == ACTUAL)                                         \
        << "\nExpected JSON:\n"                                             \
        << "*********************" << EXPECTED << "*********************\n" \
                                                  "\nActual JSON:\n"        \
        << "*********************" << ACTUAL << "*********************\n"

TEST(SON2JSON, 001)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_json;

    son_schema << R"INPUT(

options{
    MaxOccurs=1
    fixed_fission_energy{
        MaxOccurs=NoLimit
    }
}

case{
    MaxOccurs=NoLimit

    title{
        MaxOccurs=1
    }

    lib{
        MaxOccurs=NoLimit
        files{
           MaxOccurs=NoLimit
           id{
             MaxOccurs=1
           }
           value{
               MaxOccurs=NoLimit
           }
        }
        path{
           MaxOccurs=1
        }
        unit{
           MaxOccurs=NoLimit
        }
    }

    time{
        MaxOccurs=NoLimit
        value{
            MaxOccurs=NoLimit
        }
    }
    power{
        MaxOccurs=1
        value{
            MaxOccurs=NoLimit
        }
    }
    mat{
        MaxOccurs=NoLimit
        units{
            MaxOccurs=1
        }
        idform{
            MaxOccurs=1
        }
    }

    print {
        MaxOccurs=1
        nuc {
            MaxOccurs=1
            sublibs{
                MaxOccurs=1
                value{
                    MaxOccurs=NoLimit
                }
            }
            units{
                MaxOccurs=1
                value{
                    MaxOccurs=NoLimit
                }
            }
            total{
                MaxOccurs=1
                value{
                    MaxOccurs=1
                }
            }
        }
        absfrac_sublib{
            MaxOccurs=1
            value{
                MaxOccurs=NoLimit
            }
        }
        fisrate{
            MaxOccurs=1
            value{
                MaxOccurs=NoLimit
            }
        }
        kinf{
            MaxOccurs=NoLimit
            value{
                MaxOccurs=1
            }
        }
    }

    save {
        MaxOccurs=NoLimit
        steps{
            MaxOccurs=1
            value{
                MaxOccurs=NoLimit
            }
        }
        file{
            MaxOccurs=1
            id{
                 MaxOccurs=1
            }
            value{
                MaxOccurs=1
            }
        }
    }
}

)INPUT";

    son_input << R"INPUT(

options {
    fixed_fission_energy(id_1)=1
    fixed_fission_energy(id_2)=2
}

case(1) {
    title="Cycle 1: Irradiation (1 MTU)"

    lib(lib1){
      files(something_1)=[ w17x17_one  w17x16_two w17x17_three ]
      files(something_2)=[ w17x17_four w17x16_five             ]
      unit=7
      unit=8
      unit=9
      path="some/path"
  }

    lib(lib2){
        files(something_1)=[ w17x17_one  w17x16_two w17x17_three ]
        path="some/path"
        files(something_2)=[ w17x17_four w17x16_five             ]
    }

    lib(lib3){
        path="some/path"
        files(something_1)=[ w17x17_one  w17x16_two w17x17_three ]
        files(something_2)=[ w17x17_four w17x16_five             ]
    }
    time(time_id_1)=[ 50 100 150 200 ]
    time(time_id_2)=[ 60 110 160 210 ]

    power(hello)=[ 15 15 15 15 ]

    mat(mat1) {
        units="grams"
        idform=123
    }
    mat(mat2) {
        units="kg"
        idform=456
    }

    print {
        nuc {
            sublibs=["ac"]
            units=["grams"]
            total=no
        }
        absfrac_sublib="ac"
        fisrate="abs"
        kinf(kinf_id_1)=yes
        kinf(kinf_id_2)=yes
    }

    save {
        steps=[ 1 2 3 4 ]
        file(file_id_1)="test_dump.f71"
    }
    save {
        steps=[ 5 6 7 8 ]
    }
}

)INPUT";

    expected_json << R"INPUT(
{
  "options":{
    "fixed_fission_energy":[
      {
        "_id":"id_1",
        "value":"1"
      },
      {
        "_id":"id_2",
        "value":"2"
      }
    ]
  },
  "case":[
    {
      "_id":"1",
      "title":{
        "value":"Cycle 1: Irradiation (1 MTU)"
      },
      "lib":[
        {
          "_id":"lib1",
          "files":[
            {
              "_id":"something_1",
              "value":[ "w17x17_one", "w17x16_two", "w17x17_three" ]
            },
            {
              "_id":"something_2",
              "value":[ "w17x17_four", "w17x16_five" ]
            }
          ],
          "unit":[
            {
              "value":"7"
            },
            {
              "value":"8"
            },
            {
              "value":"9"
            }
          ],
          "path":{
            "value":"some/path"
          }
        },
        {
          "_id":"lib2",
          "files":[
            {
              "_id":"something_1",
              "value":[ "w17x17_one", "w17x16_two", "w17x17_three" ]
            },
            {
              "_id":"something_2",
              "value":[ "w17x17_four", "w17x16_five" ]
            }
          ],
          "path":{
            "value":"some/path"
          }
        },
        {
          "_id":"lib3",
          "path":{
            "value":"some/path"
          },
          "files":[
            {
              "_id":"something_1",
              "value":[ "w17x17_one", "w17x16_two", "w17x17_three" ]
            },
            {
              "_id":"something_2",
              "value":[ "w17x17_four", "w17x16_five" ]
            }
          ]
        }
      ],
      "time":[
        {
          "_id":"time_id_1",
          "value":[ "50", "100", "150", "200" ]
        },
        {
          "_id":"time_id_2",
          "value":[ "60", "110", "160", "210" ]
        }
      ],
      "power":{
        "_id":"hello",
        "value":[ "15", "15", "15", "15" ]
      },
      "mat":[
        {
          "_id":"mat1",
          "units":{
            "value":"grams"
          },
          "idform":{
            "value":"123"
          }
        },
        {
          "_id":"mat2",
          "units":{
            "value":"kg"
          },
          "idform":{
            "value":"456"
          }
        }
      ],
      "print":{
        "nuc":{
          "sublibs":{
            "value":[ "ac" ]
          },
          "units":{
            "value":[ "grams" ]
          },
          "total":{
            "value":"no"
          }
        },
        "absfrac_sublib":{
          "value":[ "ac" ]
        },
        "fisrate":{
          "value":[ "abs" ]
        },
        "kinf":[
          {
            "_id":"kinf_id_1",
            "value":"yes"
          },
          {
            "_id":"kinf_id_2",
            "value":"yes"
          }
        ]
      },
      "save":[
        {
          "steps":{
            "value":[ "1", "2", "3", "4" ]
          },
          "file":{
            "_id":"file_id_1",
            "value":"test_dump.f71"
          }
        },
        {
          "steps":{
            "value":[ "5", "6", "7", "8" ]
          }
        }
      ]
    }
  ]
}
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_TRUE(HIVE::input_to_json(schema_root, input_root, root_level,
                                    last_level_printed, actual_json,
                                    actual_errors));

    EXPECT_TRUE(actual_errors.str() == "");

    EXPECT_JSON(expected_json.str(), actual_json.str());
}

TEST(SON2JSON, 002)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_json;

    son_schema << R"INPUT(

obj_multi_one{
  MaxOccurs=NoLimit
  id{ MaxOccurs=1 }
  flag{
    MaxOccurs=NoLimit
    value{
      MaxOccurs=1
    }
  }
}

obj_multi_two{
  MaxOccurs=NoLimit
  array{
    MaxOccurs=NoLimit
    id{
      MaxOccurs=1
    }
    value{
      MaxOccurs=NoLimit
    }
  }
}

singleflag1{
 MaxOccurs=1
 value{
  MaxOccurs=1
 }
}

singleflag2{
 MaxOccurs=1
 value{
  MaxOccurs=2
 }
}

singleflag3{
 MaxOccurs=1
 value{
  MaxOccurs=2
 }
}

)INPUT";

    son_input << R"INPUT(

obj_multi_one(real_id){
    id=fake_id
    flag=one
    flag=two
    flag=three
}

singleflag1=val1

obj_multi_two{
  array(id_1)=[ 11 12 13 ]
  array(id_2)=[ 21 22 23 ]
}


obj_multi_one{
    flag=four
    flag=five
    flag=six
}

singleflag2=val2

obj_multi_two{
  array(id_3)=[ 31 32 33 ]
  array(id_4)=[ 41 42 43 ]
}

obj_multi_one{
    flag=seven
    flag=eight
    flag=nine
}

obj_multi_two{
  array(id_5)=[ 51 52 53 ]
  array(id_6)=[ 61 62 63 ]
}

singleflag3(sf3_id)=[ val3 val4 ]

)INPUT";

    expected_json << R"INPUT(
{
  "obj_multi_one":[
    {
      "_id":"real_id",
      "id":{
        "value":"fake_id"
      },
      "flag":[
        {
          "value":"one"
        },
        {
          "value":"two"
        },
        {
          "value":"three"
        }
      ]
    },
    {
      "flag":[
        {
          "value":"four"
        },
        {
          "value":"five"
        },
        {
          "value":"six"
        }
      ]
    },
    {
      "flag":[
        {
          "value":"seven"
        },
        {
          "value":"eight"
        },
        {
          "value":"nine"
        }
      ]
    }
  ],
  "singleflag1":{
    "value":"val1"
  },
  "obj_multi_two":[
    {
      "array":[
        {
          "_id":"id_1",
          "value":[ "11", "12", "13" ]
        },
        {
          "_id":"id_2",
          "value":[ "21", "22", "23" ]
        }
      ]
    },
    {
      "array":[
        {
          "_id":"id_3",
          "value":[ "31", "32", "33" ]
        },
        {
          "_id":"id_4",
          "value":[ "41", "42", "43" ]
        }
      ]
    },
    {
      "array":[
        {
          "_id":"id_5",
          "value":[ "51", "52", "53" ]
        },
        {
          "_id":"id_6",
          "value":[ "61", "62", "63" ]
        }
      ]
    }
  ],
  "singleflag2":{
    "value":[ "val2" ]
  },
  "singleflag3":{
    "_id":"sf3_id",
    "value":[ "val3", "val4" ]
  }
}
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_TRUE(HIVE::input_to_json(schema_root, input_root, root_level,
                                    last_level_printed, actual_json,
                                    actual_errors));

    EXPECT_TRUE(actual_errors.str() == "");

    EXPECT_JSON(expected_json.str(), actual_json.str());
}

TEST(SON2JSON, 003)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_json;

    son_schema << R"INPUT(

exp_id_one{
 MaxOccurs=1
}

exp_id_two{
 MaxOccurs=NoLimit
 value{
    MaxOccurs=NoLimit
 }
}

exp_id_three{
 MaxOccurs=1
 id{
  MaxOccurs=1
 }
 exp_id_one{
  MaxOccurs=1
 }
 exp_id_two{
  MaxOccurs=NoLimit
 }
}

exp_id_four{
 MaxOccurs=2
 id{
  MaxOccurs=1
 }
 exp_id_one{
  MaxOccurs=1
 }
 exp_id_two{
  MaxOccurs=NoLimit
 }
}

outer_one{
 MaxOccurs=1
 inner_one{
     MaxOccurs=1
   flag_one{
     MaxOccurs=1
     value{
       MaxOccurs=NoLimit
     }
   }
  value{ MaxOccurs=1 }
 }
}

outer_two{
 MaxOccurs=1
 value{
  MaxOccurs=NoLimit
 }
 flag_two{
   MaxOccurs=1
 }
}

)INPUT";

    son_input << R"INPUT(

exp_id_one(id1)=one

exp_id_two(id2)=[ two twotwo twotwotwo ]
exp_id_two(id22)=three

exp_id_three(id3){
 id=idthree
 exp_id_one(id1)=one
 exp_id_two(id2)=two
 exp_id_two(id22)=three
}

exp_id_four(id44){
 id=idthree
 exp_id_one(id1)=one
 exp_id_two(id2)=two
 exp_id_two(id22)=three
}

exp_id_four(id44){
 id=idthree
 exp_id_one(id1)=one
 exp_id_two(id2)=two
 exp_id_two(id22)=three
}

outer_one{
 inner_one(89){ flag_one=9 value(1)=123  }
}
outer_two{
 flag_two=99
 value(11)=456 value(12)=789
}

)INPUT";

    expected_json << R"INPUT(
{
  "exp_id_one":{
    "_id":"id1",
    "value":"one"
  },
  "exp_id_two":[
    {
      "_id":"id2",
      "value":[ "two", "twotwo", "twotwotwo" ]
    },
    {
      "_id":"id22",
      "value":[ "three" ]
    }
  ],
  "exp_id_three":{
    "_id":"id3",
    "id":{
      "value":"idthree"
    },
    "exp_id_one":{
      "_id":"id1",
      "value":"one"
    },
    "exp_id_two":[
      {
        "_id":"id2",
        "value":"two"
      },
      {
        "_id":"id22",
        "value":"three"
      }
    ]
  },
  "exp_id_four":[
    {
      "_id":"id44",
      "id":{
        "value":"idthree"
      },
      "exp_id_one":{
        "_id":"id1",
        "value":"one"
      },
      "exp_id_two":[
        {
          "_id":"id2",
          "value":"two"
        },
        {
          "_id":"id22",
          "value":"three"
        }
      ]
    },
    {
      "_id":"id44",
      "id":{
        "value":"idthree"
      },
      "exp_id_one":{
        "_id":"id1",
        "value":"one"
      },
      "exp_id_two":[
        {
          "_id":"id2",
          "value":"two"
        },
        {
          "_id":"id22",
          "value":"three"
        }
      ]
    }
  ],
  "outer_one":{
    "inner_one":{
      "_id":"89",
      "flag_one":{
        "value":[ "9" ]
      },
      "value":{
        "_id":"1",
        "value":"123"
      }
    }
  },
  "outer_two":{
    "flag_two":{
      "value":"99"
    },
    "value":[
      {
        "_id":"11",
        "value":"456"
      },
      {
        "_id":"12",
        "value":"789"
      }
    ]
  }
}
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_TRUE(HIVE::input_to_json(schema_root, input_root, root_level,
                                    last_level_printed, actual_json,
                                    actual_errors));

    EXPECT_TRUE(actual_errors.str() == "");

    EXPECT_JSON(expected_json.str(), actual_json.str());
}

TEST(SON2JSON, 004)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_json;

    son_schema << R"INPUT(

mixed_one{
    MaxOccurs=1
    value{
        MaxOccurs=NoLimit
    }
    three{
        MaxOccurs=1
        value{
            MaxOccurs=1
        }
    }
}

mixed_two{
    MaxOccurs=1
    value{
        MaxOccurs=NoLimit
    }
    three{
        MaxOccurs=NoLimit
        value{
            MaxOccurs=1
        }
    }
}

mixed_three{
    MaxOccurs=1
    value{
        MaxOccurs=NoLimit
    }
    three{
        MaxOccurs=NoLimit
        value{
            MaxOccurs=NoLimit
        }
        seven{
            MaxOccurs=1
            value{
                MaxOccurs=NoLimit
            }
        }
    }
}

)INPUT";

    son_input << R"INPUT(

mixed_one   = [ 1 2 three=four 5 ]

mixed_two   = [ 1 2 three=four three='a "sentence" with "quotes" here' 6 ]

mixed_three = [ 1 2 three="four" three=[ five six seven=[ 8 9 ] ] 10 ]

)INPUT";

    expected_json << R"INPUT(
{
  "mixed_one":{
    "value":[ "1", "2", "5" ],
    "three":{
      "value":"four"
    }
  },
  "mixed_two":{
    "value":[ "1", "2", "6" ],
    "three":[
      {
        "value":"four"
      },
      {
        "value":"a 'sentence' with 'quotes' here"
      }
    ]
  },
  "mixed_three":{
    "value":[ "1", "2", "10" ],
    "three":[
      {
        "value":[ "four" ]
      },
      {
        "value":[ "five", "six" ],
        "seven":{
          "value":[ "8", "9" ]
        }
      }
    ]
  }
}
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_TRUE(HIVE::input_to_json(schema_root, input_root, root_level,
                                    last_level_printed, actual_json,
                                    actual_errors));

    EXPECT_TRUE(actual_errors.str() == "");

    EXPECT_JSON(expected_json.str(), actual_json.str());
}

TEST(SON2JSON, error_001)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_errors;

    son_schema << R"INPUT(

object{
    MaxOccurs=1
    level{
        MaxOccurs=1
        parameter{
            MaxOccurs=1
        }
        parameter{
            MaxOccurs=NoLimit
        }
    }
}

)INPUT";

    son_input << R"INPUT(

object{
    level{
        parameter=123
    }
}

)INPUT";

    expected_errors
        << R"INPUT(***ERROR: /object/level/parameter exists multiple times in schema.
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_FALSE(HIVE::input_to_json(schema_root, input_root, root_level,
                                     last_level_printed, actual_json,
                                     actual_errors));

    EXPECT_TRUE(expected_errors.str() == actual_errors.str());
}

TEST(SON2JSON, error_002)
{
    std::stringstream son_schema;
    std::stringstream son_input;
    std::stringstream expected_errors;

    son_schema << R"INPUT(

object{
    MaxOccurs=1
    level{
        MaxOccurs=1
        parameter{
            MaxOccurs=1
        }
    }
}

)INPUT";

    son_input << R"INPUT(

object{
    level{
        not_in_schema=123
    }
}

)INPUT";

    expected_errors
        << R"INPUT(***ERROR: /object/level/not_in_schema does not exist in schema.
)INPUT";

    // parse schema
    SONInterp schema_interp(std::cerr);
    ASSERT_TRUE(schema_interp.parse(son_schema));

    // save schema root
    SONNV schema_root = schema_interp.root();

    // parse input
    SONInterp input_interp(std::cerr);
    ASSERT_TRUE(input_interp.parse(son_input));

    // save input root
    SONNV input_root = input_interp.root();

    // covert to json save in actual_json
    std::stringstream actual_json;
    std::stringstream actual_errors;
    int               root_level         = 0;
    int               last_level_printed = -1;
    ASSERT_FALSE(HIVE::input_to_json(schema_root, input_root, root_level,
                                     last_level_printed, actual_json,
                                     actual_errors));

    EXPECT_TRUE(expected_errors.str() == actual_errors.str());
}