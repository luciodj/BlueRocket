/*
 * util.c
 *
 */

#include "util.h"


putc_callback print_putc;

void print_stdout(putc_callback func) {
	print_putc = func;
}

/* CRC Routines */

#define POLYNOMIAL16 0x8005
uint16_t crc16_update(uint16_t crc, uint8_t a, uint8_t reverse)
{
	// polynomial 0xA001 is the same as 0x8005
	// in reverse implementation
	uint8_t i;
    uint8_t input = 0;

	if (reverse) {
		for (i = 0; i < 8; i++) {
			if (a & (0x01 << i)) {
                input |= (0x80 >> i);
            }
		}
	} else {
		input = a;
	}

	crc ^= (input << 8);
	for (i = 0; i < 8; i++)	{
		if (crc & 0x8000) {
			crc = (crc << 1) ^ POLYNOMIAL16;
		} else {
			crc = (crc << 1);
		}
	}

	return crc;
}

#define POLYNOMIAL7 0x09

uint8_t crc7_update(uint8_t crc, uint8_t a, uint8_t reverse)
{
	// polynomial 0xA001 is the same as 0x8005
	// in reverse implementation
	uint8_t i, input = a;

	for (i = 0; i < 8; i++)	{
		crc <<= 1;
		if ((input ^ crc) & 0x80){
			crc ^= POLYNOMIAL7;
		}
		input <<= 1;
	}

	return crc & 0x7F;
}

const uint8_t base64_lut[64] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

void base64(uint8_t * output_buf, uint8_t * input_buf, uint8_t size) {
	uint8_t sz = size;
	uint8_t idx_in = 0;
	uint8_t idx_out = 0;
	uint8_t a,b,c,d;

	while (sz > 2) {
		a = (input_buf[idx_in] >> 2) & 0x3F;
		b = ((input_buf[idx_in] << 4) | (input_buf[idx_in + 1] >> 4)) & 0x3F;
		c = ((input_buf[idx_in + 1] << 2) | (input_buf[idx_in + 2] >> 6)) & 0x3F;
		d = (input_buf[idx_in + 2]) & 0x3F;

		output_buf[idx_out + 0] = base64_lut[a];
		output_buf[idx_out + 1] = base64_lut[b];
		output_buf[idx_out + 2] = base64_lut[c];
		output_buf[idx_out + 3] = base64_lut[d];

		idx_in  += 3;
		idx_out += 4;
		sz -= 3;

		if ((idx_out % 64) == 0) {
			output_buf[idx_out] = '\r';
			//output_buf[idx_out + 1] = '\n';
			idx_out += 1;
		}
	}

	if (sz == 2) {
		a = (input_buf[idx_in] >> 2) & 0x3F;
		b = ((input_buf[idx_in] << 4) | (input_buf[idx_in+1] >> 4)) & 0x3F;
		c = ((input_buf[idx_in+1] << 2) | 0) & 0x3F;
		output_buf[idx_out + 0] = base64_lut[a];
		output_buf[idx_out + 1] = base64_lut[b];
		output_buf[idx_out + 2] = base64_lut[c];
		output_buf[idx_out + 3] = '=';
	}

	if (sz == 1) {
		a = (input_buf[idx_in] >> 2) & 0x3F;
		b = ((input_buf[idx_in] << 4) | 0) & 0x3F;
		output_buf[idx_out + 0] = base64_lut[a];
		output_buf[idx_out + 1] = base64_lut[b];
		output_buf[idx_out + 2] = '=';
		output_buf[idx_out + 3] = '=';
	}
}

/* \brief Long to ASCII INT converter
 */
static void int2uint(uint32_t num, uint8_t * outstream, uint8_t outsize)
{
	uint8_t digit_buf[11];    //Buffer to hold 10 digits + null-terminate
	uint32_t tester = num;
	uint32_t limit = 1000000000;
	uint8_t indx = 0;
	uint8_t digit_count = 1;

	while (indx < 10) {
		digit_buf[indx] = '0';
		while (tester >= limit) {
			digit_buf[indx]++;
			tester -= limit;
		}
		indx++;
		limit /= 10;
	}

	//Count digits in buffer
	for (uint8_t dcount = 0; dcount < 10; dcount++) {
		if (digit_buf[dcount] != '0') {
			digit_count = (uint8_t) (10 - dcount);
			break;
		}
	}

	//Check if requested digits are more than counted
	if (outsize > digit_count) {
        digit_count = outsize;
    }

	//Move digits to buffer
	for (uint8_t dcount=0; dcount<digit_count; dcount++) {
		outstream[dcount] = digit_buf[(uint8_t) (10 - digit_count + dcount)];
	}
	outstream[digit_count] = 0x00; //null-terminate
}

/* \brief Long to ASCII HEX converter
 */
