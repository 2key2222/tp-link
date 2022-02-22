#include <stdio.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

/* This program demonstrates that when Unicode printed text is redirected to
   a file, the file is not in correct UTF-16.
*/

int main () {

  int prevmode;

/*
  When the output of this program is redirected to a file in Windows Command
  Prompt you get for line breaks 0d0a 00, while it should be 0d00 0a00.

c:\test>.\testu16.exe > o.txt

c:\test>xxd o.txt
0000000: 6f00 6e00 6500 0d0a 0074 0077 006f 000d  o.n.e....t.w.o..
0000010: 0a00 7400 6800 7200 6500 6500 0d0a 00    ..t.h.r.e.e....



  When the output is redirected to a file in PowerShell, null characters
  0000 are inserted. It looks like UTF-32 with an UTF-16 BOM and UTF-16 line
  breaks.

PS C:\test> .\testu16.exe > p.txt
PS C:\test> xxd p.txt
0000000: fffe 6f00 0000 6e00 0000 6500 0000 0d00  ..o...n...e.....
0000010: 0a00 0000 7400 0000 7700 0000 6f00 0000  ....t...w...o...
0000020: 0d00 0a00 0000 7400 0000 6800 0000 7200  ......t...h...r.
0000030: 0000 6500 0000 6500 0000 0d00 0a00 0000  ..e...e.........
0000040: 0d00 0a00                                ....

*/

  prevmode = _setmode(_fileno(stdout), _O_U16TEXT);
  fwprintf(stdout,L"one\n");
  fwprintf(stdout,L"two\n");
  fwprintf(stdout,L"three\n");
  _setmode(_fileno(stdout), prevmode);


  return 0;
}
