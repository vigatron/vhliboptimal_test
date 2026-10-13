#### DEBUG HowTo


Full memory status

```
arm-none-eabi-nm --print-size --size-sort --radix=d test_lib_optimal_CMB32H750HDM.elf | grep -iE ' [bcd] '
```


список секций
```
arm-none-eabi-objdump -h test_lib_optimal_STM32F4DISCOVERY.elf
```

Список функций

```
arm-none-eabi-nm -C --defined-only test_lib_optimal_STM32F4DISCOVERY.elf
```

