#ifndef __KB_H_
#define __KB_H_
#ifdef __cplusplus
extern "C" {
#endif

void kb_Init(void);
void kb_Close(void);
char kb_Scan(void);

#ifdef __cplusplus
}
#endif
#endif // !__KB_H_