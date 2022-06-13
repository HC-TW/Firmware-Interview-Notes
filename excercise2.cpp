#include <iostream>

using namespace std;

union StateMachine
{
	char character;
	int number;
	char *str;
};

typedef union
{
	unsigned long l;
	unsigned char c[4];
} EndianTest;

void f(int *p, int *q)
{
	p = q;
	*p = 2;
}

class Test
{
private:
	int x;
	int y;

public:
	Test(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	static void fun1() { cout << "Inside fun1()" << endl; }
	void fun2()
	{
		cout << "Inside fun2()" << endl;
		this->fun1();
	}
};

void foo_sizeof()
{
	char i[] = "Hello";
	char *p = (char *)1;
	int n = 10;
	printf("%lu %lu %lu\n", sizeof(i), sizeof(p), sizeof(n));
}

void foo_pointer_minus()
{
	int arr[] = {10, 20, 30, 40, 50};
	int *ptr1 = arr;
	int *ptr2 = arr + 5;
	cout << ptr1 << endl
		 << ptr2 << endl;
	printf("%ld\n", (ptr2 - ptr1));
	printf("%ld\n", (char *)ptr2 - (char *)ptr1);
}

void foo_pointer_plusplus()
{
	int arr1[] = {10, 20};
	int arr2[] = {10, 20};
	int arr3[] = {10, 20};
	int *p = arr1;
	int *q = arr2;
	int *r = arr3;
	++*p;
	*q++;
	*++r;
	printf("%d %d %d\n", arr1[0], arr1[1], *p);
	printf("%d %d %d\n", arr2[0], arr2[1], *q);
	printf("%d %d %d\n", arr3[0], arr3[1], *r);
}

void foo_pointer_advanced()
{
	char s[] = "0113256";
	char *p = s;
	printf("%c\n", *p++);	// 0
	printf("%c\n", *(p++)); // 1
	printf("%c\n", (*p)++); // 1, s = 0123256
	printf("%c\n", *++p);	// 3
	printf("%c\n", *(++p)); // 2
	printf("%c\n", ++*p);	// 3, s = 0123356
	printf("%c\n", ++(*p)); // 4, s = 0123456
	printf("%s\n", s);		// 0123456

	int ref[] = {8, 4, 0, 2};
	int *ptr;
	int index;
	for (index = 0, ptr = ref; index < 2; index++, ptr++)
		printf("%d %d\n", ref[index], *ptr);
	(*ptr++);
	printf("%d %d\n", ref[index], *ptr);

	/*
	int a; // An integer　
	int *a; // A pointer to an integer　
	int **a; // A pointer to a pointer to an integer　
	int a[10]; // An array of 10 integers　
	int *a[10]; // An array of 10 pointers to integers　 
	int (*a)[10]; // A pointer to an array of 10 integers　
	int (*a)(int); // A pointer to a function a that takes an integer argument and returns an integer　
	int (*a[10])(int); // An array of 10 pointers to functions that take an integer argument and return an integer
	*/
}

void foo_char_pointer()
{
	char *str[][2] =
		{"professor", "Justin",
		 "teacher", "Momor",
		 "student", "Caterpillar"};

	char str2[3][10] = {"professor", "Justin", "etc"};
	printf("%s\n", str[1][1]);
	printf("%c\n", str2[1][1]);
}

void foo_union()
{
	union StateMachine machine;
	machine.number = 1;

	printf("sizeof: %lu\n", sizeof(machine));
	printf("number: %d\n", machine.number);
}

void pass2DArray(int (*arr)[10])
{
	cout << arr[0][0] << endl;
}

void endianTest()
{
	EndianTest et;
	et.l = 0x12345678;
	printf("本系統位元組順序為：");
	if (et.c[0] == 0x78 && et.c[1] == 0x56 && et.c[2] == 0x34 && et.c[3] == 0x12)
	{
		printf("Little Endian\n");
	}
	else if (et.c[0] == 0x12 && et.c[1] == 0x34 && et.c[2] == 0x56 && et.c[3] == 0x78)
	{
		printf("Big Endian\n");
	}
	else
	{
		printf("Unknown Endian\n");
	}
	printf("0x%lx 在記憶體中的儲存順序：\n", et.l);
	for (int i = 0; i < 4; i++)
	{
		printf("%p : 0x%02x\n", &et.c[i], et.c[i]);
	}
}

void newArray(int **ptr, int size)
{
	*ptr = (int *) malloc(size * sizeof(int));
	(*ptr)[5] = 10; 
}

int main()
{
	Test obj;
	Test::fun1();
	obj.fun2();

	foo_sizeof();
	foo_pointer_minus();
	foo_pointer_plusplus();

	int i = 0, j = 1;
	f(&i, &j);
	printf("%d %d\n", i, j);

	foo_pointer_advanced();
	foo_char_pointer();
	foo_union();

	int a[5][10];
	a[0][0] = 0;
	a[0][1] = 0;
	a[1][0] = 1;
	pass2DArray(a + 1);

	char buf[] = "1011";
	long l = strtol(buf, NULL, 2);
	cout << l << endl;

	endianTest();
	int *ptr;
	newArray(&ptr, 10);
	cout << ptr[5] << endl;
	return 0;
}