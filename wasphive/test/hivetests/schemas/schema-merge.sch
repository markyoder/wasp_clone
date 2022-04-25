
object_01
{
    MinOccurs = 1
    MaxOccurs = 1

    object_01_01
    {
        MinOccurs = 1
        MaxOccurs = 1

        param_aa_01
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = String
                ValEnums  = [ red orange yellow green blue indigo violet ]
            }
        }
    }
    object_01_02
    {
        MinOccurs = 1
        MaxOccurs = 1

        param_bb_01
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = String
            }
        }
        param_bb_02
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = String
            }
        }
        param_bb_03
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = String
            }
        }
    }
}

object_02
{
    MinOccurs = 1
    MaxOccurs = 1

    object_02_01
    {
        MinOccurs = 1
        MaxOccurs = 1

        param_cc_01
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = Int
                MinValInc = 0
                MaxValInc = 10
            }
        }
    }
    object_02_02
    {
        MinOccurs = 1
        MaxOccurs = 1

        param_dd_01
        {
            MinOccurs = 1
            MaxOccurs = 1
            value
            {
                MinOccurs = 1
                MaxOccurs = 1
                ValType   = String
                ExistsIn  = [ "../../../../object_01/object_01_02/param_bb_01"
                              "../../../../object_01/object_01_02/param_bb_02"
                              "../../../../object_01/object_01_02/param_bb_03" ]
            }
        }
    }
}
