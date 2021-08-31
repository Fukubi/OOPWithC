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

Another common thing to have in OOP are getters and setters and encapsulation. And here we have the first bad news, we can't have private members inside a struct so a fully encapsulated struct is impossible but the getters and setters are totally possible using function pointers (because they are just functions that receives values and return values).

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
