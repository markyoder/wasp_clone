test{

    ChildCountEqual(IfExists) = [ one/value   two/value  three/value ]
    ChildCountEqual(EvenNone) = [ four/value  five/value six/value   ]

    badflags{
        inside{
            ChildCountEqual           = [ three/value six/value ]
            ChildCountEqual(BadFlag)  = [ one/value   four/value ]
        }
    }

    one{
        value{
        }
    }
    two{
        value{
        }
    }
    three{
        value{
        }
    }
    four{
        value{
        }
    }
    five{
        value{
        }
    }
    six{
        value{
        }
    }

}