static void int2hex(uint32_t num, uint8_t * outstream, uint8_t outsize)
{
	uint8_t digit_count = 1;
	uint32_t nibble_mask = 0xF0000000;

	for (uint8_t dcount = 8; dcount > 0; dcount--) {
		if (num & nibble_mask) {
			digit_count = dcount;
			break;
		}
		nibble_mask >>= 4;
	}

	//Sanity check if requested digits are more than counted or too many
	if(outsize>digit_count) digit_count = outsize;
	if(digit_count > 8) digit_count = 8;

	uint8_t temp = 0;

	for (uint8_t u = digit_count; u > 0; u--) {
		temp = (uint8_t) (num & 0x0F);
		num >>= 4;
		if (temp<0x0A) {
			outstream[u - 1] = (uint8_t) (temp + 48);
		} else {
			outstream[u - 1] = (uint8_t) (temp + 55);
		}
    }
	outstream[digit_count] = 0x00; //null-terminate
}


/* \brief Long to ASCII BIN converter
 */
static void int2bin(uint32_t num, uint8_t * outstream, uint8_t outsize)
{
	uint8_t digit_count = 1;
	uint32_t bit_mask = 0x80000000;

	for (uint8_t dcount = 32; dcount > 0; dcount--) {
	    if (num & bit_mask) {
			digit_count = dcount;
		    break;
	    }
		bit_mask >>= 1;
	}

	//Sanity check if requested digits are more than counted or too many
	if (outsize > digit_count) {
        digit_count = outsize;
    }

	if (digit_count > 32) {
        digit_count = 32;
    }

	uint8_t temp = 0;
	for (uint8_t u = digit_count; u > 0; u--) {
		temp = (uint8_t) (num & 0x01);
		num >>= 1;
		if (temp) {
			outstream[u - 1] = '1';
		} else {
			outstream[u - 1] = '0';
		}
	}
	outstream[digit_count] = 0x00; //null-terminate
}


/* \brief Simple printf function to output to UART
 *
 *  Usage: printf("hello %s, %4x, %d" % "world:", 0x1234, 0x1234)
 */
void print_printf(char * stream, ...)
{
	if (print_putc == 0) {
		return;
    }

	va_list args;
	va_start(args, stream);
	uint8_t buffer[40];
	uint8_t * convStream = buffer;

	while (*stream != 0x00) {
		if (*stream == '%') {
			stream++;
			uint8_t d_cnt = 0;
			//uint8_t prefix = 0;
			//if(*stream == '0') prefix = 1;
			while (*stream >= '0' && *stream <= '9') {
				d_cnt = (uint8_t)(d_cnt * 10) + (*stream++ - '0');
			}
			//Print parameter %x as hex
			if ((uint8_t)(*stream&0x5F) == 'X') {
				int2hex(va_arg(args, uint32_t), convStream, d_cnt);
			}
			//Print parameter %d as decimal
			if ((uint8_t)(*stream&0x5F) == 'D') {
				int2uint(va_arg(args, uint32_t), convStream, d_cnt);
			}
			//Print parameter %b as binary
			if ((uint8_t)(*stream&0x5F) == 'B') {
				int2bin(va_arg(args, uint32_t), convStream, d_cnt);
			}
			//Print parameter %s as string
			if ((uint8_t)(*stream&0x5F)== 'S') {
				convStream = va_arg(args, uint8_t*);
			}
			//Print parameter %c as char
			if ((uint8_t)(*stream&0x5F)== 'C') {
				*convStream = (uint8_t) va_arg(args, int);
                //*convStream = va_arg(args, uint8_t);
				convStream[1] = 0;
			}
			//Print parameter % as %
			if ((*stream)== '%') {
				convStream[0] = '%';
				convStream[1] = 0;
			}

			while (*convStream != 0x00) {
				print_putc(*convStream++);
			}
		} else {
			print_putc(*stream);
		}
		stream++;
	}
	va_end(args);
}

//Raw sending
void print_char(uint8_t byte)
{
	print_putc(byte);
}


//Print an array as hex value list
void print_array_as_hex(uint8_t* hex_data, uint32_t len, uint8_t size)
{
	uint8_t buffer[3];

    print_putc('[');
	for (uint32_t cnt=0; cnt<len; cnt++) {
		int2hex(hex_data[cnt], buffer, size);
		print_putc('0');
		print_putc('x');
		print_putc(buffer[0]);
		print_putc(buffer[1]);
		if (cnt < (len - 1)) {
			print_putc(',');
			print_putc(' ');
		}
	}
	print_putc(']');
}

void print_array_as_uint(uint8_t* uint_data, uint32_t len, uint8_t size)
{
	uint8_t buffer[12];
	uint8_t * convBuf = buffer;

	print_putc('[');
	for (uint32_t cnt = 0; cnt < len; cnt++) {
		int2uint(uint_data[cnt], convBuf, size);
		while (*convBuf != 0x00) {
			print_putc(*convBuf++);
		}
		if (cnt < (len - 1)) {
			print_putc(',');
			print_putc(' ');
		}
	}
	print_putc(']');
}