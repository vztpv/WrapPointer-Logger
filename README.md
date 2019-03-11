# WrapPointer-Logger
    WrapPointer (Wrapper class for pointer)
    Code Example)
       WrapPointer<Node> x = WrapPointer<Node>::NewWithName("x", 3);
        WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);
        WrapPointer<Node> z;

        x->next = y;
        y->next = x;

        x.Delete();
        y.Delete();
        //x.Delete();

        x = WrapPointer<Node>::NewWithName("a", 3); 
        y = WrapPointer<Node>::NewWithName("b", 5);

        x->next = y;
        y->next = x;

        x.Delete();
        y.Delete();
    Log Example) // A, B, C, D -> address?
        New = { 
        1"x" = { 

        2"" = { }
        3"" = { }
        4"" = { }
         } } 

        NewFromOther = { 5"_x" = 1"x" }
        ReturnId = { 1"x" }
        New = { 
        1"y" = { 

        6"" = { }
        7"" = { }
        8"" = { }
         } } 

        NewFromOther = { 9"_y" = 1"y" }
        ReturnId = { 1"y" }
        delete = { 5"_x" }
        ReturnId = { 4"next" }
        ReturnId = { 3"child" }
        ReturnId = { 2"parent" }
        delete = { 9"_y" }
        ReturnId = { 8"next" }
        ReturnId = { 7"child" }
        ReturnId = { 6"parent" }
        New = { 
        1"a" = { 

        2"" = { }
        3"" = { }
        4"" = { }
         } } 

        NewFromOther = { 6"_a" = 1"a" }
        ReturnId = { 1"a" }
        assign = { 
        5"_x" = 6"_a"  
         } 
        ReturnId = { 6"_a" }
        New = { 
        1"b" = { 

        6"" = { }
        7"" = { }
        8"" = { }
         } } 

        NewFromOther = { 10"_b" = 1"b" }
        ReturnId = { 1"b" }
        assign = { 
        9"_y" = 10"_b"  
         } 
        ReturnId = { 10"_b" }
        delete = { 5"_x" }
        ReturnId = { 4"next" }
        ReturnId = { 3"child" }
        ReturnId = { 2"parent" }
        delete = { 9"_y" }
        ReturnId = { 8"next" }
        ReturnId = { 7"child" }
        ReturnId = { 6"parent" }
        ReturnId = { 9"_y" }
        ReturnId = { 5"_x" }

