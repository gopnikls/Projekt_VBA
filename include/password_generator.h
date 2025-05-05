#ifndef PASSWORD_GENERATOR_H
#define PASSWORD_GENERATOR_H

char* generate_password(int length, bool use_uppercase, bool use_lowercase,
						bool use_digits, bool use_symbols);

#endif
