# OOPWithC

## About

This repository tries to use and explain OOP concepts in C, that is Procedural Oriented, note that I don't know if this is a recommended way of doing things and all the things that are here were used for study purposes only.

## Class like Structs

Structs can already store variables inside it, like a integer, a double, a float, and all other types. But for it to behave like classes they need to store methods too.  

### What are methods

Methods methods are just functions that are stored inside the classes and can be run using them, it makes the code more readable because you know exactly what is using them.

### How methods are used in Structs

The way I've found of how to use methods in structs is using function pointers, function pointers are just pointers that holds the address to a function.

Example of a function pointer:

```C
// This points to a function that returns void and don't have any parameters
// The name "func" is the name of the variable and not of the function that will be executed
void (*func)();

// Here is the function that will be executed when we use the func()
void functionToPoint() 
{
    printf("Hello World");
}

// Attributing the address of the function to the func variable
func = &functionToPoint;
// Executing the function
func();
```

With that in mind we can create a Struct that will hold the value of the function pointer and use it that way:

```C
typedef struct 
{
    void (*func)();
} structWithFunction;

// The same function as before
void functionToPoint() 
{
    printf("Hello World");
}

// As said before, the func is just the name of the pointer
structWithFunction.func = &functionToPoint;

// Executing the function
structWithFunction.func();
```

And now we have structs that can hold functions

### Argument in function pointers

It's a common thing to add arguments to functions and we can do that too in function pointers, here is a overview:

```C
// A function pointer that don't have any argument
void (*func)();

// A function pointer that receives one int argument
void (*func)(int);

// A function pointer that receives one double argument
void (*func)(double);

// A function pointer that receives one int and one float argument
void (*func)(int, float);
```

And that's all for methods

## Constructors

Constructors are often used to create a object, and in C it will always be used. Why? Well because, as you saw before, you need to give the address to the function pointer, if not then it will not work.  

But constructors are just methods, if we can't use them inside a struct because of the function pointer, what can we do?

Well, simple, just don't create them inside the structs, like that:

Using the same example as before, we have:

```C
// The same function as before
void functionToPoint() 
{
    printf("Hello World");
}

typedef struct 
{
    void (*func)();
} structWithFunction;

// The constructor for the struct
// Note that it's written the name of the struct just to differenciate the functions names
structWithFunction_new(structWithFunction *this)
{
    // or (*this).func = &functionToPoint;
    this->func = &functionToPoint;
}


structWithFunction myStructWithMethods;
// Using the constructor
structWithFunction_new(&myStructWithMethods);

// Executing the function
structWithFunction.func();
```

With that we know that the constructor is just a function that receives a pointer to the struct and inside this function we initialize it, if using functions inside the struct always remember to pass the address to them.

## Getters and Setters

Another common thing to have in OOP are getters and setters and encapsulation. About encapsulation, I've found a good answer on what could be done for private variables on a Stack Overflow Answer ([Here is the stack overflow question and answer](https://stackoverflow.com/questions/2672015/hiding-members-in-a-c-struct)) but, for short, we can't stop someone from accessing a variable inside a struct but we can give a "alert" (like using the private name) and even make it a hard to access variable (like using a _ in the start).

Here's a example:

```C
struct bankAccount {
    // Here we have a public float variable
    float balance;

    // Here we have a private int variable
    int _private_accountId;
};
```

Getters and setters are totally possible using function pointers (because they are just functions that receives values and return values).

But we find our first problem here, the C language isn't object oriented and, because of that, it doesn't have a "this" keyword, but we can make our own.

Example:

For this example we will be using the previous code and add a int value one getter and setter for it

```C
// We use the typedef before, that way we can use the defined keyword inside the struct for the "this" keyword
typedef struct StructWithFunction StructWithFunction;

// The implementation of the set
void StructWithFunction_setSomeValue(StructWithFunction *this, int someValue) 
{
    // or (*this).someValue = someValue;
    this->someValue = someValue;
}

// The implementation of the get
int StructWithFunction_getSomeValue(StructWithFunction *this)
{
    // or (*this).someValue;
    return this->someValue;
}

struct StructWithFunction
{
    int someValue;
    // Here we will add the "this" keyword as a pointer to the struct
    /* 
     * In this function we are asking for the pointer   
     * of itself, that way we can access all the 
     * members inside it, and one int value 
    */
    void (*setSomeValue)(StructWithFunction *, int);
    /*
     * In this function we are asking for the pointer of itself that will be used for the this keyword and it will return some int value
    */
    int (*getSomeValue)(StructWithFunction *);
};

// The constructor for the struct
// Note that it's written the name of the struct just to differenciate the functions names
structWithFunction_new(structWithFunction *this)
{
    // or (*this).setSomeValue = &StructWithFunction_setSomeValue;
    this->setSomeValue = &StructWithFunction_setSomeValue;
    this->getSomeValue = &StructWithFunction_getSomeValue;
}


structWithFunction myStructWithMethods;
// Using the constructor
structWithFunction_new(&myStructWithMethods);

// Using set
myStructWithMethods.setSomeValue(&myStructWithMethods, 10);

// Using get
myStructWithMethods.getSomeValue(&myStructWithMethods);
```

