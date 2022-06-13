#include <iostream>
#include <bitset>
#include <vector>

#define SECONDS_PER_YEAR (60 * 60 * 24 * 365)
#define SUM(a, b) a + b
#define MAX(a, b) (a >= b ? a : b)
#define BIT3 (01 << 3)
#define setBit(x, n) (x |= (1 << n))
#define clearBit(x, n) (x &= ~(1 << n))
#define clearBit0to3(x) (x &= (~0) << 4)
#define inverseBit(x, n) (x ^= (1 << n))

using namespace std;

extern void func1(void);
extern void func2(void);
extern void func3(void);
extern void func4(void);
extern void func5(void);

void func5()
{
    cout << "func5" << endl;
}

void func_pointer(int n)
{
    cout << endl
         << "func_pointer: " << endl;
    void (*func[5])() = {0, 0, 0, 0, func5};
    func[n - 1]();
}

void func_pointer2(int n)
{
    /* void main(int n)
    {
        if n==33 execute func1;
        if n==67 execute func2;
        if n==324 execute func3;
        if n==231 execute func4;
        if n==687 execute func5;
    } */
    // void (*f[7])() = {func4, func5, func3, 0, func2, func1, 0};
    // f[n%7]();
}

void set_and_clear_bit3()
{
    cout << endl
         << "set and clear bit3: " << endl;
    int a = 8;
    a |= BIT3;
    cout << a << endl;
    a &= ~BIT3;
    cout << a << endl;
}

void setPointer()
{
    int *ptr;
    ptr = (int *)0x67a9;
    *ptr = 0xAA;
}

void foo()
{
    unsigned int a = 6;
    int b = -20;
    cout << a + b << endl; // int -> unsigned int
    string s;
    s = (a + b > 6) ? ">6" : "<=6";
    cout << s << endl;
}

void foo_compzero()
{
    cout << endl
         << "compzero: " << endl;
    unsigned int zero = 0;
    unsigned int bad_compzero = 0xFFFF;
    unsigned int compzero = ~0;
    cout << bad_compzero << endl;
    cout << compzero << endl;
}

void foo_malloc()
{
    cout << endl
         << "malloc: " << endl;
    int *p1 = (int *)malloc(4 * sizeof(int)); // allocates enough for an array of 4 int
    int *p2 = (int *)malloc(sizeof(int[4]));  // same, naming the type directly
    int *p3 = (int *)malloc(4 * sizeof *p3);  // same, without repeating the type name

    if (p1)
    {
        for (int n = 0; n < 4; ++n) // populate the array
            p1[n] = n * n;
        for (int n = 0; n < 4; ++n) // print it back out
            printf("p1[%d] == %d\n", n, p1[n]);
    }
    free(p1);
    free(p2);
    free(p3);
    char *ptr;
    if ((ptr = (char *)malloc(0)) == NULL)
        cout << "NULL pointer" << endl;
    else
    {
        cout << ptr << endl;
        cout << "Valid pointer" << endl;
    }
}

int fun(int x) // pow of 2
{
    int count = 0;
    while (x)
    {
        count++;
        cout << (x &= (x - 1)) << endl;
    }
    return count;
}

void func()
{
    static int i = 0;
    i++;
    cout << i << endl;
}

void swap2(int &n1, int &n2)
{
    n1 ^= n2;
    n2 ^= n1;
    n1 ^= n2;
}

template <class T>
void swap1(T &x, T &y)
{
    T temp = x;
    x = y;
    y = temp;
}

void template_swap()
{
    cout << endl
         << "template_swap: " << endl;
    int a = 5, b = 3;
    double d1 = 3.4, d2 = 5.6;
    swap1(a, b);
    cout << a << " " << b << endl;
    swap2(a, b);
    cout << a << " " << b << endl;
    swap1(d1, d2);
    cout << d1 << " " << d2 << endl;
}

class base
{
public:
    void fun_1() { cout << "base-1\n"; }
    virtual void fun_2() { cout << "base-2\n"; }
    virtual void fun_3() { cout << "base-3\n"; }
    virtual void fun_4() { cout << "base-4\n"; }
};

class derived : public base
{
public:
    void fun_1() { cout << "derived-1\n"; }
    void fun_2() { cout << "derived-2\n"; }
    void fun_4(int x) { cout << "derived-4\n"; }
};

