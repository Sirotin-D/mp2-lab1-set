// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen (len)
{
	if (len > -1) {
		MemLen = (len + 31) >> 5;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
		{
			for (int i = 0; i < MemLen; i++) pMem[i] = 0;
		}
		else
		{
			throw - 1;
		}
	}
	else throw - 3;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	else throw -2;
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen))
	{
		int res = n >> 5;
		return res;
	}
	else
	{
		throw - 1;
	}

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > -1) && (n < BitLen))
	{
		int res = 1 << (n & 31);
		return res;
	}
	else
	{
		throw - 1;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem [GetMemIndex(n)] |= GetMemMask(n);
	}
	else
	{
	throw -3;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
		pMem [GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	else
	{
		throw -3;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	else
	{
		throw - 3;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf) {
		return *this;
	}
	else {
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		if (pMem != NULL)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		return *this;
	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool res = 1;
	if (BitLen != bf.BitLen) res = 0;
	else 
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) { res = 0; break; }
		}
  return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i, len = BitLen;
	if (bf.BitLen > BitLen) len = bf.BitLen;
	TBitField res(len);
	for (i = 0; i < MemLen; i++) res.pMem[i] = pMem[i];
	for (i = 0; i < bf.MemLen; i++) res.pMem[i] |= bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i,len = bf.BitLen;
	if (bf.BitLen > BitLen) { len = bf.BitLen; }
	TBitField res(len);
	for ( i = 0; i < MemLen; i++) { res.pMem[i] = pMem[i]; }
	for ( i = 0; i < res.MemLen; i++) { res.pMem[i] &= bf.pMem[i]; }
	return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	int cnt = (BitLen / 32);
	for (int i = 0; i < cnt; i++)
		res.pMem[i] = ~pMem[i];

	for (int j = cnt * 32; j < BitLen; j++) {
		if (GetBit(j) == 0) {
			res.SetBit(j);
		}
		else {
			res.ClrBit(j);
		}
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0; char ch;
	do { istr >> ch; } while (ch != ' ');

	while (1) 
	{ 
		istr >> ch; 
	if (ch == '0') { bf.ClrBit(i++); }
	else if (ch == '1') bf.SetBit(i++);
	else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	for (int i = 0; i < len; i++)
		if (bf.GetBit(i)) ostr << "1";
		else ostr << "1";
	return ostr;
}
