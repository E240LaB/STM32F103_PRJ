#include <sys/stat.h>
#include <errno.h>
#undef errno
extern int errno;
register char *stack_ptr asm ("sp");
/**
 * @brief Close a file
 * @param file
 * @return
 */
int _close(int file)
{
    return -1;
}

/**
 * @brief Status of an open files
 * @param file
 * @param st
 * @return
 */
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/**
 * @brief Query whether output stream is a terminal
 * @param file
 * @return
 */
int _isatty(int file)
{
    return 1;
}

/**
 * @brief Set position in a file
 * @param file
 * @param ptr
 * @param dir
 * @return
 */
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

/**
 * @brief Read from a file
 * @param file
 * @param ptr
 * @param len
 * @return
 */
int _read(int file, char *ptr, int len)
{
    return 0;
}

/**
 * @brief Write to a file
 * @param file
 * @param ptr
 * @param len
 * @return
 */
int _write(int file, char *ptr, int len)
{
    int todo;

    for (todo = 0; todo < len; todo++)
    {
        USART_SendData(USART2, *ptr);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        ptr++;
    }
    return len;
}

/**
 * @brief Increase program data space
 * @param incr
 * @return
 */
caddr_t _sbrk(int incr)
{
    extern char _end; /* Defined by the linker */
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_end;
    }
    prev_heap_end = heap_end;
    if (heap_end + incr > stack_ptr)
    {
        _write(1, "Heap and stack collision\n", 25);
        while(1);
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;
}
