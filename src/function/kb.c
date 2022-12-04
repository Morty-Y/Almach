#include <sys/time.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/* The original and new terminal attributes */
static struct termios Savedtty,
                      Rawtty;

void kb_Init(void)
{
    tcgetattr(0,&Savedtty);
    Rawtty = Savedtty;
    Rawtty.c_lflag &= ~ICANON;    // 设置不以规范模式工作，读请求直接从队列读取字符，至少接到MIN字节或者两个字节之间超时值TIME到期时，read才返回
    Rawtty.c_lflag &= ~ECHO;      // 关闭输入字符回显到终端设备
    // Rawtty.c_lflag &= ~ISIG;   // 判断输入字符是否要产生终端信号的特殊字符
    Rawtty.c_cc[VMIN] = 1;        // 至少接到MIN字节
    Rawtty.c_cc[VTIME] = 0;       // 两个字节之间超时值TIME
    tcsetattr(0, TCSANOW, &Rawtty);
}

void kb_Close(void)
{
    tcsetattr(0, TCSANOW, &Savedtty);
}

static int chin (int ech, char *buf, unsigned cnt)
{
   int rc;
   fflush(stdout);
   if (!ech)
      rc = read(STDIN_FILENO, buf, cnt);
   else {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Savedtty);
      rc = read(STDIN_FILENO, buf, cnt);
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &Rawtty);
   }
   // may be the beginning of a lengthy escape sequence
   tcflush(STDIN_FILENO, TCIFLUSH);
   return rc;                   // note: we do NOT produce a vaid 'string'
}

char kb_Scan(void){
    long file_flags;
    int rc;
    char c;
    fd_set fs;
    FD_ZERO(&fs);
    FD_SET(STDIN_FILENO, &fs);
    file_flags = fcntl(STDIN_FILENO, F_GETFL);
    if(file_flags==-1) file_flags=0;

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK|file_flags);

    // check 1st, in case tv zeroed (by sig handler) before it got set
    rc = chin(0, &c, 1);
    if (rc <= 0) {
        // EOF is pretty much a "can't happen" except for a kernel bug.
        // We should quickly die via SIGHUP, and thus not spin here.
        // if (rc == 0) end_pgm(0); /* EOF from terminal */
        fcntl(STDIN_FILENO, F_SETFL, file_flags);
        select(1, &fs, NULL, NULL, NULL);
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK|file_flags);
    }

    if (chin(0, &c, 1) > 0) {
        fcntl(STDIN_FILENO, F_SETFL, file_flags);
        return c;
    } else {
        fcntl(STDIN_FILENO, F_SETFL, file_flags);
    }
}