#include "comm.hpp"

int main()
{
    NamedFifo fifo(PATH, FILENAME);

    FileOper readerfile(PATH, FILENAME);
    readerfile.OpenForRead();
    readerfile.Read();
    readerfile.Close();
    return 0;
}