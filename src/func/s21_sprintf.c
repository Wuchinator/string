#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  va_list vars;
  va_start(vars, format);
  struct flags flag = {0};
  int nulls_accuracy, nulls = 0;
  int null_p = -1;
  s21_strcpy(str, "");
  start_cycle {
    if (CURRENT == '%' AND !flag.Fformat) {
      flag.Fformat = 1;
      continue;
    }
    if (flag.Fformat) {
      if (CURRENT == '+') {
        flag.sign = 1;
      }
      ELIF(CURRENT == ' ') {
        if (flag.sign != 1) {
          flag.sign = 2;
        }
      }
      ELIF(CURRENT == '-' AND !flag.dot) {
        flag.align = 1;
        flag.zero_width = 0;
      }
      ELIF(CURRENT == '-' AND flag.dot) {
        flag.setAccuracy = 0;
        nulls_accuracy = 1;
      }
      ELIF(CURRENT == '#') { flag.spec = 1; }
      ELIF(CURRENT <= '9' AND CURRENT >= '0' AND !flag.dot) {
        if (CURRENT == '0' AND !flag.align) flag.zero_width = 1;
        while (CURRENT <= '9' AND CURRENT >= '0') {
          int n = CURRENT - '0';
          WIDTH = WIDTH * 10 + n;
          i++;
        }
        i--;
      }
      ELIF(CURRENT == '*' AND !flag.dot) {
        WIDTH = va_arg(vars, int);
        if (WIDTH < 0) {
          WIDTH *= -1;
          flag.align = 1;
        }
      }
      ELIF(CURRENT == '.') {
        flag.dot = 1;
        flag.setAccuracy = 1;
      }
      ELIF(CURRENT == '*' AND flag.dot) {
        flag.accuracy = va_arg(vars, int);
        if (flag.accuracy < 0) {
          flag.setAccuracy = 0;
          nulls_accuracy = 1;
        }
      }
      ELIF(CURRENT <= '9' AND CURRENT >= '0' AND flag.dot) {
        while (CURRENT <= '9' AND CURRENT >= '0') {
          flag.accuracy = flag.accuracy * 10 + (CURRENT - '0');
          i++;
        }
        i--;
        if (nulls_accuracy) {
          if (!WIDTH) {
            WIDTH = flag.accuracy;
            flag.align = 1;
          }
          flag.accuracy = 0;
        }
      }
      else {
        if (CURRENT == 'h') {
          flag.length -= 1;
        }
        ELIF(CURRENT == 'l') { flag.length += 1; }
        ELIF(CURRENT == 'L') { flag.double_length = 1; }
        else {
          char string[1000] = {endOfstr};
          if (CURRENT == 'd' OR CURRENT == 'i' OR CURRENT == 'o' OR CURRENT ==
              'x' OR CURRENT == 'X') {
            if (!flag.setAccuracy) {
              flag.accuracy = 1;
            }
            flag.isDigit = 1;
            int radix = 10;
            if (CURRENT == 'o') {
              radix = 8;
            }
            ELIF(CURRENT == 'x' OR CURRENT == 'X') { radix = 16; }
            if (CURRENT == 'i' OR CURRENT == 'd') {
              FlagDi(flag, &vars, string);
            } else {
              flagO(flag, string, &vars, CURRENT, &radix);
            }
            if ((CURRENT == 'X' OR CURRENT == 'x') AND flag.spec) {
              int k = (int)s21_strlen(string);
              while (k != -1) {
                string[k + 2] = string[k];
                k--;
              }
              string[0] = '0';
              string[1] = CURRENT;
            }
            ELIF(CURRENT == 'o' AND flag.spec) {
              int k = (int)s21_strlen(string);
              while (k != -1) {
                string[k + 1] = string[k];
                k--;
              }
              string[0] = '0';
            }
          }
          ELIF(CURRENT == 'e' OR CURRENT == 'E' OR CURRENT == 'g' OR CURRENT ==
               'G') {
            flagEeGg(flag, &vars, CURRENT, string);
          }
          ELIF(CURRENT == 'c') {
            flagC(flag, &vars, string, &null_p, str, &nulls);
          }
          ELIF(CURRENT == 's') { flagS(flag, string, &vars); }
          ELIF(CURRENT == '%') { flagPercent(string, &flag); }
          ELIF(CURRENT == 'p') { flagP(flag, string, &vars); }
          ELIF(CURRENT == 'n') { flagN(flag, &vars, str); }
          ELIF(CURRENT == 'f') { flagF(flag, &vars, string); }
          ELIF(CURRENT == 'u') { flagU(flag, string, &vars); }
          else {
            string[0] = CURRENT;
            string[1] = endOfstr;
          }
          if (s21_strlen(string) < (size_t)WIDTH) {
            process(flag, string, str);
          }
          if (CURRENT == 'x' OR CURRENT == 'g' OR CURRENT == 'e' OR CURRENT ==
              'p') {
            for (int j = 0; string[j] != endOfstr; j++) {
              if (string[j] >= 'A' AND string[j] <= 'H') {
                string[j] = string[j] - 'A' + 'a';
              }
            }
          }
          s21_strcat(str, string);
          flag.Fformat = 0;
          flag.sign = 0;
          flag.accuracy = 0;
          flag.setAccuracy = 0;
          WIDTH = 0;
          flag.align = 0;
          flag.length = 0;
          flag.dot = 0;
          flag.double_length = 0;
          flag.spec = 0;
          flag.isDigit = 0;
          flag.zero_width = 0;
          nulls_accuracy = 0;
        }
      }
    } else {
      char ptr[2];
      ptr[0] = CURRENT;
      ptr[1] = endOfstr;
      s21_strcat(str, ptr);
    }
    va_end(vars);
  }
  s21_strcat(str, "\0");
  int len = (s21_strlen(str)) + nulls;
  while (null_p != len AND null_p != -1) {
    str[null_p] = endOfstr;
    null_p++;
  }
  return len;
}

