# Style guide

This is style guide for RAPP-API contributors. 
You should use it for any new code that you would add to this project 
and try to format existing code to use this
style.

## Formatting

1. RAPP-API uses the Allman/BSD style of indentation.
2. Indent *with spaces*, not tabs.
3. Use *4 spaces per indent* (unless needed like `Makefile`).
4. Opening curly bracket is on the following line:

        // ✔:
        ```
        struct name
        {
            // code
        };
        
        void func()
        {
            // code
        }

        if (...)
        {
            // code
        }
        ```

        // ✗:
        ```
        void func() {
            // code
        }
        ```

5. Put space after `if`, `while` and `for` before conditions.

        // ✔:
        ```
        if () {}
        ```

        // ✗:
        ```
        if() {}
        ```

6. Put spaces before and after operators excluding increment and decrement;

        // ✔:
        ```
        int a = 1 + 2 * 3;
        a++;
        ```

        // ✗:
        ```
        int a=1+2*3;
        a ++;
        ```

7. Never put spaces between function name and parameters list.

        // ✔:
        ```
        func(args);
        ```

        // ✗:
        ```
        func (args);
        ```

8. Never put spaces after `(` and before `)`.
9. Always put space after comma and semicolon.

        // ✔:
        ```
        func(arg1, arg2);

        for (int i = 0; i < LENGTH; i++) {}
        ```

        // ✗:
        ```
        func(arg1,arg2);

        for (int i = 0;i<LENGTH;i++) {}
        ```

10. Function *Declaration parameters* should be aligned into new lines

        // ✔:
        ```
        func(
                param1,
                param2,
                param3
            );
        ```

        // ✗:
        ```
        func(param1, param2, param3);
        ```

11. Calling Functions with *multiple parameters* that would extend the line in width,
should be broken into new lines where and when possible:

        // ✔:
        ```
        func(param1,
             param2,
             func2(param3, param4),
             param5);
        ```

        // ✗:
        ```
        func(param1, param2, func2(param3, param4), param5);
        ```

12. Naming *class* members which are private should follow an underscore:
The only excpetion to this rule is `struct` when a public member is used.

        // ✔:
        ```
        class foo
        {
        private:
            int var_;
        };
        ```

        // ✗:
        ```
        class foo
        {
        private:
            int var;
        };
        ```

## Documentation

Document your code using [Doxygen][dox].

1. Documentation comment should use double star notation or tripple slash:

        // ✔:
        ```
        /// Some var
        int var;

        /**
         * Some func
         */
        void func();
        ```

2. Use slash as tag mark:

        // ✔:
        ```
        /**
         * \param a an integer argument.
         * \param s a constant character pointer.
         * \return The results
         */
        int foo(int a, const char *s);
        ```

## Naming

All names in code should be `small_snake_case`. No Hungarian notation is used.
Classes and structs names should not have capital letters.
Use namespaces (in C++) and class modules (in Node.JS).

## Directory Hierarchy

1. Use a class directory for each class file.
For example, class `foo` should be in `foo/foo.hpp`.
2. Use the same name for both definition headers and implementation files.
Do not break up the definition and implementation files into different locations.

    `foo/foo.hpp`
    `foo/foo.cpp`

3. Use only internal headers (`.ihh`) for including files.

    `foo/includes.ihh`

4. Only include what is absolutely nessesairy, minimising dependencies.
5. Do not polute the namespace or class definitions with various `#include`/`require`,
put all of them within your internal include header (`includes.ihh`/`includes.js`).


[dox]: http://www.stack.nl/~dimitri/doxygen/ "Doxygen homepage"
