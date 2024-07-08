#ifndef DATA_H
#define DATA_H

class Data 
{ 
private: 
    double operand;
    char operate;

public: 
    Data()      { operand = 0; operate = ' '; }
    Data(double operand1)    { operand = operand1; }
    Data(char operate1)      { operate = operate1; }
    Data(double operand1, char operate1)    { operand = operand1; operate = operate1; }

    double getOperand()     { return operand; }
    char getOperator()      { return operate; }

    void setOperand(double operand1)    { operand = operand1; }
    void setOperator(char operate1)     { operate = operate1; }
};

#endif
