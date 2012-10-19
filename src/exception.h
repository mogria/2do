#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include <setjmp.h>
#include <string.h>

jmp_buf _exception_h_jumper;
#define _EXCEPTION_H_MESSAGE_LENGTH 300
char _exception_h_message[_EXCEPTION_H_MESSAGE_LENGTH];
 

#define THROW(msg, errcode) strncpy(_exception_h_message, (msg), _EXCEPTION_H_MESSAGE_LENGTH); longjmp(_exception_h_jumper, (errcode))

#define TRY int _exception_h_errcode = 0; if((_exception_h_errcode = setjmp(_exception_h_jumper)) == 0)

#define CATCH else 

#define EXCEPTION_MESSAGE (_exception_h_message)

#define EXCEPTION_ERRCODE (_exception_h_errcode)

#endif /* _EXCEPTION_H */

