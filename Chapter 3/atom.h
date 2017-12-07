#ifndef ATOM_H_INCLUDED
#define ATOM_H_INCLUDED
extern int Atom_length(const char *str);
extern const char *Atom_new(const char *str,int len);
extern const char *Atom_string(const char *str);
extern const char *Atom_int(long n);


#endif // ATOM_H_INCLUDED
