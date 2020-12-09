#ifndef __MACRO_H__
#define __MACRO_H__

#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
    || (defined(__clang__) && (__clang_major__ >= 3)) || (_MSC_VER >= 1800)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete; \
    TypeName &operator =(const TypeName &) = delete;
#else
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName &); \
    TypeName &operator =(const TypeName &);
#endif

#endif