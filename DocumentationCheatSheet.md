## Code Documentation Cheat Sheet

Programmers, use this concise guide to help you quickly comment your code!

### Files
```c
/**
 * @file  ExampleFile.c
 * @brief Description stating the purpose of the file.
 *
 * @author   Bob Smith     bob@swag.com
 * @author   Jake Puggins  jake@swag.com
 *
 */
```

### Sections
```c
/////////////////////////////////////////////////////////////////////////////////////////
//
//                               Section Name
//
/////////////////////////////////////////////////////////////////////////////////////////
```

### Functions
```c
/**
 * Description about what the function does
 * and any notes for other developers.
 *
 * @author   Bob Smith     bob@swag.com
 * @author   Jake Puggins  jake@swag.com
 *
 * @param  ticks  amount of ticks for bot to travel
 * @param  speed  speed of motors while moving forwards
 *
 */
void forward(int ticks, int speed=80){ ... }
```

### In-Line
```c
// describe a line or group of lines
```

### Other Comment Commands

- **@warning** _warning for other developers_
- **@details** _more indepth description_
- **@todo** _something that needs to be done_
- **etc...**
http://www.stack.nl/~dimitri/doxygen/manual/commands.html
