# WrapPointer-Logger
    WrapPointer (Wrapper class for pointer)
    Code Example)
        class Node {
        public:
            int val;
            WrapPointer<Node> next;
        };
        WrapPointer<Node> testA = WrapPointer<Node>::New();
        WrapPointer<Node> testC = WrapPointer<Node>::New();
        testA->next = testC;
        testC->next = testA;
        testA.Delete();
        testB.Delete();
        
    Log Example) // A, B, C, D -> address?
        new = { A = { B } }
        new = { C = { D } }
        assign = { B = C }
        assign = { D = A }
        delete = { A }
        delete = { C }
      
