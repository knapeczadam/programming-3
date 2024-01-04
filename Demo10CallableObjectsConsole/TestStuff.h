#pragma once

///////////////////////////////
// global namespace functions
///////////////////////////////

void Print(int nr);
void PrintTimes(int nr, int nrTimes);

//////////////
// Functor
//////////////

class PrintFunctor final
{
public:
    void operator()(int nr);
};

//////////////
// Test class
//////////////

class Test final
{
public:
    // constructor
    Test();
    Test(const Test&);
    Test(int value);

    // member functions
    void SetValue(int newValue);

    void IncrementValue();
    void DoubleValue();

    void Print() const;
    void PrintMultiplied(int multiplier) const;
    void PrintMultipliedTimes(int nrTimes, int multiplier) const;

    // static member function
    static void PrintNrObjects(int nrTimes);

private:
    static int m_NrObjects;
    int m_ID{};
    int m_Value{};
};

//////////////
// Alternative test class
//////////////

class Alternative final 
{
public:
    // constructor
    Alternative(int value);

    // member functions
    void Print() const;
    double OutputMultiplied(int nrTimes, double multiplier) const;

    void IncrementValue();
    void DoubleValue();

private:
    int m_Value{};
};
