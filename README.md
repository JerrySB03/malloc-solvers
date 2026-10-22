# Zadání - vlastní heap alokátor
Vytvořte vlastní heap alokátor v programovacím jazyce C který imlementuje následující header file:
```c
void *OSE_malloc(size_t size);
void OSE_free(void *p);
void *OSE_realloc(void *p, size_t size);
```

Pro implementaci nepoužívejte funkce `malloc`, `free` a `realloc` ze standardní C knihovny ani jiné alokační funkce z jiných knihoven.
Funkce z knihoven `<string.h>` a `sys/mman.h` jako třeba `mmap`, `munmap`, `memcmp`, `memcpy` můžete použít. 

Tyto 3 funkce společně tvoří základ heap alokace v programovacím jazyce C, další jazyky používají obdobné funkce. I jazyky jako je třeba Python kde neupravujete přímo paměť mají své vlastní implementace. Například v CPythonu jsou funkce `PyMem_Free()`,`PyMem_Malloc()`, `PyMem_Realloc()`.

### malloc
```c
void *OSE_malloc(size_t size);
```
Funkce `malloc` dynamicky alokuje heap pamět z virtuálního adresního prostoru a vrátí pointer s minimální velikostí `size`.
 - Může vrátit `NULL`, což signalizuje chybu při alokaci.
 - Adresa, kterou `malloc` vrátí bude zarovnána na násobek 16 bajtů. 

### free
```c
void OSE_free(void *p);
```
`free` uvolní paměť po alokaci přes `malloc`.
 - Pokud `p == NULL`, nic se neděje.
 - Když je `free` zavolán s pamětí která nebyla alokována přes `malloc` chování je nedefinované.

### realloc
Není nutná speciální implementace, zjednodušená implementace může vypadat takto v pseudokódu:
```python
realloc(old_p, new_size):
    new_p = malloc(new_size)
    if new_p == NULL:
        return NULL

    old_size = read_size(old_p)
    copy min(old_size, new_size) bytes from old_p to new_p
    free(old_p)

    return new_p
```

 - Pokud `p == NULL` tak se `realloc` chová stejně jako `malloc`.
 - Pokud `realloc` selže vrátí `NULL` a data na adrese`p` zůstávají nezměněna.

## Reference
Zadání je zjednodušený standard libc `malloc`, který je dostupný [zde](https://man7.org/linux/man-pages/man3/malloc.3.html).

