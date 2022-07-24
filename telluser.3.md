# NAME

`telluser()`, `telluser_chk_type()`, `telluser_pop_key()`, `telluser_pop_fp()`.

# SYNOPSIS

    #include <telluser.h>
    
    void telluser(char const *_key, char _type, char const *_fmt, ...);
    
    char telluser_chk_type (char const *_key);
    bool telluser_pop_key (char const *_key, struct telluser **_m);
    void telluser_pop_fp (char _type, FILE *_fp, const char *_opt_nl);

# DESCRIPTION

Telluser allows postponing and positioning error/warning/... messages
shown to the user.

When a program want's to set an error it uses `telluser()`.

    telluser("username", 'e', "The username is invalid!");

Then when colouring the username field the program can check whether
an error was set.

    switch (telluser_chk_type("username")) {
    case 'e': color_username_field("red"); ...
    case 'w': color_username_field("yellow"); ...
    }

# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**GETTEXT(3)**
