existsin{

    validtest{
        defineone{
        }
        definetwo{
        }
        definethree{
        }
        useone{
            value{
                ExistsIn=[ "../../defineone/value"
                           "../../definetwo/value"
                           "../../definethree/value" ]
            }
        }
        usetwo{
            value{
                ExistsIn=[ EXTRA:"ford"
                           EXTRA:"chevy"
                           EXTRA:"bmw"
                           EXTRAREF:ReferencedColors
                           EXTRAREF:ReferencedNumbers
                           "../../defineone/value"
                           "../../definetwo/value"
                           "../../definethree/value" ]
            }
        }
        usethree{
            value{
                ExistsIn(Abs)=[ EXTRAREF:ReferencedNumbers
                                "../../definetwo/value" ]
            }
        }
        usefour{
            value{
                ExistsIn(Abs)=[ EXTRA:"hamburger"
                                EXTRA:"hotdog"
                                EXTRA:800
                                EXTRA:900
                                "../../defineone/value"
                                "../../definethree/value" ]
            }
        }
        usefive{
            value{
                ExistsIn(Abs)=[ EXTRAREF:ReferencedColors
                                "../../definetwo/value"
                                "../../definethree/value"
                                EXTRA:0
                                RANGE:[ 1200 1300 ]
                                RANGE:[ 1400 1500 ]
                                RANGE:[ 1600 1700 ]
                                RANGE:[ 1800 1900 ] ]
            }
        }
    }


    invalidtest{
        defineone{
        }
        definetwo{
        }
        definethree{
        }
        useone{
            value{
                ExistsIn=[ "../../defineone/value"
                           "../../definetwo/value"
                           "../../definethree/value" ]
            }
        }
        usetwo{
            value{
                ExistsIn=[ EXTRA:"ford"
                           EXTRA:"chevy"
                           EXTRA:"bmw"
                           EXTRAREF:ReferencedColors
                           EXTRAREF:ReferencedNumbers
                           "../../defineone/value"
                           "../../definetwo/value"
                           "../../definethree/value" ]
            }
        }
        usethree{
            value{
                ExistsIn(Abs)=[ EXTRAREF:ReferencedNumbers
                                "../../definetwo/value" ]
            }
        }
        usefour{
            value{
                ExistsIn=[ EXTRA:"hamburger"
                           EXTRA:"hotdog"
                           EXTRA:800
                           EXTRA:900
                           "../../defineone/value"
                           "../../definethree/value" ]
            }
        }
        usefive{
            value{
                ExistsIn=[ EXTRAREF:ReferencedColors
                           "../../definetwo/value"
                           "../../definethree/value"
                            EXTRA:0
                            RANGE:[ 1200 1300 ]
                            RANGE:[ 1400 1500 ]
                            RANGE:[ 1600 1700 ]
                            RANGE:[ 1800 1900 ] ]
            }
        }
        usesix{
            value{
                ExistsIn(BadFlag)=[ "../../defineone/value" ]
            }
        }
        useseven{
            value{
                ExistsIn=[ "../../defineone/value"
                           RANGE:[ 25 fifty ] ]
            }
        }
        useeight{
            value{
                ExistsIn=[ "../../defineone/value"
                           RANGE:[ 50 25 ] ]
            }
        }
        usenine{
            value{
                ExistsIn=[ "../../defineone/value"
                           RANGE:[ 25 50 100 ] ]
            }
        }
    }


}

ReferencedColors=[ red orange yellow green blue indigo violet ]
ReferencedNumbers=[ 1 2 3 4 5 ]
