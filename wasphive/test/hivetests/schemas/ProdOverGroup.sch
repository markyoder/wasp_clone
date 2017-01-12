prodovergroup{
    validtest{
        id{
        }
        container{
            id{
            }
            inside{
                ProdOverGroup("../..")=[ ComparePath="../id"
                                         GroupDivide=1000
                                         GroupProd=15199.8e-2 ]
            }
        }
        array{
            value{
                ProdOverGroup("../../..")=[ ComparePath="../../id"
                                            GroupDivide=10
                                            GroupProd=0.571781 ]
            }
        }
    }
    invalidtest{
        id{
        }
        container{
            id{
            }
            inside{
                ProdOverGroup("../..")=[ ComparePath="../id"
                                         GroupDivide=1000
                                         GroupProd=15199.8e-2 ]
            }
            badruleone{
                ProdOverGroup("../..")=[ 
                                        GroupDivide=1000
                                        GroupProd=107.6 ]
            }
            badruletwo{
                ProdOverGroup("../..")=[ ComparePath="../id"
                                        
                                        GroupProd=107.6 ]
            }
            badrulethree{
                ProdOverGroup("../..")=[ ComparePath="../id"
                                        GroupDivide=1000
                                       ]
            }
        }
        array{
            value{
                ProdOverGroup("../../..")=[ ComparePath="../../id"
                                            GroupDivide=10
                                            GroupProd=0.571781 ]
            }
        }
    }
}