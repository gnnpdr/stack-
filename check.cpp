#include <stdio.h>

#include "check.h"

void dump(Stack* stk)
{
    assert(stk != nullptr);

    printf("%s [%x]\n",stk->name, stk);  //можно ли сделать так, чтобы название типа данных (Stack), передавалось автоматически? #stk?

    printf("called from %s: %d (%s)\n", stk->file, stk->code_str, stk->func);
    printf("name %s born at %s: %d (%s)\n", stk->origin_file, stk->origin_str, stk->origin_func);

    printf("{\nleft canary  = %x\n", );  //дописать значение hexspeak

    printf("array data address %p\n", stk->data);
    printf("capacity %d\n", stk->capacity);

    for (int i = 0; i < stk->size; i++)
    {
        printf("element №%d value %lf\n", i, stk->data[i]);
        printf("element №%d address %p\n", i, stk->data + i);
    }
}

int errors(Stack* stk)
{
    assert(stk != nullptr);

    if (stk->capacity <= 0)
        return NO_PLACE;

    if (stk->size > stk->capacity)
        return ARRAY_LIMIT_PROBLEM;

    for (int i = 0; i < stk->size; i++)
    {
        if (*(stk->data + i) == 0)  //проверка, конечно, не очень, ведь мы ограничиваем диапазон возможных значений. Можно ли заполнить все нанами или типа того?
            return FILLING_PROBLEM;
    }
}

void stack_assert_func(Stack* stk) // хочется, чтобы именно эта функция принимала текущее занчение файла и тд
{
    assert(stk != nullptr);

    stk->CurrentData.file = __FILE__; //так будет работать? эахватит изначальный файл иди обратится именно к функции stack_assert?
    stk->CurrentData.func = __func__;
    stk->CurrentData.code_str = __LINE__;

    if (errors(stk) != ALL_RIGHT)
    {
        dump(stk);
        assert(0);                  //я прописала конкретные проблемы в enum, как это можно использовать? как код ошибки?
    }
}