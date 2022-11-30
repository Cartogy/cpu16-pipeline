# Implementing Control unit

I need to implement the control unit.
I can create a component that can have different control implementations.

```
Base:
    ControlUnit
        - bit_info


Derive:
    ControlUnit16
        - bit_info
    
```

# Parameterized Tests

I notice that for the pipeline stages, there is duplicate code that is tedious.
I need to figure out how to use parametrized tests in Google's testing framework.

http://www.ashermancinelli.com/gtest-type-val-param

This link has given me an idea as to how I can implement this behaviour in my test.