void flagEeGg(struct flags flag, va_list* vars, char current, char* string) {
  flag.isDigit = 1;
  double num;
  if (flag.double_length)
    num = va_arg(*vars, long double);
  else
    num = va_arg(*vars, double);
  double num_copy = num;
  if (!flag.setAccuracy) flag.accuracy = 6;
  int exp = 0;
  int num_sign = 1;
  splitting(&num, &num_sign, &exp);
  char test_len_str[20];
  char test_accuracy_str[20];
  if (current == 'e' OR current == 'E')
    itoa(flag.accuracy, test_accuracy_str, 10, 0, 0);
  ELIF(!(exp >= -4 AND flag.accuracy > exp))
  itoa(flag.accuracy - 1, test_accuracy_str, 10, 0, 0);
  ELIF(flag.accuracy)
  itoa(flag.accuracy - 1 - exp, test_accuracy_str, 10, 0, 0);
  else itoa(-exp, test_accuracy_str, 10, 0, 0);
  char test_format[10] = "%.";
  s21_strcat(test_format, test_accuracy_str);
  s21_strcat(test_format, "f");
  s21_sprintf(test_len_str, test_format, num);
  if ((test_len_str[0] == '1' AND test_len_str[1] == '0')
          OR(test_len_str[1] == '1' AND test_len_str[2] == '0')) {
    num /= 10;
    exp++;
  }
  char format_string[100] = "%";
  if (flag.sign == 1) {
    s21_strcat(format_string, "+");
  }
  ELIF(flag.sign == 2) { s21_strcat(format_string, " "); }
  if (flag.spec) {
    s21_strcat(format_string, "#");
  }
  if (current == 'g' OR current == 'G') {
    flagG(&exp, flag, &num, &num_sign, &num_copy);
  }
  char accuracy_str[20];
  itoa(flag.accuracy, accuracy_str, 10, 0, 0);
  s21_strcat(format_string, ".");
  s21_strcat(format_string, accuracy_str);
  if (current == 'E') {
    s21_strcat(format_string, "fE%+.2d");
    s21_sprintf(string, format_string, num * num_sign, exp);
  }
  ELIF(current == 'e') {
    s21_strcat(format_string, "fe%+.2d");
    s21_sprintf(string, format_string, num * num_sign, exp);
  }
  else {
    s21_strcat(format_string, "f");
    char trim_zeroes[20];
    s21_sprintf(trim_zeroes, format_string, num * num_sign);
    if (s21_strcspn(trim_zeroes, ".") != (s21_strlen(trim_zeroes) - 1)) {
      trimZeroes(trim_zeroes);
    }
    if (num != num_copy AND current == 'g') {
      s21_sprintf(string, "%se%+.2d", trim_zeroes, num * num_sign, exp);
    }
    ELIF(num != num_copy AND current == 'G') {
      s21_sprintf(string, "%sE%+.2d", trim_zeroes, num * num_sign, exp);
    }
    else {
      s21_sprintf(string, "%s", trim_zeroes, num, exp);
    }
  }
}

