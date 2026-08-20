#### DEBUG HowTo


Full memory status

```
arm-none-eabi-nm --print-size --size-sort --radix=d test_lib_optimal_CMB32H750HDM.elf | grep -iE ' [bcd] '
```