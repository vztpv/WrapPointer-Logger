# WrapPointer-Logger
    WrapPointer (Wrapper class for pointer)
    Code Example)
        class Node {
        public:
            int val;
            WrapPointer<Node> next;
        };
        WrapPointer<Node> testA;
        WrapPointer<Node> testc;
        testA->next = testC;
        testC->next = testA;
        testA.remove();
        testB.remove();
        
    Log Example) // A, B, C, D -> address?
        new = { A = { new = { B } } }
        new = { C = { new = { D } } }
        assign = { B = C }
        assign = { D = A }
        delete = { A }
        delete = { C }
      
