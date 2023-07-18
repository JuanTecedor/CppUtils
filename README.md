# CppUtils

This project contains experimental C++20 headers.

## Vector

Mathematical vector (nothing to do with std::vector), supporting all basic operations (+, ., *, /), modulus, normalization, etc.

Useful for adding points in space, simulate positions, velocity and acceleration, etc.

Example:

```
Vector2i v1{1, -7};
Vector2i v2{-9, 13};
(v1 * v2) == -100;  // true
```
```
Vector2i v1{5, 1};
v.lengthSquared() == 26;  // true
v.length() == 5;  // true
```

```
Vector2i v1{1, -5};
Vector2i v2{-3, 7};
v1 -= v2;
v1 == Vector2i{4, -12} //  true;
```

```
Vector2i v4{8, -10};
v4 /= -2;
v4 == Vector2i{-4, 5};  // true
```

There are currently two implementations of the vector:
* Vector: Based in a std::array
* VectorTuple: Based in a std::tuple

The results at different optimization levels can be seen in Results.txt.

## Ostream redirector

Redirects the std::cout output to an internal stringstream. Normally used to test the output of another module.

Example:
```
int main()
{
    {
        std::cout << "normal output\n";
        auto os_redir = juan::OstreamRedirector();
        std::cout << "this does not print\n";
        std::printf("os_redir.get() = %s", os_redir.get().c_str());
    }
    std::cout << "normal output again";

    return 0;
}
```
```
Prints:
normal output
os_redir.get() = this does not print
normal output again
```
