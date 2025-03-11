#include "consoleio.h"
#include <iomanip>
#include <bitset>
#include <string.h>

using namespace std;

// Default enumeraton base is decimal
#define BASE_DFLT   BASE_10
#define BASE_DFLT_N BASE_10_N

// Space symbol
#define SP ' '

// Enumerated base types for integer values
enum class base_t {
    BASE_2,
    BASE_8,
    BASE_10,
    BASE_16,
};

// Base names in string form
#define BASE_2_S "binary"
#define BASE_8_S "octal"
#define BASE_10_S "decimal"
#define BASE_16_S "hexadecimal"

// Enumerated base numbers for integer value
enum base_n {
    BASE_2_N = 2,
    BASE_8_N = 8,
    BASE_10_N = 10,
    BASE_16_N = 16,
};

// Enumerated printable number of symbols for integer values
// in various base representations
enum base_w {
    // Binary
    BASE_2_W_BYTE = 8,
    BASE_2_W_SHORT = 16,
    BASE_2_W_LONG = 32,
    BASE_2_W_DOUBLE = 64,
    // Octal
    BASE_8_W_BYTE = 3,
    BASE_8_W_SHORT = 6,
    BASE_8_W_LONG = 11,
    BASE_8_W_DOUBLE = 22,
    // Decimal
    BASE_10_W_BYTE = 3,
    BASE_10_W_SHORT = 5,
    BASE_10_W_LONG = 10,
    BASE_10_W_DOUBLE = 20,
    // Hexadecimal
    BASE_16_W_BYTE = 2,
    BASE_16_W_SHORT = 4,
    BASE_16_W_LONG = 8,
    BASE_16_W_DOUBLE = 16,
};

// Common constants for all class units
static const char*
base_name[] = {BASE_2_S, BASE_8_S, BASE_10_S, BASE_16_S};

static const int
base_num[] = {BASE_2_N, BASE_8_N, BASE_10_N, BASE_16_N};

static const int
base_w_char[] = {BASE_2_W_BYTE, BASE_8_W_BYTE, BASE_10_W_BYTE, BASE_16_W_BYTE};

static const int
base_w_short[] =
    {BASE_2_W_SHORT, BASE_8_W_SHORT, BASE_10_W_SHORT, BASE_16_W_SHORT};

static const int
base_w_long[] =
    {BASE_2_W_LONG, BASE_8_W_LONG, BASE_10_W_LONG, BASE_16_W_LONG};

static const int
base_w_double[] =
    {BASE_2_W_DOUBLE, BASE_8_W_DOUBLE, BASE_10_W_DOUBLE, BASE_16_W_LONG};

// Class to represent enumeration base of all integer values
class base {
    private:
        // Base type
        base_t base_type;
        int base_type_i;
    public:
        base(base_t type);
        base_t type(void);
        const char *name(void);
        int num(void);
        int w_char(void);
        int w_short(void);
        int w_long(void);
        int w_double(void);
};

// Class base methods
// Constructor
base::base(base_t type) : base_type(type), base_type_i((int)type)

// Get base type
base::type(void)
{
    return base_type;
}

// Get enumerated constants
#define BASE_GET(_field) \
base::##_field(void) \
{ \
    return base_##_field[base_type_i]; \
}
BASE_GET(num)
BASE_GET(name)
BASE_GET(w_char)
BASE_GET(w_short)
BASE_GET(w_long)
BASE_GET(w_double)
#undef BASE_GET

// Class base entries for all base types
#define BASE_ENTRY(_name, _type) \
static base \
base_##_name(BASE_##_type);
BASE_ENTRY(bin, 2)
BASE_ENTRY(oct, 8)
BASE_ENTRY(dec, 10)
BASE_ENTRY(hex, 16)
#undef BASE_ENTRY

// See definition in consoleio.h
void
console_get_user_input(string &input)
{
    cin >> input;
    cin.ignore();
}

// Convert value from string decimal format to scalar
static int
str_dec2signed(string &str, int &val)
{
    try
    {
        val = stoi(str);
    }
    catch (invalid_argument(str))
    {
        return -1;
    }

    return 0;
}

