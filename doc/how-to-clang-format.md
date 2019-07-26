# How to clang-format

```bash
find src/ -iname *.h -o -iname *.c | xargs /opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i -style=file
find test/ -iname *.h -o -iname *.c | xargs /opt/rh/llvm-toolset-7/root/usr/bin/clang-format -i -style=file
```