void virtual_function()
{
    cout << endl
         << "virtual_function: " << endl;
    base *p;
    derived obj1;
    p = &obj1;

    // Early binding because fun1() is non-virtual
    // in base
    p->fun_1();
    obj1.fun_1();
    // Late binding (RTP)
    p->fun_2();
    obj1.fun_2();
    // Late binding (RTP)
    p->fun_3();
    obj1.fun_3();
    // Late binding (RTP)
    p->fun_4();
    obj1.fun_4(0);
    // Early binding but this function call is
    // illegal(produces error) becasue pointer
    // is of base type and function is of
    // derived class
    // p->fun_4(5);
}

void int_pointer()
{
    cout << endl
         << "int_pointer: " << endl;
    int aa[5] = {1, 2, 3, 4, 5};
    int *p1 = aa + 1;
    int *p2 = (int *)&aa + 1; // error: (int *)(&aa+1)

    cout << *(aa + 1) << endl;
    cout << *(p1 + 1) << endl;
    cout << p1 << endl;
    cout << *p1 - 1 << endl;
    cout << *(p2 + 1) << endl;
    cout << *p2 << endl;
    cout << p2 + 1 << endl;
}

bool multipleOf3(int n)
{
    if (!n)
        return true;
    if (n < 3)
        return false;
    int even = 0, odd = 0;
    while (n != 0)
    {
        even += n & 1;
        n >>= 1;
        odd += n & 1;
        n >>= 1;
    }
    return multipleOf3(abs(even - odd));
}

void exchange_odd_and_even_bits(int x)
{
    cout << endl
         << "exchange_odd_and_even_bits: " << endl;
    x = (x & 0xaaaaaaaa) >> 1 | (x & 0x55555555) << 1;
    cout << bitset<32>(x) << endl;
}

void reverseString(string s)
{
    cout << endl
         << "reverseString: " << endl;
    int n = s.length();
    for (int i = 0; i < n / 2; i++)
    {
        swap(s[i], s[n - 1 - i]);
    }
    cout << s << endl;
}

void myPrime(int n)
{
    cout << endl
         << "myPrime: " << endl;
    bool notPrime[n + 1];
    for (int i = 2; i <= sqrt(n); i++)
        for (int j = i * i; j <= n; j += i)
            notPrime[j] = true;

    for (int i = 2; i <= n; i++)
    {
        if (!notPrime[i])
            cout << i << " ";
    }
    cout << endl;
}

int bitwise_compare(uint32_t a, uint32_t b)
{
    cout << endl
         << "bitwise_compare: " << endl;
    bitset<32> bits;
    uint32_t diff = a ^ b;
    if (!diff)
        return 0;

    // 001xxxxx -> 00100000
    diff |= diff >> 1;
    diff |= diff >> 2;
    diff |= diff >> 4;
    diff |= diff >> 8;
    diff |= diff >> 16;
    diff ^= diff >> 1;
    cout << bitset<32>(diff) << endl;

    return a & diff ? 1 : -1;
}

int main()
{
    int k = 0;
    const int *a;              // 一個 pointer，指向 const int 變數。
    int const *b;              // 一個 pointer，指向 const int 變數。
    int *const c = &k;         // 一個 const pointer，指向 int 變數。
    int const *const d = NULL; // 一個 const pointer，指向 const int 變數。

    // void(*(*papf)[3])(char *);
    typedef void (*pf)(char *);
    pf(*papf)[3];

    cout << endl
         << "SECONDS_PER_YEAR = " << SECONDS_PER_YEAR << endl;
    cout << endl
         << "SUM(2, 5) * 10 = " << SUM(2, 5) * 10 << endl;
    cout << endl
         << "MAX(2, 5) = " << MAX(2, 5) << endl;
    set_and_clear_bit3();
    cout << endl
         << "int -> unsigned int: " << endl;
    foo();
    foo_compzero();
    foo_malloc();
    cout << endl
         << "fun: " << endl
         << fun(15) << endl;
    cout << endl
         << "static variable in function: " << endl;
    for (int i = 0; i < 5; i++)
    {
        func();
    }
    template_swap();
    virtual_function();
    int_pointer();
    cout << endl
         << "multipleOf3: " << endl;
    cout << "45: " << multipleOf3(45) << endl;
    cout << "46: " << multipleOf3(46) << endl;
    cout << "47: " << multipleOf3(47) << endl;
    cout << "48: " << multipleOf3(48) << endl;
    exchange_odd_and_even_bits(0xA);
    reverseString("reverse");
    myPrime(1000);
    cout << bitwise_compare(15, 20) << endl;
    func_pointer(5);
    // func_pointer2(687);
}