static int
str2unsigned(string &str, base &base, unsigned &val)
{
    try
    {
        val = stoul(str, nullptr, base::num());
    }
    catch (invalid_argument(val))
    {
        return -1;
    }

    return 0;
}

#define ESIGNED(_str_val) \
    cerr << __FUNCTION__ << "() ERROR: Failed to convert user input '" << \
        _str_val << "' to the signed integer value" << endl

#define EUNSIGNED(_str_val, _base_str) \
    cerr << __FUNCTION__ << "() ERROR: Failed to convert user input '" << \
        _str_val << "' to the unsigned string value" << endl << \
        " Enumeration base is " << _base_str << endl

// See definition in consoleio.h
int
console_get_dec(signed &val)
{
    int rc;
    string input;

    console_get_user_input(input);

    if ((rc = str_dec2signed(input, val)) != 0)
        ESIGNED(input);

    return rc;
}

// Get signed integer value from user input
static int
console_get_base_unsigned(base &base, unsigned &val)
{
    int rc;
    string input;
    const char *base_name = base::name();

    console_get_user_input(input);

    rc = str2unsigned(input, base, val);

    if (rc != 0)
        EUNSIGNED(input, base_name);

    return rc;
}

#define CONSOLE_GET_BASE_UNSIGNED(_name, _base_t) \
int \
console_get_##_name(unsigned &val) \
{ \
    base base(_base_t); \
    return console_get_base_unsigned(base, val); \
}
/* See definition in consoleio.h */
CONSOLE_GET_BASE_UNSIGNED(bin, base_t::BASE_2)
CONSOLE_GET_BASE_UNSIGNED(oct, base_t::BASE_8)
CONSOLE_GET_BASE_UNSIGNED(dec, base_t::BASE_10)
CONSOLE_GET_BASE_UNSIGNED(hex, base_t::BASE_16)
#undef CONSOLE_GET_BASE_UNSIGNED

// See definition in consoleio.h
static int
console_log_gen(ostream stream, const char *msg)
{
    int rc = -1;

    if (msg == 0)
    {
        cerr << __FUNCTION__ << "() ERROR: message string NULL" << endl;
    }
    else if (strlen(msg) == 0)
    {
        cerr << __FUNCTION__ << "() ERROR: message string is empty" << endl;
    }
    else
    {
        stream << msg;
        rc = 0;
    }

    return rc;
}

// See definition in consoleio.h
int
console_log_msg(const char *msg)
{
    return console_log_gen(cout, msg);
}

// See definition in consoleio.h
int
console_log_err(const char *msg)
{
    return console_log_gen(cerr, msg);
}

#define CONSOLE_PUT_HEX_GEN_SCALAR(_val_type)\

// See definition in consoleio.h
static int
console_put_gen_base_char(ostream stream, base_t base_type,
                          const char *preamble, int val)
{
    base num_base(base_type);

    if (preamble != 0)
    {
        stream
            << preamble
            << setw(base_type::w_char)
            << setfill('0')
    }
    else
    {
    }

    return 0;
}
#define CONSOLE_PUT_BASE_TYPE(_base, _type) \
static int \
console_put_##_base##_gen_##_type(ostream stream, int val) \
{ \
    stream \
        << setw(base_##_base::w_##_type()) \
        << setfill('0') \
        << _base \
        << (unsigned _type)val; \
    return 0; \
}
CONSOLE_PUT_BASE_TYPE(oct, char)
CONSOLE_PUT_BASE_TYPE(dec, char)
CONSOLE_PUT_BASE_TYPE(hex, char)
CONSOLE_PUT_BASE_TYPE(oct, short)
CONSOLE_PUT_BASE_TYPE(dec, short)
CONSOLE_PUT_BASE_TYPE(hex, short)
CONSOLE_PUT_BASE_TYPE(oct, long)
CONSOLE_PUT_BASE_TYPE(dec, long)
CONSOLE_PUT_BASE_TYPE(hex, long)