void splitting(double* num, int* num_sign, int* exp) {
  if (*num < 0) {
    *num_sign = -1;
    *num = *num * -1;
  }
  if (*num >= 10) {
    while (*num > 10) {
      *num /= 10;
      (*exp)++;
    }
  }
  ELIF(*num != 0) {
    while (*num * 10 < 10) {
      *num *= 10;
      (*exp)--;
    }
  }
}

void process(struct flags flag, char* string, char* str) {
  char* space = " \0";
  if (flag.zero_width AND flag.isDigit) {
    space = "0\0";
    if (string[1] == 'x' OR string[1] == 'X') {
      char ch[3];
      ch[0] = string[0];
      ch[1] = string[1];
      ch[2] = endOfstr;
      s21_strcat(str, ch);
      int k = 0;
      while (string[k] != endOfstr) {
        string[k] = string[k + 2];
        k++;
      }
      string[k] = endOfstr;
      WIDTH = WIDTH - 2;
    }
    ELIF(string[0] > '9' OR string[0] < '0') {
      char ch[2];
      ch[0] = string[0];
      ch[1] = endOfstr;
      s21_strcat(str, ch);
      int k = 0;
      while (string[k] != endOfstr) {
        string[k] = string[k + 1];
        k++;
      }
      string[k] = endOfstr;
      WIDTH = WIDTH - 1;
    }
  }
  WIDTH -= s21_strlen(string);
  if (flag.align) {
    while (WIDTH > 0) {
      s21_strcat(string, space);
      WIDTH--;
    }
  } else {
    while (WIDTH > 0) {
      s21_strcat(str, space);
      WIDTH--;
    }
  }
}

void flagO(struct flags flag, char* string, va_list* vars, char current,
           int* radix) {
  unsigned long long int n = va_arg(*vars, long long int);
  if (n == 0) {
    flag.spec = 0;
  }
  if (!flag.setAccuracy) flag.accuracy = 1;
  if (n OR flag.accuracy) {
    if (flag.spec == 1 AND current == 'o') flag.accuracy--;
    if (flag.length == -2) {
      UINT8 m = (unsigned char)n;
      itoa(m, string, *radix, 0, flag.accuracy);
    }
    ELIF(flag.length == -1) {
      UINT8 m = (UINT8)n;
      itoa(m, string, *radix, 0, flag.accuracy);
    }
    ELIF(flag.length == 1) {
      UINT64 m = (UINT64)n;
      itoa(m, string, *radix, 0, flag.accuracy);
    }
    ELIF(flag.length == 2) { itoa(n, string, *radix, 0, flag.accuracy); }
    else {
      unsigned int m = (unsigned int)n;
      itoa(m, string, *radix, 0, flag.accuracy);
    }
  }
}

void trimZeroes(char* trim_zeroes) {
  size_t str_len = s21_strlen(trim_zeroes) - 1;
  while (trim_zeroes[str_len] == '0' OR trim_zeroes[str_len] == '.') {
    if (trim_zeroes[str_len] == '.') {
      str_len--;
      break;
    }
    str_len--;
  }
  trim_zeroes[str_len + 1] = endOfstr;
}

void FlagDi(struct flags flag, va_list* vars, char* string) {
  if (flag.setAccuracy)
    flag.zero_width = 0;
  else
    flag.accuracy = 1;
  long long n = va_arg(*vars, long long);
  if (!(n OR flag.accuracy)) {
    if (flag.sign == 1) {
      s21_strcpy(string, "+");
    }
    ELIF(flag.sign == 2) { s21_strcpy(string, " "); }
  } else {
    if (flag.length == -2) {
      short int m = (char)n;
      itoa(m, string, 10, flag.sign, flag.accuracy);
    }
    ELIF(flag.length == -1) {
      short int m = (short int)n;
      itoa(m, string, 10, flag.sign, flag.accuracy);
    }
    ELIF(flag.length == 1) {
      int placeholder = n == LONG_MIN;
      if (placeholder) {
        s21_strcat(string, "-9223372036854775808");
      } else {
        long int m = (long int)n;
        itoa(m, string, 10, flag.sign, flag.accuracy);
      }
    }
    ELIF(flag.length == 2) { itoa(n, string, 10, flag.sign, flag.accuracy); }
    else {
      int m = (int)n;
      itoa(m, string, 10, flag.sign, flag.accuracy);
    }
  }
}

