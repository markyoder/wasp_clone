childatleastone{

    validtest{

        ChildAtLeastOne = [ one two/value three/value ]

        one{
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
        }
        five{
            ChildAtLeastOne=[ "../four" "../two/value" ]
        }
        six{
            value{
            }
        }
        seven{
            ChildAtLeastOne=[ "../six/value" ]
        }

    }

    invalidtest{

        ChildAtLeastOne = [ one two/value three/value ]

        one{
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
        }
        five{
            ChildAtLeastOne=[ "../four" ]
        }
        six{
            value{
            }
        }
        seven{
            ChildAtLeastOne=[ "../six/value" ]
        }

    }


}
