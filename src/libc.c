#include "reg.h"
#include "os.h"

int putc(char c)
{
	char str[2] = {0};
	str[0] = c;
	svc_call_write_string(str);
	return 1;
}

int puts(char *s)
{
	svc_call_write_string(s);
	return 1;
}


char *itoa(int n, char *str, int radix)
{
	char digit[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p = str;
	char *head = str;
	char tmp;

	if (!p || radix < 2 || radix > 36)
		return p;
	if (radix != 10 && n < 0)
		return p;
	if (n == 0) {
		*p++ = '0';
		*p = 0;		/* string end \0 */
		return p;
	}

	if (radix == 10 && n < 0) {
		*p++ = '-';
		n = -n;
	}

	while (n) {
		*p++ = digit[n % radix];
		n /= radix;
	}

	*p = 0;

	for (--p; head < p; ++head, --p) {
		tmp = *head;
		*head = *p;
		*p = tmp;
	}

	return str;
}

unsigned int strlen(char *str)
{
	int cnt = 0;
	if (!str)
		return 0;
	
	for (; *str != '\0'; ++str)
		++cnt;
	return cnt;
}

int printf(const char *format, ...) 
{
	int translating = 0;
	int ret = 0;
	const char *p = 0;
	char buf[16];
	char **arglist = (char **)(&format);

	for (p = format; *p != '\0'; ++p) {
		switch (*p) {
		case '%':
			if (!translating)
				translating = 1;
			else {
				if (putc('%') < 0)
					return 0;
				else {
					ret++;
					translating = 0;
				}
			}
			break;
		case 'b':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 2);
				if (puts(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else {
				putc('x');
				ret++;
			}
			break;
	
		case 'x':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 16);
				if (puts(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else {
				putc('x');
				ret++;
			}
			break;
		case 'd':
			if (translating) {
				translating = 0;
				arglist = arglist + 1;
				itoa(*((int *)arglist), buf, 10);
				if (puts(buf) < 0)
					return 0;
				ret += strlen(buf);
			} else if (putc('d') < 0)
				return 0;
			else
				ret++;
			break;
		case 's':
			if (translating) {
				arglist = arglist + 1;
				translating = 0;
				puts(*arglist);
				ret += strlen(*arglist);
			} else 
				putc('s');
			break;
		default:
			if (translating)
				translating = 0;
			if (*p == '\n')
				putc('\r');
			putc(*p);
			ret++;
			break;
		}
	}
	return ret;
}

void memcpy(uint8_t *dest, uint8_t *src, uint32_t size)
{
	uint32_t i;
	for (i = 0; i < size; i++)
		*(dest + i) = *(src + i);
	return;
}