void flagU(struct flags flag, char* string, va_list* vars) {
  flag.isDigit = 1;
  unsigned long long n = va_arg(*vars, unsigned long long);
  if (!flag.setAccuracy) flag.accuracy = 1;
  if (flag.accuracy OR n) {
    if (flag.length == -2) {
      short unsigned int num = n % 256;
      itoa(num, string, 10, 0, flag.accuracy);
    }
    ELIF(flag.length == -1) {
      short unsigned int num = (short unsigned int)n;
      itoa(num, string, 10, 0, flag.accuracy);
    }
    ELIF(flag.length == 1 OR flag.length == 2) {
      if (n == ULONG_MAX) {
        s21_strcpy(string, "18446744073709551615");
      } else {
        unsigned long long num = (unsigned long long)n;
        itoa(num, string, 10, 0, flag.accuracy);
      }
    }
    else {
      unsigned int num = (unsigned int)n;
      itoa(num, string, 10, 0, flag.accuracy);
    }
  }
}

void flagG(int* exp, struct flags flag, double* num, int* num_sign,
           double* num_copy) {
  if (*exp >= -4 AND flag.accuracy > *exp) {
    if (!flag.accuracy) flag.accuracy = 1;
    flag.accuracy = flag.accuracy - *exp - 1;
    *num = *num_copy;
    *num_sign = 1;
  } else {
    flag.accuracy--;
  }
  if (flag.accuracy < 0) flag.accuracy = 0;
}

void flagPercent(char* string, struct flags* flag) {
  string[0] = '%';
  string[1] = endOfstr;
  flag->width = 1;
}

void ftoa(long double n, char* s, int digits, int sign) {
  int i = 0;
  int no_dot = digits;
  if (n < 0.0) {
    n = -n;
    s[0] = '-';
    i++;
  } else if (sign == 1) {
    s[0] = '+';
    i++;
  } else if (sign == 2) {
    s[0] = ' ';
    i++;
  }
  long double frac = n - (__int128)n;
  char frac_str[50];
  __int128 whole;
  int bank = 0;
  if (frac == 0.5 && digits == 0) {
    bank = 1;
  }
  if (digits != 0) {
    size_t frac_len = (size_t)digits;
    while (digits != 0) {
      frac *= 10;
      digits--;
    }
    frac += 0.5;
    itoa((__int128)frac, frac_str, 10, 0, frac_len);
    whole = (__int128)n;
    if (s21_strlen(frac_str) > frac_len) {
      if (whole < 0) {
        whole -= 1;
      } else {
        whole += 1;
      }
      int i;
      for (i = 0; frac_str[i] != '\0'; i++) {
        frac_str[i] = frac_str[i + 1];
      }
    }
    frac_str[frac_len] = '\0';
  } else {
    if (!bank) {
      n += 0.5;
      whole = (__int128)n;
    } else {
      if (((__int128)n) % 2 == 0) {
        whole = (__int128)n;
      } else {
        whole = (__int128)(n + 0.5);
      }
    }
  }
  char whole_str[50];
  itoa(whole, whole_str, 10, 0, 0);
  s21_strcat(s, whole_str);
  if (no_dot != 0) {
    s21_strcat(s, ".");
    s21_strcat(s, frac_str);
  }
}

void flagS(struct flags flag, char* string, va_list* vars) {
  if (!flag.setAccuracy) flag.accuracy = -1;
  if (flag.length > 0) {
    wchar_t* temp = va_arg(*vars, wchar_t*);
    if (temp != NULL) {
      int j = 0;
      if (flag.accuracy) {
        while (temp[j] != endOfstr AND(flag.accuracy) != 0) {
          string[j] = temp[j];
          j++;
          flag.accuracy--;
        }
      }
      string[j] = endOfstr;
    } else {
      if (flag.accuracy<6 AND flag.accuracy> 0)
        s21_strncpy(string, "(null)", flag.accuracy);
      ELIF(flag.accuracy) { s21_strcpy(string, "(null)"); }
    }
  } else {
    char* temp = va_arg(*vars, char*);
    if (temp != NULL) {
      if (flag.accuracy > 0) s21_strncpy(string, temp, flag.accuracy);
      ELIF(flag.accuracy) { s21_strcpy(string, temp); }
    } else {
      if (flag.accuracy<6 AND flag.accuracy> 0)
        s21_strncpy(string, "(null)", flag.accuracy);
      ELIF(flag.accuracy) { s21_strcpy(string, "(null)"); }
    }
  }
}

