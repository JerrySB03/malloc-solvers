//Nepovinné, ale pravděpodobně se bude hodit hodit definovat následující funkce:
//  align()
//  debug_print()
//  pozn.:Při kompilaci přes `make debug` se programy skompilují s -DDEBUG
//        toto nadefinuje(-D) makro "DEBUG". V praxi můžete využít takto:
//
//   #ifdef DEBUG
//   #include <stdio.h>
//   #endif //DEBUG
//   ...
//
//   ...
//   #ifdef DEBUG
//     fprintf(stderr, "DEBUG PRINT %d", nejake_cislo);
//   #endif // DEBUG
//  popřípadně další, dle potřeby
