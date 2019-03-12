# WrapPointer-Logger
    WrapPointer (Wrapper class for pointer)
    Code Example)
        WrapPointer<Node> x = WrapPointer<Node>::NewWithName("x", 3);
        WrapPointer<Node> y = WrapPointer<Node>::NewWithName("y", 5);
        WrapPointer<Node> z("z");

        x->next = y;
        y->next = x;

        x.Delete();
        y.Delete();
        //x.Delete();

        x = WrapPointer<Node>::NewWithName("a", 3); 
        y = WrapPointer<Node>::NewWithName("b", 5);

        x->next = y;
        y->next = x;
        z = y;
        x.Delete();
        y.Delete();
        z.Delete();
    Log Example) // A, B, C, D -> address?
        New = { 
        1"x" = { 

        NewEmpty = { 2"" }
        NewEmpty = { 3"" }
        NewEmpty = { 4"" }
         } } 

        NewFromOther = { 5"_x" = 1"x" }
        ReturnId = { 1"x" }
        New = { 
        1"y" = { 

        NewEmpty = { 6"" }
        NewEmpty = { 7"" }
        NewEmpty = { 8"" }
         } } 

        NewFromOther = { 9"_y" = 1"y" }
        ReturnId = { 1"y" }
        NewEmpty = { 1"z" }
        access = { 5"_x" } 
        assign = { 
        4"next" = 9"_y"  
         } 
        access = { 9"_y" } 
        assign = { 
        8"next" = 5"_x"  
         } 
        delete = { 5"_x" }
        ReturnId = { 4"next" }
        ReturnId = { 3"child" }
        ReturnId = { 2"parent" }
        delete = { 9"_y" }
        ReturnId = { 8"next" }
        ReturnId = { 7"child" }
        ReturnId = { 6"parent" }
        New = { 
        2"a" = { 

        NewEmpty = { 3"" }
        NewEmpty = { 4"" }
        NewEmpty = { 6"" }
         } } 

        NewFromOther = { 7"_a" = 2"a" }
        ReturnId = { 2"a" }
        assign = { 
        5"_x" = 7"_a"  
         } 
        ReturnId = { 7"_a" }
        New = { 
        2"b" = { 

        NewEmpty = { 7"" }
        NewEmpty = { 8"" }
        NewEmpty = { 10"" }
         } } 

        NewFromOther = { 11"_b" = 2"b" }
        ReturnId = { 2"b" }
        assign = { 
        9"_y" = 11"_b"  
         } 
        ReturnId = { 11"_b" }
        access = { 5"_x" } 
        assign = { 
        6"next" = 9"_y"  
         } 
        access = { 9"_y" } 
        assign = { 
        10"next" = 5"_x"  
         } 
        assign = { 
        1"z" = 9"_y"  
         } 
        delete = { 5"_x" }
        ReturnId = { 6"next" }
        ReturnId = { 4"child" }
        ReturnId = { 3"parent" }
        delete = { 9"_y" }
        ReturnId = { 10"next" }
        ReturnId = { 8"child" }
        ReturnId = { 7"parent" }
        delete = { 1"z" }