Comment on This: Interestigly enough I think that the possibility to change the "this" keyword in a code is great for flexibility, even tough not recommended.

## Inheritance

Inheritence are often used to inherit some methods from a super class that will be used by other members. As expected we can't do something like that in a normal way, what It's possible to do is create a base parameter that receives a base class.

Example:

```C
// beep() implementation
void Vehicle_beep()
{
    puts("beep beep");
}

typedef struct Vehicle {
    // Every vehicle can do a beep sound
    void *(beep)();
} Vehicle;

// The Vehicle constructor
void Vehicle_newVehicle(Vehicle *this)
{
    this->beep = &Vehicle_beep;
}

// Car is a vehicle, so he will inherit all the methods of vehicle
typedef struct Car {
    // Here is the "inheritance"
    Vehicle base;
} Car;

// The Car constructor
void Car_newCar(Car *this)
{
    // Initializing the inherited vehicle to use the methods inside it
    Vehicle_newVehicle(&this->base);
}

Car car;
Car_newCar(&car);

// That's the way we can call the inherited method
car.base.beep();
```

## Strings

I know that Strings are not OOP only but it is something that is heavily used and don't have a good C support, even more because you need to set the size of the string to use it correctly, but what I want to talk here is not about strings in the ```char string[STRING_SIZE]``` way but the way that you don't acually need to set the size of the String.

Here is a full code explanation of the way to do it:

```C
/* 
 * char * is the same as char string
 * Because arrays are just a collection
 * Of pointers, but using this way we
 * Don't actually need to set a size for it
*/
char *string;

// You have to allocate one byte in memory and you will know why in a while
string = malloc(1);

/*
 * Reading a string without stoping
 * in the \n character and without needing
 * to say the size again
*/ 
scanf("%[^\n]s", string);
// Just remember to clear the buffer after the scanf
setbuf(stdin, NULL);

/*
 * Here is the main problem, if we do it
 * This way we will be having a memory overflow
 * Because the memory is not allocated for a string
 * In a random size, but with the dynamic allocation
 * We can solve this issue
*/

// Here is a way to do it
// PS: The realloc can be found in the stdlib.h
// And the strlen in the string.h
string = realloc(string, strlen(string) + 1);
/*
 * Quick explanation on what's happening here
 * To use realloc we need to, firt of all, already
 * have allocated some memory for it before and that's
 * why we use the malloc(1) in the second line. After
 * the string has been readed we can use it own value
 * to get the size of the string and, because it
 * already is a pointer, we can use it to find
 * the memory block that it was stored before
 * With that it becomes easy to realloc the memory
 * using the length of the string and adding 1 (for
 * the null character or '\0').
*/
```

## Decorators

Decorators are structures that can be used to initialize, do action, store some data, or anything in a "decorated way". If you already used Spring Boot in java you know about it because it's often used the decorator ``` @Autowired ``` or if you're developing APIs using JavaScript and TypeORM you can see a lot of ``` @Column ``` and that's decorators.

What I was looking for was something that I could use like this:

``` @InitializeCarClass(&car) Car car; ```

And, as expected, I've failed, but not totally, in fact I've found a way to do something similar but not so simplistic like that using Macros with arguments. Here's what I've found:

```C
#include <stdio.h>

// First I define a Macro that will be used like a Decorator
// I'm using _ because the C compiler can't actually accept a @ in a macro but you could use it with any character
#define _InitializeCarClass_(X) _InitializeCarClass__EXECUTE(&X);
/* 
 * After giving a name to the decorator 
 * (_InitializeCarClass_) I indicate that I want it to 
 * call the _InitializeCarClass__EXECUTE function,
 * make sure to create a function with this exact same
 * name if not, it will fail while compiles
*/

// The actual decorator action
void _InitializeCarClass__EXECUTE(Car *this)
{
    this->price = 275.00;
    this->seats = 5;
}

typedef struct car 
{
    float price;
    int seats;
} car;

int main(void)
{
    // This is the "Class" that will be used
    Car car;
    // Here is the decorator usage
    _InitializeCarClass_(car);

    // After that we can freely use the initialized class
    car.seats;
    return 0;
}
```
