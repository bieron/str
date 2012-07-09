#include<iostream>
#include "str.h"
//---------PRIVATE-----------------------------------------------
void str::_copy(const char* string) {
  _l = str::len(string);
  if(_l>_res) _resize(_l);//_s = new char[_l+1];
  for(int i=0; _s[i] = string[i]; i++);
}
//---------STATIC-----------------------------------------------
int str::len(const char* string) {
  int i=0;
  while(string[i++]) {};
  return i-1;
}
//---------CTOR AND DEST-----------------------------------------------
str::str(int length): _s(NULL), _l(length) {//private!
  if(_l) _s = new char[_l+1];//used by operator+
}
str::str(): _l(0),_res(0) { _s = new char[1]; _s[0] = 0; }
str::str(char c, int length=1): _s(NULL) {
  if(length<1) {
    _l = 0;
    return;
  }
  _l = _res = length;
  _s = new char[_res+1];
  for(int i=0; i<_l; i++)
    _s[i] = c;
  _s[_l] = 0;
}
str::str(const char* string): _s(NULL), _l(str::len(string)) {
  if(!_l) return;
  _copy(string);
  _res = _l;//_copy zmienilo juz _l
}
str::str(const str& her): _s(NULL), _l(her._l) {
  if(!_l) return;
  _copy(her._s);
  _res = _l;//_copy zmienilo juz _l
}
str::~str() {if(_s != NULL) delete [] _s;}


int str::size()const {return _l;}
bool str::empty()const {return _l==0;}
int str::cmp(const char* string)const {
  int i=0,d=0;
  for(; !(d=_s[i]-string[i]) && _s[i]; i++) {};
  if(d > 0) return 1;
  if(d < 0) return -1;
  return 0;
}
void str::clear() { _res = _l = 0; if(_s) { delete [] _s; _s = NULL; } }

str str::operator+(const str& her)const { return operator+(her._s); }  
str str::operator+(const char* string)const {
  int sum_l =  _l + str::len(string);
  str sum( sum_l );
  sum._copy(this->_s);
  for(int i=0; sum._s[_l+i] = string[i]; i++) {};
  return sum;
}
void str::_resize(int size) {
  if(_s) delete [] _s;
  _res = _l = size;
  _s = new char[_l+1];
}

str& str::operator=(const char* string) {
  if(!cmp(string)) return *this;
  _copy(string);
  return *this;
}
str& str::operator=(const str& her) { return operator=(her._s); }

str& str::operator+=(const str& her) { return operator+=(her._s); }
str& str::operator+=(const char* string) {
  *this = *this + string;
  return *this;
}

char& str::operator[](int i)const {
  if(i>_l) throw i;//out of range
  return _s[i];
}
bool str::operator==(const str& her)const {
  if(_l != her._l) return false;
  return !cmp(her._s);
}
bool str::operator==(const char* string)const {
  return !cmp(string);
}
std::ostream& operator<<(std::ostream& out, const str& me) {
  if(me._s) out<<me._s;
  return out;
}
std::istream& operator>>(std::istream& in, str& me) {
  int span = 20, read=0;
  char* tmp, *buf = new char[span];
  while(1) {
    while(read < span) {
      in.get(buf[read]);
      switch(buf[read]) {
        case ' ': case '\t': 
          in.ignore(10000,'\n');
        case '\n': case '\0':
          buf[read] = 0;
          me = buf;
          delete [] buf;
          return in;
      }
      read++;
    }
    tmp = new char[span*=2];
    for(int i=0; i<read+1 && (tmp[i]=buf[i]); i++) {};
    delete [] buf;
    buf = tmp;
  }
}
