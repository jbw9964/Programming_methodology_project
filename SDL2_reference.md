

## 0. Execution
Replace `{$FileName}`


- Mac os X
```bash
gcc {$FileName}.c -g -o {$FileName} -I /opt/homebrew/include -L /opt/homebrew/lib
```
```bash
g++ {$FileName}.c -g -o {$FileName} -I /opt/homebrew/include -L /opt/homebrew/lib
```

- Linux
```bash
gcc {$FileName}.c -g -o {$FileName} -I /usr/include/SDL2 -L /usr/lib
```
```bash
gcc {$FileName}.c -g -o {$FileName} -I /usr/include/SDL2 -lSDL2
```

## 1. `SDL2` library functions

