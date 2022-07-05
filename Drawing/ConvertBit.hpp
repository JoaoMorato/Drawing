#pragma once
#ifndef _CONVERT_BIT_
#define _CONVERT_BIT_

#include <list>

class Byte {
private:
	unsigned char code;

public:
	static bool bigEndian;

	unsigned char GetByte();
	static void SetBytes(std::list<Byte>& bytes, char* byte, unsigned int size);
	Byte(unsigned char num);
	void operator = (char c);
};

unsigned char Byte::GetByte() {
	return code;
}

Byte::Byte(unsigned char num) {
	code = num;
}

void Byte::SetBytes(std::list<Byte>& bytes, char* c, unsigned int size) {
	for (size_t i = 0; i < size; i++) {
		bytes.push_back(c[i]);
	}
}

void Byte::operator=(char c) {
	code = c;
}

bool Byte::bigEndian = false;


class ConvertBit {
public:
	static void ToByte(std::list<Byte>& bytes, bool data);

	static void ToByte(std::list<Byte>& bytes, char data);

	static void ToByte(std::list<Byte>& bytes, unsigned char data);

	static void ToByte(std::list<Byte>& bytes, short data);

	static void ToByte(std::list<Byte>& bytes, int data);

	static void ToByte(std::list<Byte>& bytes, long long data);
	
	static void ToByte(std::list<Byte>& bytes, unsigned short data);

	static void ToByte(std::list<Byte>& bytes, unsigned int data);

	static void ToByte(std::list<Byte>& bytes, unsigned long long data);

	static void ToByte(std::list<Byte>& bytes, float data);

	static void ToByte(std::list<Byte>& bytes, double data);

	static void ToByte(std::list<Byte>& bytes, char* data);

	//////////////////////////////////////////////////////

	static bool Boolean(std::list<Byte>& bytes);

	static char Char(std::list<Byte>& bytes);

	static unsigned char uChar(std::list<Byte>& bytes);

	static short Int16(std::list<Byte>& bytes);

	static int Int32(std::list<Byte>& bytes);

	static long long Int64(std::list<Byte>& bytes);
	
	static unsigned short uInt16(std::list<Byte>& bytes);

	static unsigned int uInt32(std::list<Byte>& bytes);

	static unsigned long long uInt64(std::list<Byte>& bytes);

	static float Single(std::list<Byte>& bytes);

	static double Double(std::list<Byte>& bytes);

	static char* String(std::list<Byte>& bytes);

	static char* String(std::list<Byte>& bytes, unsigned int size);

};

void ConvertBit::ToByte(std::list<Byte>& bytes, long long data) {
	for (size_t i = 0; i < sizeof(long long); i++) {
		bytes.push_back(char(data >> (i * 8)));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, int data) {
	for (size_t i = 0; i < sizeof(int); i++) {
		bytes.push_back(data >> (i * 8));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, short data) {
	for (size_t i = 0; i < sizeof(short); i++) {
		bytes.push_back(data >> (i * 8));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, unsigned long long data) {
	for (size_t i = 0; i < sizeof(unsigned long long); i++) {
		bytes.push_back(data >> (i * 8));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, unsigned int data) {
	for (size_t i = 0; i < sizeof(unsigned int); i++) {
		bytes.push_back(data >> (i * 8));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, unsigned short data) {
	for (size_t i = 0; i < sizeof(unsigned short); i++) {
		bytes.push_back(data >> (i * 8));
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, float data) {
	char* a = (char*)&data;
	for (size_t i = 0; i < sizeof(float); i++) {
		ToByte(bytes, *a);
		a += 1;
	}
}

void ConvertBit::ToByte(std::list<Byte>& bytes, double data) {
	unsigned long long aux;
	memcpy(&aux, &data, sizeof(double));
	ToByte(bytes, aux);
}

void ConvertBit::ToByte(std::list<Byte>& bytes, char data) {
	bytes.push_back(data);
}

void ConvertBit::ToByte(std::list<Byte>& bytes, unsigned char data) {
	bytes.push_back(data);
}

void ConvertBit::ToByte(std::list<Byte>& bytes, bool data) {
	bytes.push_back(data);
}

void ConvertBit::ToByte(std::list<Byte>& bytes, char* data) {
	int len = 0;
	while (data[len++]);
	ToByte(bytes, len - 1);

	for (size_t i = 0; i < len - 1; i++) {
		bytes.push_back(data[i]);
	}
}


///Convert in type

void* Convert(std::list<Byte>& bts, size_t size) {
	unsigned char* valor = new unsigned char[size];
	if (!Byte::bigEndian) {
		for (size_t i = 0; i < size; i++) {
			valor[i] = bts.begin()->GetByte();
			bts.pop_front();
		}
	}
	else {
		for (size_t i = size; i > 0; i--) {
			valor[i - 1] = bts.begin()->GetByte();
			bts.pop_front();
		}
	}
	return valor;
}

long long ConvertBit::Int64(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(long long))
		return 0;
	return *(long long*)Convert(bytes, sizeof(long long));
}

int ConvertBit::Int32(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(int))
		return 0;
	return *(int*)Convert(bytes, sizeof(int));
}

short ConvertBit::Int16(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(short))
		return 0;
	return *(short*)Convert(bytes, sizeof(short));
}

unsigned long long ConvertBit::uInt64(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(unsigned long long))
		return 0;
	return *(unsigned long long*)Convert(bytes, sizeof(unsigned long long));
}

unsigned int ConvertBit::uInt32(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(unsigned int))
		return 0;
	return *(unsigned int*)Convert(bytes, sizeof(unsigned int));
}

unsigned short ConvertBit::uInt16(std::list<Byte>& bytes) {
	if (bytes.size() < sizeof(unsigned short))
		return 0;
	return *(unsigned short*)Convert(bytes, sizeof(unsigned short));
}

float ConvertBit::Single(std::list<Byte>& bytes) {
	if (bytes.size() < 4)
		return 0;

	return *(float*)Convert(bytes, sizeof(float));
}

double ConvertBit::Double(std::list<Byte>& bytes) {
	if (bytes.size() < 8)
		return 0;

	return *(double*)Convert(bytes, sizeof(double));
}

bool ConvertBit::Boolean(std::list<Byte>& bytes) {
	bool result = bytes.begin()->GetByte();
	bytes.pop_front();
	return result;
}

char ConvertBit::Char(std::list<Byte>& bytes) {
	char result = bytes.begin()->GetByte();
	bytes.pop_front();
	return result;
}

unsigned char ConvertBit::uChar(std::list<Byte>& bytes) {
	unsigned char result = bytes.begin()->GetByte();
	bytes.pop_front();
	return result;
}

char* ConvertBit::String(std::list<Byte>& bytes) {
	unsigned int size = uInt32(bytes);
	char* result;
	result = (char*)malloc(size+1);
	if (!result) return NULL;
	for (size_t i = 0; i < size; i++) {
		result[i] = Char(bytes);
	}
	result[size] = 0;
	return result;
}

char* ConvertBit::String(std::list<Byte>& bytes, unsigned int size) {
	if (!size) {
		for (auto i = bytes.begin(); i != bytes.end(); ++i) {
			size++;
			if (!i->GetByte())
				break;
		}
	}

	char* result;
	result = (char*)malloc(size + 1);
	for (size_t i = 0; i < size; i++) {
		result[i] = Char(bytes);
	}
	result[size] = 0;
	return result;
}

#endif