void flagC(struct flags flag, va_list* vars, char* string, int* null_p,
           char* str, int* nulls) {
  if (flag.length > 0) {
    wchar_t c = (wchar_t)va_arg(*vars, UINT64);
    if (c != endOfstr) {
      string[0] = c;
      string[1] = endOfstr;
    } else {
      if (*null_p == -1) {
        if (!flag.align) {
          if (WIDTH)
            *null_p = s21_strlen(str) + WIDTH - 1;
          else
            *null_p = s21_strlen(str);
        } else {
          *null_p = s21_strlen(str);
        }
        string[0] = 0;
      }
      WIDTH -= 1;
      (*nulls)++;
    }
  } else {
    unsigned char c = (unsigned char)va_arg(*vars, int);
    if (c != endOfstr) {
      string[0] = c;
      string[1] = endOfstr;
    } else {
      if (*null_p == -1) {
        if (!flag.align) {
          if (WIDTH)
            *null_p = s21_strlen(str) + WIDTH - 1;
          else
            *null_p = s21_strlen(str);
        } else {
          *null_p = s21_strlen(str);
        }
        string[0] = 0;
      }
      WIDTH -= 1;
      (*nulls)++;
    }
  }
}

void* itoa(__int128 n, char* s, int radix, int sign, int accuracy) {
  int i = 0;
  s21_strcpy(s, "");
  char* alphabet = "0123456789ABCDEFGH";
  if (n < 0) {
    n = -n;
    s[0] = '-';
    i++;
  } else if (sign == 1) {
    s[0] = '+';
    i++;
  } else if (sign == 2) {
    s[0] = ' ';
    i++;
  }
  __int128 m = 1;
  int n_len = 1;
  while ((m * radix) <= (long long unsigned)n) {
    m = m * radix;
    n_len += 1;
  }
  while (n_len < accuracy) {
    accuracy--;
    s[i] = '0';
    i++;
  }
  while (m > 0) {
    s[i++] = alphabet[(n / m) % radix];
    n = n % m;
    m = m / radix;
  }
  s[i++] = '\0';
  return 0;
}

void flagF(struct flags flag, va_list* vars, char* string) {
  flag.isDigit = 1;
  if (!flag.setAccuracy) flag.accuracy = 6;
  if (flag.double_length)
    ftoa(va_arg(*vars, long double), string, flag.accuracy, flag.sign);
  else
    ftoa(va_arg(*vars, double), string, flag.accuracy, flag.sign);
  if (flag.spec AND !flag.accuracy) s21_strcat(string, ".");
}

void flagN(struct flags flag, va_list* vars, char* str) {
  if (flag.length == -2) *(char*)va_arg(*vars, char*) = s21_strlen(str);
  ELIF(flag.length == -1)
  *(short int*)va_arg(*vars, short int*) = s21_strlen(str);
  ELIF(flag.length == 0)
  *(int*)va_arg(*vars, int*) = s21_strlen(str);
  ELIF(flag.length == 1)
  *(long int*)va_arg(*vars, long int*) = s21_strlen(str);
  ELIF(flag.length == 2)
  *(long long int*)va_arg(*vars, long long int*) = s21_strlen(str);
  WIDTH = 0;
}

void flagP(struct flags flag, char* string, va_list* vars) {
  if (!flag.setAccuracy) flag.accuracy = 1;
  flag.isDigit = 1;
  int* a = va_arg(*vars, int*);
  itoa((long long int)a, string, 16, 0, flag.accuracy);
  int k = (int)s21_strlen(string);
  while (k != -1) {
    string[k + 2] = string[k];
    k--;
  }
  string[0] = '0';
  string[1] = 'x';
}

// d или i	Целое со знаком в в десятичном виде	392
// u	Целое без знака в десятичном виде	7235
// o	Беззнаковое в восьмеричном виде	657
// x	Беззнаковое целое в шестнадцатеричном виде	7fa
// X	Беззнаковое целое в шестнадцатеричном виде, верхний регистр	7FA
// f или F	Число с плавающей точкой	3.4563745
// e	Экспоненциальная форма для числа с плавающей точкой	3.1234e+3
// E	Экспоненциальная форма для числа с плавающей точкой, верхний
// регистр	3.1234E+3 g	Кратчайшее из представлений форматов f и
// e	3.12 G	Кратчайшее из представлений форматов F и E	3.12 a
// Шестнадцатеричное представление числа с плавающей точкой	-0xc.90fep-2 A
// Шестнадцатеричное представление числа с плавающей точкой, верхний регистр
// -0xc.90FEP-2 c	Буква	a s	Строка (нуль-терминированный массив
// букв)	Hello World p	Адрес указателя	b8000000 n	Ничего не
// печатает. Аргументом должен быть указатель на signed int. По этому адресу
// будет сохранено количество букв, которое было выведено до встречи %n %
// Два идущих друг за другом процента выводят знак процента	%