#ifndef STR_H
#define STR_H

class str {
  char* _s;
  int _l,_res;
  void _copy(const char*);
  str(int);
public:
  static int len(const char*);

  str();
  str(char, int);
  str(const char*);
  str(const str&);
  ~str();

  void _resize(int);
  int size()const;
  int cmp(const char*)const;
  void clear();
  bool empty()const;
  str operator+(const str&)const;
  str operator+(const char*)const;
  str& operator+=(const str&);
  str& operator+=(const char*);
  str& operator=(const char*);
  str& operator=(const str&);
  char& operator[](int)const;
  bool operator==(const str&)const;
  bool operator==(const char*)const;
  friend std::ostream& operator<<(std::ostream&, const str&);
  friend std::istream& operator>>(std::istream&, str&);
};
#endif
