#ifndef HAVE_CONSOLEIO_H
#define HAVE_CONSOLEIO_H
#include <iostream>

/* Get string value from user console input with skipping final CR/EOL sequence */
extern void console_get_user_input(std::string &input);

/* Get signed integer value from user console input in decimal form */
extern int console_get_dec(signed &val);
extern int console_get_dec(unsigned &val);

/* Get unsigned integer value from user console input decimal form */

/* Get unsigned integer value from user console input in hexadecimal form */
extern int console_get_hex(unsigned &val);

/* Get unsigned integer value from user console input in octal form */
extern int console_get_oct(unsigned &val);

/* Get unsigned integer value from user console input in binary form */
extern int console_get_bin(unsigned &val);

/* Put message to STDOUT stream */
extern int console_log_msg(const char *msg);

/* Put message to STDERR stream */
extern int console_log_err(const char *msg);

/* Put scalar value to STDOUT stream in hexadecimal form */
extern int console_out_hex(unsigned val);
extern int console_out_hex(signed val);

/* Put scalar value to STDERR stream in hexadecimal form */
extern int console_err_hex(unsigned val);
extern int console_err_hex(signed val);

#endif //HAVE_CONSOLEIO_H
